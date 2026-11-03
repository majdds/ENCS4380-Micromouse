# Team T30 — Fathi

ENCS4380 Interfacing Techniques, Birzeit University, 2026/27 S1.

## Members and roles

The brief asks for one owner per subsystem. Proposed split (confirm as a team):

| Member | Student ID | Group | Role | Owns |
| --- | --- | --- | --- | --- |
| Majd Shalash | 12331360 | Hardware | Electronics lead | Schematic, power, wiring, sensors, bill of materials |
| Ahmad Nasser | 1230507 | Hardware | Mechanical lead | CAD, 3D printing, mounting, mass and size budget |
| Zaid Rasras | 1230187 | Software & control | Algorithm lead | Maze map, flood fill, simulator, HAL interface |
| Basil Zraiq | 1241671 | Software & control | Motion lead | Motors, encoders, PID, straight lines and turns |

## Links

- Git repository: https://github.com/majdds/ENCS4380-Micromouse
- Trello board: `ENCS4380-T30-Fathi` (link to be added)

## Building on macOS

The kit's `hal_sim.c` calls `snprintf` without including `<stdio.h>`. Apple
clang treats that as an error, so on a Mac add `-include stdio.h` (the HAL
files must not be edited):

```
gcc -O2 -std=c99 -include stdio.h -o solver main_sim.c hal_sim.c mm_common.c solver.c
```

or `make example CFLAGS="-O2 -std=c99 -Wall -Wextra -include stdio.h"`.
The Moodle VM (Linux gcc) builds the kit unchanged.
