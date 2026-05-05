# Month 1 
## Week 1
### Day 1 — [29/04/2026]

**Studied:** Khan Academy Algebra 1 Units 1, 2, and 3. K&R Chapter 1 — read the 
intro and did the first two exercises. Spent more time than expected on the 
.gitignore setup.

**Done:**
- ALG-01 done. Was mostly review, went straight to the test, passed.
- ALG-02 done. Same story — a bit rusty on compound inequalities but nothing 
  that slowed me down.
- ALG-03 done. Dimensional analysis. Straightforward, good reminder that units 
  matter — will matter more later with sensor data.
- First two K&R exercises done. hello world runs. That's the start.

**Confused by:**
- The .gitignore. On WSL the compiled binaries have no extension — no `.o`, 
  nothing, just a bare binary filename. The usual `*.o` rule doesn't catch them. 
  Ended up ignoring everything inside all the months and  weeks folders and then un-ignoring 
  only `.c`, `.h`, and `.md` explicitly. Works, but took longer than it should.
- Still figuring out how to actually use K&R properly — not just read and copy 
  but actually close the book and write from memory. Haven't fully switched to 
  that method yet. Tomorrow I will.

**Tomorrow:** Section 1.2 — Fahrenheit table. Book closed before I touch the 
keyboard.


### Day 2 — [30/04/2026]

**Studied:** K&R Chapter 1, Section 1.2 — Fahrenheit/Celsius tables, integer and float versions. Exercises 1-3 and 1-4. Built revision notes on types, numeric encoding, and printf formatting. First real session using the closed-book method.

**Done:**
- `fahrenheit-int.c` — integer version. Learned why the formula must be `(5 * (fahr - 32)) / 9` and not `5/9 * (fahr - 32)`. Integer division truncates immediately — `5/9` is `0`, and everything downstream is garbage.
- `fahrenheit-float.c` — float version. `5.0/9.0` now gives a real fraction. Rewrote from memory as `fahrenheit-float-from-memory.c`. Blanked on the formula — used pen and paper first, then typed. Method worked.
- `ex01-03` — printed the Fahrenheit table in reverse (descending). `ex01-04` — reversed the table to go Celsius → Fahrenheit with a custom step and range.
- Wrote four revision docs: numeric encoding, printf cheatsheet, order of operations, and a summary of the converter. Wrote the study method doc.
- Git workflow running cleanly: `git status` → `git add` → `git commit -m` → `git push`. No friction today, unlike the `.gitignore` struggle yesterday.

**Key things locked in:**
- `%6.1f` — the number *before* the dot is total field width, *after* the dot is decimal precision. Not the other way around. Column widths exist to align output cleanly.
- `&&` in bash means "only run the second command if the first succeeded." Using `;` instead would run the stale binary on a failed compile — a dangerous silent habit.
- `-Wall` tells gcc to surface all warnings, not just hard errors.
- `int` and `float` are both 4 bytes, but `int` uses all 32 bits for direct magnitude. `float` splits them into sign/exponent/mantissa (IEEE 754) — wider range, imprecise. `0.1` has no exact binary representation for the same reason `1/3` has no exact decimal one.
- The three things a `while` loop needs: initialize before, condition at the top, update inside. Miss any one and it either never runs or runs forever.
- Side observation: my Casio calculator uses BCD encoding instead of IEEE 754. It sacrifices range (only up to ~10^99 vs 10^308 for double) in exchange for exact decimal representation. That's why it doesn't have the `0.1 + 0.2 ≠ 0.3` problem.

**SAR drone connection:** IMU sensors output raw readings that need converting to m/s² and radians/s. GPS altitude can come in mixed units depending on the module. And the position estimation problem I half-remembered has a name — Kalman filter — a way of fusing noisy sensor readings using weighted probability to estimate true position. That's later, but today's unit conversion work is the foundation it sits on.

**Confused by / want to revisit:**
- printf format specifiers need more reps — the width/precision order was backwards in my head until corrected.
- Chapter 1 is denser than it looks. Need to keep moving through it before old concepts go cold.

**Tomorrow:** Section 1.3 — the `for` loop version of the Fahrenheit table. Book closed before keyboard. Pen and paper for the structure first.

### Day 3 — [05/05/2026]

**Studied:** Khan Academy Algebra 1 Unit 4 (linear equations). 

**Done:**
- ALG-04 done. did the whole quizzes and the final unit test, revisited the concepts of slope and linear equations

**Confused by:**
- first time I did english Masa2il, so i tried to understand the context and then i applied the formulas that I already knew. It was great success.


**Tomorrow:**. Book closed before keyboard. Pen and paper for the structure first.


 Section 1.5 — the `File copying` thingys.
