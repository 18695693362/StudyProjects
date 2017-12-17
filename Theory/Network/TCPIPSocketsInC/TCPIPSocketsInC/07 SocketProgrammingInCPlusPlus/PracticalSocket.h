//
//  PracticalSocket.h
//  TCPIPSocketsInC
//
//  Created by guodong on 5/4/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//

#ifndef __TCPIPSocketsInC__PracticalSocket__
#define __TCPIPSocketsInC__PracticalSocket__

#include <string>
#include <exception>

class GSocketException:public std::exception
{
public:
    /**
     *   Construct a SocketException with a explanatory message.
     *   @param message explanatory message
     *   @param incSysMsg true if system message (from strerror(errno))
     *   should be postfixed to the user provided message
     */
    GSocketException(const std::string &message, bool inclSysMsg = false) throw();
    
    /**
     *   Provided just to guarantee that no exceptions are thrown.
     */
    ~GSocketException() throw();
    
    /**
     *   Get the exception message
     *   @return exception message
     */
    const char *what() const throw();
    
private:
    std::string user_msg;  // Exception message
};

class GSocketAddress
{
};

class GSocket
{
public:
    
};

class GCommunicatingSocket : public GSocket
{
public:
    void Send(const void* buffer, int buff_len);
    int Recv(void* buffer, int buff_len);
    int RecvFully(void* buffer, int buff_len);
};

class GTCPSocket : public GCommunicatingSocket
{
public:
    GTCPSocket();
};

class GUDPSocket : public GCommunicatingSocket
{
};

class GTCPServerSocket : public GSocket
{
public:
    GTCPServerSocket(unsigned int local_port);
    GTCPSocket* Accept();
};

#endif /* defined(__TCPIPSocketsInC__PracticalSocket__) */
