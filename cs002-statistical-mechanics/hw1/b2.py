import random

def markov_pi_acceptance(N, delta):
  x, y = 1.0, 1.0
  accepted = 0

  for i in range(N):
    del_x, del_y = random.uniform(-delta, delta), random.uniform(-delta, delta)

    if abs(x + del_x) < 1.0 and abs(y + del_y) < 1.0:
      accepted += 1
      x, y = x + del_x, y + del_y

  return accepted

x, y     = 1.0, 1.0
n_trials = 2**12

print "delta | acceptance rate"

for delta in [0.062, 0.125, 0.25, 0.5, 1.0, 2.0, 4.0]:
  accepted = markov_pi_acceptance(n_trials, delta)
  print "%1.3f | %f" % (delta, accepted / float(n_trials))
