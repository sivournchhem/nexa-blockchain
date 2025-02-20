#ifndef POWPOS_H
#define POWPOS_H

#include <cstdint>

// Define staking and mining ratios
const double POW_REWARD_RATIO = 0.6;  // 60% PoW reward
const double POS_REWARD_RATIO = 0.4;  // 40% PoS reward

// Functions for PoW and PoS validation
bool validatePoW(uint64_t blockHash, uint64_t difficulty);
bool validatePoS(uint64_t stakeAmount, uint64_t stakeTime);

#endif // POWPOS_H
