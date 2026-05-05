# On Getting Sidetracked — And What To Do About It

## What actually happened today

I planned to do Section 1.3 — the `for` loop version of the Fahrenheit table. Instead I:

- Added `celsius-fahrenheit-float` in sandbox (another float converter variant)
- Wrote `floating-point-accumulation-pitfall.md`
- Downloaded and saved a research paper on floating point arithmetic
- Created `subCh-03` but didn't fill it

None of that is bad work. But none of it was the plan.

This is the pattern I need to understand and manage — not eliminate.

---

## Why it happens

When I'm learning C and I hit something interesting, my brain wants to pull the thread. I wrote a float converter, noticed something odd about precision, and suddenly I'm reading a paper written for computer scientists. That curiosity is genuinely good. It's the same instinct that will make me a good engineer.

The problem isn't the curiosity. The problem is that I have no system for *when* to follow it.

Without a system, every interesting thing becomes an immediate detour. And detours stack. By the end of a session I've touched six things and finished none of them.

---

## The real cost of unmanaged sidetracks

- I lose the thread of the main material. Chapter 1 of K&R has a shape — each section builds on the last. If I keep re-solidifying section 1.2 instead of moving to 1.3, I never build the full picture.
- I confuse *depth* with *progress*. Writing a fifth variant of the Fahrenheit converter feels productive. It is not progress on the project.
- I create a false sense of completion. The sandbox fills up, the revision folder grows, the tree looks impressive — but the chapter isn't done.

---

## The rule I'm setting for myself

**Finish the planned thing first. Fully. Then decide.**

This means:

1. At the start of each session I write one sentence: *"Today is done when I have completed X."* That sentence is the session goal. It doesn't change mid-session.
2. If something interesting comes up mid-session — a question, a pitfall, a tangent — I write it in a **parking lot** section at the bottom of my daily log. One line. I do not act on it until the session goal is complete.
3. After the session goal is done, I look at the parking lot. If something there is genuinely important, I do it now or schedule it for tomorrow. If it was just excitement, it usually looks less urgent 30 minutes later.

---

## The parking lot

At the bottom of each daily log entry I keep a section called **Parking Lot**. It looks like this:

```
**Parking lot (do not act on mid-session):**
- floating point accumulation — is this relevant to sensor fusion later?
- try the for loop version without initializing first, see what gcc says
```

That's it. Writing it down quiets the urge to chase it immediately. My brain trusts that it won't be lost.

---

## When a sidetrack is actually justified

Not every detour is waste. Some tangents are load-bearing — they fix a gap that would have caused problems later. The test is:

**Would skipping this now cause me to misunderstand something in the next section?**

If yes — do it, but timebox it. Set a limit of 20 minutes and write what I learned.

If no — park it.

The floating point paper I downloaded today? That's a "park it." I don't need IEEE 754 internals to understand the `for` loop. It's good material for later, maybe when I'm dealing with sensor data. I'll keep the file and come back to it then.

---

## What to do with the sandbox

The sandbox exists for one purpose: **quick experiments that answer a specific question I hit during the main work.** It is not a second workspace for building polished versions of things I already built.

If I find myself creating a new variant in the sandbox and I can't answer "what specific question does this answer?" — I stop and go back to the main task.

---

## In short

I am not trying to eliminate curiosity. I am trying to *sequence* it. The main path first, always. The interesting detour second, parked and scheduled, not chased in the moment.

The project is the SAR drone. Everything I do should be pulling toward that. When I'm not sure if a tangent is worth it, I ask: *does this make me a better builder of that system, right now, at this stage?* If not — park it.
