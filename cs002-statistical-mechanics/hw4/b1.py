import random, math
import pylab as plot

n_trials = 5000000
delta    = 0.01
dim      = 4

old_radius_square = 0
x      = [0.0]*dim
data   = []

for i in range(n_trials):
  k = random.randint(0, dim - 1)
  x_old_k = x[k]
  x_new_k = x_old_k + random.uniform(-delta, delta)

  new_radius_square = old_radius_square + x_new_k**2 - x_old_k**2

  if new_radius_square < 1.0:
    x[k] = x_new_k
    old_radius_square = new_radius_square

  data.append(math.sqrt(old_radius_square))

plot.hist(data, 100, normed=True)

r = [v / 100.0 for v in range(0, 101)]
y = [dim*(v**(dim-1)) for v in r]
plot.plot(r, y, c='red', linewidth=2.0)

plot.title("Sphere markov sampling in " + str(dim) + " dimensions", fontsize = 18)
plot.xlabel("$r$", fontsize = 10)
plot.ylabel("distribution", fontsize = 10)

plot.savefig("b1_%d.png" % dim)
plot.show()
