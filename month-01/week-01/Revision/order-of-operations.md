# Understanding Order of operations and truncation and stuff 

## 1. What K&R Says about order of operation in C and programming in general ? for ints
> Most of the work gets done in the body of the loop. The Celsius temperature is computed and
> assigned to the variable celsius by the statement
> celsius = 5 * (fahr-32) / 9;
> The reason for multiplying by 5 and dividing by 9 instead of just multiplying by 5/9 is that in
> C, as in many other languages, integer division truncates: any fractional part is discarded.
> Since 5 and 9 are integers. 5/9 would be truncated to zero and so all the Celsius temperatures
> would be reported as zero

---

### My understanding of the order of operations and truncation for integer calculation

The formula `celsius = 5 * (fahr-32) / 9` uses integer arithmetic deliberately.
Multiplication and division have equal precedence and group left to right,
so the expression is evaluated as:

    celsius = ( 5 * (fahr - 32) ) / 9;

The multiplication comes **first**. This is essential because if we instead wrote:

    celsius = (5 / 9) * (fahr - 32);   // wrong!

then `5 / 9` would be computed **first** as an integer division. Since `5` and `9`
are both integers, integer division truncates (discards the fractional part).
`5 / 9` truncates to `0`, and the whole result would be `0` for any temperature.

By multiplying `5` by `(fahr - 32)` before dividing by `9`, we keep the
intermediate value large enough that the final truncation only removes a small
fraction (less than `1` degree), giving a correct integer conversion.

**Takeaway:** In integer arithmetic, always multiply before dividing to
preserve magnitude and avoid premature truncation to zero.




