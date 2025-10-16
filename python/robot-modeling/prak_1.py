# Пересчитаем П-образную траекторию для двузвенного робота без использования caas_jupyter_tools
# и просто выведем первые строки DataFrame, а также сохраним CSV в UTF-8.
import math
import pandas as pd

L1 = 30.0
L2 = 30.0
v = 5.0

segments = [
    {"start": (0.0, 0.0), "end": (0.0, 50.0)},
    {"start": (0.0, 50.0), "end": (50.0, 50.0)},
    {"start": (50.0, 50.0), "end": (50.0, 0.0)}
]

def seg_length(s):
    (x1, y1) = s["start"]; (x2, y2) = s["end"]
    return math.hypot(x2 - x1, y2 - y1)

seg_lengths = [seg_length(s) for s in segments]
total_len = sum(seg_lengths)
T = total_len / v
t_max = math.ceil(T)
times = list(range(0, t_max + 1))

def point_at_s(s):
    acc = 0.0
    for seg, L in zip(segments, seg_lengths):
        if s <= acc + L + 1e-9:
            frac = (s - acc) / L if L > 0 else 0
            x = seg["start"][0] + frac * (seg["end"][0] - seg["start"][0])
            y = seg["start"][1] + frac * (seg["end"][1] - seg["start"][1])
            return (x, y)
        acc += L
    return segments[-1]["end"]

def inverse_kinematics(x, y, L1, L2):
    d2 = x * x + y * y
    cos_q2 = (d2 - L1 * L1 - L2 * L2) / (2 * L1 * L2)
    if cos_q2 < -1 or cos_q2 > 1:
        return (None, None), (None, None)
    cos_q2 = max(-1.0, min(1.0, cos_q2))
    sin_q2 = math.sqrt(1 - cos_q2 ** 2)
    q2a, q2b = math.atan2(sin_q2, cos_q2), math.atan2(-sin_q2, cos_q2)
    k1 = L1 + L2 * cos_q2
    k2a, k2b = L2 * sin_q2, -L2 * sin_q2
    q1a = math.atan2(y, x) - math.atan2(k2a, k1)
    q1b = math.atan2(y, x) - math.atan2(k2b, k1)
    to_deg = lambda rad: (math.degrees(rad) + 180) % 360 - 180
    return (to_deg(q1a), to_deg(q2a)), (to_deg(q1b), to_deg(q2b))

rows = []
for t in times:
    s = min(v * t, total_len)
    x, y = point_at_s(s)
    (t1a, t2a), (t1b, t2b) = inverse_kinematics(x, y, L1, L2)
    reachable = not (t1a is None and t1b is None)
    rows.append({
        "t (s)": t,
        "x (cm)": round(x, 3),
        "y (cm)": round(y, 3),
        "reachable": reachable,
        "theta1_A (deg)": None if t1a is None else round(t1a, 3),
        "theta2_A (deg)": None if t2a is None else round(t2a, 3),
        "theta1_B (deg)": None if t1b is None else round(t1b, 3),
        "theta2_B (deg)": None if t2b is None else round(t2b, 3),
    })

df = pd.DataFrame(rows)

# Сохраняем CSV с корректной UTF-8 кодировкой
csv_path = "P_trajectory_utf8.csv"
df.to_csv(csv_path, index=False, encoding="utf-8")

df.head(15), {"total_length_cm": total_len, "T_seconds": T}
