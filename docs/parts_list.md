# Draft parts list — T30 Fathi (M0)

Owner: Electronics lead. Status: **draft**. Prices are rough AliExpress
estimates in USD for planning only; replace each one with the real price and
supplier when ordered (the brief requires real prices in the bill of
materials). Budget limit: $200 total, donated parts at market value.

| # | Part | Qty | Why this part | Est. unit $ | Est. total $ | Supplier | Real price |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 1 | ESP32 DevKit V1 (ESP32-WROOM-32) | 1 (+1 spare) | Brief's recommended controller; hardware pulse counters (PCNT) for encoders | 5 | 10 | | |
| 2 | VL53L0X ToF breakout with XSHUT pin | 5 (+1 spare) | 1 front, 2 diagonal 45°, 2 side, as the M2 layout suggests; XSHUT needed to re-address on one I2C bus | 2.5 | 15 | | |
| 3 | N20 micro gear motor 6 V with magnetic quadrature encoder (~300–600 rpm) | 2 | Encoders required from M4; small enough for a 10 x 11 cm footprint | 7 | 14 | | |
| 4 | Wheels for N20 3 mm D-shaft, ~32–34 mm, rubber tyre | 2 | Grip on painted plywood floor | 2 | 4 | | |
| 5 | TB6612FNG dual motor driver | 1 (+1 spare) | Brief's recommendation; more efficient than L298N | 2 | 4 | | |
| 6 | 2S LiPo 7.4 V, 300–500 mAh, JST/XT30 | 2 | Swappable between runs; second pack charges while the first runs | 8 | 16 | | |
| 7 | 2S LiPo balance charger (e.g. B3/B6 class) | 1 | LiPos must be balance-charged | 12 | 12 | | |
| 8 | Mini buck converter (MP1584 or similar) set to 5 V → DevKit 5 V pin | 1 (+1 spare) | Keeps 8.4 V off the logic side; ESP32 board's own 3.3 V LDO then feeds ESP32 and sensors | 1.5 | 3 | | |
| 9 | MPU6050 gyro/accelerometer (optional) | 1 | Helps accurate turns (M6) | 2 | 2 | | |
| 10 | Ball caster / low-friction skid | 1–2 | Third contact point; low profile for 3–5 mm clearance | 1 | 2 | | |
| 11 | Power switch, 2 push buttons, 2 LEDs, buzzer | set | Start/mode buttons and status for the interface (M3) | 3 | 3 | | |
| 12 | Resistors for battery voltage divider into an ADC1 pin | set | Battery monitoring (M3) | 1 | 1 | | |
| 13 | Perfboard / prototype PCB, headers, JST connectors, wire | set | Wiring harness | 6 | 6 | | |
| 14 | M2/M3 screws and nuts | set | Mounting | 3 | 3 | | |
| 15 | PLA filament for chassis (market value if printed on campus) | ~100 g | 3D printed chassis (M2) | 3 | 3 | | |
| | **Estimated total** | | | | **~98** | | |

About $100 is left for breakages, reprints and replacement sensors.

## Decisions to check before ordering

- **Motor speed.** Faster N20s (1000 rpm) are quick but harder to control at
  low speed; ~300–600 rpm is a safer start. Confirm gear ratio and encoder
  counts per revolution on the listing (needed in M4).
- **Logic power.** Feed the DevKit's 5 V pin from the buck converter, never
  the battery directly, and keep motor power (battery → TB6612 VM) separate
  from logic power with one common ground. A previous team burned an ESP32
  by putting the supply voltage on the 3.3 V side.
- **ToF count.** 5 sensors need 5 XSHUT GPIOs. Avoid GPIO 0, 2, 12, 15 for
  pins that hold a level at boot, and remember GPIO 34–39 are input only.
- **Shipping.** M0 says order by Wed 4 Nov; international shipping can take
  weeks. Check what is available locally first.
