#pragma once

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 800
#define DEFAULT_PORT "8080"

class TCPClient
{
private:
	char recvbuf[DEFAULT_BUFLEN]; //server dumps info in this data structure
	char sendbuf[DEFAULT_BUFLEN]; //client writes data to be sent in this array 
	int recvbuflen = DEFAULT_BUFLEN;
	int sendbuflen = DEFAULT_BUFLEN;
	SOCKET ConnectSocket = INVALID_SOCKET;
	int iResult;

public:
	enum TCPConnectionStatus
	{
		WSA_DATA_STARTUP_FAIL = 0,
		GET_ADD_INFO_FAIL,
		SOCKET_FAIL,
		SERVER_CONNECTION_FAIL,
		INITIAL_DATA_SEND_FAIL,
		CONNECTION_SUCCESSFUL
	};
	TCPClient();
	~TCPClient();
	TCPConnectionStatus connectToPi();
	void sendData(int message);
	void endConnection();
	double recieveData();

};

