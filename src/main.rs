#![allow(dead_code)]
mod consensus;
mod network;

use std::collections::HashMap;
use std::sync::Arc;
use tokio::sync::Mutex;
use tokio::task;
use tokio::time::{sleep, Duration};
use wasmer::{Instance, Module, Store, imports, Value};
use crate::consensus::simulate_consensus;
use crate::network::P2PNetwork;
use std::io;

#[derive(Debug, Clone)]
pub struct Block {
    pub index: u64,
    pub previous_hash: String,
    pub transactions: Vec<Transaction>,
    pub hash: String,
    pub nonce: u64,
    pub validator: Option<String>,
}

#[derive(Debug, Clone)]
pub struct Transaction {
    pub inputs: Vec<String>,
    pub outputs: Vec<(String, u64)>,
}

#[derive(Debug, Clone)]
pub struct SmartContract {
    pub contract_code: Vec<u8>,
}

impl SmartContract {
    pub fn execute(&self, _store: &mut Store, input: i32) -> i32 {  // Added _store to avoid warning
        // Placeholder implementation - replace with actual WASM execution
        println!("Executing smart contract with input: {}", input);
        input * 2 // Dummy result
    }
}


pub struct Blockchain {
    pub chain: Arc<Mutex<Vec<Block>>>,
    pub difficulty: usize,
    pub stakes: Arc<Mutex<HashMap<String, u64>>>,
    pub contracts: Arc<Mutex<Vec<SmartContract>>>,
    pub network: Arc<P2PNetwork>,
    pub transaction_pool: Arc<Mutex<Vec<Transaction>>>,
}

impl Blockchain {
    pub fn new(peer_list_path: &str) -> Arc<Self> {
        Arc::new(Self {
            network: Arc::new(P2PNetwork::new(peer_list_path)),
            chain: Arc::new(Mutex::new(Vec::new())),
            difficulty: 4,
            stakes: Arc::new(Mutex::new(HashMap::new())),
            contracts: Arc::new(Mutex::new(Vec::new())),
            transaction_pool: Arc::new(Mutex::new(Vec::new())),
        })
    }
}

#[tokio::main]
async fn main() -> io::Result<()> {
    let peer_list_path = "peers.txt";
    let blockchain = Blockchain::new(peer_list_path);
    let network = blockchain.network.clone();

    println!("🚀 Nexa Blockchain Started!");

    network.start_listener(30333).await?;
    network.discover_and_connect_to_peers().await?;

    // Simulate consensus mechanism
    let chain_clone = blockchain.chain.clone();
    task::spawn(async move {
        simulate_consensus(chain_clone).await;
    });

    // Generate transactions
    let blockchain_clone_tx = blockchain.clone();
    task::spawn(async move {
        let mut tx_id = 1;
        loop {
            let tx = Transaction {
                inputs: vec![format!("Input from tx {}", tx_id)],
                outputs: vec![(format!("Output to User {}", tx_id), tx_id * 10)],
            };
            blockchain_clone_tx.transaction_pool.lock().await.push(tx);
            tx_id += 1;
            sleep(Duration::from_secs(7)).await;
        }
    });

    loop {
        sleep(Duration::from_secs(60)).await;
    }
}
