# Floating‑Point Accumulation Pitfall: Missing the Last Value

## 1. The Problem

You want to print exactly `N` evenly‑spaced values from `lower` to `upper` (inclusive).  
The mathematically correct step is:

```c
step = (upper - lower) / (N - 1);
```

You then write a typical `while` loop:

```c
float celsius = lower;
while (celsius <= upper) {
    printf("%3.2f\n", celsius);
    celsius += step;
}
```

**Expected output:** exactly `N` lines, ending with `upper`.  
**Actual output:** only `N-1` lines, and the last printed value is **not** `upper`.

In your real case (`lower = -272.15`, `upper = 56.7025`, `N = 20`), the loop printed only 19 lines and stopped at `39.39` instead of reaching `56.70`.

## 2. Why It Happens – Floating‑Point Drift

The root cause is **accumulated rounding error** in IEEE 754 `float` arithmetic.

- The constants `-272.15` and `56.7025` cannot be represented exactly in binary (see [[c-numeric-encoding]]).  
- The division `step = (upper - lower) / 19` introduces another tiny rounding error.  
- The computed `step` is therefore **slightly larger** than the ideal mathematical value (by something like `1e-15`).

When you repeatedly add this slightly‑too‑big step:

```
celsius = lower + step + step + ... (19 times)
```

the small errors accumulate. After 19 additions, `celsius` becomes `56.7025 + epsilon`, i.e. **a tiny fraction greater** than `upper`. The loop condition `celsius <= upper` then fails, so the final value is never printed.

This is **not** a mistake in your step formula – it’s inherent to binary floating‑point representation.

## 3. The Reliable Fix (Integer‑Controlled Loop)

Calculate each point directly from an **integer counter** instead of accumulating a variable:

```c
for (int i = 0; i < numberOfValues; i++) {
    celsius = lower + i * step;
    fahr = (9.0/5.0) * celsius + 32.0;
    printf("%3.2f\t%6.2f\n", celsius, fahr);
}
```

Why this works:
- `i` is an exact integer, so `i * step` is computed using multiplication, not repeated addition.
- Each `celsius` is computed from the original `lower` and the exact multiplication, eliminating drift.
- The last iteration (`i = N-1`) gives exactly `lower + (N-1)*step`, which is mathematically `upper` (and its floating‑point representation is usually close enough to pass `<=` when not accumulated).

This is the cleanest, most predictable solution.

## 4. Alternative Fix: `while` Loop with a Tolerance (Epsilon)

If you prefer (or must) keep the `while` loop structure, you can add a tiny **tolerance** (epsilon) to the loop condition:

```c
#define EPSILON 1e-6

float celsius = lower;
while (celsius <= upper + EPSILON) {
    printf("%3.2f\n", celsius);
    celsius += step;
}
```

### How it works

- The condition now checks `celsius <= upper + 1e-6`.  
- Because of the drift, `celsius` may become `56.7025003` when you expect `56.7025`.  
- Adding `1e-6` (0.000001) to `upper` makes `56.7025003 <= 56.7035` true, so the final value is printed.

### Choosing the epsilon

- The value must be **larger than the accumulated error** but **smaller than your step**.  
- For `float` with ~6‑7 decimal digits of precision, `1e-6` is a safe choice when the numbers are around tens or hundreds.  
- For `double`, `1e-12` might be more appropriate. Adjust based on your data’s magnitude.

### 4.1 Computing a Safe Epsilon Programmatically

Hard‑coding a magic number like `1e-6` is fragile. If your numbers change magnitude (e.g., from `-272.15` to `5e10`), the required tolerance changes. You can derive the epsilon **from the machine’s own floating‑point characteristics** using `<float.h>`.

#### The Idea

For a floating‑point number `x`, the smallest representable change (one Unit in the Last Place) is approximately `fabs(x) * FLT_EPSILON` (for `float`).  
When you **accumulate** a value inside a loop, the worst‑case error after `N` steps can be roughly:

```
max_error ≈ N * fabs(upper) * FLT_EPSILON
```

So a safe tolerance for the loop condition is:

```c
#include <float.h>

float epsilon_safe = 2.0f * N * fabsf(upper) * FLT_EPSILON;
```

Here `2.0f` is a safety factor (you can increase it if needed).  
Then use:

```c
while (celsius <= upper + epsilon_safe) { ... }
```

#### Concrete Example with Your Data

- `N = 20`  
- `upper = 56.7025f`  
- `FLT_EPSILON = 1.1920929e-7` (on your system)  

Calculation:
```
epsilon_safe = 2 * 20 * 56.7025 * 1.1920929e-7
             ≈ 40 * 56.7025 * 1.192e-7
             ≈ 2.704e-4
```

So `epsilon_safe ≈ 0.00027`, which is still much less than your step (`17.308`), and it comfortably swallows the tiny accumulated drift. This value adapts automatically if you later change `N` or the temperature range.

#### Full Code Snippet

```c
#include <stdio.h>
#include <float.h>

int main(void) {
    float lower = -272.15f, upper = 56.7025f;
    int N = 20;
    float step = (upper - lower) / (N - 1);
    
    // Compute a safe epsilon based on machine precision and loop size
    float epsilon_safe = 2.0f * N * fabsf(upper) * FLT_EPSILON;
    
    float celsius = lower;
    int count = 0;
    while (celsius <= upper + epsilon_safe) {
        printf("%3.2f\n", celsius);
        celsius += step;
        count++;
    }
    printf("Printed %d values (expected %d)\n", count, N);
    return 0;
}
```

#### Why This Works

- `FLT_EPSILON` is the difference between 1.0 and the next representable `float` (≈1.19e-7).  
- Scaled by `fabs(upper)`, it gives the approximate spacing between adjacent representable floats near `upper`.  
- Multiplying by `N` accounts for the error accumulating across many additions.  
- The factor `2` is a simple safety margin; you could also use `10` to be extra conservative – as long as it stays much smaller than your step.

> **Remember:** This is a pragmatic tolerance, not a mathematically exact error bound. For absolute certainty, the integer‑indexed loop (Section 3) remains the superior solution because it avoids accumulation entirely.

### Caveats for the Epsilon Approach

- This is a **workaround**, not a fundamental fix. If the drift exceeds your epsilon, or if the step is extremely small, you may still miss values or (worse) get an extra unwanted iteration.  
- It’s less robust than the integer‑indexed `for` loop, which is immune to accumulation drift.  
- Use this method only when you have a good reason to stick with a `while` loop and you understand the magnitude of possible error.

## 5. Why `step = (upper - lower) / 20` Gave 21 Values (the Off‑by‑One)

Earlier you tried `step = (upper - lower) / 20`.  
That produced **20 intervals**, which means **21 points** when you include both ends.  
The fencepost principle (N points → N‑1 intervals) is the reason you got one extra value.  
The fix for that is the `N-1` divisor, not a change in loop style.

## 6. Connection with Your Other Notes

- See [[c-numeric-encoding]] for how `float` stores numbers and why `0.1` is not exact.  
- See [[order-of-operations]] – that document deals with integer truncation, which is a different arithmetic pitfall. This one is about floating‑point drift, but both stem from the internal representation of numbers.  
- The `printf` format cheatsheet explains the `%3.2f` printing used in these experiments.

## 7. Quick Demonstration Code

```c
#include <stdio.h>

int main(void) {
    float lower = -272.15f, upper = 56.7025f;
    int N = 20;
    float step = (upper - lower) / (N - 1);

    // BAD: drifting loop (no epsilon)
    int count = 0;
    float celsius = lower;
    while (celsius <= upper) {
        count++;
        celsius += step;
    }
    printf("while loop (no epsilon) printed %d values (should be %d)\n", count, N);

    // OK: drifting loop with epsilon
    const float EPS = 1e-6;
    count = 0;
    celsius = lower;
    while (celsius <= upper + EPS) {
        count++;
        celsius += step;
    }
    printf("while loop with epsilon printed %d values\n", count);

    // GOOD: direct calculation in for loop
    count = 0;
    for (int i = 0; i < N; i++) {
        celsius = lower + i * step;
        count++;
    }
    printf("for loop gives %d values\n", count);

    return 0;
}
```

Expected output (on your system):

```
while loop (no epsilon) printed 19 values (should be 20)
while loop with epsilon printed 20 values
for loop gives 20 values
```

---

## 8. Key Takeaway

> **Never accumulate a floating‑point variable in a loop to generate a sequence of evenly‑spaced points.**  
> Always prefer an integer‑controlled loop (`for (i=0; i<N; i++)`).  
> If you absolutely must accumulate, add a small epsilon to the loop condition – and know its limitations.

This is a classic numeric programming pitfall, and now you have three ways to handle it: the right way (integer counter), the tolerant way (epsilon), and the wrong way (bare `while` loop).
