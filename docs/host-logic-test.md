# Host-side logic test (PC, not Wokwi, not hardware)

`tests/host/` compiles the **real** `.ino` files on a PC against a stub Arduino API (fake clock, scripted
distances, scripted button) and reports what the UFFL and button logic do. Run: `sh tests/host/run_tests.sh`.
Raw output: [host-logic-test-output.txt](host-logic-test-output.txt).

What it proves: the C++ logic of each sketch. What it does NOT prove: Wokwi behaviour, sensor timing, PWM output, or anything physical.
Timing is quantised to the 60 ms loop.

| Scenario | Expected (design) | original_tested | v1.1 |
|---|---|---|---|
| Sparse events (~3.9 s apart) | gain 1.25 | ends at 1.00 | **1.25** |
| Rapid events (~0.36 s apart) | gain 0.75 | 0.75 | **0.75** |
| Normal events (~1.5 s apart) | gain 1.00 | ends at 0.75 | **1.00** |
| One obstacle held close 5 s | 1 event, gain stays 1.00 | 0.75 (bug) | **1.00** |
| Button held 1 s | 1 mode change | 3 changes (bug) | **1** |
| 3 short presses (180 ms each) | 3 mode changes | 0 (taps shorter than 250 ms ignored) | **3** |

## Findings in the original firmware
1. `recordCloseEvent()` ran on every loop iteration for every sensor inside the danger zone, so intervals were about 60 ms
   and `adaptiveGain` dropped to 0.75 whenever an obstacle simply stayed close. It did not measure event timing as intended.
2. The mode button fired repeatedly while held and ignored taps shorter than 250 ms.

v1.1 fixes both with minimal changes: see [firmware-v1.1.diff](firmware-v1.1.diff).
