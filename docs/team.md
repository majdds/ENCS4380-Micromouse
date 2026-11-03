# Team T30 — Fathi

ENCS4380 Interfacing Techniques, Birzeit University, 2026/27 S1.

## Members and roles

Existing team roster and proposed split (confirm as a team; official brief
has not been available for this documentation review):

| Member | Student ID | Group | Role | Owns |
| --- | --- | --- | --- | --- |
| Majd Shalash | 12331360 | Hardware | Electronics lead | Schematic, power, wiring, sensors, bill of materials |
| Ahmad Nasser | 1230507 | Hardware | Mechanical lead | CAD, 3D printing, mounting, mass and size budget |
| Zaid Rasras | 1230187 | Software & control | Algorithm lead | Maze map, flood fill, simulator, HAL interface |
| Basil Zraiq | 1241671 | Software & control | Motion lead | Motors, encoders, PID, straight lines and turns |

Ahmad confirmed his Mechanical Lead role during the M0 audit on 4 November
2026. Other role acceptances and the student IDs still need confirmation.

## Links

- Git repository: https://github.com/majdds/ENCS4380-Micromouse
- Trello board: https://trello.com/b/6ae985185d0535c390c2ef16/encs4380-t30-fathe (supplied team link; board name, privacy and membership await verification)

## Windows example setup (verified local build)

From the repository directory, build the supplied example:

```powershell
gcc -O2 -std=c99 -Wall -Wextra -o example.exe main_sim.c hal_sim.c mm_common.c example_wallfollow.c
```

The audit's Windows GCC 6.3.0 build returned exit 0 with no compiler
diagnostics. MinGW Make 3.82.90 failed with an internal directory-reading
error on that machine; the direct GCC command worked without source edits.

In mms, add a Mouse profile with this repository's absolute directory,
the build command above, and the full quoted path to `example.exe` as
the Run command. Use the actual compiler path if mms cannot find `gcc`.
Load `mazes/practice4_1.txt`, press Run, and retain configuration,
build output and actual movement evidence. Each member must do this on
their own laptop. Compilation and mms startup were checked by the audit;
a real maze run remains unverified. Running the executable directly
without mms produces a missing-connection diagnostic, not a maze test.

These instructions were prepared with AI setup/documentation assistance.
Students must review them and record their own actual tests. No solver,
controller, driver or HAL implementation was generated for this contribution.

## Building on macOS

The current `hal_sim.c` includes `<stdio.h>`. The earlier missing-header
note does not apply to this checkout. macOS has not been tested by this
audit; each member must capture their own compiler output. Build the
unchanged supplied example using:

```
gcc -O2 -std=c99 -Wall -Wextra -o example main_sim.c hal_sim.c mm_common.c example_wallfollow.c
```

Run `./example` through mms, not as a standalone maze simulator. Report
actual errors before changing build flags; do not modify protected HAL files.
Linux/VM execution also requires an independent test.
