#[macro_use]
extern crate cpp;

mod qbytearray;
mod qstring;
mod qurl;
mod sailfishapp;

use sailfishapp::SailfishApp;

#[no_mangle]
pub extern "C" fn __libc_csu_init() {}

#[no_mangle]
pub extern "C" fn __libc_csu_fini() {}

fn main() {
    let mut app = SailfishApp::new();
    app.set_source("main.qml".into());
    app.show();
    app.exec();
}
