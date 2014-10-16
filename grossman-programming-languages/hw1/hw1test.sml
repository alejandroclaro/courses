(* Homework1 Simple Test *)
(* These are basic test cases. Passing these tests does not guarantee that your code will pass the actual homework grader *)
(* To run the test, add a new line to the top of this file: use "homeworkname.sml"; *)
(* All the tests should evaluate to true. For example, the REPL should say: val test1 = true : bool *)


val test1 = is_older((1,2,3),(2,3,4)) = true

val test2 = number_in_month([(2012,2,28),(2013,12,1)],2) = 1

val test3 = number_in_months([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28)],[2,3,4]) = 3

val test4 = dates_in_month([(2012,2,28),(2013,12,1)],2) = [(2012,2,28)]

val test5 = dates_in_months([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28)],[2,3,4]) = [(2012,2,28),(2011,3,31),(2011,4,28)]

val test6 = get_nth(["hi", "there", "how", "are", "you"], 2) = "there"

val test7 = date_to_string((2013, 6, 1)) = "June 1, 2013"

val test8 = number_before_reaching_sum(10, [1,2,3,4,5]) = 3

val test9 = what_month(70) = 3

val test10 = month_range(31, 34) = [1,2,2,2]

val test11 = oldest([(2012,2,28),(2011,3,31),(2011,4,28)]) = SOME (2011,3,31)

(* MORE TEST *)

val test1_1 = is_older((1,2,3),(1,2,3)) = false
val test1_2 = is_older((2,3,4),(1,2,3)) = false
val test1_3 = is_older((2,2,4),(2,3,4)) = true
val test1_4 = is_older((2,3,4),(2,2,4)) = false
val test1_5 = is_older((2,3,4),(2,3,5)) = true
val test1_6 = is_older((2,3,5),(2,2,4)) = false

val test2_1 = number_in_month([], 2) = 0
val test2_2 = number_in_month([(2012,3,28),(2013,4,1)], 2) = 0
val test2_3 = number_in_month([(2012,12,28),(2013,12,1)], 12) = 2

val test3_1 = number_in_months([],[5]) = 0
val test3_2 = number_in_months([(2012,1,28),(2013,2,1),(2011,3,31),(2011,4,28)],[]) = 0
val test3_3 = number_in_months([(2012,1,28),(2013,2,1),(2011,3,31),(2011,4,28)],[5]) = 0
val test3_4 = number_in_months([(2012,1,28),(2013,2,1),(2011,3,31),(2011,4,28)],[1,4]) = 2
val test3_5 = number_in_months([(2012,5,28),(2013,6,1),(2011,3,31),(2011,4,28)],[5,3, 4]) = 3
val test3_6 = number_in_months([(2012,5,28),(2013,6,1),(2011,3,31),(2011,4,28)],[5, 5, 3, 4]) = 4

val test7_1 = date_to_string((2013,   1,  2)) = "January 2, 2013"
val test7_2 = date_to_string((2014,   2,  3)) = "February 3, 2014"
val test7_12 = date_to_string((2024,  3, 13)) = "March 13, 2024"
val test7_3 = date_to_string((2015,   4,  4)) = "April 4, 2015"
val test7_4 = date_to_string((2016,   5,  5)) = "May 5, 2016"
val test7_5 = date_to_string((2017,   6,  6)) = "June 6, 2017"
val test7_6 = date_to_string((2018,   7,  7)) = "July 7, 2018"
val test7_7 = date_to_string((2019,   8,  8)) = "August 8, 2019"
val test7_8 = date_to_string((2020,   9,  9)) = "September 9, 2020"
val test7_9 = date_to_string((2021,  10, 10)) = "October 10, 2021"
val test7_10 = date_to_string((2022, 11, 11)) = "November 11, 2022"
val test7_11 = date_to_string((2023, 12, 12)) = "December 12, 2023"

val test8_1 = number_before_reaching_sum(2, [2,3]) = 0
val test8_2 = number_before_reaching_sum(5, [2,3]) = 1

val test9_1 = what_month(1) = 1
val test9_2 = what_month(365) = 12

val test10_1 = month_range(34, 31) = []
val test10_2 = month_range(31, 31) = [1]
val test10_3 = month_range(58, 60) = [2, 2, 3]

val test11_1 = oldest([]) = NONE
val test11_2 = oldest([(2012,2,30),(2012,3,31),(2012,4,28)]) = SOME (2012,2,30)
val test11_3 = oldest([(2012,2,28),(2012,2,31),(2012,2,29)]) = SOME (2012,2,28)
val test11_4 = oldest([(2012,2,1),(2012,2,1),(2012,2,1)]) = SOME (2012,2,1)

val test12_1 = number_in_months_challenge([(2012,5,28),(2013,6,1),(2011,3,31),(2011,4,28)],[5, 5, 3, 4]) = 3
val test12_2 = number_in_months_challenge([(2012,5,28),(2011,3,31),(2011,4,28)],[5, 3, 4]) = 3
val test12_3 = number_in_months_challenge([(1,2,25),(3,5,26),(1,12,29),(3,2,28),(1,2,27),(1,2,25),(6,7,8)],[]) = 0

val test13_1 = reasonable_date((0,0,0)) = false
val test13_2 = reasonable_date((1,0,0)) = false
val test13_3 = reasonable_date((1,1,0)) = false
val test13_4 = reasonable_date((1,13,1)) = false
val test13_5 = reasonable_date((1,12,32)) = false
val test13_6 = reasonable_date((1981,2,29)) = false
val test13_7 = reasonable_date((2000,2,29)) = true
val test13_8 = reasonable_date((1,4,31)) = false


