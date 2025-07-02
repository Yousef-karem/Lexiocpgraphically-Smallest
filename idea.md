## Problem Development

The core idea of the problem was to find the **lexicographically smallest substring** of every possible length from `1` to `n` in a given string.
Instead of returning the substring itself, we decided to return its **starting index**.
If multiple substrings of the same length are equally smallest, we output the one that appears **earliest** in the string.

### First Attempt

Initially, we observed that the positions of the smallest substrings might follow a **monotonic pattern** as the lengths increase.
Based on this observation, we tried to apply **binary search** to find the best starting position for each length.
To compare substrings quickly, we used **string hashing**.

However, this idea turned out to be flawed. While the smallest substring of length `k` may come from a later index than that of length `k - 1`, this is **not always true**.
The monotonicity assumption doesn't hold in all cases, which made the binary search logic incorrect.

### Final Approach

To ensure correctness and efficiency, we switched to a more reliable technique: **Suffix Arrays**. With the suffix array and the **LCP (Longest Common Prefix)** array, we could:
- Sort all suffixes of the string lexicographically.
- Efficiently compare substrings of any length.
- Use **range minimum queries** to find the earliest starting index of the lex smallest substring of a given length.

This approach provided both accuracy and performance, allowing us to handle large inputs within the problem's constraints.
