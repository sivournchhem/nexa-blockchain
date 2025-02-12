use std::time::{SystemTime, UNIX_EPOCH};

// Derive Debug to allow printing the Block struct
#[derive(Debug, Clone)]
pub struct Block {
    pub index: u64,
    pub previous_hash: String,
    pub timestamp: u64,
    pub data: String,
    pub hash: String,
}

impl Block {
    fn new(index: u64, previous_hash: String, data: String) -> Self {
        let timestamp = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .expect("Time went backwards")
            .as_secs();

        let hash = format!("{:x}", md5::compute(format!("{}{}{}{}", index, previous_hash, timestamp, data)));

        Block {
            index,
            previous_hash,
            timestamp,
            data,
            hash,
        }
    }
}

// Derive Debug to allow printing the Blockchain struct
#[derive(Debug)]
pub struct Blockchain {
    pub blocks: Vec<Block>,
}

impl Blockchain {
    pub fn new() -> Self {
        let mut blockchain = Blockchain { blocks: Vec::new() };
        blockchain.add_block("Genesis Block".to_string());
        blockchain
    }

    pub fn add_block(&mut self, data: String) {
        let index = self.blocks.len() as u64;
        let previous_hash = if index == 0 {
            String::from("0")
        } else {
            self.blocks[index as usize - 1].hash.clone()
        };
        let block = Block::new(index, previous_hash, data);
        self.blocks.push(block);
    }
}

fn main() {
    let mut blockchain = Blockchain::new();

    // Print the blockchain with Debug trait
    println!("Blockchain created: {:?}", blockchain);

    blockchain.add_block("Second Block".to_string());
    blockchain.add_block("Third Block".to_string());

    // Print the blockchain after adding blocks
    println!("Blockchain after adding new blocks: {:?}", blockchain);
}

