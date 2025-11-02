# B&R PLC in Automation Studio

[Русская версия](README.md)

A lab for the course on software for mechatronic and robotic systems (October 2025): a C program for a B&R controller in Automation Studio, debugged in the PLC simulator. The lab was done as a team.

## What the program does

The program models two DC motors and compares two ways of controlling them:
- **the first motor** runs open-loop: the voltage is set proportionally to the speed setpoint;
- **the second motor** runs under a PI controller (`FB_Regulator`) that receives the error between the setpoint and the actual speed.

The setpoint changes as a step: the speed becomes 40 at cycle 200, goes back to 0 at cycle 400, and then everything repeats. Variable traces in Automation Studio show how both motors follow the step.

The function blocks live in the `Logical/Libraries/Library` library:
- `FB_Integrator`: Euler integration with a step of 0.01 s;
- `FB_Motor`: the motor as a first-order lag, dω/dt = (u/ke − ω)/Tm, where `ke` = 0.24 and `Tm` = 0.1 s;
- `FB_Regulator`: a PI controller (`k_p` = 0.3, `k_i` = 2.7) with the voltage limited to ±24 V. To keep the integrator from winding up during saturation, the difference between the limited and the raw output is fed back to its input.

## Two versions of the project

| Folder | Contents |
|---|---|
| `Laba_1/` | The full project: `Init.c`, `Cyclic.c` and `Exit.c` handle initialization, the cyclic task and shutdown. Debugging and trace settings are included |
| `Laba_1_refactored/` | The same lab from the team repository (October 9, 2025): initialization and the cyclic task are in a single `Main.c`, the limiter function is called `VoltageLimitation`, and the function blocks have comments |

## Quick start

Open `Laba_1/LABA1.apj` or `Laba_1_refactored/LAB1.apj` in B&R Automation Studio 4.5 and run the `Config1` configuration in the simulator (ARsim).

## Tech stack

C, B&R Automation Studio, Automation Runtime (ARsim).

## License

[MIT](../../LICENSE)
