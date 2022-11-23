// reference: https://youtu.be/XYkiwsplDTg?list=PLai5B987bZ9CoVR-QEIN9foz4QCJ0H2Y8
use std::env;
use std::fs;
use std::process;
use std::error::Error;

fn main() {
    let args: Vec<String> = env::args().collect();

    let config = Config::new(&args).unwrap_or_else(|err| {
        println!("Problem parsing arguments: {}", err);
        process::exit(1);
    });

    println!("Searching for {}", config.query);
    println!("In file {:?}", config.filename);

    if let Err(e) = run(config) {
        println!("Application error: {}", e);
        process::exit(1);
    }
}

fn run(config: Config) -> Result<(), Box<dyn Error>> {
    println!("Searching for {}", config.query);
    println!("In file {:?}", config.filename);

    let contents = fs::read_to_string(config.filename)?;
    println!("With text: {}", contents);

    Ok(())
}

struct Config {
    query: String,
    filename: String,
}

impl Config {
    fn new(args: &[String]) -> Result<Config, &str> {
        if args.len() < 3 {
            return Err("not enough arguments!\n");
        }

        let query = args[1].clone();
        let filename = args[2].clone();
        
        Ok(Config { query, filename })
    }

}
