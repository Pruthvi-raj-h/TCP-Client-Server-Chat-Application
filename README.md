# TCP-Client-Server-Chat-Application
A TCP-based Client-Server Chat Application developed using C/C++ and Socket Programming concepts for real-time communication between systems.

## Features

* Real-time client-server communication
* TCP/IP based reliable data transfer
* Connection establishment and termination handling
* Message exchange using sockets

## Technologies Used

* C/C++
* TCP/IP
* Socket Programming
* Winsock API / Linux Sockets

## Concepts Implemented

* socket()
* bind()
* listen()
* accept()
* connect()
* send()
* recv()

## Project Structure

* `server.cpp` → Handles server-side communication
* `client.cpp` → Handles client-side communication

## How to Run

### Server

```bash
g++ server.cpp -o server
./server
```

### Client

```bash
g++ client.cpp -o client
./client
```

## Learning Outcomes

* Understanding of TCP/IP networking
* Socket programming fundamentals
* Client-server architecture
* Network debugging and communication handling

