#include "network.h"
#include <iostream>
#include <mutex>
#include <vector>

std::mutex peerMutex; // Ensure mutex is declared before use

// Add a new peer to the list (Thread-Safe)
void PeerManager::addPeer(const std::string& peerIP) {
    std::lock_guard<std::mutex> lock(peerMutex);
    peers.push_back(peerIP);
    std::cout << "[NETWORK] Connected to peer: " << peerIP << std::endl;
}

// Retrieve the list of connected peers (Thread-Safe)
std::vector<std::string> PeerManager::getPeers() const {
    std::lock_guard<std::mutex> lock(peerMutex);
    return peers;
}
