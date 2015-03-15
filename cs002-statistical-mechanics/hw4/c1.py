import random, math
import pylab as plot

def V_sph(dim):
  return math.pi ** (dim / 2.0) / math.gamma(dim / 2.0 + 1.0)

dim      = 200
n_trials = 1000000
delta    = 0.1
volume   = [2.0]

for d in range(1, dim):
  n_hits = 0
  x      = [0.0]*d
  old_radius_square = 0

  for i in range(n_trials):
    k = random.randint(0, d - 1)
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
  volume.append(volume[-1] * q)

  print "<Q_%d> = %f" % (d+1, q)
  print "<V_sph(%d)> = %e" % (d+1, volume[-1])
  print "V_sph(%d) = %e" % (d+1, V_sph(d+1))
  print ""

d = [v+1 for v in range(0, dim)]
plot.plot(d, volume, c="red", linewidth=2.0)

plot.yscale("log")
plot.title("Sphere volume", fontsize = 18)
plot.xlabel("$d$", fontsize = 10)
plot.ylabel("V_sph", fontsize = 10)

plot.savefig("c1_%d.png" % dim)
plot.show()

