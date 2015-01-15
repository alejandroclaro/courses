import sys
import collections

ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz "

def strxor(a, b):
  if len(a) > len(b):
    return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a[:len(b)], b)])
  else:
    return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a, b[:len(a)])])

def build_alphabet_map():
  print "* ALPHABET XOR map\n"
  result = {}

  for i, symbol in enumerate(ALPHABET):
    result[symbol] = sorted([chr(ord(symbol) ^ ord(x)) for x in ALPHABET])
    print "%2d %s %s" % (i, symbol, "".join([format(ord(x), "02x") for x in result[symbol]]))

  print ""
  return result

def build_sub_problem(ciphertexts, index):
  result          = { }
  sub_ciphertexts = "".join(sorted({ s[index] for s in ciphertexts if len(s) > index }))

  print "Index: %d SubProblem: %s (%d)" % (index, sub_ciphertexts.encode("hex"), len(sub_ciphertexts))

  for c in sub_ciphertexts:
    characters = { strxor(c, x) for x in sub_ciphertexts }
    result[c]  = "".join(sorted(characters))

    print "    Char: %s XOR: %s" % (c.encode("hex"), result[c].encode("hex"))

  return result

def solve_sub_problem(problem, alphabet_map):
  possible_results = {}
  symbols_set      = {}

  for c, xor in problem.iteritems():
    intersection_set    = { symbol : "".join(set(values).intersection(set(xor))) for symbol, values in alphabet_map.iteritems() }
    symbols_set[c]      = [ symbol for symbol, value in intersection_set.iteritems() if len(value) == len(max(intersection_set.values(), key=len)) ]
    possible_results[c] = { chr(ord(c) ^ ord(symbol)) for symbol in symbols_set[c] }

  result = reduce(lambda x, y: x + "".join(y), possible_results.itervalues(), "")
  result = collections.Counter(result).most_common()
  print "    Possible maps:    %s" % symbols_set
  print "    Possible results: %s" % possible_results
  print "    Result:           %s" % result

  return result[0][0]

def find_key(ciphertexts , key_len):
  alphabet_map = build_alphabet_map()
  key          = ""

  for index in range(0, key_len):
    sub_problem    = build_sub_problem(ciphertexts, index)
    next_character = solve_sub_problem(sub_problem, alphabet_map)

    if next_character == None:
      return None

    key += next_character

  return key

def decrypt(key, ciphertext):
  msg = strxor(key, ciphertext)
  return msg

if __name__ == "__main__":

  with open("ciphertexts.txt") as f:
    ciphertexts = [x.strip().decode("hex") for x in f.readlines()]

  key = find_key(ciphertexts, reduce(lambda x,y: min(x, len(y)), ciphertexts, 1000))

  if key == None:
    print "Unable to find the KEY."
  else:
    print "Key: %s" % key.encode("hex")
    for i, c in enumerate(ciphertexts):
      msg = decrypt(key, c)
      print "Msg: %s" % "".join([i if ord(i) < 127 and ord(i) > 31 else '_' for i in msg])
