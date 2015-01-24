import io
import os
import sys
from Crypto.Hash import SHA256

BLOCK_SIZE = 1024

def compute_hash(data):
  h = SHA256.new()
  h.update(data)
  return h.digest()

def generate(data):
  blocks = [ data[i:i + BLOCK_SIZE] for i in range(0, len(data), BLOCK_SIZE) ]
  hash   = ""
  result = []

  print len(data)
  print len(blocks)

  for b in reversed(blocks):
    r    = b + hash
    hash = compute_hash(r)
    result.insert(0, r)
    print "".join([ "%02x" % ord(x) for x in hash ])

  result.insert(0, hash)
  return "".join(result)

if __name__ == "__main__":
  result = ""

  with io.open(sys.argv[1], "rb") as in_file:
    data   = in_file.read()
    result = generate(data)

  with io.open(sys.argv[2], "wb") as out_file:
    out_file.write(result)
