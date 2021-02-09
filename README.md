# GUI App in Rust for Aurora OS

This is an example of the simplest GUI application written in Rust to be run on the mobile Aurora OS.

# Prerequisites

* Ubuntu Linux host OS
* Rust installed (see https://rustup.rs for details)
* `make`

# Build

* Prepare:

    ```
    make prepare
    ```

* Compile:

    ```
    make
    # or
    make release
    ```

* Build RPM-package

    ```
    make rpm
    ```

    Output .rpm file is in `target/armv7-unknown-linux-gnueabihf/release/rpmbuild/RPMS/armv7hl` directory.

* Copy to a mobile device (without package signing):

    ```
    make install
    ```

# Install and Run

After package signing it is necessary to copy it to the target device and install onto the Aurora OS:

```
$ devel-su
# pkcon install-local ./aurora-rust-gui-*.armv7hl.rpm
```

Run:

```
$ aurora-rust-gui
```

Or just tap the `Rust GUI` shortcut on the Aurora OS desktop.

# License

Source code is licensed under the [MIT license](LICENSE).
