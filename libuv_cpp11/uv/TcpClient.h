/*
   Copyright 2017, object_he@yeah.net  All rights reserved.

   Author: object_he@yeah.net

   Last modified: 2017-8-8

   Description:
*/

#ifndef   TCP_CLIENT_H
#define   TCP_CLIENT_H

#include  <uv.h>
#include  <functional>
#include  "TcpConnection.h"

namespace uv
{

typedef std::function<void(bool)>  ConnectCallback;
typedef std::function<void(const char* buf,ssize_t size)>  NewMessageCallback;
typedef std::function<void()> OnConnectClose;

class TcpClient
{
public:
    TcpClient(uv_loop_t* loop);
    ~TcpClient();

    void connect(const char* ip, unsigned short port);

    void onConnect(bool successed);
    void onConnectClose(uv_tcp_t* socket);
    void onMessage(std::shared_ptr<TcpConnection> connection,const char* buf,ssize_t size);

    void write(const char* buf,unsigned int size,AfterWriteCallback callback = nullptr)
    {
        tcpConnection->write(buf,size,callback);

    }
    void writeInLoop(const char* buf,unsigned int size,AfterWriteCallback callback)
    {
        tcpConnection->writeInLoop(buf,size,callback);
    }

    void setConnectCallback(ConnectCallback callback)
    {
        connectCallback = callback;
    }
    void setMessageCallback(NewMessageCallback callback)
    {
        onMessageCallback = callback;
    }
    void setConnectCloseCallback(OnConnectClose callback)
    {
        onConnectCloseCallback = callback;
    }

protected:
    uv_loop_t* loop;
private:
    uv_tcp_t* socket;
    uv_connect_t* connect_;
    struct sockaddr_in dest;
    ConnectCallback connectCallback;
    NewMessageCallback onMessageCallback;
    OnConnectClose onConnectCloseCallback;

    std::shared_ptr<TcpConnection> tcpConnection;
    void updata();
};

}
#endif
