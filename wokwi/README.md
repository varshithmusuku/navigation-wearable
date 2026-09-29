# Wokwi simulation

Live project: https://wokwi.com/projects/474586122834940929

Files
- `diagram.json`: **your original tested circuit, unchanged.**
- `sketch.ino`: copy of `firmware/navigation_wearable/navigation_wearable.ino` (v1.1).

## Current state
The live Wokwi link still runs the ORIGINAL sketch (`firmware/original_tested/original_tested.ino`), which is what the
earlier tests used. To make the link match this repo:
1. Open the project, replace the contents of `sketch.ino` with `wokwi/sketch.ino`, run it, then **Save**.
2. Re-run the checks in `docs/test-results.md` section B.
Until step 1 is done, describe the link as "original firmware".
