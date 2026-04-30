## The problem I've had

I was  treating the book like a script to copy. Eyes on page, hands on keyboard, code appears. But nothing is going through my thick skull and brain in between. That's why it feels like hand-copying — because it is.

The fix is to put friction between reading and typing. My hands should never touch the keyboard while my eyes are on the book.

---

## The method, step by step

### 1 — Read the whole section first, no keyboard

Open K&R. Read the section — say, the Fahrenheit table in 1.2. Read it slowly. Read the code too, but just read it, don't type it. When you hit something you don't understand, stop and reread that sentence. Don't move on until you can say out loud in plain Arabic or English what that line is doing.

### 2 — Close the book. Actually close it.

Face down on the desk (or tab down). This is not optional. As long as the book is open your brain knows it can look, so it won't bother remembering anything.

### 3 — Write what you remember

Now open the editor and write as much of the program as you can from memory. You will get stuck. That's the point — where you get stuck is exactly where you don't understand yet. Don't open the book yet. Sit with the confusion for a minute and think about what you're missing.

### 4 — Check, don't copy

Open the book again. Find only the part you were stuck on. Read it, understand why it works, close the book again. Fix your code from memory. Repeat until the program compiles and runs correctly.

### 5 — Do the exercises the same way

Read the exercise. Close the book. Think on paper first — write in a notebook what the program needs to do, in steps, before touching the keyboard. Then code it. The notebook step forces your brain to plan instead of just react.

---

## What to do with something you don't understand at all

Some lines in K&R will make no sense on first read. When that happens:

1. Copy the confusing line into your daily log exactly as written
2. Write in plain language what you think it might be doing, even if you're wrong
3. Change one thing about it and recompile — see what breaks
4. Write in the log what you learned from breaking it

Breaking things deliberately is one of the fastest ways to understand C. The compiler's error messages are feedback on your mental model.

---

## What "understanding" actually means for a K&R exercise

You understand a piece of code when you can do all three of these:

- Explain what every line does in plain language out loud
- Predict what happens if you change one specific thing before running it
- Write it again from scratch tomorrow without looking

If you can't do those three things, you've read it but you haven't learned it yet. That's fine — go back and do the process again.

---

## Concretely for tonight

Take section 1.2 — the Fahrenheit table. Do this:

1. Read the whole section, every word, no keyboard
2. Close the book
3. Write the program from memory — get as far as you can
4. Compile it, read the errors, fix from memory
5. When it runs correctly, open the log and write two sentences: what the `while` loop is doing, and why `5.0/9.0` and not `5/9`

That log entry is the proof you actually learned it. The working program is just the side effect.
