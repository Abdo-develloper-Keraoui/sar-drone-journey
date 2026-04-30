# Understanding Numeric Types: K&R, GCC, and My Casio Calculator

## 1. What K&R Says

> The type **`int`** means that the variables listed are integers; by contrast with **`float`**, which means floating point, i.e., numbers that may have a fractional part. The range of both `int` and `float` depends on the machine you are using; 16-bit `int`s, which lie between -32768 and +32767, are common, as are 32-bit `int`s. A `float` number is typically a 32-bit quantity, with at least six significant digits and magnitude generally between about 10⁻³⁸ and 10³⁸.  
> C provides several other data types besides `int` and `float`, including:  
> `char` – a single byte  
> `short` – short integer  
> `long` – long integer  
> `double` – double-precision floating point  
> The size of these objects is also machine‑dependent.

---

## 2. My Machine’s Reality (GCC on x86_64, WSL)

The typical configuration today (GCC on 64‑bit Intel/AMD) gives us:

| Type     | Size (bytes) | Range (approx.)                         | Precision / significant digits |
|----------|--------------|-----------------------------------------|--------------------------------|
| `int`    | 4            | –2,147,483,648 … 2,147,483,647          | exact (integer)                |
| `float`  | 4            | ±1.2×10⁻³⁸ … ±3.4×10³⁸                  | 6–7 decimal digits (`FLT_DIG=6`) |
| `double` | 8            | ±2.2×10⁻³⁰⁸ … ±1.8×10³⁰⁸                | 15–16 decimal digits (`DBL_DIG=15`) |
| `char`   | 1            | –128 … 127 (or 0…255 if `unsigned`)     | —                              |
| `short`  | 2            | –32,768 … 32,767                        | —                              |
| `long`   | 8 (LP64)     | –9.2×10¹⁸ … 9.2×10¹⁸                    | —                              |

*This follows the IEEE 754 floating‑point standard and the LP64 data model (normal on 64‑bit Linux/WSL).*

### 2.1 Proof – run this program

```c
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
    printf("Sizes (bytes):\n");
    printf("  char      : %zu\n", sizeof(char));
    printf("  short     : %zu\n", sizeof(short));
    printf("  int       : %zu\n", sizeof(int));
    printf("  long      : %zu\n", sizeof(long));
    printf("  float     : %zu\n", sizeof(float));
    printf("  double    : %zu\n\n", sizeof(double));

    printf("int range  : %d to %d\n", INT_MIN, INT_MAX);
    printf("float dig  : %d (decimal digits)\n", FLT_DIG);
    printf("float min>0: %e\n", FLT_MIN);
    printf("float max  : %e\n", FLT_MAX);
    printf("double dig : %d (decimal digits)\n", DBL_DIG);
    printf("double min>0: %e\n", DBL_MIN);
    printf("double max : %e\n", DBL_MAX);
    return 0;
}
```

### 2.2 My actual output

```bash
abdottawab@DESKTOP-PC405N0:~/projects/sar-drone-journey/month-01/sandbox$ gcc -Wall -o testTypesRanges testTypesRanges.c && ./testTypesRanges
Sizes (bytes):
  char      : 1
  short     : 2
  int       : 4
  long      : 8
  float     : 4
  double    : 8

int range  : -2147483648 to 2147483647
float dig  : 6 (decimal digits)
float min>0: 1.175494e-38
float max  : 3.402823e+38
double dig : 15 (decimal digits)
double min>0: 2.225074e-308
double max : 1.797693e+308
```

This is exactly the “typical machine” K&R described: 32‑bit `int`, 32‑bit `float` with 6‑digit precision, and 64‑bit `double`.

---

## 3. How Each Type is Encoded & Decoded

### 3.1 Integer types (`char`, `short`, `int`, `long`)

**Encoding: Two’s complement**
- Positive numbers are stored as normal binary, left‑padded with zeros.
- Negative numbers: take the positive magnitude, flip all bits, then add 1.
- The most significant bit (MSB) acts as the **sign bit** – `0` for positive, `1` for negative.

**Example: `int` (4 bytes = 32 bits)**
- `0`   → `00000000 00000000 00000000 00000000` (hex `00 00 00 00`)
- `1`   → `00000000 00000000 00000000 00000001` (hex `01 00 00 00` little‑endian)
- `-1`  → `11111111 11111111 11111111 11111111` (hex `FF FF FF FF`)

**Byte order: Little‑endian (x86)**
The least significant byte comes at the lowest memory address.
Example: `int n = 0x12345678;` is stored as `78 56 34 12` in memory.

**`char`**  
A single byte. Usually interpreted as:
- A **signed** integer (−128 … 127) or
- An ASCII character: `'A'` = 65 (0x41), `'a'` = 97 (0x61), `'0'` = 48 (0x30).

*Decoding*: The CPU simply reads the two’s complement value and treats it as a signed integer, or maps the byte to a glyph via the ASCII table.

### 3.2 Floating‑point types (`float` and `double`)

**Encoding: IEEE 754**
- `float` (32 bits): 1 sign bit | 8 exponent bits | 23 fraction (mantissa) bits
- `double` (64 bits): 1 sign bit | 11 exponent bits | 52 fraction bits

The value is:  
`(-1)^sign × (1.fraction) × 2^(exponent - bias)`
(For normalised numbers; subnormals handle the very smallest values.)

**Decoding a `float` example**  
Suppose we have the 32‑bit pattern `0x3F800000` (stored little‑endian as `00 00 80 3F`):
- Binary: `0  01111111  00000000000000000000000`
- Sign = 0 → positive
- Exponent = 127 → subtract bias (127) → 0
- Fraction = 0 → implied leading 1 gives `1.0`
- Result: `1.0 × 2⁰ = 1.0`

**Precision implications**
- `float` only stores 23 bits of fraction → about 6‑7 reliable decimal digits.
- `double` with 52 fraction bits gives 15‑16 reliable decimal digits.
- Values like `0.1` cannot be represented exactly in binary, leading to tiny rounding errors: `0.1` in IEEE 754 `float` is actually `0.100000001490116119384765625`. This is why `0.1 + 0.2 != 0.3` in many languages.

**Range from the output**
- `float min>0` = 1.175494×10⁻³⁸ is the smallest **normal** positive float.
- `float max` = 3.402823×10³⁸ is the largest finite value.
- `double` dramatically extends both ends (≈10⁻³⁰⁸ to 10³⁰⁸).

> All floating‑point constants in C source code are `double` by default (e.g., `0.1` is a `double`). Use `f` suffix (`0.1f`) for `float`.

### 3.3 Quick visualisation: peek inside memory

```c
#include <stdio.h>
int main() {
    int n = -1;
    float f = 1.0f;
    printf("int -1 bytes: ");
    for (size_t i = 0; i < sizeof(n); i++)
        printf("%02x ", ((unsigned char*)&n)[i]);
    printf("\nfloat 1.0 bytes: ");
    for (size_t i = 0; i < sizeof(f); i++)
        printf("%02x ", ((unsigned char*)&f)[i]);
    printf("\n");
    return 0;
}
```
Output on my WSL/GCC:
```
int -1 bytes: ff ff ff ff 
float 1.0 bytes: 00 00 80 3f
```

---

## 4. Sidenote: My Casio fx‑991 ES Plus

### 🖩 Casio fx‑991 ES Plus – Number System & Precision  

The calculator uses a **decimal‑native** system internally, likely **Binary‑Coded Decimal (BCD)**. It does **not** use IEEE 754 binary floating‑point.

- **Internal precision:** 15 significant digits (all calculations are performed with 15‑digit accuracy).  
- **Display format:** “10 + 2 digits” – a 10‑digit mantissa and a 2‑digit exponent (range 10⁻⁹⁹ to 10⁹⁹).  
- **Accuracy:** typically ±1 at the 10th digit for a single operation; errors can accumulate in long chains of calculations.  
- **Standard mode (Norm):** numbers are shown in scientific notation with exactly 10 digits in the mantissa.

#### “Décodage des nombres” – How the display encoding works

In Norm mode, a number is shown as:  
`s.mmmmmmmmm × 10ᵉᵉ`  
where `s` is the sign, `m` is a 10‑digit mantissa (one integer digit + nine decimals), and `ee` is a 2‑digit exponent (±99).  
Examples:
- `1234567890` → `1.234567890 × 10⁹`
- `0.0000000001` → `1.000000000 × 10⁻¹⁰`

In **Fix** or **Sci** modes you choose fewer decimal places, but the internal 15‑digit value is unchanged – only the display is rounded.

#### Comparison with GCC’s binary floats

| Feature | Casio fx‑991 ES Plus | GCC `float` (IEEE 754) | GCC `double` (IEEE 754) |
|---------|----------------------|---------------------------|----------------------------|
| Number base | **Decimal (BCD)** | Binary | Binary |
| Internal precision | **15 decimal digits** | 6–7 decimal digits | 15–16 decimal digits |
| Display precision | 10‑digit mantissa | (depends on printing) | (depends on printing) |
| Exponent range | 10⁻⁹⁹ to 10⁹⁹ | 10⁻³⁸ to 10³⁸ | 10⁻³⁰⁸ to 10³⁰⁸ |
| Exact decimal fractions? | Yes (e.g., 0.1 exactly) | No – small binary rounding error | No – tiny binary rounding error |

The Casio’s **internal** precision actually matches a `double`, but because it works in decimal (BCD), it completely avoids the binary‑fraction artefacts that plague IEEE 754 when dealing with everyday decimal numbers.

---

## 5. Summary

- K&R’s “typical” machine matches my modern 64‑bit Linux/GCC environment: **4‑byte `int`, 4‑byte `float` (6‑7 digits), 8‑byte `double` (15‑16 digits)**.
- Integers are stored in **two’s complement** (little‑endian on x86), characters are ASCII bytes.
- Floating‑point numbers follow **IEEE 754**: a sign‑exponent‑fraction layout that gives the cited ranges and precisions, but introduces tiny conversion errors for decimal fractions.
- My Casio fx‑991 ES Plus uses **decimal (BCD) arithmetic** internally with 15‑digit precision, giving it `double`‑like accuracy without base‑conversion quirks – a perfect companion when I want exact decimal handling.









## Deriving Range & Precision from the Encoding

### `int` (4 bytes, two’s complement)

- 4 bytes = 32 bits.
- **Range formula** for two’s complement:  
  - **Max** = \( 2^{N-1} - 1 \) (all bits 1 except the sign bit)  
  - **Min** = \( -2^{N-1} \) (sign bit 1, all others 0)
- With \( N = 32 \):  
  - Max = \( 2^{31} - 1 = 2,\!147,\!483,\!647 \)  
  - Min = \( -2^{31} = -2,\!147,\!483,\!648 \)

That’s exactly what `INT_MAX` and `INT_MIN` reported.

### `float` (4 bytes, IEEE 754 single precision)

Layout: 1 sign bit | 8 exponent bits | 23 fraction (mantissa) bits.

- **Exponent bias** = \( 2^{8-1} - 1 = 127 \).  
- **Normalised value** = \( (-1)^{\text{sign}} \times (1.\text{fraction}) \times 2^{\text{exponent} - 127} \).

#### Maximum finite value
- Largest exponent (not reserved) = 254 (bits 11111110). Reserved 255 is for infinity/NaN.
- Largest fraction = all 1s (23 bits) → significand = \( 1.\underbrace{11\ldots1}_{23} = 2 - 2^{-23} \).
- Max = \( (2 - 2^{-23}) \times 2^{127} \approx 3.4028235 \times 10^{38} \).

#### Minimum positive normal value
- Smallest exponent for normal numbers = 1 (bits 00000001).
- Smallest fraction = 0 → significand = 1.0.
- Min positive normal = \( 1.0 \times 2^{1 - 127} = 2^{-126} \approx 1.175494 \times 10^{-38} \).

> Subnormals allow even smaller values (down to \( 2^{-149} \approx 1.4\times10^{-45} \)), but `FLT_MIN` reports the smallest **normal**.

#### Decimal precision
- With 23 fraction bits + implicit leading 1, we have 24 bits of precision → \( \log_{10}(2^{24}) \approx 7.22 \) decimal digits.
- The standard guarantees **6** safe decimal digits (`FLT_DIG = 6`).

### `double` (8 bytes, IEEE 754 double precision)

Layout: 1 sign bit | 11 exponent bits | 52 fraction bits.

- **Exponent bias** = \( 2^{11-1} - 1 = 1023 \).
- Value = \( (-1)^{\text{sign}} \times (1.\text{fraction}) \times 2^{\text{exponent} - 1023} \).

#### Maximum finite value
- Largest exponent = 2046 (bits 11111111110).
- Largest fraction = all 1s (52 bits) → significand = \( 2 - 2^{-52} \).
- Max = \( (2 - 2^{-52}) \times 2^{1023} \approx 1.7976931348623157 \times 10^{308} \).

#### Minimum positive normal value
- Smallest normal exponent = 1, fraction = 0.
- Min normal = \( 2^{-1022} \approx 2.2250738585072014 \times 10^{-308} \).

#### Decimal precision
- 53 bits of precision (52 explicit + 1 implicit) → \( \log_{10}(2^{53}) \approx 15.95 \) decimal digits.
- Guarantees **15** safe digits (`DBL_DIG = 15`).

### 🖩 Casio fx-991 ES Plus (decimal BCD)

- **Internal precision**: 15 decimal digits.
- **Display**: 10‑digit mantissa + 2‑digit exponent.
- **Exponent range**: \( 10^{-99} \) to \( 10^{99} \).
- Since it’s decimal (BCD), it does **not** use IEEE 754 binary floating‑point. The range and precision are fixed by design:
  - **Precision** is exactly 15 digits (no binary‑conversion quirks).
  - **Extremes** are simply the limits of the 2‑digit exponent: min = \( 1\times10^{-99} \), max = \( 9.999999999\times10^{99} \).

**Comparing self‑derived values with the actual output** – the numbers we calculated from first principles exactly match the `FLT_MIN`, `FLT_MAX`, `DBL_MIN`, `DBL_MAX` your program printed (within rounding of the printf `%e` format).
