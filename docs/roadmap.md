# Roadmap

## Phase 0: Make Wokwi and GitHub the same firmware (do first)
- [ ] Paste `wokwi/sketch.ino` (v1.1) into the Wokwi project, run, **Save** (see `wokwi/README.md`)
- [x] `wokwi/diagram.json` is the original tested circuit

## Phase 1: Finish simulation
- [ ] Re-run Wokwi with the updated firmware and capture Serial Monitor output for all three modes (screenshots into `docs/img/`)
- [ ] Test each mode at its caution and danger boundaries (INDOOR 80/30, OUTDOOR 150/60, CROWDED 60/25)
- [ ] UFFL runs per `docs/uffl-test-protocol.md`; save the log
- [ ] Add CSV logging and plot gain vs time with Python

## Phase 2: 3D-printed enclosure
- [ ] Wrist/armband housing: start from `hardware/enclosure_v1.scad` (or rebuild in Tinkercad with the same dimensions). Front sensor on the end face, left/right on the long sides
- [ ] Export `.stl` files into `hardware/`, add renders. Decide final dimensions (see `hardware/README.md` size note)
- [ ] Document mounting angles and why you chose them

## Phase 3: Physical prototype
- [ ] Bill of materials in `hardware/BOM.md` with real costs (supports the "low-cost" claim)
- [ ] Breadboard test with real HC-SR04s. HC-SR04 is a 5 V part, so put a voltage divider (1k/2k) on each ECHO line going into the ESP32 (3.3 V)
- [ ] Replace LEDs with coin vibration motors, each driven by an NPN transistor (2N2222) + 1k base resistor + flyback diode (1N4148)
- [ ] Power from a single-cell Li-ion with TP4056 charger and regulator; measure current draw and estimate battery life

## Phase 4: Evaluation
- [ ] Measure accuracy at 20/50/100/200 cm against a tape measure (mean error, plot)
- [ ] Measure latency from obstacle to feedback
- [ ] Obstacle-course trial with supervised volunteers and consent, UFFL on vs off
- [ ] Write a short results report (PDF) and link it in the README

## Phase 5: Connect to research
- [ ] Link to the Woosong University paper once published (only reference what your mentor has approved for public sharing)
