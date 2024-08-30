#[derive(Debug)]
struct Deck {
    cards: Vec<String>,
}

impl Deck {

    // new() is an associated functions, that is to say
    // a function asociated with the struct definition
    // in constrast with methods, which are functions
    // which operate in an instance on an struct.
    fn new() -> Self {
        let suits = ["Hearts", "Spades", "Diamonds"];
        let values = ["Ace", "Two", "Three"];

        let mut cards = vec![];

        for suit in suits {
            for value in values {
                let card = format!("{} of {}", value, suit);
                cards.push(card);
            }
        }

        Deck{ cards }
    }

    fn shuffle(&self) {

    }
}

fn main() {
    let deck = Deck::new();
    deck.shuffle();
    println!("Here is your deck: {:#?}", deck);
}
