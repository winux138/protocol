use protocol_sys::protocol_frame;
pub use protocol_sys::{animal, car};
pub use protocol_sys::{PROTOCOL_ANIMAL, PROTOCOL_CAR};

pub struct ProtocolFrame {
    protocol_frame: protocol_frame,
}

impl Default for ProtocolFrame {
    fn default() -> Self {
        Self {
            protocol_frame: protocol_frame {
                data: Box::new([0u8; 255]).as_mut_ptr(),
                data_size: 255,
                ..Default::default()
            },
        }
    }
}

impl ProtocolFrame {
    pub fn new(encoded_frame: &str) -> Self {
        let mut s = ProtocolFrame::default();

        let res = unsafe {
            protocol_sys::protocol_decode(
                &mut s.protocol_frame,
                encoded_frame.as_ptr() as *const i8,
                encoded_frame.len(),
            )
        };
        if res != 0 {
            println!("An error occured in the call to protocol_sys::protocol_decode()");
        }

        s
    }

    pub fn ts(&self) -> i64 {
        self.protocol_frame.ts
    }

    pub fn id(&self) -> u8 {
        self.protocol_frame.id
    }
}

// TODO: Use Result intead
pub fn encode(input: &mut protocol_sys::animal) -> Option<String> {
    let mut encoded_frame = [0i8; 256];
    let mut_ptr: *mut protocol_sys::animal = input;
    let u8_ptr = mut_ptr as *mut u8;
    let mut protocol_frame = protocol_sys::protocol_frame {
        data: u8_ptr,
        data_size: std::mem::size_of::<protocol_sys::animal>()
            .try_into()
            .unwrap_or_default(),
        ..Default::default()
    };

    let res = unsafe {
        protocol_sys::protocol_encode(
            &mut protocol_frame,
            encoded_frame.as_mut_ptr(),
            encoded_frame.len(),
        )
    };
    if res != 0 {
        return None;
    }

    let encoded_frame: Vec<u8> = encoded_frame.iter().map(|e| *e as u8).collect();
    Some(String::from_utf8(encoded_frame).unwrap_or_default())
}
