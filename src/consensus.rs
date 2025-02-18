use std::sync::Arc;
use tokio::time::sleep;
use std::time::{Duration, SystemTime};
use sha2::{Sha256, Digest};
use tokio::sync::Mutex; // Use async-friendly Mutex
use crate::{Block, Transaction};

/// Compute a SHA256 hash from the given input string.
fn compute_hash(input: &str) -> String {
    let mut hasher = Sha256::new();
    hasher.update(input.as_bytes());
    let result = hasher.finalize();
    format!("{:x}", result)
}

/// **Simulate Hybrid PoW/PoS Consensus Process**
///
/// This function **produces linked blocks** by draining the dummy transaction pool,
/// computing a SHA256 hash, and appending blocks to the chain.
pub async fn simulate_consensus(chain: Arc<Mutex<Vec<Block>>>) {
    let mut block_index = 1;

    loop {
        let now = SystemTime::now();

        let (previous_hash, pending_transactions) = {
            let mut chain_lock = chain.lock().await;

            // Get previous block hash
            let previous_hash = if chain_lock.is_empty() {
                "genesis".to_string()
            } else {
                chain_lock.last().unwrap().hash.clone()
            };

            // Create a dummy transaction.
            let dummy_transaction = Transaction {
                inputs: vec!["Alice".to_string()],
                outputs: vec![("Bob".to_string(), 100)],
            };

            // Store the new transactions
            (previous_hash, vec![dummy_transaction])
        };

        // Compute hash based on block index, previous hash, and transactions.
        let data = format!("block:{}:{}:{:?}", block_index, previous_hash, pending_transactions);
        let computed_hash = compute_hash(&data);

        println!(
            "⛏️ [Consensus] Block {} produced at {:?} with previous_hash: {} and hash: {}",
            block_index, now, previous_hash, computed_hash
        );

        // Create the new block
        let new_block = Block {
            index: block_index,
            previous_hash,
            transactions: pending_transactions,
            hash: computed_hash,
            nonce: 0,
            validator: None,
        };

        // Append block to blockchain
        {
            let mut chain_lock = chain.lock().await;
            chain_lock.push(new_block);
            println!("✅ Block {} added to the blockchain!", block_index);
        }

        // Increment block index
        block_index += 1;

        // Simulate mining/staking delay
        sleep(Duration::from_secs(10)).await; // Use `tokio::time::sleep()`
    }
}
