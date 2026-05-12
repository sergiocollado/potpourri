use clap::Parser;

#[derive(Parser)]
#[command(name="smf")]
#[command(version="1.0")]
#[command(about="5G Session Manager Function (SMF)")]
struct Args
{
    #[arg(short, long, help="Load configuration from 'FILE'", value_name="CONFIG_FILE")] 
    config: String,

    #[arg(short, long, help="Load uerouting configuration from 'FILE'", value_name="UEROUTING_FILE")]
    uerouting: String,

    #[arg(short, long, help="Output NF log to 'FILE'", value_name="LOG_FILE")]
    log: String,
}

fn main() {
    let args = Args::parse();
    println!("file: config: {}, uerouting: {}, logs: {}", args.config, args.uerouting, args.log);
}

