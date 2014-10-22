(* Homework2 Simple Test *)
(* These are basic test cases. Passing these tests does not guarantee that your code will pass the actual homework grader *)
(* To run the test, add a new line to the top of this file: use "homeworkname.sml"; *)
(* All the tests should evaluate to true. For example, the REPL should say: val test1 = true : bool *)

val test1 = all_except_option("string", ["string"]) = SOME []
val test1_1 = all_except_option("string", ["a", "b"]) = NONE
val test1_2 = all_except_option("string", ["a", "string", "b"]) = SOME ["a", "b"]

val test2 = get_substitutions1([["foo"],["there"]], "foo") = []
val test2_1 = get_substitutions1([["Fred","Fredrick"],["Elizabeth","Betty"],["Freddie","Fred","F"]], "Fred") = ["Fredrick", "Freddie", "F"]
val test2_2 = get_substitutions1([], "") = []
val test2_3 = get_substitutions1([], "bar") = []
val test2_4 = get_substitutions1([[]], "baz") = []

val test3 = get_substitutions2([["foo"],["there"]], "foo") = []
val test3_1 = get_substitutions2([["Fred","Fredrick"],["Elizabeth","Betty"],["Freddie","Fred","F"]], "Fred") = ["Fredrick", "Freddie", "F"]
val test3_2 = get_substitutions2([], "") = []
val test3_3 = get_substitutions2([], "bar") = []
val test3_4 = get_substitutions2([[]], "baz") = []

val test4 = similar_names([["Fred","Fredrick"],["Elizabeth","Betty"],["Freddie","Fred","F"]], {first="Fred", middle="W", last="Smith"}) =
      [{first="Fred", last="Smith", middle="W"}, {first="Fredrick", last="Smith", middle="W"},
       {first="Freddie", last="Smith", middle="W"}, {first="F", last="Smith", middle="W"}]

val test4_1 = similar_names([], {first="Fred", middle="W", last="Smith"}) = [{first="Fred", last="Smith", middle="W"}]
val test4_2 = similar_names([[]], {first="Fred", middle="W", last="Smith"}) = [{first="Fred", last="Smith", middle="W"}]
val test4_3 = similar_names([["Elizabeth","Betty"]], {first="Fred", middle="W", last="Smith"}) = [{first="Fred", last="Smith", middle="W"}]

val test5   = card_color((Clubs, Num 2))    = Black
val test5_1 = card_color((Spades, Num 2))   = Black
val test5_2 = card_color((Diamonds, Num 2)) = Red
val test5_3 = card_color((Hearts, Num 2))   = Red

val test6   = card_value((Clubs, Num 2)) = 2
val test6_1 = card_value((Clubs, Ace))   = 11
val test6_2 = card_value((Clubs, Jack))  = 10
val test6_3 = card_value((Clubs, Queen)) = 10
val test6_4 = card_value((Clubs, King))  = 10

val test7   = remove_card([(Hearts, Ace)], (Hearts, Ace), IllegalMove) = []
val test7_1 = remove_card([(Hearts, Ace), (Hearts, Ace)], (Hearts, Ace), IllegalMove) = [(Hearts, Ace)]
val test7_2 = (remove_card([], (Clubs, Ace), IllegalMove); false) handle IllegalMove => true
val test7_3 = (remove_card([(Hearts, Ace)], (Clubs, Ace), IllegalMove); false) handle IllegalMove => true

val test8   = all_same_color([(Hearts, Ace), (Hearts, Ace)])    = true
val test8_1 = all_same_color([(Hearts, King), (Diamonds, Ace)]) = true
val test8_2 = all_same_color([(Clubs, King), (Spades, Ace)])    = true
val test8_3 = all_same_color([(Hearts, King), (Spades, Ace)])   = false
val test8_4 = all_same_color([(Diamonds, King), (Spades, Ace)]) = false

val test9   = sum_cards([(Clubs, Num 2),(Clubs, Num 2)])  = 4
val test9_1 = sum_cards([(Diamonds, Num 1),(Spades, Ace)]) = 12
val test9_2 = sum_cards([(Hearts, Jack),(Spades, Queen),(Spades, Queen)])  = 30

val test10   = score([(Hearts, Num 2),(Clubs, Num 4)], 10) = 4
val test10_1 = score([(Hearts, Num 2),(Clubs, Num 4)], 6)  = 0
val test10_2 = score([(Hearts, Num 2),(Clubs, Num 4)], 3)  = 9
val test10_3 = score([(Clubs, Num 2), (Clubs, Num 4)], 3)  = 4

val test11 = officiate([(Hearts, Num 2),(Clubs, Num 4)],[Draw], 15) = 6

val test12 = officiate([(Clubs,Ace),(Spades,Ace),(Clubs,Ace),(Spades,Ace)],
                       [Draw,Draw,Draw,Draw,Draw],
                       42)
             = 3

val test12_1 = officiate([(Hearts, Num 2),(Clubs, Num 4),(Clubs, King)],[Draw, Draw, Draw, Discard(Clubs, King)], 15) = 3

val test13 = ((officiate([(Clubs,Jack),(Spades,Num(8))],
                         [Draw,Discard(Hearts,Jack)],
                         42);
               false)
              handle IllegalMove => true)
