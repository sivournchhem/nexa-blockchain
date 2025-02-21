#include "network.h"
#include <iostream>
#include <mutex>
#include <vector>

std::mutex peerMutex;
std::vector<std::string> peers;

void PeerManager::addPeer(const std::string& peerIP) {
    std::lock_guard<std::mutex> lock(peerMutex);
    peers.push_back(peerIP);
    std::cout << "[NETWORK] Connected to peer: " << peerIP << std::endl;
}

std::vector<std::string> PeerManager::getPeers() const {
    std::lock_guard<std::mutex> lock(peerMutex);
    return peers;
}
