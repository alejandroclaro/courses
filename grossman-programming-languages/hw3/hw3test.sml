(* Homework3 Simple Test*)
(* These are basic test cases. Passing these tests does not guarantee that your code will pass the actual homework grader *)
(* To run the test, add a new line to the top of this file: use "homeworkname.sml"; *)
(* All the tests should evaluate to true. For example, the REPL should say: val test1 = true : bool *)

val test1 = only_capitals ["A","B","C"] = ["A","B","C"]

val test2 = longest_string1 ["A","bc","C"] = "bc"

val test3 = longest_string2 ["A","bc","C"] = "bc"

val test4a = longest_string3 ["A","bc","C"] = "bc"

val test4b = longest_string4 ["A","B","C"] = "C"

val test5 = longest_capitalized ["A","bc","C"] = "A";

val test6 = rev_string "abc" = "cba";

val test7 = first_answer (fn x => if x > 3 then SOME x else NONE) [1,2,3,4,5] = 4

val test8 = all_answers (fn x => if x = 1 then SOME [x] else NONE) [2,3,4,5,6,7] = NONE

val test9a   = count_wildcards Wildcard = 1
val test9a_1 = count_wildcards (TupleP [Wildcard, Wildcard, UnitP]) = 2

val test9b   = count_wild_and_variable_lengths (Variable("a")) = 1
val test9b_1 = count_wild_and_variable_lengths (TupleP [Wildcard, Wildcard, Variable("aa")]) = 4

val test9c   = count_some_var ("x", Variable("x")) = 1;
val test9c_1 = count_some_var ("wild", ConstructorP("wild", Wildcard)) = 0

val test10   = check_pat (Variable("x")) = true
val test10_1 = check_pat (TupleP [Variable("x"), Variable("x")]) = false
val test10_2 = check_pat (ConstructorP ("hi",TupleP[Variable "x",Variable "x"])) = false

val test11   = match (Const(1), UnitP) = NONE
val test11_1 = match (Const(1), Variable "a") = SOME [("a", Const(1))]
val test11_2 = match (Tuple [Const(1), Const(2)], TupleP [Variable("a"), Variable("b")]) = SOME [("a", Const(1)), ("b", Const(2))]
val test11_3 = match (Const(1), ConstP(1)) = SOME []
val test11_4 = match (Const(1), Wildcard) = SOME []

val test12   = first_match Unit [UnitP] = SOME []
val test12_1 = first_match Unit [Variable "a"] = SOME [("a",Unit)];
