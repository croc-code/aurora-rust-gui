fn main() {
    let include_path = "include";
    let qt_include_path = "include/qt5";
    let sailfish_include_path = "include/sailfishapp";
    let library_path = "lib";

    let mut config = cpp_build::Config::new();
    config
    	.include(include_path)
        .include(qt_include_path)
        .include(sailfish_include_path)
        .opt_level(2)
        .flag("-std=gnu++1y")
        .flag("-mfloat-abi=hard")
        .flag("-mfpu=neon")
        .flag("-mthumb")
        .build("src/main.rs");

    println!("cargo:rustc-link-search={}", library_path);
    println!("cargo:rustc-link-lib=sailfishapp");
    println!("cargo:rustc-link-lib=Qt5Gui");
    println!("cargo:rustc-link-lib=Qt5Core");
    println!("cargo:rustc-link-lib=Qt5Quick");
    println!("cargo:rustc-link-lib=Qt5Qml");
}
