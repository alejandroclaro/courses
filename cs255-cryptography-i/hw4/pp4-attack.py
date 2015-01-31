import urllib2
import sys

TARGET     = "http://crypto-class.appspot.com/po?er="
CIPHERTEXT = "f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4"
BLOCK_SIZE = 16

ALPHABET = "\x0F\x0E\x0D\x0C\x0B\x0A\x09\x08\x07\x06\x05\x04\x03\x02\x01 .ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

#--------------------------------------------------------------
# padding oracle
#--------------------------------------------------------------
class PaddingOracle(object):
  def query(self, q):
    try:
      target = TARGET + urllib2.quote(q)    # Create query URL
      req = urllib2.Request(target)         # Send HTTP request to server
    except:
      return self.query(q)

    try:
      f = urllib2.urlopen(req)          # Wait for response
      #print "Valid"
      return None
    except urllib2.HTTPError, e:
      #print "We got: %d" % e.code       # Print response code
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

      print "# PLAIN BLOCK: %s" % "".join(plain_block)
      result = plain_block + result

    return result

  def split_blocks(self, ciphertext):
    return [map(ord, ciphertext[i:i+BLOCK_SIZE]) for i in range(0, len(ciphertext), BLOCK_SIZE)]

  def decrypt_block(self, index, blocks):
    result = []

    for position in range(BLOCK_SIZE - 1, 0, -1):
      print "# block: %d byte: %d padding: %d " % (index, position, BLOCK_SIZE - position),
      byte = self.decrypt_byte(position, result, blocks[0:index], blocks[index])
      result.insert(0, byte)
      print "%d (%s)" % (byte, chr(byte))

    return map(chr, result)

  def decrypt_byte(self, position, know_bytes, prev_blocks, block):
    prime       = list(prev_blocks[-1])
    prev_blocks = reduce(lambda x,y: x + y, prev_blocks[0:len(prev_blocks)-1], [])

    for k in range(0, len(know_bytes)):
      prime[position + k + 1] = prime[position + k + 1] ^ know_bytes[k] ^ (BLOCK_SIZE - position)

    for guess in ALPHABET:
      guess_block = list(prime)
      guess_block[position] = prime[position] ^ ord(guess) ^ (BLOCK_SIZE - position)
      q = "".join(map(chr, prev_blocks)) + "".join(map(chr, guess_block)) + "".join(map(chr, block))

      sys.stdout.write(".")
      sys.stdout.flush()

      if self.query(q.encode("hex")) != False:
        return ord(guess)

    print "NOT FOUND"
    return 0x00

if __name__ == "__main__":
  po = PaddingOracle()
  #po.query(sys.argv[1])       # Issue HTTP query with the given argument
  result = po.attak(CIPHERTEXT.decode("hex"))
  print "".join(result)
