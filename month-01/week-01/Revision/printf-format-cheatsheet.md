## `printf` Format Specifiers – Quick Reference

### Width and Precision

| Specifier  | Meaning |
|------------|---------|
| `%f`       | Print as floating‑point (no width or precision constraints) |
| `%6f`      | At least **6 characters wide** |
| `%.2f`     | **2 characters after** the decimal point, width unconstrained |
| `%6.2f`    | At least 6 wide **and** exactly 2 after the decimal point |

*Width* and *precision* can be combined or omitted independently.  
If the number is narrower than the width, it is right‑justified (padded with spaces by default).  
If the number is wider, the width is ignored—the full value is printed.

### Common specifiers for integers

| Specifier  | Meaning |
|------------|---------|
| `%d`       | **Decimal** integer (signed) |
| `%6d`      | Decimal integer, at least 6 characters wide |
| `%i`       | Like `%d` (reads input as decimal, octal `0…`, or hex `0x…` with `scanf`, but in `printf` they are identical) |
| `%u`       | Unsigned decimal integer |
| `%o`       | **Octal** (base 8) |
| `%x`       | **Hexadecimal** (lower‑case), `%X` for upper‑case |
| `%ld`      | `long` decimal integer (`%lu`, `%lo`, `%lx` etc. for `long` variants) |

### Characters, strings, and the percent sign

| Specifier  | Meaning |
|------------|---------|
| `%c`       | Single **character** |
| `%s`       | **String** (null‑terminated) |
| `%%`       | A literal **percent sign** |

### Examples (for `printf`)

```c
printf("%%s:   [%s]\n",   "hello" );   // %s:   [hello]
printf("%%6s:  [%6s]\n",  "hi" );      // %6s:  [    hi]
printf("%%c:   [%c]\n",   'A' );       // %c:   [A]
printf("%%d:   [%d]\n",   42 );         // %d:   [42]
printf("%%6d:  [%6d]\n",  42 );         // %6d:  [    42]
printf("%%f:   [%f]\n",   3.14159 );    // %f:   [3.141590]
printf("%%6.2f:[%6.2f]\n",3.14159 );    // %6.2f:[  3.14]
printf("%%.2f: [%.2f]\n", 3.14159 );    // %.2f: [3.14]
printf("%%o:   [%o]\n",   255 );        // %o:   [377]
printf("%%x:   [%x]\n",   255 );        // %x:   [ff]
printf("%%X:   [%X]\n",   255 );        // %X:   [FF]
printf("%%%%:  [%%]\n");                // %%:   [%]
```

### How to remember

- `%` starts the specifier.
- Optional width (minimum characters) comes first.
- Optional `.precision` comes next (decimal places for `%f`, max characters for `%s`).
- A mandatory conversion letter follows (`d`, `f`, `s`, etc.).
- Everything else is just literal text.
