import random, math

n_trials = 10000000
delta    = 0.1
x, y, z  = 0.0, 0.0, 0.0
n_hits   = 0

for i in range(n_trials):
  dx, dy, dz = random.uniform(-delta, delta), random.uniform(-delta, delta), random.uniform(-delta, delta)
  next_x = x + dx
  next_y = y + dy
  next_z = z + dz

  if (next_x**2 + next_y**2 + next_z**2) < 1.0:
    x, y, z = next_x, next_y, next_z

  alpha = random.uniform(-1.0, 1.0)

  if (x**2 + y**2 + z**2 + alpha**2) < 1.0:
    n_hits += 1

q4 = 2.0 * float(n_hits) / float(n_trials)
q3 = 1.333660

print "<Q_4> = %f" % q4
print "V_sph(3) * <Q_4> = %f" % (q4 * (4.0 * math.pi / 3.0))
print "V_sph(2) * <Q_4> * <Q_3> = %f" % (q4 * q3 * math.pi)
