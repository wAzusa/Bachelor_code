import numpy as np
import argparse
import pandas as pd
import os, sys
import math
import scipy
#import matplotlib.pyplot as plt
from scipy.stats import pearsonr
from scipy import spatial
import itertools as it
import string
import re



parser = argparse.ArgumentParser(description = 'Signature Matrix Generator')
parser.add_argument('--ts_type', type = str, default = "node",
				   help = 'type of time series: node or link')
parser.add_argument('--step_max', type = int, default = 5,
				   help = 'maximum step in ConvLSTM')
parser.add_argument('--gap_time', type = int, default = 10, # tride width...
				   help = 'gap time between each segment')
parser.add_argument('--win_size', type = int, default = [10, 30, 60],
				   help = 'window size of each segment')
parser.add_argument('--min_time', type = int, default = 0,
				   help = 'minimum time point')
parser.add_argument('--max_time', type = int, default = 20000,
				   help = 'maximum time point')
parser.add_argument('--train_start_point',  type = int, default = 0,
						help = 'train start point')
parser.add_argument('--train_end_point',  type = int, default = 8000,
						help = 'train end point')
parser.add_argument('--test_start_point',  type = int, default = 8000,
						help = 'test start point')
parser.add_argument('--test_end_point',  type = int, default = 20000,
						help = 'test end point')
parser.add_argument('--raw_data_path', type = str, default = './data/synthetic_data_with_anomaly-s-1.csv',
				   help='path to load raw data')
parser.add_argument('--save_data_path', type = str, default = './data/',
				   help='path to save data')

args = parser.parse_args()
print(args)

ts_type = args.ts_type
step_max = args.step_max  # LSTM和attentino时，向前回溯的步长
min_time = args.min_time
max_time = args.max_time
gap_time = args.gap_time  # 多少时间间隔检测一次; gap_time=10
win_size = args.win_size  # windowSize:[10,30,60]
# 训练测试集
train_start = args.train_start_point
train_end = args.train_end_point
test_start = args.test_start_point
test_end = args.test_end_point
# 文件路径和存储路径
raw_data_path = args.raw_data_path
save_data_path = args.save_data_path

ts_colname="agg_time_interval"
agg_freq='5min'

matrix_data_path = save_data_path + "matrix_data/"
if not os.path.exists(matrix_data_path):
	os.makedirs(matrix_data_path)


def generate_signature_matrix_node():
	data = np.array(pd.read_csv(raw_data_path, header = None), dtype=np.float64)  # (30, 20000): 30个传感器，没有20000个时间序列
	sensor_n = data.shape[0]  # 传感器数量; Multivariate
	# min-max normalization
	max_value = np.max(data, axis=1)
	min_value = np.min(data, axis=1)
	data = (np.transpose(data) - min_value)/(max_value - min_value + 1e-6)  # 归一化[0,1]
	data = np.transpose(data)

	# multi-scale signature matix generation
	for w in range(len(win_size)):  # 多尺度特征生成; win_size: [10, 30, 60]
		matrix_all = []  # 该尺度上，每个时间点相似矩阵
		win = win_size[w]  # 向前推window时间窗口
		print ("generating signature with window " + str(win) + "...")
		for t in range(min_time, max_time, gap_time):  # 构造数据，构建相似矩阵
			#print t
			matrix_t = np.zeros((sensor_n, sensor_n))  # 构造相似矩阵
			if t >= 60:  # 满足条件的
				for i in range(sensor_n):
					for j in range(i, sensor_n):
						# 计算该时刻，每个sensor之间的相似关系
						matrix_t[i][j] = np.inner(data[i, t - win:t], data[j, t - win:t])/(win) # rescale by win; 每个时间点，都计算其在该时刻，向前推win个时间的序列
						matrix_t[j][i] = matrix_t[i][j]  # 对称矩阵
			matrix_all.append(matrix_t)  # 每个时刻的Signature Matrices; matrix_t.shape = (30, 30)
		path_temp = matrix_data_path + "matrix_win_" + str(win)
		np.save(path_temp, matrix_all)  #  将win上相似矩阵存储
		del matrix_all[:]

	print ("matrix generation finish!")

def generate_train_test_data():
	# data sample generation
	print ("generating train/test data samples...")
	matrix_data_path = save_data_path + "matrix_data/"

	train_data_path = matrix_data_path + "train_data/"
	if not os.path.exists(train_data_path):
		os.makedirs(train_data_path)
	test_data_path = matrix_data_path + "test_data/"
	if not os.path.exists(test_data_path):
		os.makedirs(test_data_path)

	data_all = []
	# for value_col in value_colnames:
	for w in range(len(win_size)):  # 导入时间窗口相似矩阵; (3, 2000, 30, 30): 3个时间窗口，2000时间点，(30,30)相似矩阵
		#path_temp = matrix_data_path + "matrix_win_" + str(win_size[w]) + str(value_col) + ".npy"
		path_temp = matrix_data_path + "matrix_win_" + str(win_size[w]) + ".npy"
		data_all.append(np.load(path_temp))

	train_test_time = [[train_start, train_end], [test_start, test_end]]  # 定义训练，测试集时间的窗口
	for i in range(len(train_test_time)):  # 训练，测试
		for data_id in range(int(train_test_time[i][0]/gap_time), int(train_test_time[i][1]/gap_time)):  # 找到训练测试id(之前处理数据是有gap的)
			#print data_id
			step_multi_matrix = []
			for step_id in range(step_max, 0, -1):  # 5,4,3,2,1; 这个是计算lstm和attention时，使用的时间序列
				multi_matrix = []  # 该时刻(data_id)下的时间序列
				# for k in range(len(value_colnames)):
				for i in range(len(win_size)):  # [10, 30, 60]; data_all: 3个win下的相似矩阵
					multi_matrix.append(data_all[i][data_id - step_id])  # 每个win下的Mt矩阵; (向前推step_id步长); (3, 30, 30)
				step_multi_matrix.append(multi_matrix)  # (5, 3, 30, 30)
			# 删除无效点; 保证data_id在向前推时间步存在，不超过最大时间步
			if data_id >= (train_start/gap_time + win_size[-1]/gap_time + step_max) and data_id < (train_end/gap_time): # remove start points with invalid value
				path_temp = os.path.join(train_data_path, 'train_data_' + str(data_id))
				np.save(path_temp, step_multi_matrix)
			elif data_id >= (test_start/gap_time) and data_id < (test_end/gap_time):
				path_temp = os.path.join(test_data_path, 'test_data_' + str(data_id))
				np.save(path_temp, step_multi_matrix)

			#print np.shape(step_multi_matrix)

			del step_multi_matrix[:]

	print ("train/test data generation finish!")


if __name__ == '__main__':
	'''need one more dimension to manage mulitple "features" for each node or link in each time point,
	this multiple features can be simply added as extra channels
	'''

	if ts_type == "node":
		generate_signature_matrix_node()  # 生成signature matrix

	generate_train_test_data()