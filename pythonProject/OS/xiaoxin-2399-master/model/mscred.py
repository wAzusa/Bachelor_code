import torch
import torch.nn as nn
import numpy as np
from model.convolution_lstm import ConvLSTM
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

def attention(ConvLstm_out):  # 对5个时间步和最后一步做attention; (5, 32, 30, 30)
    attention_w = []
    for k in range(5):  # 注意选择的lstm的时间步长，为5!!! 如果是ConvLstm_out.shape[0]，应该更好
        attention_w.append(torch.sum(torch.mul(ConvLstm_out[k], ConvLstm_out[-1]))/5)
    m = nn.Softmax()
    attention_w = torch.reshape(m(torch.stack(attention_w)), (-1, 5))  # softmax
    cl_out_shape = ConvLstm_out.shape
    ConvLstm_out = torch.reshape(ConvLstm_out, (5, -1))  # 注意选择的lstm的时间步长，为5!!! 如果是ConvLstm_out.shape[0]，应该更好
    convLstmOut = torch.matmul(attention_w, ConvLstm_out)  # 加权求和
    convLstmOut = torch.reshape(convLstmOut, (cl_out_shape[1], cl_out_shape[2], cl_out_shape[3]))  # (32, 30, 30)
    return convLstmOut

class CnnEncoder(nn.Module):
    def __init__(self, in_channels_encoder):
        super(CnnEncoder, self).__init__()
        self.conv1 = nn.Sequential(
            nn.Conv2d(in_channels_encoder, 32, 3, (1, 1), 1),
            nn.SELU()
        )
        self.conv2 = nn.Sequential(
            nn.Conv2d(32, 64, 3, (2, 2), 1),
            nn.SELU()
        )    
        self.conv3 = nn.Sequential(
            nn.Conv2d(64, 128, 2, (2, 2), 1),
            nn.SELU()
        )   
        self.conv4 = nn.Sequential(
            nn.Conv2d(128, 256, 2, (2, 2), 0),
            nn.SELU()
        )
    def forward(self, X):  # x:[5, 3, 30, 30]
        conv1_out = self.conv1(X)  # 3->32channel; [5, 32, 30, 30]
        conv2_out = self.conv2(conv1_out)  # 步长为2; [5, 64, 15, 15]
        conv3_out = self.conv3(conv2_out)  # 步长为2; [5, 128, 8, 8]
        conv4_out = self.conv4(conv3_out)  # [5, 256, 4, 4]
        return conv1_out, conv2_out, conv3_out, conv4_out  # 将4个conv返回


class Conv_LSTM(nn.Module):
    def __init__(self):
        super(Conv_LSTM, self).__init__()
        self.conv1_lstm = ConvLSTM(input_channels=32, hidden_channels=[32], 
                                   kernel_size=3, step=5, effective_step=[4])
        self.conv2_lstm = ConvLSTM(input_channels=64, hidden_channels=[64], 
                                   kernel_size=3, step=5, effective_step=[4])
        self.conv3_lstm = ConvLSTM(input_channels=128, hidden_channels=[128], 
                                   kernel_size=3, step=5, effective_step=[4])
        self.conv4_lstm = ConvLSTM(input_channels=256, hidden_channels=[256], 
                                   kernel_size=3, step=5, effective_step=[4])

    def forward(self, conv1_out, conv2_out, 
                conv3_out, conv4_out):
        conv1_lstm_out = self.conv1_lstm(conv1_out)  # conv1_out: [5, 32, 30, 30]
        conv1_lstm_out = attention(conv1_lstm_out[0][0])  # 最后一层lstm的输出，经过attention;
        conv2_lstm_out = self.conv2_lstm(conv2_out)
        conv2_lstm_out = attention(conv2_lstm_out[0][0])
        conv3_lstm_out = self.conv3_lstm(conv3_out)
        conv3_lstm_out = attention(conv3_lstm_out[0][0])
        conv4_lstm_out = self.conv4_lstm(conv4_out)
        conv4_lstm_out = attention(conv4_lstm_out[0][0])
        return conv1_lstm_out.unsqueeze(0), conv2_lstm_out.unsqueeze(0), conv3_lstm_out.unsqueeze(0), conv4_lstm_out.unsqueeze(0)

class CnnDecoder(nn.Module):
    def __init__(self, in_channels):

        super(CnnDecoder, self).__init__()
        self.deconv4 = nn.Sequential(
            nn.ConvTranspose2d(in_channels, 128, 2, 2, 0, 0),  # 反卷积操作
            nn.SELU()
        )
        self.deconv3 = nn.Sequential(
            nn.ConvTranspose2d(256, 64, 2, 2, 1, 1),
            nn.SELU()
        )
        self.deconv2 = nn.Sequential(
            nn.ConvTranspose2d(128, 32, 3, 2, 1, 1),
            nn.SELU()
        )
        self.deconv1 = nn.Sequential(
            nn.ConvTranspose2d(64, 3, 3, 1, 1, 0),
            nn.SELU()
        )
    
    def forward(self, conv1_lstm_out, conv2_lstm_out, conv3_lstm_out, conv4_lstm_out):
        deconv4 = self.deconv4(conv4_lstm_out)
        deconv4_concat = torch.cat((deconv4, conv3_lstm_out), dim = 1)  # [1, 128, 8, 8]->[1, 256, 8, 8]
        deconv3 = self.deconv3(deconv4_concat)  # [1, 256, 8, 8]->[1, 64, 15, 15]
        deconv3_concat = torch.cat((deconv3, conv2_lstm_out), dim = 1)
        deconv2 = self.deconv2(deconv3_concat)
        deconv2_concat = torch.cat((deconv2, conv1_lstm_out), dim = 1)
        deconv1 = self.deconv1(deconv2_concat)
        return deconv1


class MSCRED(nn.Module):
    def __init__(self, in_channels_encoder, in_channels_decoder):
        super(MSCRED, self).__init__()
        self.cnn_encoder = CnnEncoder(in_channels_encoder)  # Cnn
        self.conv_lstm = Conv_LSTM()  # ConvLSTM
        self.cnn_decoder = CnnDecoder(in_channels_decoder)  # CnnDecoder
    
    def forward(self, x):  # x:[5, 3, 30, 30]; 5个时间步，3个win，30*30相似矩阵
        conv1_out, conv2_out, conv3_out, conv4_out = self.cnn_encoder(x)  # 计算conv层;  conv输出当做是conv_lstm输入
        conv1_lstm_out, conv2_lstm_out, conv3_lstm_out, conv4_lstm_out = self.conv_lstm(  # conv输出当做是conv_lstm输入
                                conv1_out, conv2_out, conv3_out, conv4_out)  # convLstm输出结果;
        # deCNN
        gen_x = self.cnn_decoder(conv1_lstm_out, conv2_lstm_out, 
                                conv3_lstm_out, conv4_lstm_out)
        return gen_x


