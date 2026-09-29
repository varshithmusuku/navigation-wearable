# Offline Navigation Wearable for the Visually Impaired

A low-cost, offline obstacle-awareness wearable concept built around an ESP32 and three ultrasonic sensors.
It gives **directional** feedback (front / left / right) and includes an adaptive-feedback concept, the
**User-First Feedback Loop (UFFL)**. Form factor: **wrist/armband-mounted unit**.

## Status
| Item | State |
|---|---|
| Wokwi circuit (`wokwi/diagram.json`, original) and core detection tests | Done with the **original** firmware |
| Firmware v1.1 (button + UFFL event fixes) | Written; PC logic test passed; **Wokwi re-test pending** |
| UFFL adaptive gain | Implemented; logic verified on PC; **no Wokwi log or user trial yet** |
| Enclosure | Parametric source (`hardware/enclosure_v1.scad`); Tinkercad model, STL and renders pending |
| Cost breakdown | BOM template ready; prices pending |
| Physical prototype | Not built |

Wokwi: https://wokwi.com/projects/474586122834940929 (currently runs the original firmware, see [wokwi/README.md](wokwi/README.md))

## Features
- 3 x HC-SR04 sensors (front, left, right), each mapped to its own feedback output
- Feedback intensity scales with obstacle distance; buzzer for a front obstacle in the danger zone
- 3 environment modes selected with one button

| Mode | Caution | Danger |
|---|---|---|
| INDOOR | 80 cm | 30 cm |
| OUTDOOR | 150 cm | 60 cm |
| CROWDED | 60 cm | 25 cm |

- **UFFL:** close-obstacle events are timed and set an adaptive gain on feedback intensity:
  0.75 for rapid events, 1.0 normal, 1.25 for sparse events (thresholds: average interval < 0.8 s / > 3 s)
- Core operation needs no Wi-Fi or Bluetooth

## Pin map (ESP32 DevKit)
| Function | Pin | Function | Pin |
|---|---|---|---|
| Front TRIG / ECHO | D5 / D18 | Front feedback | D25 |
| Left TRIG / ECHO | D19 / D21 | Left feedback | D26 |
| Right TRIG / ECHO | D22 / D23 | Right feedback | D27 |
| Buzzer | D32 | Mode button | D33 (to GND, INPUT_PULLUP) |

**Simulation vs hardware:** in Wokwi, LEDs (Red = Front, Yellow = Left, Green = Right) are visual proxies for three
directional vibration outputs; no vibration motors have been tested. A physical build needs NPN transistor drivers with
flyback diodes, and 1k/2k voltage dividers on the 5 V HC-SR04 ECHO lines.

## Repository layout
```
firmware/original_tested/    sketch used for the earlier Wokwi tests (unchanged)
firmware/navigation_wearable/ v1.1 (original + 3 minimal fixes, see docs/firmware-v1.1.diff)
wokwi/       original diagram.json + sketch.ino (v1.1 copy)
tests/host/  PC logic test harness (run_tests.sh)
hardware/    enclosure source, BOM
scripts/     plot_uffl.py
logs/ media/ docs/
```

## Docs
[test-results](docs/test-results.md) | [host logic test](docs/host-logic-test.md) | [UFFL protocol](docs/uffl-test-protocol.md) |
[roadmap](docs/roadmap.md) | [claims guide](docs/claims.md)

## Limitations
- Ultrasonic sensors can miss soft, angled or thin obstacles and cannot detect drop-offs or stairs down
- Not a certified mobility aid; meant to supplement, not replace, a white cane or guide dog
- No user trials have been performed

## Author
Varshith Reddy Musuku, Hyderabad, India. UFFL was later extended in collaborative research at Woosong University.

## License
MIT. See [LICENSE](LICENSE).
