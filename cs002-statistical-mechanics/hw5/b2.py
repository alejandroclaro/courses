import math, random
import pylab as plot

def rho_free(x, y, beta):
  return math.exp(-(x - y) ** 2 / (2.0 * beta))

def read_file(filename):
  list_x = []
  list_y = []

  with open(filename) as f:
    for line in f:
      x, y = line.split()
      list_x.append(float(x))
      list_y.append(float(y))

  f.close()
  return list_x, list_y

beta    = 4.0
N       = 10
dtau    = beta / N
delta   = 1.0
n_steps = 1000000
slice_n = 0
x       = [0.0] * N
samples = []

for step in range(n_steps):
  k            = random.randint(0, N - 1)
  knext, kprev = (k + 1) % N, (k - 1) % N
  x_new        = x[k] + random.uniform(-delta, delta)
  old_weight   = (rho_free(x[knext], x[k], dtau)  * rho_free(x[k], x[kprev], dtau)  * math.exp(-0.5 * dtau * x[k] ** 2))
  new_weight   = (rho_free(x[knext], x_new, dtau) * rho_free(x_new, x[kprev], dtau) * math.exp(-0.5 * dtau * x_new ** 2))

  if random.uniform(0.0, 1.0) < new_weight / old_weight:
    x[k] = x_new

  if step % 10 == 0:
    samples.append(x[slice_n])

plot.hist(samples, 100, normed=True, label="slice %d histogram" % slice_n)

list_x, list_y = read_file("data_harm_matrixsquaring_beta" + str(beta) + ".dat")
plot.plot(list_x, list_y, c='red', linewidth=2.0, label="matrix squaring $\pi(x)$")

plot.title("Path-integral Monte Carlo algorithm for the harmonic oscillator.\n$\\beta$=" + str(beta) + " N=" + str(N) + " steps=" + str(n_steps), fontsize = 14)
plot.xlabel("$x$", fontsize = 12)
plot.ylabel("$\pi(x)$", fontsize = 12)
plot.xlim(-2.0, 2.0)
plot.legend()

plot.savefig("b2_" + str(beta) + ".png")
plot.show()
