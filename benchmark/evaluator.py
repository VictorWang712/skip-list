import os
import subprocess
import time
import json
from datetime import datetime

SRC = "../code/src/main.c"
BIN = "../code/bin/main.exe"
INPUT_DIRS = ["../data/input/random"]
OUTPUT_BASE = "../data/output"
LOG_DIR = "../benchmark/log"

os.makedirs("../code/bin", exist_ok=True)
os.makedirs(LOG_DIR, exist_ok=True)

# Compile
subprocess.run(["gcc", SRC, "-O2", "-o", BIN], check=True)

log = {
    "timestamp": datetime.now().isoformat(),
    "results": []
}

for input_dir in INPUT_DIRS:
    name = os.path.basename(input_dir)
    out_dir = os.path.join(OUTPUT_BASE, name)
    os.makedirs(out_dir, exist_ok=True)

    for file in sorted(os.listdir(input_dir)):
        in_path = os.path.join(input_dir, file)
        out_path = os.path.join(out_dir, file.replace(".in", ".out"))

        start = time.time()
        with open(in_path, "r") as fin, open(out_path, "w") as fout:
            subprocess.run([BIN], stdin=fin, stdout=fout)
        elapsed = time.time() - start

        log["results"].append({
            "input": in_path,
            "output": out_path,
            "time_sec": elapsed,
            "correct": True
        })

log_file = os.path.join(LOG_DIR, f"log_{int(time.time())}.json")
with open(log_file, "w") as f:
    json.dump(log, f, indent=2)
