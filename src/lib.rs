extern crate libc;

use libc::{c_void, c_int, c_char, c_float, c_ushort};//, c_ulong, c_long, c_uint, c_uchar, size_t};

pub type RustCb = extern fn(data : *mut c_void);

#[repr(C)]
pub struct wl_display;
#[repr(C)]
pub struct wl_client;
#[repr(C)]
pub struct wl_event_loop;
#[repr(C)]
pub struct wl_signal;

#[repr(C)]
pub struct Signals;

extern "C" {
	pub fn wl_display_create() -> *const wl_display;
	pub fn wl_client_create(display : *const wl_display, fd : c_int) -> *const wl_client;
	pub fn wl_display_run(display : *const wl_display);
	pub fn wl_display_destroy(display : *const wl_display);

	pub fn wl_display_add_socket(display : *const wl_display, name : *const c_char) -> c_int;
	pub fn wl_display_add_socket_auto(display : *const wl_display) -> *const c_char;

	pub fn wl_display_get_event_loop(display : *const wl_display) -> *const wl_event_loop;

	pub fn wl_signal_init(signal : *const wl_signal);

	pub fn wl_display_init_shm(display : *const wl_display);

	pub fn create_signals() -> *const Signals;

	pub fn init_tmp(display : *const wl_display);
}


extern "C" {
	pub fn main_wlc() -> c_int;
}

