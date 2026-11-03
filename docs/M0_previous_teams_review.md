# M0 — Review of two earlier teams' boards (T30 Fathi)

Status: **draft** — read both boards yourselves and edit before submitting.

Boards studied (from the instructor's Trello, `waselghanem2`):

- **Team A** — "Interfacing Techniques", spring 2026: https://trello.com/b/IGvx6oQh
- **Team B** — "Micromouse Maze Project", 2025: https://trello.com/b/iHZIRaBC

## What they chose

| | Team A | Team B |
| --- | --- | --- |
| Controller | ESP32 | ESP32 |
| Wall sensing | 3x VL53L0X (front, left, right), shared bus via XSHUT | 1x VL53L0X front + 2 digital IR sensors (left/right) |
| Motors / driver | DC motors with quadrature encoders, DRV8833 | DC motors with encoders, H-bridge (L298N-style pins) |
| Extra | MPU6050 gyro for turns; Wi-Fi web dashboard for live tuning | MPU6050 |
| Power | 2S LiPo through a buck-boost "UPS" module at 9 V | not documented |
| Algorithm | Simulated left/right-hand, DFS, A*, chose flood fill (BFS) | not documented on the board |
| Reached a goal? | Yes, reports a full 8x8 run | Sensor and encoder tests shown; no maze run on the board |

## What went wrong

1. **Burned ESP32 (Team A).** Over 3.3 V reached the logic side from the 9 V
   / buck-boost supply and destroyed the ESP32 and an I/O expander.
2. **I2C bus failures (Team A).** Default pins 21/22 stopped returning data;
   they split sensors over two I2C buses on other pins to recover.
3. **Drift (both).** Team B's left motor was faster; they hard-coded a PWM
   offset of -10/-15 instead of closing the loop. Team A needed gyro +
   encoder + wall fusion with many hand-tuned gains.
4. **Turns in a 16.8 cm corridor (Team A).** Wheels mounted at the front
   meant a pivot left the robot off-centre and a 180° spin hit walls; they
   needed back-up/pivot/forward sequences and reversing into visited cells.
5. **Weak side sensing (Team B).** Digital IR gives wall / no wall only, so
   it cannot be used to centre between walls.
6. **Library/clone issues (Team B).** Their MPU6050 clone did not work with
   the standard library and needed 5 V instead of 3.3 V.
7. **Tracking (both).** Many cards have no owner, due date or evidence;
   Team B's board still contains template cards ("Make Final Exam").

## What we will do differently

1. **Power first.** Separate motor and logic power with one common ground:
   battery → TB6612 motor supply; buck to 5 V → ESP32 board → 3.3 V for
   sensors. Check every rail with a meter before connecting the ESP32.
2. **Five ToF sensors, no IR.** Front, two 45° diagonals and two sides as
   M2 suggests, so we can centre and square up on walls. Each on its own
   XSHUT GPIO; test the I2C bus with all sensors at 10 Hz in M3.
3. **Wheel axle at the centre of the footprint** (about 10 x 11 cm) so the
   robot can turn in place and stay centred without extra manoeuvres.
4. **Closed loop, measured.** Encoder P/PI correction and measured
   ticks-per-mm per wheel (M4/M5) instead of a fixed PWM offset.
5. **Radios off on race day.** Wi-Fi only for debugging, behind the
   `MM_RADIOS_ENABLED` switch in `robot_config.h`.
6. **Flood fill from day one**, with no hard-coded 8x8 or centre goal (Team A
   hard-coded the centre four cells; our hidden test mazes move it).
7. **Board discipline.** Every card has one owner, a due date, a checklist,
   and evidence before Done; weekly log from every member.
