use tokio::net::{TcpListener, TcpStream};
use tokio::io::{AsyncReadExt, BufReader};
use std::fs;
use std::sync::Arc;
use tokio::sync::Mutex;
use std::io;

pub struct P2PNetwork {
    pub peers: Arc<Mutex<Vec<TcpStream>>>,
    pub peer_list_path: String,
}

impl P2PNetwork {
    pub fn new(peer_list_path: &str) -> Self { // Implement the new function
        P2PNetwork {
            peers: Arc::new(Mutex::new(Vec::new())),
            peer_list_path: peer_list_path.to_string(),
        }
    }

    pub async fn start_listener(&self, port: u16) -> io::Result<()> {
        let listener = TcpListener::bind(("0.0.0.0", port)).await?;

        println!("🚀 Nexa TCP P2P Network is Listening on 0.0.0.0:{}", port);

        let self_clone = Arc::new(Self {
            peers: self.peers.clone(),
            peer_list_path: self.peer_list_path.clone(),
        });

        tokio::spawn(async move {
            loop {
                match listener.accept().await {
                    Ok((stream, addr)) => {
                        println!("🔥 New peer connected: {}", addr);
                        let mut peers = self_clone.peers.lock().await;
                        peers.push(stream);
                    }
                    Err(e) => {
                        println!("⚠️ Failed to accept connection: {}", e);
                    }
                }
            }
        });

        Ok(())
    }

    pub async fn connect_to_peer(&self, ip: &str, port: u16) -> io::Result<()> {
        let stream = TcpStream::connect((ip, port)).await?;
        println!("✅ Connected to peer: {}:{}", ip, port);
        let mut peers = self.peers.lock().await;
        peers.push(stream);
        Ok(())
    }

    pub async fn discover_and_connect_to_peers(&self) -> io::Result<()> { // Implement this function
        let peers = self.discover_peers().await?;
        for (ip, port) in peers {
            self.connect_to_peer(&ip, port).await?;
        }
        Ok(())
    }

    async fn discover_peers(&self) -> io::Result<Vec<(String, u16)>> {
        let mut peers = Vec::new();
        let peer_list_str = fs::read_to_string(&self.peer_list_path)?;
        for line in peer_list_str.lines() {
            let parts: Vec<&str> = line.split(":").collect();
            if parts.len() == 2 {
                if let (Ok(ip), Ok(port)) = (parts[0].parse(), parts[1].parse()) {
                    peers.push((ip, port));
                } else {
                    println!("Invalid peer format: {}", line);
                }
            }
        }
        Ok(peers)
    }

    pub async fn broadcast_message(&self, message: &str) -> io::Result<()> {
        let peers = self.peers.lock().await;
        for peer in peers.iter() {
            // ... (Serialize the message) ...
            // ... (Send the message over the stream) ...
        }
        Ok(())
    }
}
