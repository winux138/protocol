#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

impl TryFrom<protocol_frame> for animal {
    type Error = &'static str;

    fn try_from(value: protocol_frame) -> Result<Self, Self::Error> {
        if value.id == PROTOCOL_ANIMAL.try_into().unwrap_or_default() {
            return Ok(Self {
                ..Default::default()
            });
        }
        Err("Expected self.id = PROTOCOL_ANIMAL, got: {value.id}")
    }
}

impl TryFrom<protocol_frame> for car {
    type Error = &'static str;

    fn try_from(value: protocol_frame) -> Result<Self, Self::Error> {
        if value.id == PROTOCOL_CAR.try_into().unwrap_or_default() {
            return Ok(Self {
                ..Default::default()
            });
        }
        Err("Expected self.id = PROTOCOL_CAR, got: {value.id}")
    }
}
