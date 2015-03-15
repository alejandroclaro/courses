import math, numpy
import pylab as plot

def V(x, cubic, quartic):
  return (x**2) / 2.0 + cubic * (x**3) + quartic * (x**4)

def pi_quant(x, beta):
  return math.sqrt(math.tanh(beta / 2.0) / math.pi) * math.exp(-x**2 * math.tanh(beta / 2.0))

def rho_free(x, xp, beta):
  return (math.exp(-(x - xp) ** 2 / (2.0 * beta)) / math.sqrt(2.0 * math.pi * beta))

def  rho_anharmonic_trotter(grid, beta, cubic, quartic):
  return numpy.array([[rho_free(x, xp, beta) * numpy.exp(-0.5 * beta * (V(x, cubic, quartic) + V(xp, cubic, quartic))) for x in grid] for xp in grid])

cubic   = -1.0
quartic = -cubic

x_max    = 5.0
nx       = 100
dx       = 2.0 * x_max / (nx - 1)
x        = [i * dx for i in range(-(nx - 1) / 2, nx / 2 + 1)]
beta_tmp = 2.0 ** (-8)
beta     = 4.0
rho      = rho_anharmonic_trotter(x, beta_tmp, cubic, quartic)

while beta_tmp < beta:
  rho = numpy.dot(rho, rho)
  rho *= dx
  beta_tmp *= 2.0

Z       = sum(rho[j, j] for j in range(nx + 1)) * dx
pi_of_x = [rho[j, j] / Z for j in range(nx + 1)]
f       = open("data_anharm_matrixsquaring_beta" + str(beta) + ".dat", "w")

for j in range(nx + 1):
  f.write(str(x[j]) + " " + str(rho[j, j] / Z) + "\n")

f.close()

plot.plot(x, pi_of_x, c='blue', linewidth=2.0, label="matrix squaring $\pi(x)$ (anharmonic oscillator)")

curve_y = [pi_quant(v, beta) for v in x]
plot.plot(x, curve_y, c='red', linewidth=2.0, label="exact quantum $\pi(x)$ (harmonic oscillator)")

plot.title("Anharmonic oscillator - Matrix-squaring method.\n$\\beta$=" + str(beta) + " cubic=" + str(cubic) + " quartic=" + str(quartic), fontsize = 14)
plot.xlabel("$x$", fontsize = 12)
plot.ylabel("$\pi(x)$", fontsize = 12)
plot.legend()

plot.savefig("c1_" + str(beta) + ".png")
plot.show()
