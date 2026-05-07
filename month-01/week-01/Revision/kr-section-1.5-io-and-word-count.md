# K&R §1.5 – Character I/O, EOF, and Word Counting

---

## 1. What K&R Says

> The model of input and output supported by the standard library is very simple. Text input or
> output, regardless of where it originates or where it goes, is dealt with as streams of
> characters. A **text stream** is a sequence of characters divided into lines; each line consists
> of zero or more characters followed by a newline character.
>
> `getchar()` reads the *next input character* from a text stream and returns it as its value.
> `putchar(c)` prints the contents of the integer variable `c` as a character, usually on the screen.

> The problem is distinguishing the end of input from valid data. The solution is that `getchar`
> returns a distinctive value when there is no more input, a value that cannot be confused with
> any real character. This value is called **EOF**, for "end of file". We must declare `c` to be a
> type big enough to hold any value that `getchar` returns. We can't use `char` since `c` must
> be big enough to hold EOF in addition to any possible `char`. Therefore we use `int`.

---

## 2. The Core Building Blocks

### 2.1 `getchar()` and `putchar(c)`

```
getchar()  ──→  reads ONE character from stdin  ──→  returns it as int
putchar(c) ──→  writes ONE character to stdout  ──→  returns the character written
```

These two functions are enough to build: file copiers, character counters, line counters,
word counters — all without knowing anything else about I/O.

### 2.2 Why `int c`, not `char c`?

| Declaration | Can hold regular chars? | Can hold EOF (–1)? | Safe? |
|-------------|------------------------|--------------------|-------|
| `char c`    | Yes                    | **Maybe not** (if `char` is unsigned, –1 wraps to 255) | ❌ |
| `int c`     | Yes                    | Yes (int is always signed and wide enough) | ✅ |

`EOF` is defined in `<stdio.h>` as `–1` on most systems. If `c` is `unsigned char`,
`–1` wraps around to `255` — which is a valid character value — so the loop never
terminates. Using `int` is the only safe choice.

### 2.3 What EOF actually is

```c
// Inside <stdio.h> – something like:
#define EOF (-1)
```

The *specific* value doesn't matter to you. What matters is: it's **outside** the
range of valid `char` values (0–255), so it can never be confused with real input.
That's the whole point of the symbolic constant — you write `EOF`, not `-1`, so
your program doesn't depend on the implementation detail.

---

## 3. §1.5.1 – File Copying

### Version 1 – Explicit style

```c
#include <stdio.h>

main()
{
    int c;
    c = getchar();               /* read first character */
    while (c != EOF) {
        putchar(c);              /* print it */
        c = getchar();           /* read next */
    }
}
```

**Flow:**
```
read c
┌─────────────────────────────┐
│  c != EOF?  ──No──→  STOP   │
│     │ Yes                   │
│  putchar(c)                 │
│  read c again               │
└─────────────────────────────┘
```

Problem with this version: `getchar()` appears **twice** — once before the loop,
once inside. That's easy to forget to keep in sync.

### Version 2 – Idiomatic C style

```c
#include <stdio.h>

main()
{
    int c;
    while ((c = getchar()) != EOF)
        putchar(c);
}
```

**What the condensed line does, step by step:**

```
while ( (c = getchar()) != EOF )
          └────┬────┘      │
               │           └─ 3. compare result of assignment to EOF
               └─ 1. call getchar()
                  2. assign return value to c  (assignment is an expression; its VALUE is c)
```

The **parentheses around `(c = getchar())`** are mandatory. Without them:

```c
// WITHOUT parens — WRONG:
while (c = getchar() != EOF)
// Parsed as:
while (c = (getchar() != EOF))   // != has higher precedence than =
// c gets 0 or 1 (boolean), not the character. Bug!
```

This is a classic C precedence trap. The rule: **`!=` binds tighter than `=`**.
Always parenthesise assignments used as expressions inside conditions.

---

## 4. §1.5.2 – Character Counting

```c
#include <stdio.h>

main()
{
    long nc;
    nc = 0;
    while (getchar() != EOF)
        ++nc;
    printf("%ld\n", nc);
}
```

**New things here:**

| Feature | Explanation |
|---------|-------------|
| `long nc` | Used instead of `int` because large files could overflow a 16-bit `int` (max 32 767). `long` is at least 32 bits everywhere. |
| `++nc` | Pre-increment: adds 1 to `nc`. Equivalent to `nc = nc + 1` but more concise. |
| `%ld` | `printf` format specifier for `long` (not `%d` which is `int`). |
| `getchar()` return value discarded | We don't need the character itself here, only whether we've hit EOF. |

### `++` and `--` operators

```
++nc   (prefix)  – increment nc FIRST, then use its value
nc++   (postfix) – use nc's current value FIRST, then increment
```

For a standalone `++nc;` statement, both do the same thing.
The difference only matters when the expression's value is used (covered in Chapter 2).

**Double version with `for`:**

```c
double nc;
for (nc = 0; getchar() != EOF; ++nc)
    ;                       /* null statement — body is intentionally empty */
printf("%.0f\n", nc);
```

- `double` can count even more characters (up to ~10¹⁵ without precision loss).
- `%.0f` — prints a `double` with **zero** decimal places (suppresses the `.0`).
- The **null statement** (`;` alone on a line) satisfies C's grammar requirement
  that a `for` loop must have a body, when all the work is in the header.

---

## 5. §1.5.3 – Line Counting

```c
#include <stdio.h>

main()
{
    int c, nl;
    nl = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            ++nl;
    printf("%d\n", nl);
}
```

**Key idea:** The standard library guarantees every line ends with `'\n'`. So
counting lines = counting newline characters. No special logic needed.

### Character constants

| Literal | Type | Value (ASCII) | Meaning |
|---------|------|---------------|---------|
| `'\n'`  | `int`| 10            | newline |
| `'\t'`  | `int`| 9             | tab     |
| `'\\'`  | `int`| 92            | backslash |
| `'A'`   | `int`| 65            | letter A |
| `'0'`   | `int`| 48            | digit zero |

A character constant like `'\n'` is just a small integer — it's not a string.
`'\n'` (single quotes) ≠ `"\n"` (double quotes / string constant with 2 bytes: char + null terminator).

### `==` vs `=`

```c
if (c == '\n')   // CORRECT: equality TEST  (is c equal to newline?)
if (c = '\n')    // BUG: ASSIGNMENT (sets c to 10, condition is always true)
```

C will not warn you about using `=` in a condition — it's syntactically legal.
Train yourself: **comparisons use `==`, assignments use `=`**.

---

## 6. §1.5.4 – Word Counting

This section ties everything together into a real utility — a bare-bones version
of the Unix `wc` command.

### 6.1 What K&R Says

> A **word** is any sequence of characters that does not contain a blank, tab, or newline.
> The variable `state` records whether the program is currently inside a word or not.

### 6.2 The Program

```c
#include <stdio.h>

#define IN  1   /* inside a word  */
#define OUT 0   /* outside a word */

main()
{
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;

    while ((c = getchar()) != EOF) {
        ++nc;                          /* count every character */
        if (c == '\n')
            ++nl;                      /* count newlines */
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;               /* whitespace → we left a word */
        else if (state == OUT) {
            state = IN;                /* first non-whitespace after whitespace → new word */
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}
```

### 6.3 State Machine — the core idea

The variable `state` turns this into a tiny **finite state machine** with two states:

```
        whitespace                 whitespace
           ┌──┐                      ┌──┐
           │  ↓                      │  ↓
     ┌─────────────┐  non-ws   ┌───────────┐
     │    OUT      │ ─────────→│    IN     │
     │ (not in     │           │ (inside   │
     │  a word)    │ ←─────────│  a word)  │
     └─────────────┘ whitespace└───────────┘
                                    ↑
                               ++nw fires HERE,
                               on the OUT→IN transition only
```

**Why count on the transition, not while IN?**
If we incremented `nw` every character while `state == IN`, we'd count
*letters* not *words*. By firing `++nw` only when we *enter* IN from OUT,
we count exactly one word per word, regardless of its length.

### 6.4 Line-by-line breakdown

```c
state = OUT;
nl = nw = nc = 0;
```
Right-to-left chained assignment — equivalent to `nc = 0; nw = 0; nl = 0;`
Assignment is an expression whose *value* is the assigned value, so this chains.

---

```c
if (c == ' ' || c == '\n' || c == '\t')
    state = OUT;
else if (state == OUT) {
    state = IN;
    ++nw;
}
```

**`||` is OR, `&&` is AND.** Both short-circuit:
- `||` stops as soon as it finds a `true` — no point checking further.
- `&&` stops as soon as it finds a `false`.

So if `c == ' '` is true, C never evaluates `c == '\n'` or `c == '\t'`.
Not important here, but critical in more complex conditions.

**The `else if` chain:**

```
Is c whitespace?
    YES → state = OUT   (we exited or stayed outside a word)
    NO  → were we already IN?
              YES → do nothing (still inside the same word)
              NO  → state = IN, ++nw  (just entered a new word)
```

### 6.5 Tracing through "hello world\n"

| Char | nc | c == '\n'? | whitespace? | state before | state after | nw |
|------|----|-----------|-------------|--------------|-------------|-----|
| `h`  | 1  | no        | no          | OUT          | IN          | 1  |
| `e`  | 2  | no        | no          | IN           | IN          | 1  |
| `l`  | 3  | no        | no          | IN           | IN          | 1  |
| `l`  | 4  | no        | no          | IN           | IN          | 1  |
| `o`  | 5  | no        | no          | IN           | IN          | 1  |
| ` `  | 6  | no        | **yes**     | IN           | OUT         | 1  |
| `w`  | 7  | no        | no          | OUT          | IN          | **2** |
| `o`  | 8  | no        | no          | IN           | IN          | 2  |
| `r`  | 9  | no        | no          | IN           | IN          | 2  |
| `l`  | 10 | no        | no          | IN           | IN          | 2  |
| `d`  | 11 | no        | no          | IN           | IN          | 2  |
| `\n` | 12 | **yes** → nl=1 | **yes** | IN          | OUT         | 2  |

Output: `1 2 12`

---

## 7. New Syntax Introduced in §1.5

### 7.1 `if-else`

```c
if (expression)
    statement1
else
    statement2
```

Exactly one branch executes. `else` is optional. Multiple conditions chain with `else if`:

```c
if (x < 0)
    printf("negative");
else if (x == 0)
    printf("zero");
else
    printf("positive");
```

### 7.2 `||` and `&&`

| Operator | Meaning | Precedence (lower # = higher) |
|----------|---------|-------------------------------|
| `&&`     | AND — true if **both** sides are true | higher |
| `\|\|`   | OR — true if **at least one** side is true | lower than `&&` |
| `!`      | NOT — flips true/false | highest of the three |

Both **short-circuit**: evaluation stops the moment the result is determined.

```c
if (x != 0 && y/x > 2)   // safe: y/x only evaluated if x != 0
```

### 7.3 `#define` symbolic constants (recap from §1.4)

```c
#define IN  1
#define OUT 0
```

The preprocessor replaces every occurrence of `IN` with `1` and `OUT` with `0`
before compilation. No semicolon, no `=`. Using names instead of "magic numbers"
makes the code readable and easy to change in one place.

---

## 9. My Code – Exercise 1-12 (One Word Per Line)

> **Exercise 1-12:** Write a program that prints its input one word per line.

### 9.1 The Solution

```c
#include <stdio.h>
#define IN  1
#define OUT 0

int main(void) {
    int c, nl, nw, nc, state;
    nl = nw = nc = 0;
    state = OUT;

    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n') {
            ++nl;
        }
        if (c == ' ' || c == '\t' || c == '\n') {
            state = OUT;
            putchar('\n');                  /* end the current line on whitespace */
        }
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
        if (state == IN)
            putchar(c);                     /* only print when inside a word */
    }
    printf("%d\t%d\t%d\n", nl, nw, nc);
    return 0;
}
```

### 9.2 The Core Insight – What Changed vs the Original

The word-counter already *detects* word boundaries perfectly via the `state` machine.
The exercise just asks to *print* each word on its own line. The change is minimal:

| Part | Original word-counter | Exercise 1-12 |
|------|----------------------|---------------|
| On whitespace | `state = OUT` only | `state = OUT` + `putchar('\n')` |
| On word character | (nothing printed) | `if (state == IN) putchar(c)` |
| Purpose | count words | print words, one per line |

The original state machine is left completely intact. Two `putchar` calls are layered on top:
one that ends the line, and one that prints the character when inside a word.

### 9.3 How the Two `if` Blocks Interact

```c
/* Block A */
if (c == ' ' || c == '\t' || c == '\n') {
    state = OUT;
    putchar('\n');         // fires on whitespace
}
else if (state == OUT) {
    state = IN;
    ++nw;
}

/* Block B — separate if, not else */
if (state == IN)
    putchar(c);            // fires on non-whitespace characters
```

**Why Block B is a separate `if` and not an `else`:**

If it were an `else`, it would fire on *every* non-whitespace character — including the
very first character of a new word, at the exact moment `state` is *just being set* to `IN`.
Because Block B is its own `if`, it runs after Block A has finished updating `state`.
So the transition character (the first letter of a new word) is correctly printed.

**Trace through `"hi you\n"`:**

| Char | Block A fires? | state before → after | nw | Block B fires? | Output |
|------|---------------|----------------------|----|----------------|--------|
| `h`  | no | OUT → IN | 1 | yes (IN) | `h` |
| `i`  | no | IN → IN  | 1 | yes (IN) | `i` |
| ` `  | yes | IN → OUT | 1 | no (OUT) | `\n` |
| `y`  | no | OUT → IN | 2 | yes (IN) | `y` |
| `o`  | no | IN → IN  | 2 | yes (IN) | `o` |
| `u`  | no | IN → IN  | 2 | yes (IN) | `u` |
| `\n` | yes (nl=1) | IN → OUT | 2 | no (OUT) | `\n` |

Final output on screen:
```
hi
you

1	2	7
```

### 9.4 Edge Case – Multiple Consecutive Spaces

If the input is `"hello   world"` (3 spaces), each space triggers `putchar('\n')` in Block A,
producing two extra blank lines between the words:

```
hello
          ← blank line (2nd space)
          ← blank line (3rd space)
world
```

This is a known limitation of this direct approach. The fix would be to only print `'\n'`
on the *OUT→OUT* transition (i.e., only the first whitespace after a word):

```c
// Fix: only emit the newline once, on the IN→OUT transition
if (c == ' ' || c == '\t' || c == '\n') {
    if (state == IN)        /* only fires the FIRST time we leave a word */
        putchar('\n');
    state = OUT;
}
```

But for the scope of this exercise, the original solution is correct and demonstrates
the key pattern cleanly.

---

## 10. Key Takeaways

1. **Always use `int c`, never `char c`, with `getchar()`.**
   `char` may be unsigned on some machines; it cannot hold `EOF (–1)` safely.

2. **`(c = getchar()) != EOF` is idiomatic C** — assignment inside a condition.
   The parentheses around the assignment are *mandatory* due to precedence.

3. **`++nc` (pre-increment) and `nc++` (post-increment)** both add 1 to `nc` as a
   standalone statement. The difference only matters when the result is used in a
   larger expression.

4. **A null statement `;` satisfies the grammar** when a loop body has nothing to do.
   Put it on its own line so it's obviously intentional, not a typo.

5. **State machines are powerful.** The `IN`/`OUT` pattern is reusable: any time you
   need to detect *transitions* (entering/leaving a region), a state variable is the
   right tool.

6. **`||` and `&&` short-circuit.** This is not just an optimisation — it is a
   correctness guarantee you can rely on (e.g., checking for null before dereferencing).

7. **`==` for comparison, `=` for assignment.** C won't warn you when you use the
   wrong one in a condition. Burn this into muscle memory.

8. **Chained assignment `nl = nw = nc = 0`** works because assignment is a right-to-left
   expression with a value — not a special syntax feature.

9. **Extending a state machine costs almost nothing.** Exercise 1-12 added printing
   behaviour by layering two `putchar` calls onto the existing word-counter skeleton —
   the state logic itself was untouched.

---

## 11. Self-Test Q&A

Use these to quiz yourself during revision. Cover the right column, read the question, answer aloud, then check.

---

### I/O Fundamentals

**Q1: Why must `c` be declared `int` and not `char` when used with `getchar()`?**
> `getchar()` returns `EOF` (typically `–1`) in addition to valid character values (0–255).
> On machines where `char` is `unsigned`, it cannot represent `–1` — it wraps to `255`, a
> valid character, so the loop never terminates. `int` is always signed and wide enough to
> hold both EOF and all char values safely.

---

**Q2: What does `getchar()` return, and what type is it?**
> It returns the next character from standard input as an `int`. When there is no more input,
> it returns `EOF` (an integer constant defined in `<stdio.h>`, typically `–1`).

---

**Q3: What does `putchar(c)` do?**
> It writes the character whose integer value is `c` to standard output and returns the
> character written (or EOF on error).

---

### Precedence & Expressions

**Q4: What is wrong with `while (c = getchar() != EOF)`? What does it actually do?**
> `!=` has higher precedence than `=`, so it parses as `c = (getchar() != EOF)`.
> `c` receives `0` or `1` (the boolean result of the comparison), not the character.
> The fix is `while ((c = getchar()) != EOF)` — parentheses force the assignment first.

---

**Q5: What is `EOF` and where is it defined?**
> `EOF` is a symbolic integer constant defined in `<stdio.h>`, typically `–1`. The specific
> value doesn't matter — what matters is that it is guaranteed to be outside the range of
> valid `char` values, so it can never be confused with real input data.

---

**Q6: What is the difference between `'\n'` (single quotes) and `"\n"` (double quotes)?**
> `'\n'` is a **character constant** — a single integer value (10 in ASCII).
> `"\n"` is a **string constant** — an array of two bytes: the newline byte and a null
> terminator `'\0'`. They are different types and not interchangeable.

---

**Q7: What does `c == '\n'` test, and what would `c = '\n'` do instead?**
> `c == '\n'` tests whether `c` equals the newline character (equality, returns 0 or 1).
> `c = '\n'` *assigns* the newline value (10) to `c` — always "true" as a condition (10 ≠ 0),
> creating an infinite or always-true branch. C will not warn you.

---

### Operators & Counting

**Q8: What is the difference between `++nc` and `nc++`?**
> Both increment `nc` by 1. The difference is the *value of the expression*:
> `++nc` (prefix) gives the value *after* incrementing;
> `nc++` (postfix) gives the value *before* incrementing.
> As a standalone statement (`++nc;`) they are identical.

---

**Q9: Why does the character-counting program use `long nc` instead of `int nc`?**
> On older or 16-bit machines, `int` may be only 16 bits (max 32 767). A file with more
> than 32 767 characters would overflow it. `long` is guaranteed to be at least 32 bits,
> supporting counts up to ~2 billion. `%ld` is the corresponding `printf` format specifier.

---

**Q10: What is a null statement in C and when is it used?**
> A null statement is a lone semicolon (`;`). It satisfies C's grammar requirement that
> control structures (like `for`) must have a body, when all the work is done in the
> header. It should be placed on its own line to signal it is intentional, not a typo.

---

### State Machines

**Q11: In the word-counter, when exactly does `++nw` fire? Why not on every character inside a word?**
> `++nw` fires only on the **OUT → IN transition** — the moment the first non-whitespace
> character is seen after whitespace. If it fired on every character inside a word, it would
> count letters, not words. The `else if (state == OUT)` guard ensures it fires exactly once
> per word regardless of length.

---

**Q12: Why is `state` initialised to `OUT` before the loop?**
> Because the program starts before reading any input — it is "not inside a word" by
> definition. If `state` started as `IN`, the first non-whitespace character would not
> trigger `++nw` (since the `else if (state == OUT)` guard would be false), and the
> first word would go uncounted.

---

**Q13: What does `||` do, and what does "short-circuit evaluation" mean?**
> `||` is the logical OR operator — the whole expression is true if *at least one* operand
> is true. Short-circuit means: if the left operand is already `true`, the right operand
> is **not evaluated at all** — the result is already determined. This matters for
> correctness when the right side has a side-effect or could cause an error (e.g., division
> by zero, dereferencing a null pointer).

---

**Q14: What does `nl = nw = nc = 0` mean? Why does it work?**
> Assignment in C is an expression whose value is the assigned value, and it associates
> right-to-left. So this is `nl = (nw = (nc = 0))`: `nc` is set to `0`, that expression
> has value `0`, which is assigned to `nw`, and so on. It is not special syntax — it is
> a direct consequence of assignments being expressions.

---

### Exercise 1-12

**Q15: In your Exercise 1-12 solution, why is `if (state == IN) putchar(c)` a separate `if` and not an `else`?**
> If it were an `else`, it would only fire when Block A's condition was false (i.e., on
> non-whitespace) — but at that point `state` may have *just been updated* to `IN` by
> the `else if` branch. Because Block B is a separate `if`, it runs after Block A has
> finished updating `state`, so the very first character of a new word is correctly printed.

---

**Q16: What is the edge-case limitation of the Exercise 1-12 solution, and how would you fix it?**
> Multiple consecutive spaces each trigger `putchar('\n')`, producing blank lines between words.
> The fix: only emit `'\n'` on the first whitespace after a word (the IN → OUT transition):
> ```c
> if (c == ' ' || c == '\t' || c == '\n') {
>     if (state == IN)
>         putchar('\n');
>     state = OUT;
> }
> ```
> This guards the `putchar('\n')` with `state == IN`, so it fires exactly once per word boundary.

---

## 12. Connection With Other Notes

- [[for-statement]] — the `for` loop used in character-counting version 2; null statement.
- [[order-of-operations]] — why `(c = getchar()) != EOF` needs the parens; `||`/`&&` precedence.
- [[c-numeric-encoding]] — why `char` may be unsigned and cannot hold EOF; `int` layout.
- [[symbolic-constants]] — `#define IN 1` / `#define OUT 0` pattern from §1.4.
- [[printf-format-cheatsheet]] — `%ld` for `long`, `%.0f` for `double` with no decimals.

- [[for-statement]] — the `for` loop used in character-counting version 2; null statement.
- [[order-of-operations]] — why `(c = getchar()) != EOF` needs the parens; `||`/`&&` precedence.
- [[c-numeric-encoding]] — why `char` may be unsigned and cannot hold EOF; `int` layout.
- [[symbolic-constants]] — `#define IN 1` / `#define OUT 0` pattern from §1.4.
- [[printf-format-cheatsheet]] — `%ld` for `long`, `%.0f` for `double` with no decimals.
