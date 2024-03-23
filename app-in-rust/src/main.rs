use protocol_rs;

#[derive(Default)]
struct Frame(());

impl protocol_rs::ProtocolFrame for Frame {}

fn main() {
    let frame = Frame::default();
    protocol_rs::encode(&frame);
    println!("Hello, world!");
}
