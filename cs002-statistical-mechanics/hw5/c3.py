import math, numpy

def V(x, cubic, quartic):
  return (x**2) / 2.0 + cubic * (x**3) + quartic * (x**4)

def rho_free(x, xp, beta):
  return (math.exp(-(x - xp) ** 2 / (2.0 * beta)) / math.sqrt(2.0 * math.pi * beta))

def  rho_anharmonic_trotter(grid, beta, cubic, quartic):
  return numpy.array([[rho_free(x, xp, beta) * numpy.exp(-0.5 * beta * (V(x, cubic, quartic) + V(xp, cubic, quartic))) for x in grid] for xp in grid])

def Energy_pert(n, cubic, quartic):
  return n + 0.5 - 15.0 / 4.0 * cubic **2 * (n ** 2 + n + 11.0 / 30.0) + 3.0 / 2.0 * quartic * (n ** 2 + n + 1.0 / 2.0)

def Z_pert(cubic, quartic, beta, n_max):
  Z = sum(math.exp(-beta * Energy_pert(n, cubic, quartic)) for n in range(n_max + 1))
  return Z

quartic_list = [ 0.001, 0.01, 0.1, 0.2, 0.3, 0.4, 0.5 ]

print "quartic    | Z          | Z perturbation"

for quartic in quartic_list:
  cubic = -quartic

  x_max    = 5.0
  nx       = 1000
  dx       = 2.0 * x_max / (nx - 1)
  x        = [i * dx for i in range(-(nx - 1) / 2, nx / 2 + 1)]
  beta_tmp = 2.0 ** (-8)
  beta     = 2.0
  rho      = rho_anharmonic_trotter(x, beta_tmp, cubic, quartic)

  while beta_tmp < beta:
    rho = numpy.dot(rho, rho)
    rho *= dx
    beta_tmp *= 2.0

  Z_a = sum(rho[j, j] for j in range(nx + 1)) * dx
  Z_b = Z_pert(cubic, quartic, beta, 10)

  print "%10.3f | %10.3e | %10.3e" % (quartic, Z_a, Z_b)
