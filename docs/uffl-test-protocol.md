# UFFL measurement protocol (Wokwi)

Design rule (from the code): gain = 0.75 if the average interval between the last <=5 close events is < 800 ms,
1.25 if > 3000 ms, else 1.0. A "close event" = any sensor entering its mode's danger distance. Gain only changes when an event occurs.

1. Set `#define LOG_CSV 1` in the sketch (also in Wokwi `sketch.ino`). Mode INDOOR (danger = 30 cm). Start all sensors at 200 cm.
2. **Sparse (expect 1.25):** set FRONT to 20 cm for about 1 s, back to 200 cm, wait about 4 s. Repeat 4 times.
3. **Normal (expect 1.00):** reload/restart. Repeat the same but with about 1.5-2.5 s between events.
4. **Rapid (expect 0.75):** needs events under 0.8 s apart, which is hard to do by hand in Wokwi. Try dragging the distance
   slider down and up quickly. If you cannot reproduce it, write "not reproduced manually" in the results. The PC
   logic test (`docs/host-logic-test.md`) covers this case.
5. Copy the Serial Monitor output (with header line) to `logs/uffl_run1.csv`, then run
   `python3 scripts/plot_uffl.py logs/uffl_run1.csv` to create `media/uffl_gain_run1.png`.
6. Record what you actually observed in `docs/test-results.md`, even if it differs from the expected values.
