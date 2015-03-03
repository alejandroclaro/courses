import os, pylab, random, math

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

def show_conf(L, sigma, title, fname):
  pylab.axes()

  for [x, y] in L:
    for ix in range(-1, 2):
      for iy in range(-1, 2):
        cir = pylab.Circle((x + ix, y + iy), radius=sigma,  fc='r')
        pylab.gca().add_patch(cir)

  pylab.axis('scaled')
  pylab.title(title)
  pylab.axis([0.0, 1.0, 0.0, 1.0])
  pylab.savefig(fname)
  pylab.show()
  pylab.close()

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
sigma = math.sqrt(eta / (math.pi * N))
L = read_configuration(N, eta)
delta = 0.1
n_steps = 10000

for steps in range(n_steps):
  a = random.choice(L)
  b = [a[0] + random.uniform(-delta, delta), a[1] + random.uniform(-delta, delta)]
  min_dist = min(dist(b, c) for c in L if c != a)

  if not (min_dist < 2.0 * sigma):
    a[:] = fold_point(b)

save_configuration(N, eta, L)
show_conf(L, sigma, 'Hard disk monte carlo simulation', 'b5_3.png')
