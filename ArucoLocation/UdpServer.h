/*
* UdpServer.h
*
*  Created on: Jun 13, 2017
*      Author: szsz
*/

#ifndef UDPSERVER_H_
#define UDPSERVER_H_

#include <winsock2.h>
#include <stdio.h>

#define BUF_SIZE 1024

class UdpServer {
private:
	void InitWinsock();
	SOCKET socketS;

	char buffer[BUF_SIZE];
	struct sockaddr_in local;
	struct sockaddr_in from;
	int fromlen;

public:
	UdpServer(unsigned short port);
	virtual ~UdpServer();
	int ReciveLen;
	char* Receive();
};

#endif /* UDPSERVERLINUX_H_ */