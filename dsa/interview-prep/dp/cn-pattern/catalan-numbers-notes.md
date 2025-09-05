# Catalan Numbers

Catalan numbers are a sequence of natural numbers that occur in various counting problems, often involving recursively defined objects. The sequence was discovered by Belgian mathematician Eugène Charles Catalan.

## The Sequence

The first few Catalan numbers are:
1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, ...

## Formula

1. **Recursive Formula:**

   ```
   C(n) = Σ(i=0 to n-1) C(i) * C(n-1-i)
   ```

   where C(0) = C(1) = 1

2. **Direct Formula:**
   ```
   C(n) = (1 / (n+1)) * (2n choose n)
   ```
   or
   ```
   C(n) = (2n)! / ((n+1)! * n!)
   ```

## Common Applications

1. **Valid Parentheses Combinations**

   - Number of ways to form n pairs of balanced parentheses
   - For n=2: `()()`, `(())`
   - For n=3: `()()()`, `(())()`, `()(())`, `((()))`, `(()())`

2. **Binary Tree Structures**

   - Number of unique binary trees with n nodes
   - Each Catalan number represents possible tree structures for n nodes

3. **Mountain Ranges**

   - Number of ways to draw mountain ranges with n upstrokes and n downstrokes
   - Must stay above the baseline

4. **Matrix Chain Multiplication**

   - Number of ways to parenthesize matrix multiplications

5. **Polygon Triangulation**
   - Number of ways to triangulate a convex polygon with (n+2) sides

## Dynamic Programming Solution

The most efficient way to calculate Catalan numbers for large values is using Dynamic Programming:

1. Create a DP array to store intermediate results
2. Use the recursive formula but store computed values
3. Time Complexity: O(n²)
4. Space Complexity: O(n)

## Code Pattern

```cpp
// DP Solution for nth Catalan Number
long long catalanDP(int n) {
    vector<long long> catalan(n + 1, 0);

    // Base case
    catalan[0] = catalan[1] = 1;

    // Build up the values using previously computed results
    for(int i = 2; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            catalan[i] += catalan[j] * catalan[i-1-j];
        }
    }

    return catalan[n];
}
```

## Time Complexity Analysis

1. **Recursive Solution**

   - Time: O(4^n)
   - Space: O(n) for recursion stack

2. **Dynamic Programming Solution**

   - Time: O(n²)
   - Space: O(n)

3. **Direct Formula Solution**
   - Time: O(n) for calculation
   - Space: O(1)
   - May have overflow issues for large n

## Important Notes

1. Catalan numbers grow exponentially
2. They are used in many combinatorial problems
3. The sequence appears in many seemingly unrelated counting problems
4. For large n, use DP or direct formula with big integer support
5. The numbers become very large quickly, so consider modulo operations for large inputs
