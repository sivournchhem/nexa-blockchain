#include "governance.h"
#include <iostream>
#include <unordered_map>

void Governance::createProposal(const std::string& proposalID) {
    proposals[proposalID] = 0;
    std::cout << "[DAO] Proposal Created: " << proposalID << std::endl;
}

void Governance::voteOnProposal(const std::string& proposalID, int vote) {
    if (proposals.find(proposalID) != proposals.end()) {
        proposals[proposalID] += vote;
        std::cout << "[DAO] Vote Casted: " << vote << " for " << proposalID << std::endl;
    } else {
        std::cerr << "[DAO] Proposal Not Found: " << proposalID << std::endl;
    }
}

int Governance::getProposalVotes(const std::string& proposalID) {
    if (proposals.find(proposalID) != proposals.end()) {
        return proposals[proposalID];
    } else {
        std::cerr << "[DAO] Proposal Not Found: " << proposalID << std::endl;
        return -1;
    }
}
