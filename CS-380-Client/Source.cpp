//Client & Socket Functionality
//Copied from: https://docs.microsoft.com/en-us/windows/win32/winsock/complete-client-code
//Learn how to Run: https://docs.microsoft.com/en-us/windows/win32/winsock/finished-server-and-client-code
//Will be altered and adapted to our uses, for now is just here to learn from and understand over time how it works.

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include "GUIManager.h"
using namespace std;

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int __cdecl main(int argc, char** argv)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	int recvbuflen = DEFAULT_BUFLEN;
	int sendbuflen = DEFAULT_BUFLEN;
	char sendbuf[DEFAULT_BUFLEN];
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	

	// Validate the parameters
	if (argc != 2) {
		printf("usage: %s server-name\n", argv[0]);
		return 1;
	}

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	string est = "ESTABLISH";
	strcpy_s(sendbuf, est.c_str());

	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	printf("Bytes Sent: %ld\n", iResult);

	//Wait for return ESTABLISH message from server
	cout << "Waiting for ESTABLISH Return" << endl;
	iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
	if (iResult > 0)
		printf("Bytes received: %d\n", iResult);
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed with error: %d\n", WSAGetLastError());


	//Connection Established
	//Beginning Actual Program

	//Login
	GUIManager GUI;
	string LoginResult;
	bool LoginSuccess = false;
	while (!LoginSuccess)
	{
		LoginResult = "";
		string login = GUI.DisplayLoginScreen();
		cout << "Sending login" << endl;
		strcpy_s(sendbuf, login.c_str());
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		cout << "Verifying Login..." << endl;

		for (int i = 0; i < DEFAULT_BUFLEN; i++)
		{
			recvbuf[i] = '\0';
		}

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

		cout << "iResult: " << iResult << endl;
		
		int i = 0;
		while (i < 6)
		{
			LoginResult += recvbuf[i];
			i++;
		}
		
		cout << "LoginResult: " << LoginResult << endl;

		if (LoginResult == "ACCEPT")
		{
			LoginSuccess = true;
		}
		else if (LoginResult == "DENIED")
		{
			cout << "Login Failed";
		}

		cout << "Press Enter to retry login...";
		cin.get();
	}
	
	//Login worked, begin main loop
	// Receive until the peer closes the connection
	char command = '\0';
	string message;
	do {
		//Empty command character, ping user for new command
		command = '\0';
		message = "";
		command = GUI.DisplayCommandScreen();

		if (command == 'Q')
		{
			break;
		}

		//Switch statement to get info for command from user
		switch (command)
		{
		case 'S':
			message = GUI.SearchMachine();
			break;
		case 'E':
			message = GUI.EditMachine();
			break;
		case 'A':
			message = GUI.AddMachine();
			break;
		case 'D':
			message = GUI.DeleteMachine();
			break;
		case 'Q':
			message = "QUIT";
			break;
		default:
			return 0;
		}

		if (message == "NODELETE")
		{
			continue;
		}

		//Clear the sendbuffer
		for (int i = 0; i < DEFAULT_BUFLEN; i++)
		{
			sendbuf[i] = '\0';
		}

		//Insert the message into the buffer
		strcpy_s(sendbuf, message.c_str());

		//Send the command
		cout << "Sending command" << endl;
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
		for (int i = 0; i < DEFAULT_BUFLEN; i++)
		{
			sendbuf[i] = '\0';
		}
		//Get reply back
		cout << "Waiting for reply" << endl;
		for (int i = 0; i < DEFAULT_BUFLEN; i++)
		{
			recvbuf[i] = '\0';
		}
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());
		cout << "Buffer received: " << recvbuf << endl;
		string result;
		int i = 0;
		while (i < (int)strlen(sendbuf))
		{
			result += recvbuf[i];
			i++;
		}

		cout << result << endl;
		cout << "Press Enter to return to Command Screen...";
		cin.get();
	} while (iResult > 0);

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
}