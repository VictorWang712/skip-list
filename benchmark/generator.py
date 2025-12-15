import random
import os

BASE = "../data/input/random"
os.makedirs(BASE, exist_ok=True)

SCALES = [10, 50, 100, 500, 1000, 5000, 10000, 20000, 50000, 100000]

for i in range(10):
    ops = SCALES[i]
    filename = os.path.join(BASE, f"{i}.in")

    existing = set()
    next_key = 1

    with open(filename, "w") as f:
        f.write(str(ops) + "\n")

        for _ in range(ops):
            r = random.random()

            # Insert
            if r < 0.4:
                key = next_key
                next_key += 1
                existing.add(key)
                f.write(f"I {key}\n")

            # Search
            elif r < 0.8:
                if existing and random.random() < 0.8:
                    key = random.choice(list(existing))
                else:
                    key = next_key + random.randint(1, 1000)
                f.write(f"S {key}\n")

            # Delete
            else:
                if existing:
                    key = random.choice(list(existing))
                    existing.remove(key)
                else:
                    key = next_key + random.randint(1, 1000)
                f.write(f"D {key}\n")
