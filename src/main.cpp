#include <iostream>
#include "network/network.h"
#include "consensus/consensus.h"
#include "governance/governance.h"

int main() {
    std::cout << "[Nexa Core] Starting node..." << std::endl;

    // Governance test
    Governance::createProposal("Increase block size");
    Governance::voteOnProposal("Increase block size", 1);
    Governance::getProposalVotes("Increase block size");

    return 0;
}
