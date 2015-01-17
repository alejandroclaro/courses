import sys
from Crypto        import Random
from Crypto.Util   import Counter
from Crypto.Cipher import AES

def pkcs5_unpad(text):
  return text[:-ord(text[-1])]

def decrypt(mode, key, text):
  iv     = text[0 : AES.block_size]
  text   = text[AES.block_size : len(text)]
  result = ""

  if mode == "CBC":
    cipher  = AES.new(key, AES.MODE_CBC, IV=iv)
    result  = cipher.decrypt(text)
    result  = pkcs5_unpad(result)
  elif mode == "CTR":
    ctr     = Counter.new(128, initial_value=int(iv.encode("hex"), 16))
    cipher  = AES.new(key, AES.MODE_CTR, counter=ctr)
    result  = cipher.decrypt(text)
  else:
    print "Mode %s not supported." % mode
    exit(-1)

  print mode
  print key.encode("hex")
  print result

if __name__ == "__main__":
  cases = []

  with open("encrypted.txt") as f:
    lines = [ x.strip() for x in f.readlines() ]
    cases = [lines[x : (x + 3)] for x in xrange(0, len(lines) - (len(lines) % 3), 3)]

  for c in cases:
    decrypt(c[0], c[1].decode("hex"), c[2].decode("hex"))
