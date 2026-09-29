# Bill of Materials (physical prototype)

Fill the **Unit cost** column from your real receipts or product links, then the total.
The "low-cost" claim in the README is only valid once this table is filled with actual prices.

| # | Part | Qty | Unit cost (INR) | Line total | Source / link |
|---|---|---|---|---|---|
| 1 | ESP32 DevKit (30/38-pin) | 1 | | | |
| 2 | HC-SR04 ultrasonic sensor | 3 | | | |
| 3 | Coin vibration motor (3 V) | 3 | | | |
| 4 | NPN transistor 2N2222 / BC547 | 3 | | | |
| 5 | Diode 1N4148 (flyback) | 3 | | | |
| 6 | Resistor 1 kohm (transistor base) | 3 | | | |
| 7 | Resistors 1 kohm + 2 kohm (ECHO voltage dividers) | 3 + 3 | | | |
| 8 | Active buzzer | 1 | | | |
| 9 | Pushbutton 12 mm | 1 | | | |
| 10 | Li-ion cell (18650 or LiPo) + holder | 1 | | | |
| 11 | TP4056 charger module (with protection) | 1 | | | |
| 12 | 5 V boost module (HC-SR04 needs 5 V) | 1 | | | |
| 13 | 3D-printed enclosure (filament/print cost) | 1 | | | |
| 14 | Wire, screws (M2), strap | - | | | |
| | **TOTAL** | | | | |

Notes
- HC-SR04 ECHO outputs 5 V. Use a 1k/2k divider before each ESP32 input (about 3.3 V).
- Verify each part's voltage before wiring. Measure current draw and record it in `docs/`.
