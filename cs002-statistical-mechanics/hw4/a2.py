import random

n_trials = 10000000
delta    = 0.1
x, y     = 0.0, 0.0
n_hits   = 0

for i in range(n_trials):
  dx, dy = random.uniform(-delta, delta), random.uniform(-delta, delta)
  next_x = x + dx
  next_y = y + dy

  if (next_x**2 + next_y**2) < 1.0:
    x, y = next_x, next_y

  z = random.uniform(-1.0, 1.0)

  if (x**2 + y**2 + z**2) < 1.0:
    n_hits += 1

print "<Q_3> = %f" % (2.0 * float(n_hits) / float(n_trials))
