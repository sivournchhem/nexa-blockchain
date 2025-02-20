#include "network.h"
#include <iostream>

// Add a new peer to the list
void PeerManager::addPeer(const std::string& peerIP) {
    peers.push_back(peerIP);
    std::cout << "[NETWORK] Connected to peer: " << peerIP << std::endl;
}

// Retrieve the list of connected peers
std::vector<std::string> PeerManager::getPeers() const {
    return peers;
}
