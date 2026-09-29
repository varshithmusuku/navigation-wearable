# Test Results

## A. Wokwi, ORIGINAL firmware (`firmware/original_tested/`), observed earlier
Simulation: https://wokwi.com/projects/474586122834940929

| Test | Input | Observed |
|---|---|---|
| Front sensor | 70 cm | Front LED ON |
| Front sensor | 50 cm | Front LED ON |
| Front sensor | 20 cm | Front LED ON + buzzer |
| Front sensor | 100 cm | Front LED OFF |
| Front sensor | 200 cm | Front LED OFF |
| Left sensor | 50 cm | Left LED ON |
| Right sensor | 50 cm | Right LED ON |
| All sensors | 200 cm | All outputs OFF |

Mode-button messages were not captured in the Serial Monitor.

## B. Wokwi, v1.1 firmware (`firmware/navigation_wearable/`): TO DO
| Test | Expected | Observed | Evidence file |
|---|---|---|---|
| Front 20 cm | Front LED + buzzer | | media/front-20cm.png |
| Left/Right 50 cm | Left/Right LED | | media/left-right-50cm.png |
| All 200 cm | All off | | media/all-200cm.png |
| One button press | INDOOR -> OUTDOOR, one message | | media/mode-outdoor.png |
| Button held | Only one change | | |
| Full cycle | INDOOR -> OUTDOOR -> CROWDED -> INDOOR | | media/mode-cycle.png |
| UFFL sparse / normal / rapid | 1.25 / 1.00 / 0.75 | | logs/uffl_run1.csv, media/uffl_gain_run1.png |

## C. Host-side logic test (PC): DONE
See [host-logic-test.md](host-logic-test.md). v1.1 logic behaves as designed in all six scenarios; the original
firmware showed two defects that v1.1 fixes. This is a logic test only.

## Not done
- Physical hardware tests (sensors, motors, battery, current draw)
- User trials
