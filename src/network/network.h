#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>

class PeerManager {
private:
    std::vector<std::string> peers;

public:
    void addPeer(const std::string& peerIP);
    std::vector<std::string> getPeers() const;
};

#endif // NETWORK_H
