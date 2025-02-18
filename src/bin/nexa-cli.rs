use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Usage: nexa-cli <command>");
        return;
    }

    match args[1].as_str() {
        "getblockcount" => {
            // TODO: Replace with actual logic to get the block count from the running node
            println!("Block count: 0"); // Placeholder, replace this with actual blockchain data retrieval
        }
        "getpeerinfo" => {
            println!("Peer info: Not implemented yet"); // Placeholder
        }
        _ => {
            println!("Unknown command: {}", args[1]);
        }
    }
}

