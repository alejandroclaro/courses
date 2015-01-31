import urllib2
import sys

TARGET     = "http://crypto-class.appspot.com/po?er="
CIPHERTEXT = "f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4"
BLOCK_SIZE = 16

ALPHABET = "\x0F\x0E\x0D\x0C\x0B\x0A\x09\x08\x07\x06\x05\x04\x03\x02\x01 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

#--------------------------------------------------------------
# padding oracle
#--------------------------------------------------------------
class PaddingOracle(object):
  def query(self, q):
    try:
      target = TARGET + urllib2.quote(q) # Create query URL
      req = urllib2.Request(target) # Send HTTP request to server
    except:
      return self.query(q)

    try:
      f = urllib2.urlopen(req) # Wait for response
      return None
    except urllib2.HTTPError, e:
      if e.code == 404:
        return True # good padding
      return False # bad padding
    except:
      return self.query(q)

  def attak(self, ciphertext):
    result = []
    blocks = self.split_blocks(ciphertext)

    for index in range(len(blocks) - 1, 0, -1):
      plain_block = self.decrypt_block(index, blocks)
      result = plain_block + result

    return result

  def split_blocks(self, ciphertext):
    return [map(ord, ciphertext[i:i+BLOCK_SIZE]) for i in range(0, len(ciphertext), BLOCK_SIZE)]

  def decrypt_block(self, index, blocks):
    result = []

    for position in range(BLOCK_SIZE - 1, -1, -1):
      print "# block: %d byte: %d padding: %d " % (index, position, BLOCK_SIZE - position),
      byte = self.decrypt_byte(position, result, blocks[index-1], blocks[index])
      result.insert(0, byte)
      print "%d (%s)" % (byte, chr(byte))

    return map(chr, result)

  def decrypt_byte(self, position, know_bytes, iv, block):
    iv_prime = list(iv)

    for k in range(0, len(know_bytes)):
      iv_prime[position + k + 1] = iv_prime[position + k + 1] ^ know_bytes[k] ^ (BLOCK_SIZE - position)

    for guess in ALPHABET:
      iv_guess = list(iv_prime)
      iv_guess[position] = iv_prime[position] ^ ord(guess) ^ (BLOCK_SIZE - position)
      q = "".join(map(chr, iv_guess)) + "".join(map(chr, block))

      sys.stdout.write(".")
      sys.stdout.flush()

      if self.query(q.encode("hex")) != False:
        return ord(guess)

    print "NOT FOUND"
    return 0x00

if __name__ == "__main__":
  po = PaddingOracle()
  result = po.attak(CIPHERTEXT.decode("hex"))
  print "".join(result)
