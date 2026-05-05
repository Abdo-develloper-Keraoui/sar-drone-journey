# K&R §1.3 – The `for` Statement

## 1. What K&R Says

> The `for` statement is a loop, a generalization of the `while`. Within the parentheses, there
> are three parts, separated by semicolons. The first part, the **initialization**, is done once,
> before the loop proper is entered. The second part is the **test or condition** that controls
> the loop. The third part is the **increment step**, executed after each body, before the
> condition is re-evaluated. The loop terminates if the condition has become false.
>
> The choice between `while` and `for` is arbitrary, based on which seems clearer. The `for` is
> usually appropriate for loops in which the initialization and increment are single statements
> and logically related, since it is more compact than `while` and it keeps the loop control
> statements together in one place.

The chapter's motivating example prints a Fahrenheit → Celsius table using a `for` instead of a
`while`, and with `int fahr` instead of `float`:

```c
#include <stdio.h>

/* print Fahrenheit-Celsius table */
main()
{
    int fahr;
    for (fahr = 0; fahr <= 300; fahr = fahr + 20)
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}
```

---

## 2. Anatomy of a `for` Loop

```
for ( initialization ; condition ; increment )
      ──────────┬──    ─────┬────   ─────┬────
                │           │            │
                │           │            └─ runs after each body iteration
                │           └─ checked before every iteration (including the first)
                └─ runs exactly once, before anything else
```

Equivalent `while` rewrite (to prove they are the same machine):

```c
initialization;
while (condition) {
    body;
    increment;
}
```

Everything the `for` does can be done with `while` — it is purely a readability choice.

---

## 3. Key Differences from the Previous `while` Version

### 3.1 `int` instead of `float` for the loop variable

In the earlier `while` version (`float fahr, celsius; float lower, upper, step;`), all
temperature variables were `float`.  
Here **`fahr` is `int`** and there are no separate `lower`/`upper`/`step` variables at all —
those roles are played by the literal constants `0`, `300`, and `20` inside the `for` header.

Why is that fine? The step is a whole number (`20`), the range endpoints are whole numbers
(`0`, `300`), and Fahrenheit temperatures in the desired table happen to be integers. So an
`int` loop variable is exact and avoids any floating-point drift (see
[[floating-point-accumulation-pitfall]]).

### 3.2 The Celsius formula lives inside `printf` – no extra variable needed

Old version:
```c
celsius = (5.0/9.0) * (fahr - 32);   // separate assignment
printf("%3d %6.1f\n", fahr, celsius);
```

New version:
```c
printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));  // expression as argument
```

K&R's general rule: **wherever a value of some type is legal, any expression of that type is
equally legal.** The third `printf` argument just needs to produce a `float`/`double` — and
`(5.0/9.0)*(fahr-32)` does exactly that (because `5.0` and `9.0` are `double` constants, so
the whole expression is `double`).

This is not always the clearest choice, but it shows that C is expression-based: you are never
forced to name an intermediate result.

### 3.3 `5.0/9.0` vs `5/9` — why the decimal points matter

| Expression | Type of operands | Division type | Result |
|------------|-----------------|---------------|--------|
| `5/9`      | both `int`      | integer (truncates) | `0` |
| `5.0/9.0`  | both `double`   | floating-point | `0.5555…` |
| `5.0/9`    | mixed           | floating-point | `0.5555…` |

Because `5` and `9` are integer literals, `5/9` truncates to `0` — every Celsius result would
be `0`. Writing at least one operand as a floating-point constant (`5.0`) forces the division
to be done in floating-point. (See also [[order-of-operations]] for more on truncation.)

---

## 4. My Code – Exercise 1-5 (Reverse Table)

> **Exercise 1-5:** Modify the temperature conversion program to print the table in **reverse
> order**, that is, from 300 degrees to 0.

```c
#include <stdio.h>

int main(void)
{
    int fahr;
    for (fahr = 300; fahr >= 0; fahr = fahr - 20) {
        printf("%3d\t%6.2f\n", fahr, (5.0/9.0) * (fahr - 32));
    }
}
```

**What changed vs the forward version:**

| Part          | Forward version      | Reverse version      |
|---------------|----------------------|----------------------|
| Initialization | `fahr = 0`          | `fahr = 300`         |
| Condition      | `fahr <= 300`        | `fahr >= 0`          |
| Increment      | `fahr = fahr + 20`   | `fahr = fahr - 20`   |

The body and the formula are identical — only the loop-control triple flips direction.  
`fahr = fahr - 20` can also be written `fahr -= 20` (compound assignment), which works the
same way.

---

## 5. `for` vs `while` – When to Choose Which

| Situation | Prefer |
|-----------|--------|
| Init, condition, and increment are closely related and each a single expression | `for` |
| Loop runs "until some event happens" with no clear counter | `while` |
| You want all loop-control logic visible in one line | `for` |
| The increment is complex or happens in the middle of the body | `while` |

K&R's own advice: use whichever is **clearer**. There is no performance difference.

---

## 6. Integer Loop Variable + Float Arithmetic = Best of Both

The §1.3 example is a good pattern to remember:

```c
for (int i = 0; i < N; i++) {
    // compute float result from the exact integer i
    printf("%6.2f\n", some_float_expression(i));
}
```

- The **loop variable is an integer** → no floating-point drift, exact iteration count.
- The **computation inside uses floats/doubles** → full precision for the result.

This is exactly the "integer-indexed loop" recommended in [[floating-point-accumulation-pitfall]]
as the cure for the drift problem.

---

## 7. Connection with Other Notes

- [[order-of-operations]] — integer truncation, why `5/9 = 0`, why order matters.
- [[floating-point-accumulation-pitfall]] — why accumulating a `float` loop variable is
  dangerous; the integer-indexed `for` loop is the recommended fix.
- [[c-numeric-encoding]] — how `int` and `double` are stored; why `5.0` is a `double` literal.
- [[printf-format-cheatsheet]] — `%3d`, `%6.1f`, `%6.2f` format specifiers used in these
  programs.

---

## 8. Key Takeaways

1. **`for` is syntactic sugar for `while`** — init, condition, increment packed into one line
   for readability when all three are simple and related.

2. **Use integer loop variables whenever possible.** Integers are exact; they don't drift.
   Compute the float result inside the body from the integer counter.

3. **`5/9` truncates to `0`; `5.0/9.0` gives `0.555…`.** Always ensure at least one operand
   is a float/double literal when you need floating-point division.

4. **Expressions can appear directly as `printf` arguments.** There is no obligation to store
   every intermediate result in a named variable.

5. **Reversing a `for` loop** means flipping the init (`300` instead of `0`), the condition
   (`>=` instead of `<=`), and the increment (`-= 20` instead of `+= 20`).
