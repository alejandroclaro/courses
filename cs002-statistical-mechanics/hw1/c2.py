import random, math

n_trials = 400000
n_hits   = 0
mean     = 0.0
mean2    = 0.0

for iter in range(n_trials):
  x, y = random.uniform(-1.0, 1.0), random.uniform(-1.0, 1.0)
  Obs  = 0.0

  if x**2 + y**2 < 1.0:
    n_hits += 1
    Obs     = 4.0

  mean  += Obs
  mean2 += Obs*Obs

mean  = mean / float(n_trials)
mean2 = mean2 / float(n_trials)

print math.sqrt(mean2 - mean**2)

