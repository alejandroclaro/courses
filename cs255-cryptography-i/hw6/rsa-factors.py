#!/usr/bin/python

import sys
import gmpy2 as gmp

N1 = gmp.mpz("17976931348623159077293051907890247336179769789423065727343008115"
             "77326758055056206869853794492129829595855013875371640157101398586"
             "47833778606925583497541085196591615128057575940752635007475935288"
             "71082364994994077189561705436114947486504671101510156394068052754"
             "0071584560878577663743040086340742855278549092581")

N2 = gmp.mpz("6484558428080716696628242653467722787263437207069762630604390703787"
             "9730861808111646271401527606141756919558732184025452065542490671989"
             "2428844841839353281972988531310511738648965962582821502504990264452"
             "1008852816733037111422964210278402893076574586452336833570778346897"
             "15838646088239640236866252211790085787877")

N3 = gmp.mpz("72006226374735042527956443552558373833808445147399984182665305798191"
             "63556901883377904234086641876639384851752649940178970835240791356868"
             "77441155132015188279331812309091996246361896836573643119174094961348"
             "52463970788523879939683923036467667022162701835329944324119217381272"
             "9276147530748597302192751375739387929")

CIPHERTEXT = gmp.mpz("2209645186741038177630656113488341801741006978789283107173183"
                     "9143676135600120538004282329650473509424343946219751512256465"
                     "8399679428894607645420405815647489880137348641204523252293201"
                     "7648791666640299750918872997169052608322206777160001932926087"
                     "0009579993724077458967773697817571267229951148662959627934791540")

def check(n, p, q):
  if gmp.is_prime(p) and gmp.is_prime(q):
    return gmp.mul(p, q) == n

  return False

def find_factors(n):
  a = gmp.isqrt(n)
  p = 0
  q = 0

  while not check(n, p, q):
    a  = gmp.add(a, 1)
    a2 = gmp.mul(a, a)
    x  = gmp.isqrt(gmp.sub(a2, n))
    p  = gmp.mpz(gmp.sub(a, x))
    q  = gmp.mpz(gmp.add(a, x))

  return (p, q)

def find_factors_6n(n):
  n24 = gmp.mul(n, 24)
  a = gmp.isqrt(n24)
  p = 0
  q = 0

  while not check(n, p, q):
    a  = gmp.add(a, 1)
    a2 = gmp.mul(a, a)
    x  = gmp.isqrt(gmp.sub(a2, n24))
    p  = gmp.mpz(gmp.div(gmp.sub(a, x), 6))
    q  = gmp.mpz(gmp.div(gmp.add(a, x), 4))

  return (p, q)

def decrypt(n, p, q, ciphertext):
  euler = gmp.mul(gmp.sub(gmp.mpz(p), 1), gmp.sub(gmp.mpz(q), 1))
  e     = gmp.mpz(65537)
  d     = gmp.invert(e, gmp.mpz(euler))
  msg   = gmp.powmod(ciphertext, d, gmp.mpz(n))
  msg   = hex(msg)

  if msg.startswith('0x2'):
    header = msg.index('00') + 2
    msg = msg[header:]
    return msg.decode('hex')

  return ""

if __name__ == "__main__":
  p, q = find_factors(N1)

  if check(N1, p, q):
    print "N1: min(p, q) = %s" % long(p if p < q else q)

  msg = decrypt(N1, p, q, CIPHERTEXT)
  print "msg: %s" % msg

  p, q = find_factors(N2)

  if check(N2, p, q):
    print "N2: min(p, q) = %s" % long(p if p < q else q)

  p, q = find_factors_6n(N3)

  if check(N3, p, q):
    print "N3: min(p, q) = %s" % long(p if p < q else q)
