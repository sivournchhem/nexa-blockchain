#ifndef GOVERNANCE_H
#define GOVERNANCE_H

#include <string>

class Governance {
public:
    // Creates a new governance proposal
    static void createProposal(const std::string& proposal);

    // Casts a vote on a proposal (1 = Yes, 0 = No)
    static void voteOnProposal(const std::string& proposal, int vote);

    // Retrieves the number of votes for a given proposal
    static int getProposalVotes(const std::string& proposal);

    // Singleton instance
    static Governance& getInstance();

private:
    Governance() = default;  // Private constructor for Singleton pattern
};

#endif // GOVERNANCE_H
