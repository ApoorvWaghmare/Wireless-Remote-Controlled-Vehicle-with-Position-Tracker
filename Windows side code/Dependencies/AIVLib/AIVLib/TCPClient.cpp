#include "stdafx.h"
#include "TCPClient.h"
#include <iostream>

using namespace std;

TCPClient::TCPClient()
{
}

TCPClient::TCPConnectionStatus TCPClient::connectToPi()
{
	const char *ipAddress = "192.168.43.85";
	WSADATA wsaData;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		cout << "WSAStartup failed with error: " << iResult << endl;
		return WSA_DATA_STARTUP_FAIL;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(ipAddress, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		cout << "Getaddrinfo failed with error: " << iResult << endl;
		return GET_ADD_INFO_FAIL;
		WSACleanup();
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET)
		{
			cout << "Socket failed with error: " << WSAGetLastError() << endl;
			WSACleanup();
			return SOCKET_FAIL;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET)
	{
		cout << "Unable to connect to server!" << endl;
		WSACleanup();
		return SERVER_CONNECTION_FAIL;
	}

	return CONNECTION_SUCCESSFUL;
}

void TCPClient::sendData(int message)
{
	memcpy(sendbuf, &message, sizeof(int));
	iResult = send(ConnectSocket, sendbuf, sendbuflen, 0);
	if (iResult == 0)
		cout << "No message to send" << endl;
	else
		cout << "Connection failed" << endl;
}

double TCPClient::recieveData()
{
	double tempVal;

	iResult = recv(ConnectSocket, recvbuf, sizeof(recvbuf), 0);
	memcpy(&tempVal, recvbuf, sizeof(double));

	return tempVal;
}

void TCPClient::endConnection()
{
	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		cout << "Shutdown failed with error: " << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		WSACleanup();
	}

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();
}

TCPClient::~TCPClient()
{
}
