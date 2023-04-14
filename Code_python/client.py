import time
from socket import  *
#创建套接字
tcp_server = socket(AF_INET,SOCK_STREAM)
#绑定ip，port
#这里ip默认本机
address = ('',8000)
tcp_server.bind(address)
# 启动被动连接
#多少个客户端可以连接
tcp_server.listen(128)
#使用socket创建的套接字默认的属性是主动的
#使用listen将其变为被动的，这样就可以接收别人的链接了
client_socket, clientAddr = tcp_server.accept()
while(1):
    #接收对方发送过来的数据
    from_client_msg = client_socket.recv(1024)#接收1024给字节,这里recv接收的不再是元组，区别UDP
    if(from_client_msg=="exit"):
        break
    print("接收的数据：",from_client_msg.decode("gbk"))
    now_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))
    #发送数据给客户端
    send_data = client_socket.send((str(now_time)).encode("gbk"))
    #关闭套接字
    #关闭为这个客户端服务的套接字，就意味着为不能再为这个客户端服务了
    #如果还需要服务，只能再次重新连
client_socket.close()