pub use protocol_rs;

fn main() {
    println!("Hello, world!");
    let mut animal = protocol_rs::animal {
        age: 1,
        legs: 2,
        ..Default::default()
    };

    if let Some(encoded_frame) = protocol_rs::encode(&mut animal) {
        println!("Encoded frame is: '{encoded_frame}'");
    } else {
        println!("Could not encode the frame");
    }
}
