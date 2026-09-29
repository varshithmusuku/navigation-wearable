# Hardware

**Form factor: wrist/armband-mounted unit.** All documents use this consistently.

Files
- `enclosure_v1.scad`: parametric enclosure (base + lid). Export STL from OpenSCAD (free), then add `enclosure_v1_base.stl`, `enclosure_v1_lid.stl` and renders to this folder.
- `BOM.md`: parts and costs (fill in real prices).

## Size note
A first target of 90 x 40 x 15 mm does not physically fit this design:
- An HC-SR04's two transducers are 26 mm apart and 16 mm wide (about 42 mm total), which is wider than a 40 mm face.
- An ESP32 DevKit with headers, a Li-ion cell and wiring needs more than 15 mm of height.

v1 uses **100 x 50 x 22 mm** to keep the standard HC-SR04 sensors. To get smaller, use compact single-transducer ultrasonic modules and a smaller board. If you choose that, update `enclosure_v1.scad`, the README and your Tinkercad model together.

## Simulation vs hardware
- Wokwi uses LEDs as visual proxies for three directional vibration outputs.
- Real hardware needs transistor drivers with flyback diodes for the motors and 1k/2k dividers on each ECHO line.

## Generated CAD deliverables
- `enclosure_v1_base.stl`: printable enclosure base generated from `enclosure_v1.scad`.
- `enclosure_v1_lid.stl`: printable lid generated from `enclosure_v1.scad`.
- `strap_v1.stl`: curved armband strap segment for fit/form-factor prototyping.
- `renders/front.png`, `renders/angled.png`, `renders/back.png`: CAD renders for documentation.

These are CAD/OpenSCAD deliverables and are importable into Tinkercad. They are not native Tinkercad cloud-design screenshots.
