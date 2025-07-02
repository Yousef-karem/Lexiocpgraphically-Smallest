# Lexicographically Smallest

## Problem Statement

Given a string `s` of length `n`, for each length from `1` to `n`, output the starting index (0-based) of the **lexicographically smallest substring** of that length.  
If there are multiple such substrings, output the index of the **earliest** one.

---

## Input

Each test consists of multiple test cases.  
The first line contains a single integer `t` (**1 ≤ t ≤ 10⁵**) — the number of test cases.

Then follow `t` test cases.

For each test case:
- The first line contains an integer `n` (**1 ≤ n ≤ 5 × 10⁵**) — the length of the string `s`.
- The second line contains a string `s` of length `n`, consisting of lowercase English letters (`a` to `z`).

It is guaranteed that the **total sum of `n` over all test cases does not exceed 5 × 10⁵**.

---

## Output

For each test case, output a single line containing `n` integers separated by spaces.

The `i`-th integer (for `1 ≤ i ≤ n`) should represent the **starting index (0-based)** of the lexicographically smallest substring of length `i`.
