# Just Chat


This project provides a simple implementation of a TCP server and client using the Boost.Asio library. 
The server can handle multiple concurrent client connections and facilitates broadcasting messages to all connected clients.

## Features
- Asynchronous Operations: Both the server and client operate asynchronously, enabling non-blocking communication.
- Broadcasting: When a client sends a message to the server, the server broadcasts the message to all connected clients.
- Dynamic Port Selection: Users can specify the port for the server to run on and the port for the client to connect to.
- Nickname-based Communication: Clients specify a nickname upon connection, which is used as a prefix for all their 
- messages.

## Prerequisites
- GCC Compiler with C++17 support or newer.
- Boost library, specifically Boost.Asio.
- CMake

## Build
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Run Server
```bash
cd build/Server
./server_app
```

## Run Client
```bash
cd build/Client
./client_app
```