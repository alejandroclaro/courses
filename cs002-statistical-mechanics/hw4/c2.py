import random, math
import pylab as plot

def V_sph(dim):
  return math.pi ** (dim / 2.0) / math.gamma(dim / 2.0 + 1.0)

def compute_q(dim, n_trials, delta):
  n_hits = 0
  x      = [0.0]*dim
  old_radius_square = 0

  for i in range(n_trials):
    k = random.randint(0, dim - 1)
    x_old_k = x[k]
    x_new_k = x_old_k + random.uniform(-delta, delta)

    new_radius_square = old_radius_square + x_new_k**2 - x_old_k**2

    if new_radius_square < 1.0:
      x[k] = x_new_k
      old_radius_square = new_radius_square

    alpha = random.uniform(-1.0, 1.0)

    if (old_radius_square + alpha**2) < 1.0:
      n_hits += 1

  q = 2.0 * float(n_hits) / float(n_trials)

  return q

def compute_volume(dim, n_trials, delta):
  volume = 2.0

  for d in range(1, dim):
    q = compute_q(d, t, delta)
    volume *= q

  return volume

dim      = 20
n_runs   = 10
n_trials = [10**v for v in range(1, 8)]
delta    = 0.3

print "n_trials |   <V_sph(20)>   |   V_sph(20) (exact)   |     error     | difference"

for t in n_trials:
  v  = 0.0
  v2 = 0.0

  for run in range(n_runs):
    volume = compute_volume(dim, t, delta)
    v  += volume
    v2 += volume*volume

  v    /= n_runs
  v2   /= n_runs
  error = math.sqrt(v2 - v**2) / math.sqrt(n_runs)
  exact = V_sph(dim)

  print "%8d | %15f | %21f | %13f | %f" % (t, v, exact, error, abs(v - exact))
