# K&R §1.4 – Symbolic Constants (`#define`)

## 1. What K&R Says

> It's bad practice to bury "magic numbers" like 300 and 20 in a program; they convey little
> information to someone who might have to read the program later, and they are hard to change
> in a systematic way.
>
> `#define name replacement_text`
>
> Thereafter, any occurrence of `name` will be replaced by the corresponding replacement text.

```c
#include <stdio.h>

#define LOWER  0    /* lower limit of table */
#define UPPER  300  /* upper limit          */
#define STEP   20   /* step size            */

main()
{
    int fahr;
    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}
```

---

## 2. What `#define` Actually Does

`#define` is a **preprocessor directive** — it runs *before* the compiler. It does one thing:
**text substitution**. Every occurrence of `UPPER` in your source is swapped for `300` before
GCC ever sees the file. No variable is created, no memory is used, no type is assigned.

```
You write:              Compiler sees:
fahr <= UPPER     →     fahr <= 300
fahr + STEP       →     fahr + 20
```

---

## 3. Three Syntax Rules — The Easy Traps

```c
#define UPPER 300      // ✔ correct

#define UPPER 300;     // ✗ semicolon becomes part of the replacement text → breaks everything
#define UPPER = 300    // ✗ the = becomes part of the replacement text → breaks everything
int UPPER = 300;       // ✗ that's a variable, not a symbolic constant
```

**No semicolon. No equals sign. No type.** Memorise these three.

---

## 4. Naming Convention

ALL_CAPS for constants, lowercase for variables — always.

```c
int fahr;            // variable  → can change
#define UPPER 300    // constant  → never changes
```

Not enforced by the compiler. Universally followed in practice.

---

## 5. Why Bother? The Two Benefits

**Readability:** `UPPER` tells you *what*, `300` tells you *nothing*.  
**Maintainability:** change the limit once at the `#define`, not in every place `300` appears.

---

## 6. `#define` vs Variable — One Line

| | `#define UPPER 300` | `int upper = 300` |
|---|---|---|
| Memory used? | No | Yes |
| Has a type? | No | Yes (`int`) |
| Can change at runtime? | No | Yes |
| Visible in debugger? | No | Yes |

> Modern C also offers `const int UPPER = 300;` — typed, debuggable, same intent.
> K&R doesn't use it but you'll see it in real codebases.

---

## 7. Links to Other Notes

- [[for-statement-kr-1-3]] — the `for` loop body is unchanged; `#define` only changes where
  the constants come from.
- [[order-of-operations]] — `STEP`, `LOWER`, `UPPER` are `int` literals after substitution;
  integer truncation rules still apply.
- [[c-numeric-encoding]] — `#define` constants have no type; the replacement text inherits
  its type from context (`300` → `int`, `5.0` → `double`).

---

## 8. Self-Test — Active Recall Questions

Try to answer these **without looking above**. Check yourself after.

---

**Q1.** Write a `#define` for a step size of 20. Now write it *wrong* in three different ways
(the three common syntax traps).

<details>
<summary>Answer</summary>

```c
// Correct
#define STEP 20

// Wrong 1 – semicolon
#define STEP 20;

// Wrong 2 – equals sign
#define STEP = 20

// Wrong 3 – declared like a variable
int STEP = 20;
```
</details>

---

**Q2.** When does `#define` substitution happen — before or after compilation? What does that
mean for memory and types?

<details>
<summary>Answer</summary>

Before compilation — the **preprocessor** does a text find-and-replace. By the time the
compiler runs, the name is already gone. So: no memory allocated, no type assigned.
</details>

---

**Q3.** What are the two concrete benefits of using `#define` instead of magic numbers?

<details>
<summary>Answer</summary>

1. **Readability** — a name like `UPPER` conveys meaning; `300` alone does not.  
2. **Maintainability** — change the value once at the `#define` and it updates everywhere.
</details>

---

**Q4.** Why do symbolic constant names use ALL_CAPS?

<details>
<summary>Answer</summary>

Convention only (not enforced by the compiler). It lets a reader instantly distinguish
constants (`UPPER`) from variables (`fahr`).
</details>

---

**Q5.** What is the key practical difference between `#define UPPER 300` and
`const int upper = 300`?

<details>
<summary>Answer</summary>

`#define` has no type and no memory — it's gone after preprocessing.  
`const int` has a type (`int`), lives in memory, and is visible in the debugger.  
Both prevent the value from being changed at runtime.
</details>

---

**Q6.** Spot the bug — what does the compiler actually see after preprocessing?

```c
#define LIMIT 100;

if (x < LIMIT)
    printf("ok\n");
```

<details>
<summary>Answer</summary>

The compiler sees:

```c
if (x < 100;)       // syntax error — the semicolon is part of the replacement text
    printf("ok\n");
```

This is why there must be **no semicolon** after the replacement text in a `#define`.
</details>
