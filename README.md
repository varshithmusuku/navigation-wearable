# Offline Navigation Wearable for the Visually Impaired

A low-cost, offline obstacle-awareness wearable concept built around an **ESP32** and **three HC-SR04 ultrasonic sensors**. The prototype provides directional feedback for obstacles detected in the **front, left, and right** directions and includes an adaptive-feedback concept called the **User-First Feedback Loop (UFFL)**.

**Form factor:** wrist/armband-mounted unit.

## Status

| Item | Status |
|---|---|
| Wokwi circuit | Complete and running |
| Front / left / right obstacle detection | Tested successfully in Wokwi |
| Front danger-zone alert | Tested successfully |
| Buzzer alert | Tested successfully |
| Mode switching | Functionally verified |
| Firmware v1.1 | Implemented with button and UFFL event fixes |
| Host-side firmware logic test | Passed |
| UFFL adaptive gain | Implemented and host-side logic verified |
| UFFL real measurement log | Not collected |
| Physical vibration motors | Not tested |
| Enclosure CAD | Parametric source, STL files, and renders included |
| Native Tinkercad cloud model | Not independently verified |
| Cost breakdown | BOM template ready; purchase prices not yet entered |
| Physical prototype | Not built |
| User trials | Not performed |

## Wokwi Simulation

Live Wokwi project:

**https://wokwi.com/projects/474586122834940929**

The Wokwi simulation contains:

- ESP32 DevKit
- 3 × HC-SR04 ultrasonic sensors
- Front / Left / Right directional feedback outputs
- Piezo buzzer
- Mode-selection pushbutton

In Wokwi, LEDs are used as visual proxies for the physical vibration outputs:

- **Red LED = Front**
- **Yellow LED = Left**
- **Green LED = Right**

## Features

- Three-direction ultrasonic obstacle sensing
- Independent front, left, and right feedback channels
- Feedback intensity increases as an obstacle gets closer
- Audible warning for a very close front obstacle
- Three environment profiles:
  - Indoor
  - Outdoor
  - Crowded
- One-button mode switching
- Offline core operation with no Wi-Fi or Bluetooth dependency
- UFFL adaptive-gain logic based on close-obstacle event timing

## Environment Modes

| Mode | Caution Distance | Danger Distance |
|---|---:|---:|
| INDOOR | 80 cm | 30 cm |
| OUTDOOR | 150 cm | 60 cm |
| CROWDED | 60 cm | 25 cm |

The selected mode changes the distance range at which directional feedback becomes active.

## UFFL — User-First Feedback Loop

The project includes an adaptive-feedback concept called the **User-First Feedback Loop (UFFL)**.

The firmware tracks the timing between close-obstacle events and uses the average interval to adjust feedback gain.

| Close-event timing | Adaptive Gain |
|---|---:|
| Rapid events, average interval < 0.8 s | 0.75 |
| Normal range | 1.00 |
| Sparse events, average interval > 3 s | 1.25 |

The adaptive-gain logic has been verified through the host-side logic test.

A real Wokwi data log, physical hardware measurement, and user trial have not been completed. UFFL is therefore documented as an implemented prototype mechanism rather than a user-validated result.

## Wokwi Test Results

The following core tests were performed during the Wokwi simulation.

### Test 1 — Front danger-zone detection

Configuration:

```text
FRONT = 20 cm
LEFT  = 200 cm
RIGHT = 200 cm
```

Observed:

- Front red LED ON
- Buzzer active
- Left and right feedback inactive

**Result: PASS**

### Test 2 — Left + Right directional detection

Configuration:

```text
FRONT = 200 cm
LEFT  = 50 cm
RIGHT = 50 cm
```

Observed:

- Front red LED OFF
- Left yellow LED ON
- Right green LED ON

**Result: PASS**

### Test 3 — Far-distance condition

Configuration:

```text
FRONT = 200 cm
LEFT  = 200 cm
RIGHT = 200 cm
```

Observed:

- Front red LED OFF
- Left yellow LED OFF
- Right green LED OFF

**Result: PASS**

### Test 4 — Mode switching

The mode button was functionally verified by observing mode-dependent feedback changes.

The intended cycle is:

```text
INDOOR → OUTDOOR → CROWDED → INDOOR
```

**Functional result: PASS**

A Serial Monitor screenshot showing the exact text `Mode switched to: OUTDOOR` was not captured.

## Pin Map — ESP32 DevKit

| Function | Pin |
|---|---|
| Front TRIG | D5 |
| Front ECHO | D18 |
| Left TRIG | D19 |
| Left ECHO | D21 |
| Right TRIG | D22 |
| Right ECHO | D23 |
| Front feedback | D25 |
| Left feedback | D26 |
| Right feedback | D27 |
| Buzzer | D32 |
| Mode button | D33 |

The mode button is connected to ground and uses the ESP32 internal pull-up.

## Simulation vs. Physical Hardware

The Wokwi simulation uses LEDs as **visual substitutes for directional vibration outputs**.

A physical implementation would use:

- Coin vibration motors
- NPN transistor driver stages
- Flyback diodes
- Appropriate base resistors
- Voltage-divider protection for the HC-SR04 ECHO signals
- Battery and charging circuitry

No physical vibration motors have been tested.

## Enclosure

The project uses a **wrist/armband-mounted enclosure concept**.

Current enclosure dimensions:

**100 × 50 × 22 mm**

The repository includes:

- Parametric enclosure source
- Base STL
- Lid STL
- Strap STL
- Enclosure renders

The enclosure was enlarged from the earlier 90 × 40 × 15 mm concept to provide additional space for the standard HC-SR04 modules and ESP32 hardware.

The repository contains the CAD/STL deliverables. A native Tinkercad cloud design was not independently verified.

## Bill of Materials

See:

[`hardware/BOM.md`](hardware/BOM.md)

The component list is documented, but actual purchase prices have not yet been entered. The final physical prototype cost is therefore not established.

## Repository Layout

```text
navigation-wearable/
│
├── README.md
├── LICENSE
├── .gitignore
│
├── firmware/
│   ├── original_tested/
│   │   └── original_tested.ino
│   └── navigation_wearable/
│       └── navigation_wearable.ino
│
├── wokwi/
│   ├── diagram.json
│   ├── sketch.ino
│   └── README.md
│
├── hardware/
│   ├── BOM.md
│   ├── enclosure_v1.scad
│   ├── enclosure_v1_base.stl
│   ├── enclosure_v1_lid.stl
│   ├── strap_v1.scad
│   ├── strap_v1.stl
│   └── renders/
│
├── media/
│   ├── front-20cm.png
│   ├── left-right-50cm.png
│   ├── all-200cm.png
│   └── README.md
│
├── docs/
│   ├── test-results.md
│   ├── host-logic-test.md
│   ├── uffl-test-protocol.md
│   ├── firmware-v1.1.diff
│   ├── roadmap.md
│   └── claims.md
│
├── tests/
│   └── host/
│
├── scripts/
│   └── plot_uffl.py
│
└── logs/
```

## Documentation

- [Test Results](docs/test-results.md)
- [Host Logic Test](docs/host-logic-test.md)
- [UFFL Test Protocol](docs/uffl-test-protocol.md)
- [Firmware v1.1 Changes](docs/firmware-v1.1.diff)
- [Roadmap](docs/roadmap.md)
- [Claims Guide](docs/claims.md)
- [Hardware Documentation](hardware/README.md)
- [Wokwi Documentation](wokwi/README.md)

## Limitations

- Ultrasonic sensors may miss some soft, angled, thin, or acoustically difficult obstacles.
- The system does not detect drop-offs or stairs going downward.
- LEDs in Wokwi are only visual proxies for physical vibration motors.
- No physical vibration motors have been tested.
- No battery or current-draw testing has been performed.
- No physical prototype has been built.
- No user trials have been performed.
- The system is not a certified mobility aid.

It is intended as an assistive prototype concept and should not be treated as a replacement for established mobility aids.

## Current Project Scope

This repository represents a **software, simulation, and enclosure-design prototype**.

### Completed

- ESP32 firmware
- Three-direction ultrasonic sensing
- Directional feedback logic
- Environment-specific alert profiles
- UFFL adaptive-gain implementation
- Wokwi simulation
- Core Wokwi testing
- Host-side firmware logic testing
- Enclosure CAD source
- STL deliverables
- Test and project documentation
- GitHub repository

### Future Work

- Physical electronics assembly
- Real vibration-motor validation
- Battery and power testing
- Hardware electrical validation
- UFFL measurement with real logged data
- Physical enclosure fit testing
- User evaluation

## Author

**Varshith Reddy Musuku**  
Hyderabad, India

UFFL was later extended in collaborative research.

## License

MIT License. See [LICENSE](LICENSE).
