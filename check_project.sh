#!/bin/bash

echo "=== STEP 1: SYSTEM INFORMATION ==="
uname -a
lsb_release -a 2>/dev/null || cat /etc/os-release
echo ""

echo "=== STEP 2: CHECKING DISK SPACE & MEMORY ==="
df -h
free -m
echo ""

echo "=== STEP 3: CHECKING RUNNING PROCESSES ==="
ps aux --sort=-%cpu | head -10
echo ""

echo "=== STEP 4: CHECKING INSTALLED SOFTWARE ==="
REQUIRED_SOFTWARE=("docker" "node" "python3" "wasm-pack" "cmake" "clang" "git")
for software in "${REQUIRED_SOFTWARE[@]}"; do
    if command -v $software &> /dev/null; then
        echo "$software is installed."
    else
        echo "ERROR: $software is missing!"
    fi
done
echo ""

echo "=== STEP 5: VERIFYING PROJECT FILES & FOLDERS ==="
declare -A REQUIRED_PATHS
REQUIRED_PATHS["/var/nexa-core"]="Nexa-Core Blockchain"
REQUIRED_PATHS["/var/nexa-layer2"]="Nexa Layer2"
REQUIRED_PATHS["/opt/wasm-contracts"]="WASM Contracts"
REQUIRED_PATHS["/var/lib/sharding"]="Sharding Data"
REQUIRED_PATHS["/var/lib/libp2p"]="libp2p Network"
REQUIRED_PATHS["/etc/nxa-token"]="NXA Token Supply Config"

for path in "${!REQUIRED_PATHS[@]}"; do
    if [ -d "$path" ]; then
        echo "✔ ${REQUIRED_PATHS[$path]} folder exists at $path"
    else
        echo "❌ ERROR: ${REQUIRED_PATHS[$path]} folder is missing!"
    fi
done
echo ""

echo "=== STEP 6: CHECKING BLOCKCHAIN NODE ==="
if ps aux | grep -v grep | grep "nexa-core" > /dev/null; then
    echo "✔ Nexa-Core node is running."
else
    echo "❌ ERROR: Nexa-Core node is NOT running!"
fi
echo ""

echo "=== STEP 7: CHECKING NETWORK & P2P CONNECTIVITY ==="
netstat -tulnp | grep LISTEN
if [ $? -eq 0 ]; then
    echo "✔ P2P Network is active."
else
    echo "❌ ERROR: No active P2P network!"
fi
echo ""

echo "=== STEP 8: VERIFYING WASM SMART CONTRACTS ==="
if [ -d "/opt/wasm-contracts" ]; then
    cd /opt/wasm-contracts
    wasm-pack build
    if [ $? -eq 0 ]; then
        echo "✔ WASM Smart Contracts compiled successfully."
    else
        echo "❌ ERROR: WASM compilation failed!"
    fi
else
    echo "❌ ERROR: WASM Contracts folder missing!"
fi
echo ""

echo "=== STEP 9: VALIDATING SHARDING & ZK-ROLLUPS ==="
grep -r "shard" /var/lib/sharding/ 2>/dev/null
grep -r "zk_rollups_enabled" /var/lib/sharding/ 2>/dev/null
if [ $? -eq 0 ]; then
    echo "✔ Sharding & ZK-Rollups are configured."
else
    echo "❌ ERROR: Sharding/ZK-Rollups configuration missing!"
fi
echo ""

echo "=== STEP 10: VERIFYING UTXO MODEL ==="
if grep -r "UTXO" /var/nexa-core/ 2>/dev/null; then
    echo "✔ UTXO Model found in the blockchain."
else
    echo "❌ ERROR: UTXO model not configured!"
fi
echo ""

echo "=== STEP 11: CHECKING TOKEN SUPPLY ==="
grep -r "23000000" /etc/nxa-token/ 2>/dev/null
if [ $? -eq 0 ]; then
    echo "✔ NXA Token Supply is correctly set to 23,000,000."
else
    echo "❌ ERROR: Token supply mismatch!"
fi
echo ""

echo "=== STEP 12: FINAL SYSTEM HEALTH CHECK ==="
df -h
free -m
uptime
netstat -tulnp | grep LISTEN
echo ""

echo "✅ ALL CHECKS COMPLETE. PLEASE REVIEW ERRORS ABOVE."
