import sys
from Crypto        import Random
from Crypto.Cipher import AES

def pkcs5_pad(text):
  length = 16 - (len(text) % 16)
  return text + (chr(length) * length)

def encrypt(mode, key, text):
  iv = Random.new().read(AES.block_size)

  if mode == "CBC":
    cipher = AES.new(key, AES.MODE_CBC, IV=iv)
    text   = pkcs5_pad(text)
  elif mode == "CTR":
    ctr     = Counter.new(128, initial_value=int(iv.encode("hex"), 16))
    cipher  = AES.new(key, AES.MODE_CTR, counter=ctr)
  else:
    print "Mode %s not supported." % mode
    exit(-1)

  result = iv + cipher.encrypt(text)

  print mode
  print key.encode("hex")
  print result.encode("hex")

if __name__ == "__main__":
  cases = []

  with open("plaintext.txt") as f:
    lines = [ x.strip() for x in f.readlines() ]
    cases = [lines[x : (x + 3)] for x in xrange(0, len(lines) - (len(lines) % 3), 3)]

  for c in cases:
    encrypt(c[0], c[1].decode("hex"), c[2])
