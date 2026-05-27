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

    // Create server socket
    SOCKET serverSocket, clientSocket;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed\n";
        return 1;
    }

    // Server address structure
    sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(serverSocket,
        (sockaddr*)&serverAddr,
        sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "Bind failed\n";
        return 1;
    }

    // Listen for clients
    if (listen(serverSocket, 5) == SOCKET_ERROR)
    {
        cout << "Listen failed\n";
        return 1;
    }

    cout << "Waiting for client...\n";

    int addrLen = sizeof(serverAddr);

    // Accept client connection
    clientSocket = accept(serverSocket,
        (sockaddr*)&serverAddr,
        &addrLen);

    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Accept failed\n";
        return 1;
    }

    cout << "Client connected!\n";

    char buffer[1024];

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));

        // Receive message
        recv(clientSocket,
            buffer,
            sizeof(buffer),
            0);

        cout << "Client: " << buffer << endl;

        // Exit condition
        if (strcmp(buffer, "exit") == 0)
        {
            cout << "Client disconnected\n";
            break;
        }

        cout << "Server: ";

        cin.getline(buffer, sizeof(buffer));

        // Send reply
        send(clientSocket,
            buffer,
            (int)strlen(buffer),
            0);

        // Exit condition
        if (strcmp(buffer, "exit") == 0)
        {
            cout << "Server shutting down\n";
            break;
        }
    }

    closesocket(clientSocket);
    closesocket(serverSocket);

    WSACleanup();

    return 0;
}