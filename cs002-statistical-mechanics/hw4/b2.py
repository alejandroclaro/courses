import random, math

def V_sph(dim):
  return math.pi ** (dim / 2.0) / math.gamma(dim / 2.0 + 1.0)

dim      = 200
n_trials = 10000000
delta    = 0.1
n_hits   = 0

old_radius_square = 0
x = [0.0]*(dim - 1)

for i in range(n_trials):
  k = random.randint(0, dim - 2)
  x_old_k = x[k]
  x_new_k = x_old_k + random.uniform(-delta, delta)

  new_radius_square = old_radius_square + x_new_k**2 - x_old_k**2

  if new_radius_square < 1.0:
    x[k] = x_new_k
    old_radius_square = new_radius_square

  alpha = random.uniform(-1.0, 1.0)

  if (old_radius_square + alpha**2) < 1.0:
    n_hits += 1

print "<Q_%d> = %f" % (dim, 2.0 * float(n_hits) / float(n_trials))
print "V_sph(%d)/V_sph(%d) = %f" % (dim, dim - 1, V_sph(dim)/V_sph(dim - 1))
