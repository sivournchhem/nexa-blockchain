#include "governance/governance.h"
#include <iostream>

int main() {
    Governance dao;
    dao.createProposal("increase_block_size");
    dao.voteOnProposal("increase_block_size", 1);

    std::cout << "[Nexa Core] Governance Initialized - Votes: " 
              << dao.getProposalVotes("increase_block_size") << std::endl;

    return 0;
}
