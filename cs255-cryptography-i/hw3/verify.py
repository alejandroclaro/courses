import io
import sys
from Crypto.Hash import SHA256
from functools   import partial

BLOCK_SIZE = 1024
HASH_SIZE  = 32

def compute_hash(data):
  h = SHA256.new()
  h.update(data)
  return h.digest()

def verify_block(hash, data):
  return compute_hash(data) == hash

def verify(file):
  hash  = file.read(HASH_SIZE)
  data  = file.read(BLOCK_SIZE + HASH_SIZE)
  index = 1

  while len(data) > 0:
    valid = verify_block(hash, data)
    print "%d Block Valid: %s (%s)" % (index, valid, "".join([ "%02x" % ord(x) for x in hash ]))

    if not valid:
      return False

    hash  = data[-HASH_SIZE:]
    data  = file.read(BLOCK_SIZE + HASH_SIZE)
    index = index + 1

  return True

if __name__ == "__main__":
  with io.open(sys.argv[1], "rb") as file:
    print "File Valid: %s" % verify(file)
