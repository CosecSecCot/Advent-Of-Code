use anyhow::Result;
use std::fs;
use std::str::FromStr;

pub fn read_line<T>(path: &str) -> Result<Vec<Vec<T>>>
where
    T: FromStr,
    T::Err: std::error::Error + Send + Sync + 'static,
{
    let file = fs::read_to_string(path)?;

    file.lines()
        .map(|line| {
            line.split_whitespace()
                .map(|part| part.parse::<T>().map_err(anyhow::Error::new))
                .collect()
        })
        .collect()
}
