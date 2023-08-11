cargo new project_name --bin              # create a binary crate
cargo new project_name --lib              # create a library crate
cargo --version
cargo build                               # compiles in dev mode [unoptimized + debuginfo]
cargo build --release                     # compiles in release mode [optimized]
cargo check                               # analyzes project and report errors, but don't build object files
cargo run                                 # builds and executes src/main.rs
cargo run -p pkg_name                     # run within workspace
cargo clean                               # removes the target directory
cargo update                              # updates dependencies listed in Cargo.lock
cargo doc                                 # generate the HTML documentation from this documentation comment
cargo doc --open                          # open html doc in a web browser
cargo test                                # run test
cargo test --help                         # displays the options you can use with cargo test
cargo test -- --help                      # displays the options you can use after the separator
cargo test -- --test-threads=1            # run the tests using one thread
cargo test test_name_pattern              # run test which name match with the pattern
cargo test --test integration_test        # run tests in integration_test.rs
cargo test -p add_one                     # run test within workspace
cargo publish                             # publish to Crates.io
cargo yank --vers 1.0.1                   # deprecating version
cargo install ripgrep                     # install and use binary crates locally