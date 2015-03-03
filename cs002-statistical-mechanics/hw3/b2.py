import pylab, random, math

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

L = [[0.25, 0.25], [0.75, 0.25], [0.25, 0.75], [0.75, 0.75]]
eta = 0.25
sigma = math.sqrt(eta / (math.pi * len(L)))
delta = 0.1
n_steps = 1000

for steps in range(n_steps):
  a = random.choice(L)
  b = [a[0] + random.uniform(-delta, delta), a[1] + random.uniform(-delta, delta)]
  min_dist = min(dist(b, c) for c in L if c != a)

  if not (min_dist < 2.0 * sigma):
    a[:] = fold_point(b)

show_conf(L, sigma, 'Hard disk monte carlo simulation', 'b2.png')
