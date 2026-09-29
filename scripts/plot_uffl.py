"""Plot distances and UFFL adaptive gain from a CSV log.
Usage: python3 scripts/plot_uffl.py logs/uffl_run1.csv
"""
import sys, os
import pandas as pd
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

path = sys.argv[1]
df = pd.read_csv(path)
for c in ("front", "left", "right"):
    df[c] = df[c].where(df[c] >= 0)   # -1 = no echo -> gap in the plot
t = (df["ms"] - df["ms"].iloc[0]) / 1000.0

fig, (a1, a2) = plt.subplots(2, 1, figsize=(9, 6), sharex=True)
a1.plot(t, df["front"], label="Front"); a1.plot(t, df["left"], label="Left"); a1.plot(t, df["right"], label="Right")
a1.set_ylabel("Distance (cm)"); a1.legend(); a1.grid(alpha=.3)
a2.step(t, df["gain"], where="post", color="k")
a2.set_ylabel("adaptiveGain"); a2.set_xlabel("Time (s)"); a2.set_yticks([0.75, 1.0, 1.25]); a2.grid(alpha=.3)
fig.suptitle("UFFL adaptive gain test: " + os.path.basename(path))
out = os.path.join("media", "uffl_gain_" + os.path.splitext(os.path.basename(path))[0].replace("uffl_", "") + ".png")
os.makedirs("media", exist_ok=True)
fig.tight_layout(); fig.savefig(out, dpi=150)
print("Saved", out)
