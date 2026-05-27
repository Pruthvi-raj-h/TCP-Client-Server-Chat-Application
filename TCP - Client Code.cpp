#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstring>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main()
{
    WSADATA ws;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
    {
        cout << "WSAStartup Failed\n";
        return 1;
    }

    // Create client socket
    SOCKET clientSocket;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed\n";
        return 1;
    }

    // Server address
    sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);

    inet_pton(AF_INET,
        "127.0.0.1",
        &serverAddr.sin_addr);

    // Connect to server
    if (connect(clientSocket,
        (sockaddr*)&serverAddr,
        sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "Connection Failed\n";
        return 1;
    }

    cout << "Connected to server!\n";

    char buffer[1024];

    while (true)
    {
        cout << "Client: ";

        cin.getline(buffer, sizeof(buffer));

        // Send message
        send(clientSocket,
            buffer,
            (int)strlen(buffer),
            0);

        // Exit condition
        if (strcmp(buffer, "exit") == 0)
        {
            cout << "Disconnected from server\n";
            break;
        }

        memset(buffer, 0, sizeof(buffer));

        // Receive reply
        recv(clientSocket,
            buffer,
            sizeof(buffer),
            0);

        cout << "Server: " << buffer << endl;

        // Exit condition
        if (strcmp(buffer, "exit") == 0)
        {
            cout << "Server closed connection\n";
            break;
        }
    }

    closesocket(clientSocket);

    WSACleanup();

    return 0;
}