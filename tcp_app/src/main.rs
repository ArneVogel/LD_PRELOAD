use std::io::prelude::*;
use std::net::TcpStream;

fn main() -> std::io::Result<()> {
    let mut stream = TcpStream::connect("1.1.1.1:443")?;

    stream.write(&[1])?;
    stream.read(&mut [0; 128])?;
    println!("success");
    Ok(())
}
