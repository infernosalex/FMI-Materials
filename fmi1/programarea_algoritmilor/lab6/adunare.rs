use std::fs::File;
use std::io::{BufRead, BufReader, Write};

fn main() -> std::io::Result<()> {
    // Open the input file
    let input_file = File::open("adunare.in")?;
    let reader = BufReader::new(input_file);

    // Read the two numbers
    let mut numbers: Vec<i32> = Vec::new();
    for line in reader.lines() {
        let number: i32 = line?.trim().parse().expect("Invalid number");
        numbers.push(number);
        if numbers.len() == 2 {
            break;
        }
    }

    // Calculate the sum
    let sum = numbers[0] + numbers[1];

    // Write the sum to the output file
    let mut output_file = File::create("adunare.out")?;
    write!(output_file, "{}", sum)?;

    Ok(())
}

