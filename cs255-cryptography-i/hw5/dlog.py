#!/usr/bin/python

import sys
import gmpy2 as gmp

B = 2**20
P = gmp.mpz("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171")
G = gmp.mpz("11717829880366207009516117596335367088558084999998952205599979459063929499736583746670572176471460312928594829675428279466566527115212748467589894601965568")
H = gmp.mpz("3239475104050450443565264378728065788649097520952449527834792452971981976143292558073856937958553180532878928001494706097394108577585732452307673444020333")

def build_table(p, g, h, min, max):
  result = {}

  for x1 in range(min, max):
    key = gmp.divm(h, gmp.powmod(g, x1, p), p)
    result[key] = x1

  return result

def dlog(p, g, h, min, max):
  table  = build_table(p, g, h, min, max)
  gb     = gmp.powmod(g, max, p)
  result = 0

  for x0 in range(min, max):
    v0 = gmp.powmod(gb, x0, p)
    x1 = table.get(v0)

    if x1 != None:
      return (x0 * max) + x1

  return result

if __name__ == "__main__":
  result = dlog(P, G, H, 0, B)

  print "Dlog = %s" % result

