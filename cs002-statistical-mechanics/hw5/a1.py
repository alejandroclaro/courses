import random, math
import pylab as plot

def psi_0_sq(x):
  psi0 = (1.0 / (math.pi**0.25)) * math.exp(-(x**2) / 2.0)
  return psi0 * psi0

x        = 0.0
delta    = 0.5
n_trials = 500000
samples  = []

for k in range(n_trials):
  x_new = x + random.uniform(-delta, delta)

  if random.uniform(0.0, 1.0) < psi_0_sq(x_new) / psi_0_sq(x):
    x = x_new

  samples.append(x)

plot.hist(samples, 100, normed=True, label="Markov-chain sampling")

curve_x = [v / 100.0 for v in range(-500, 500)]
curve_y = [psi_0_sq(v) for v in curve_x]
plot.plot(curve_x, curve_y, c='red', linewidth=2.0, label="$\pi(x) = \psi_0^2(x)$")

plot.title("Theoretical Ground-state distribution $\pi(x)$ and\nnormalized histogram for " + str(len(samples)) + " samples", fontsize = 12)
plot.xlabel("$x$", fontsize = 12)
plot.ylabel("$\pi(x)$", fontsize = 12)
plot.legend()

plot.savefig("a1.png")
plot.show()
