
###  Key Idea: Use the Suffix Array

The suffix array is a powerful tool that stores all suffixes of the string sorted in **lexicographic order**.

If we build the suffix array of `s`, it tells us:
- Which suffix comes first, second, third, etc., in lexicographic order.

Let’s denote the suffix array as `sa[]`. So `s.substr(sa[0])` is the lex smallest suffix, `s.substr(sa[1])` the second smallest, and so on.

We can also build an LCP (Longest Common Prefix) array `lcp[]`, where `lcp[i]` gives the common prefix length between `s.substr(sa[i])` and `s.substr(sa[i - 1])`.

---

###  How to Solve the Problem Using Suffix Array?

We want the smallest substring of length `i`.

**Observation:**
- A substring of length `i` is a prefix of some suffix.
- So, for each length `i`, find the first suffix in the suffix array with length ≥ `i`.
- Among all suffixes in the suffix array that **share the same prefix of length `i`**, we want the one with the **smallest starting index**.

---

###  How to Efficiently Find These?

We can preprocess the following using sparse tables:
1. `queryLcp(i, j)` — to get the minimum LCP value between `sa[i]` and `sa[j]` in `O(1)`.
2. `queryMin(i, j)` — to get the minimum index among `sa[i]..sa[j]` (earliest start).

Now, for each `i = 1 to n`:
- Move a pointer `cur` to the first index in `sa[]` such that the suffix length ≥ `i`.
- Expand a range `[cur, r]` such that all suffixes in that range share a common prefix of at least `i` (using `queryLcp`).
- Among all these, pick the suffix with the smallest starting index using `queryMin`.

Output `queryMin(cur, r) `.

---

###  Time Complexity

- Building suffix array + LCP: `O(n log n)`
- Preprocessing sparse tables: `O(n log n)`
- Processing each length from `1` to `n`: amortized `O(log n)`

So total per test case: `O(n log n)`  
Fast enough for all constraints!
