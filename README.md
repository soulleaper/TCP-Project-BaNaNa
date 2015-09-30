# TCP-Project-BaNaNa
TCP/IP Programming Project

## Group Name: BaNaNa

## Group Member: 

1111115284  Mohammad Dinnie Bin Noor Mohammad

1111115338  Lim Chuan Chong

## Descriptions
This repository contains a File Repository System using client-server TCP/IP Model. To run the program, we must first initiate the server for socket connection for client. 

1. Initiate Server side

  Compile the server.c: 
  
  ```
  $ gcc -o server server.c
  ```
  
  Run the server.c:
  
  ```
  ./server
  ```
  
  Sample output:
  
  ```
  ** File Repository Server **
  Server IP address: 10.0.2.15

  Waiting for connection... [bind]
  ```
  
  Sample output that shows client connected:
  
  ```
  Client 10.0.2.15 connected now.
  ```
  
2. Run the Client side

  Run the client.c:
  
  ```
  ./client 10.0.2.15
  ```
  
  Sample output:
  
  ```
  ** Hello, welcome to the server. ** 

  Press
  1.Download File
  2.Send File
  3.Create Directory
  4.Delete Directory(include sub directory)
  [type /q to quit] : 

  ```
  
  Based on the selection, the client side able to download, send file, create and delete directory. The file downloaded from the server will be stored into client_file directory.
  
## Task distribution

Mohammad Dinnie Tasks:

1. Socket connection for server and client.
2. Create and manage Github repository.

Lim Chuan Chong Tasks:

1. Send and receive file from server to client.
2. Create and delete directory from client to server.
