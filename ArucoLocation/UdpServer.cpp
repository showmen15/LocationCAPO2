#include "UdpServer.h"

void UdpServer::InitWinsock()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
}

UdpServer::UdpServer(unsigned short port) {

	InitWinsock();
	
	fromlen = sizeof(from);
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = INADDR_ANY;

	socketS = socket(AF_INET, SOCK_DGRAM, 0);
	bind(socketS, (sockaddr*)&local, sizeof(local));
}

UdpServer::~UdpServer() {
	// TODO Auto-generated destructor stub
	closesocket(socketS);
}

char* UdpServer::Receive()
{
	ZeroMemory(buffer, sizeof(buffer));

	if (recvfrom(socketS, buffer, sizeof(buffer), 0, (sockaddr*)&from, &fromlen) != SOCKET_ERROR)
	{
		ReciveLen = fromlen;
	}
	return buffer;
}