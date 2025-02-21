#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>

class PeerManager {
public:
    void addPeer(const std::string& peerIP);
    std::vector<std::string> getPeers() const;
};

#endif // NETWORK_H
