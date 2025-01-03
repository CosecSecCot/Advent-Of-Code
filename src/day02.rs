use anyhow::Result;

fn check_level(level: &Vec<i32>) -> bool {
    let mut safe = true;
    let increasing = level[0] < level[1];
    for i in 1..level.len() {
        if !safe {
            break;
        }

        if increasing {
            safe &= level[i] > level[i - 1] && (level[i] - level[i - 1]).abs() <= 3;
        } else {
            safe &= level[i] < level[i - 1] && (level[i] - level[i - 1]).abs() <= 3;
        }
    }

    safe
}

fn part1(levels: &Vec<Vec<i32>>) -> Result<i32> {
    let mut ans = 0;

    for level in levels {
        if check_level(level) {
            // println!("{:?}", level);
            ans += 1;
        }
    }

    Ok(ans)
}

fn part2(levels: &mut Vec<Vec<i32>>) -> Result<i32> {
    let mut ans = 0;

    for level in levels {
        if check_level(level) {
            ans += 1;
        } else {
            // println!("UNSAFE: {:?}", level);
            for i in 0..level.len() {
                let mut temp_level = level.clone();
                temp_level.remove(i);
                // println!("Checking: {:?}", temp_level);
                if check_level(&temp_level) {
                    // println!("GOOD!");
                    ans += 1;
                    break;
                }
            }
        }
    }

    Ok(ans)
}

fn main() -> Result<()> {
    let mut levels = aoc::read_lines::<i32>("./data/2.input")?;

    println!("Part 1: {}", part1(&levels)?);
    println!("Part 2: {}", part2(&mut levels)?);

    Ok(())
}
