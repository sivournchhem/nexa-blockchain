use std::time::{SystemTime, UNIX_EPOCH};

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

