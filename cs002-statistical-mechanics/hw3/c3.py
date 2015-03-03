import os, pylab, random, math, cmath

def delx_dely(x, y):
  d_x = (x[0] - y[0]) % 1.0
  if d_x > 0.5: d_x -= 1.0
  d_y = (x[1] - y[1]) % 1.0
  if d_y > 0.5: d_y -= 1.0
  return d_x, d_y

def Psi_6(L, N, sigma):
  sum_vector = 0j
  for i in range(N):
    vector  = 0j
    n_neighbor = 0
    for j in range(N):
      if dist(L[i], L[j]) < 2.8 * sigma and i != j:
        n_neighbor += 1
        dx, dy = delx_dely(L[j], L[i])
        angle = cmath.phase(complex(dx, dy))
        vector += cmath.exp(6.0j * angle)
    if n_neighbor > 0:
      vector /= n_neighbor
    sum_vector += vector
  return sum_vector / float(N)

def read_configuration(N, eta):
  filename = 'disk_configuration_N%i_eta%.2f.txt' % (N, eta)

  if os.path.isfile(filename):
    f = open(filename, 'r')
    L = []
    for line in f:
      a, b = line.split()
      L.append([float(a), float(b)])
    f.close()
    print 'starting from file', filename
  else:
    k = int(math.sqrt(N))
    delta = 1.0 / k
    p0 = 0.5 * delta
    L = [[p0 + i * delta, p0 + j * delta] for i in range(k) for j in range(k)]
    print 'starting from a new random configuration'

  return L

def save_configuration(N, eta, L):
  filename = 'disk_configuration_N%i_eta%.2f.txt' % (N, eta)

  f = open(filename, 'w')
  for a in L:
    f.write(str(a[0]) + ' ' + str(a[1]) + '\n')
  f.close()

def dist(x,y):
  d_x = abs(x[0] - y[0]) % 1.0
  d_x = min(d_x, 1.0 - d_x)
  d_y = abs(x[1] - y[1]) % 1.0
  d_y = min(d_y, 1.0 - d_y)

  return  math.sqrt(d_x**2 + d_y**2)

def fold_point(p):
  nx = p[0] % 1.0
  ny = p[1] % 1.0

  return [nx, ny]

N = 64
eta = 0.72
delta = 0.1
n_steps = 10000

psi6_list = []
eta_list = []
eta_step = 0.01
samples = n_steps / 100

L = read_configuration(N, eta)

while eta > 0.2:
  psi6 = 0
  sigma = math.sqrt(eta / (math.pi * N))

  eta_list.append(eta)

  for steps in range(n_steps):
    a = random.choice(L)
    b = [a[0] + random.uniform(-delta, delta), a[1] + random.uniform(-delta, delta)]
    min_dist = min(dist(b, c) for c in L if c != a)

    if not (min_dist < 2.0 * sigma):
      a[:] = fold_point(b)

    if steps % 100 == 0:
      psi6 = psi6 + Psi_6(L, N, sigma)

  psi6_list.append(abs(psi6) / samples)
  print "psi6(%s) = %s" % (eta, psi6_list[-1])

  save_configuration(N, eta, L)
  eta = eta - eta_step

pylab.plot(eta_list, psi6_list, 'o')
pylab.xlabel('density')
pylab.ylabel('psi6')
pylab.title('Phase transition')
pylab.savefig('phase_transition.png')
pylab.show()

