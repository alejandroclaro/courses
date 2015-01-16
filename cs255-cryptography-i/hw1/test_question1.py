import question1
from nose.tools import assert_equals

def test_strxor():
  assert_equals(question1.strxor("A", "A"), "\x00")
  assert_equals(question1.strxor("AB", "AB"), "\x00\x00")
  assert_equals(question1.strxor(" " * 26, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "abcdefghijklmnopqrstuvwxyz")

def test_build_sub_problem():
  ciphertexts_1 = [ "z", "x", "w" ]
  ciphertexts_2 = [ "zr", "xt", "wu" ]

  assert_equals(question1.build_sub_problem(ciphertexts_1, 0), { "w" : "\x00\x0d\x0f", "x" : "\x00\x02\x0f", "z" : "\x00\x02\x0d" })
  assert_equals(question1.build_sub_problem(ciphertexts_2, 0), { "w" : "\x00\x0d\x0f", "x" : "\x00\x02\x0f", "z" : "\x00\x02\x0d" })
  assert_equals(question1.build_sub_problem(ciphertexts_2, 1), { "r" : "\x00\x06\x07", "t" : "\x00\x01\x06", "u" : "\x00\x01\x07" })

def test_solve_sub_problem():
  alphabet_map = question1.build_alphabet_map()
  assert_equals(question1.solve_sub_problem({ "A" : "\x03A", "B" : "\x03B", "\x00" : "AB\x00" }, alphabet_map), " ")

def test_find_key():
  assert_equals(question1.find_key(["A", "B", "\x00"], 1), " ")
  assert_equals(question1.find_key(["AA", "BB", "\x00\x00"], 2), "  ")
