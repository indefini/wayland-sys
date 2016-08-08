#![feature(append)]

extern crate pkg_config;
extern crate gcc;


use std::env;
use std::path::PathBuf;

fn main() {
    let mut paths  = Vec::new();
    if let Ok(ref mut info) = pkg_config::find_library("wayland-server") {
        paths.append(&mut info.include_paths);
    }
    build_lib(&paths);
}

fn build_lib(include_paths: &[PathBuf]) {
    let mut config = gcc::Config::new();

    for path in include_paths {
        config.include(path);
    }

    config.file("src/lib.c")
        .compile("libwayland-server_chris.a");
}

