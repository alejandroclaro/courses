(*
 * Course:   Programming Languages
 * Author:   Alejandro Claro
 * Homework: #1
 *)

(* Helper function to count the number of element in a list *)
fun list_length(values : (int * int * int) list) =
  if null values
  then 0
  else 1 + list_length(tl values)

(* Problem #1 *)
fun is_older(x : int * int * int, y : int * int * int) =
  let
    fun day_of_year(date : int * int * int) =
      ((#2 date) * 30) + (#3 date)
  in
    if (#1 x) = (#1 y)
    then day_of_year(x) < day_of_year(y)
    else (#1 x) < (#1 y)
  end

(* Problem #4 *)
fun dates_in_month(dates : (int * int * int) list, month : int) =
  if null dates
  then []
  else if (#2 (hd dates)) = month
  then (hd dates) :: dates_in_month(tl(dates), month)
  else dates_in_month(tl dates, month)

(* Problem #5 *)
fun dates_in_months(dates : (int * int * int) list, months : int list) =
  if null months
  then []
  else dates_in_month(dates, hd months) @ dates_in_months(dates, tl months)

(* Problem #2 *)
fun number_in_month(dates : (int * int * int) list, month : int) =
  list_length(dates_in_month(dates, month))

(* Problem #3 *)
fun number_in_months(dates : (int * int * int) list, months : int list) =
  list_length(dates_in_months(dates, months))

(* Problem #6 *)
fun get_nth(month_names : string list, nth : int) =
  if nth = 1
  then hd month_names
  else get_nth(tl month_names, nth - 1)

(* Problem #7 *)
fun date_to_string(date : int * int * int) =
  let
    val month_names = [ "January", "February", "March",     "April",   "May",      "June",
                        "July",    "August",   "September", "October", "November", "December"]
  in
    get_nth(month_names, #2 date) ^ " " ^ Int.toString(#3 date) ^ ", " ^ Int.toString(#1 date)
  end

(* Problem #8 *)
fun number_before_reaching_sum(sum : int, set : int list) =
  if sum <= (hd set)
  then 0
  else 1 + number_before_reaching_sum(sum - (hd set), tl set)

(* Problem #9 *)
fun what_month(day : int) =
  let
    val days_in_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
  in
    number_before_reaching_sum(day, days_in_month) + 1
  end

(* Problem #10 *)
fun month_range(day1 : int, day2 : int) =
  if day1 > day2
  then []
  else what_month(day1) :: month_range(day1 + 1, day2)

(* Problem #11 *)
fun oldest(dates : (int * int * int) list) =
  let
    fun oldest_of_two(x : int * int * int, y : int * int * int) =
      if is_older(x, y)
      then x
      else y

    fun oldest_recursion(dates : (int * int * int) list, x : int * int * int) =
      if null dates
      then x
      else oldest_recursion(tl dates, oldest_of_two(hd dates, x))
  in
    if null dates
    then NONE
    else SOME(oldest_recursion(tl dates, hd dates))
  end

(* Problem #12.2 *)
fun dates_in_months_challenge(dates : (int * int * int) list, months : int list) =
  let
    fun contains(values : int list, y : int) =
      if null values
      then false
      else if (hd values) = y
      then true
      else contains(tl values, y)

    fun remove_duplicates(values : int list, x : int list) =
      if null values
      then x
      else if contains(x, hd values)
      then remove_duplicates(tl values, x)
      else remove_duplicates(tl values, (hd values) :: x)
  in
    if null months
    then []
    else dates_in_months(dates, remove_duplicates(tl months, [hd months]))
  end

(* Problem #12.1 *)
fun number_in_months_challenge(dates : (int * int * int) list, months : int list) =
  list_length(dates_in_months_challenge(dates, months))

(* Problem #13 *)
fun reasonable_date(date : int * int * int) =
  let
    val months_days           = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    val leap_year_months_days = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

    fun is_divisible(x : int, y : int) =
      (x mod y) = 0

    fun days_in_month(days_list : int list, month : int) =
      if month = 1
      then hd days_list
      else days_in_month(tl days_list, month - 1)

    fun is_leap_year(year : int) =
      is_divisible(year, 4) andalso (not (is_divisible(year, 100))  orelse  is_divisible(year, 400))

    fun valid_year(date : int * int * int) =
      (#1 date) > 0

    fun valid_month(date : int * int * int) =
      (#2 date) >= 1 andalso (#2 date) <= 12

    fun valid_day(date : int * int * int) =
      if (#3 date) <= 0
      then false
      else if is_leap_year(#1 date)
      then (#3 date) <= days_in_month(leap_year_months_days, #2 date)
      else (#3 date) <= days_in_month(months_days, #2 date)
  in
    valid_year(date) andalso valid_month(date) andalso valid_day(date)
  end
