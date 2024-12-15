use std::collections::HashMap;

use anyhow::Result;

fn part1(left: &[i32], right: &[i32]) -> Result<i32> {
    let mut ans = 0;
    for i in 0..left.len() {
        ans += (left[i] - right[i]).abs();
    }
    Ok(ans)
}

fn part2(left: &[i32], right: &[i32]) -> Result<i32> {
    let mut ans = 0;
    let mut freq: HashMap<i32, i32> = HashMap::new();
    for &x in right {
        *freq.entry(x).or_default() += 1;
    }

    // println!("{freq:?}");

    for &x in left {
        ans += x * (*freq.entry(x).or_default());
    }

    Ok(ans)
}

fn main() -> Result<()> {
    let mut left: Vec<i32> = Vec::new();
    let mut right: Vec<i32> = Vec::new();

    aoc::read_line::<i32>("./data/1.example")?
        .iter()
        .for_each(|line| {
            left.push(line[0]);
            right.push(line[1]);
        });

    left.sort();
    right.sort();

    println!("Part 1: {}", part1(&left, &right)?);
    println!("Part 2: {}", part2(&left, &right)?);

    Ok(())
}
