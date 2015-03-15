import random, math
import pylab as plot

def psi_n_square(x, n):
  if n == -1:
    return 0.0
  else:
    psi = [math.exp(-x ** 2 / 2.0) / math.pi ** 0.25]
    psi.append(math.sqrt(2.0) * x * psi[0])

    for k in range(2, n + 1):
      psi.append(math.sqrt(2.0 / k) * x * psi[k - 1] - math.sqrt((k - 1.0) / k) * psi[k - 2])

    return psi[n] ** 2

def pi_quant(x, beta):
  return math.sqrt(math.tanh(beta / 2.0) / math.pi) * math.exp(-x**2 * math.tanh(beta / 2.0))

def pi_class(x, beta):
  return math.sqrt(beta / (2 * math.pi)) * math.exp(-(beta * x**2) / 2.0)

x        = 0.0
n        = 0
beta     = 5.0
delta    = 0.5
n_trials = 1000000
samples  = []

for k in range(n_trials):
  x_new = x + random.uniform(-delta, delta)

  if random.uniform(0.0, 1.0) < psi_n_square(x_new, n) / psi_n_square(x, n):
    x = x_new

  samples.append(x)

  n_new = n + random.choice([-1, 1])

  if random.uniform(0.0, 1.0) < (psi_n_square(x, n_new) / psi_n_square(x, n)) * math.exp(-beta * (n_new - n)):
    n = n_new

plot.hist(samples, 100, normed=True, label="$\pi(x)$ histogram")

curve_x = [v / 100.0 for v in range(-700, 700)]
curve_y = [pi_quant(v, beta) for v in curve_x]
plot.plot(curve_x, curve_y, c='red', linewidth=2.0, label="exact quantum $\pi(x)$")

curve_y = [pi_class(v, beta) for v in curve_x]
plot.plot(curve_x, curve_y, c='green', linewidth=2.0, label="exact classical $\pi(x)$")

plot.title("Quantum particle in the harmonic potential.\n$\\beta$=" + str(beta) + " samples=" + str(len(samples)), fontsize = 14)
plot.xlabel("$x$", fontsize = 12)
plot.ylabel("$\pi(x)$", fontsize = 12)
plot.legend()

plot.savefig("a2_%f.png" % beta)
plot.show()
