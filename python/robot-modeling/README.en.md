# Robot Modeling: a Two-Link Arm

[Русская версия](README.md)

A robot modeling practice task (October 2025). A two-link arm with 30 cm links follows a 50 × 50 cm U-shaped path at 5 cm/s.

`prak_1.py` computes:
- the trajectory points second by second;
- inverse kinematics with two solutions (elbow up and elbow down) and a reachability check for every point.

| File | Contents |
|---|---|
| `prak_1.py` | The trajectory and inverse kinematics; the result is saved to `P_trajectory_utf8.csv` |
| `P_trajectory_utf8.csv` | Point coordinates and joint angles for both solutions |
| `pi_trajectory_2link.csv` | The same table with an extra column for the distance along the path |
| `P_trajectory_plots.html` | Interactive joint-angle plots in Plotly |

## Quick start

```bash
pip install pandas
python prak_1.py
```

## Tech stack

Python, pandas, Plotly.

## License

[MIT](../../LICENSE)
