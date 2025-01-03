use anyhow::Result;
use regex::Regex;

fn part1(memory: &Vec<String>) -> Result<i64> {
    let mut ans: i64 = 0;

    let mul_instruction = Regex::new(r"mul\((\d+),(\d+)\)")?;

    for line in memory {
        for (_, [x, y]) in mul_instruction.captures_iter(line).map(|c| c.extract()) {
            ans += x.parse::<i64>()? * y.parse::<i64>()?;
        }
    }

    Ok(ans)
}

fn part2(memory: &Vec<String>) -> Result<i64> {
    let mut ans: i64 = 0;
    let mut disabled = false;

    let instructions = Regex::new(r"(mul\(\d+,\d+\))|(do\(\))|(don't\(\))")?;
    let mul_instruction = Regex::new(r"mul\((\d+),(\d+)\)")?;
    for line in memory {
        for (expression, [_]) in instructions.captures_iter(line).map(|c| c.extract()) {
            let res = mul_instruction.captures(expression);
            if res.is_some() {
                let (_, [x, y]) = res.unwrap().extract();
                if !disabled {
                    ans += x.parse::<i64>()? * y.parse::<i64>()?;
                }
                continue;
            }
            disabled = expression.eq("don't()");
        }
    }

    Ok(ans)
}

fn main() -> Result<()> {
    let lines = aoc::read_raw_lines("./data/3.input")?;

    println!("Part 1: {}", part1(&lines)?);
    println!("Part 2: {}", part2(&lines)?);

    Ok(())
}
