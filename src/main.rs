#![allow(dead_code)]
mod consensus;

use std::collections::HashMap;
use std::sync::Arc;
use tokio::sync::Mutex;
use tokio::task;
use tokio::time::{sleep, Duration};
use tokio::net::{TcpListener, TcpStream};
use tokio::io::{AsyncReadExt, AsyncWriteExt};
use wasmer::{Instance, Module, Store, imports, Value};
use crate::consensus::simulate_consensus;
use nix::sys::socket::{socket, bind, listen, accept, setsockopt, AddressFamily, SockType, SockFlag, SockaddrIn};
use nix::sys::socket::sockopt::{ReuseAddr, ReusePort};
use std::os::unix::io::{FromRawFd, AsRawFd};
use std::convert::TryInto;

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
    pub fn execute(&self, store: &mut Store, input: i32) -> i32 {
        let module = Module::new(store, &self.contract_code)
            .expect("Failed to create WASM module");
        let import_object = imports! {};
        let instance = Instance::new(store, &module, &import_object)
            .expect("Failed to instantiate WASM module");
        let func = instance
            .exports
            .get_function("execute")
            .expect("Function 'execute' not found");
        let result = func.call(store, &[Value::I32(input)])
            .expect("Execution failed");
        result[0].i32().unwrap()
    }
}

pub struct P2PNetwork {
    pub peers: Arc<Mutex<Vec<TcpStream>>>,
}

impl P2PNetwork {
    pub fn new() -> Self {
        P2PNetwork {
            peers: Arc::new(Mutex::new(Vec::new())),
        }
    }

    pub async fn start_listener(&self, port: u16) {
        let listener = TcpListener::bind(("0.0.0.0", port)).await
            .expect("Failed to bind TCP listener");

        println!("🚀 Nexa TCP P2P Network is Listening on 0.0.0.0:{}", port);

        loop {
            match listener.accept().await {
                Ok((stream, addr)) => {
                    println!("🔥 New peer connected: {}", addr);
                    let mut peers = self.peers.lock().await;
                    peers.push(stream);
                }
                Err(e) => {
                    println!("⚠️ Failed to accept connection: {}", e);
                }
            }
        }
    }

    pub async fn connect_to_peer(&self, ip: &str, port: u16) {
        match TcpStream::connect((ip, port)).await {
            Ok(stream) => {
                println!("✅ Connected to peer: {}:{}", ip, port);
                let mut peers = self.peers.lock().await;
                peers.push(stream);
            }
            Err(e) => {
                println!("⚠️ Failed to connect to peer {}: {}: {}", ip, port, e);
            }
        }
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
    pub fn new() -> Arc<Self> {
        Arc::new(Self {
            network: Arc::new(P2PNetwork::new()),
            chain: Arc::new(Mutex::new(Vec::new())),
            difficulty: 4,
            stakes: Arc::new(Mutex::new(HashMap::new())),
            contracts: Arc::new(Mutex::new(Vec::new())),
            transaction_pool: Arc::new(Mutex::new(Vec::new())),
        })
    }
}

#[tokio::main]
async fn main() {
    let blockchain = Blockchain::new();
    let network = blockchain.network.clone();

    println!("🚀 Nexa Blockchain Started!");

    // Start TCP P2P listener
    let network_clone = network.clone();
    task::spawn(async move {
        network_clone.start_listener(30333).await;
    });

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
