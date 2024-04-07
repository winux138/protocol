pub use protocol_rs;

fn main() {
    println!("Hello, world!");
    let mut animal = protocol_rs::animal {
        age: 1,
        legs: 2,
        ..Default::default()
    };

    if let Some(encoded_frame) = protocol_rs::encode(&mut animal) {
        println!("Encoded frame is: '{encoded_frame}' ({len})", len = encoded_frame.len());
        let decoded_frame = protocol_rs::ProtocolFrame::new(&encoded_frame);
        println!("ProtocolFrame is of id: {}", decoded_frame.id());
        if let Ok(animal) = TryInto::<protocol_rs::animal>::try_into(decoded_frame) {
            println!("I have an animal!");
            println!("{:?}", animal);
        }
    } else {
        println!("Could not encode the frame");
    }
}
