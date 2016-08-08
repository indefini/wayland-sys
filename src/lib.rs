extern crate libc;

use libc::{c_void, c_int, c_char, c_float, c_ushort};//, c_ulong, c_long, c_uint, c_uchar, size_t};

pub type RustCb = extern fn(data : *mut c_void);

#[repr(C)]
pub struct wl_display;

extern "C" {
	pub fn wl_display_create() -> *const wl_display;
}

