#ifndef GOVERNANCE_H
#define GOVERNANCE_H

#include <string>
#include <unordered_map>

class Governance {
private:
    std::unordered_map<std::string, int> proposals; // Stores proposal votes

public:
    void createProposal(const std::string& proposalID);
    void voteOnProposal(const std::string& proposalID, int vote);
    int getProposalVotes(const std::string& proposalID);
};

#endif // GOVERNANCE_H
