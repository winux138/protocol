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

impl TryFrom<ProtocolFrame> for animal {
    type Error = &'static str;

    fn try_from(value: ProtocolFrame) -> Result<Self, Self::Error> {
        if value.protocol_frame.id == PROTOCOL_ANIMAL.try_into().unwrap_or_default() {
            let v = unsafe { std::slice::from_raw_parts(value.protocol_frame.data, 18) };
            let (head, body, _tail) = unsafe { v.align_to::<animal>() };
            assert!(head.is_empty(), "Data was not aligned");
            return Ok(body[0]);
        }
        Err("Expected self.id = PROTOCOL_ANIMAL, got: {value.id}")
    }
}

impl TryFrom<ProtocolFrame> for car {
    type Error = &'static str;

    fn try_from(value: ProtocolFrame) -> Result<Self, Self::Error> {
        if value.protocol_frame.id == PROTOCOL_CAR.try_into().unwrap_or_default() {
            return Ok(Self {
                ..Default::default()
            });
        }
        Err("Expected self.id = PROTOCOL_CAR, got: {value.id}")
    }
}

unsafe extern "C" fn decoded_callback(_out_p_frame: *mut protocol_frame) {}

impl ProtocolFrame {
    pub fn new(encoded_frame: &str) -> Self {
        let mut s = ProtocolFrame::default();

        let res = unsafe {
            // FIXME: The callback should probably be a closure and make a copy of the decoded
            // frame, as it is free'd after the callback returns.
            // BE VERY CAREFUL TO STILL BE THREADSAFE !!!
            protocol_sys::protocol_decode(
                Some(decoded_callback),
                // &mut s.protocol_frame,
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
    // TODO: Replace with ProtocolFrame::Default()
    let mut encoded_frame = [0i8; 256];
    let mut_ptr: *mut protocol_sys::animal = input;
    let u8_ptr = mut_ptr as *mut u8;
    let mut protocol_frame = protocol_sys::protocol_frame {
        data: u8_ptr,
        data_size: std::mem::size_of::<protocol_sys::animal>()
            .try_into()
            .unwrap_or_default(),
        id: PROTOCOL_ANIMAL.try_into().unwrap_or_default(),
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

    let encoded_frame: Vec<u8> = encoded_frame
        .iter()
        .filter(|e| **e != 0)
        .map(|e| *e as u8)
        .collect();
    Some(String::from_utf8(encoded_frame).unwrap_or_default())
}
