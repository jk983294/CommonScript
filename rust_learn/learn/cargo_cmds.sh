cargo new project_name --bin              # create a binary crate
cargo new project_name --lib              # create a library crate
cargo --version
cargo build                               # compiles the current project
cargo check                               # analyzes project and report errors, but don't build object files
cargo run                                 # builds and executes src/main.rs
cargo clean                               # removes the target directory
cargo update                              # updates dependencies listed in Cargo.lock