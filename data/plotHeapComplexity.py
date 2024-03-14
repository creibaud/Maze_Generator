import sys
import os
import pandas as pd
import matplotlib.pyplot as plt

if len(sys.argv) < 2:
    print("Please provide a filename argument.")
    sys.exit(1)

filename = sys.argv[1]

print("Filename: %s" % filename)
data = pd.read_csv(filename)

nb = data["nb"]
timeToInsert = data["time_to_insert"]
timeToExtract = data["time_to_extract"]

plt.figure(figsize=(10, 6))

plt.plot(nb, timeToInsert, label="Time to Insert")
plt.plot(nb, timeToExtract, label="Time to Extract")

plt.xscale("log", base=2)
plt.yscale("log")

plt.title("Time to Insert and Extract vs nb")
plt.xlabel("nb")
plt.ylabel("Time (s)")

plt.legend()
plt.grid(True)

saveFile = os.path.join("data", "plot", os.path.splitext(os.path.basename(filename))[0] + ".png")
os.makedirs(os.path.dirname(saveFile), exist_ok=True)

plt.savefig(saveFile)
plt.show()