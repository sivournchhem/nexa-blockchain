#include <iostream>
#include <sys/socket.h> 
#include <netinet/in.h>

//... other necessary headers and functions...

int networkInit(int port, int maxConnections) {
    // 1. Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == 0) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    // 2. Bind the socket to a port
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Bind to all available interfaces
    address.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Error binding socket to port" << std::endl;
        return -1;
    }

    // 3. Listen for incoming connections
    if (listen(serverSocket, maxConnections) < 0) {
        std::cerr << "Error listening for connections" << std::endl;
        return -1;
    }

    std::cout << "Network module initialized! Listening on port " << port << std::endl;

    //... further initialization logic (e.g., starting threads, connecting to peers)...

    return serverSocket;
}
