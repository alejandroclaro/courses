(* Dan Grossman, Coursera PL, HW2 Provided Code *)

(* if you use this function to compare two strings (returns true if the same
   string), then you avoid several of the functions in problem 1 having
   polymorphic types that may be confusing *)
fun same_string(s1 : string, s2 : string) =
    s1 = s2

(* put your solutions for problem 1 here *)
fun all_except_option(_, []) = NONE
|   all_except_option(value, x::xs) =
  case (same_string(value, x), all_except_option(value, xs)) of
      (true, _)       => SOME xs
    | (false, SOME y) => SOME (x::y)
    | (false, NONE)   => NONE

fun get_substitutions1([], _) = []
|   get_substitutions1(y::ys, x) =
  case all_except_option(x, y) of
      NONE   => get_substitutions1(ys, x)
    | SOME z => z @ get_substitutions1(ys, x)

fun get_substitutions2(lst, x) =
  let
    fun accumulate_substitutions([], result) =
      result
    |   accumulate_substitutions(y::ys, result) =
      case all_except_option(x, y) of
          NONE   => accumulate_substitutions(ys, result)
        | SOME z => accumulate_substitutions(ys, result @ z)
  in
    accumulate_substitutions(lst, [])
  end

fun similar_names(names, {first : string, middle : string, last : string}) =
  let
    fun build_similar_names(lst, result) =
      case lst of
          []    => result
        | x::xs => build_similar_names(xs, result @ [{first = x, middle = middle, last = last}])
  in
    build_similar_names(first::get_substitutions2(names, first), [])
  end

(* you may assume that Num is always used with values 2, 3, ..., 10
   though it will not really come up *)
datatype suit = Clubs | Diamonds | Hearts | Spades
datatype rank = Jack | Queen | King | Ace | Num of int
type card = suit * rank

datatype color = Red | Black
datatype move = Discard of card | Draw

exception IllegalMove

(* put your solutions for problem 2 here *)
fun card_color(card) =
  case card of
      (Spades, _)   => Black
    | (Clubs, _)    => Black
    | (Diamonds, _) => Red
    | (Hearts, _)   => Red

fun card_value(card) =
  case card of
      (_, Num n) => n
    | (_, Ace)   => 11
    | (_, _)     => 10

fun remove_card(cs, c, e) =
  let
    fun remove_internal([], accumulator) =
      accumulator
    | remove_internal(x::xs, (found, lst)) =
      if x = c
      then remove_internal(xs, (true, lst))
      else remove_internal(xs, (found, lst @ [x]))
  in
    case remove_internal(cs, (false, [])) of
      (false, _)     => raise e
    | (true, result) => result
  end

fun all_same_color(cs) =
  case cs of
      []         => true
    | x::[]      => true
    | x::y::tail => card_color(x) = card_color(y) andalso all_same_color(y::tail)

fun sum_cards(cs) =
  let
    fun compute_sum(lst, result) =
      case lst of
          []    => result
        | x::xs => compute_sum(xs, result + card_value(x))
  in
    compute_sum(cs, 0)
  end

fun score(held_cards, goal) =
  let
    val sum = sum_cards(held_cards)
    val preliminary_score = if sum > goal then (3 * (sum - goal)) else (goal - sum)
  in
    if all_same_color(held_cards)
    then preliminary_score div 2
    else preliminary_score
  end

fun officiate(cards, moves, goal) =
  let
    fun run(ms, cs, result) =
      case (ms, cs) of
          ([], _)              => result
        | ((Discard c)::ms, _) => run(ms, cs, remove_card(result, c, IllegalMove))
        | (Draw::ms, [])       => result
        | (Draw::ms, c::left)  => if (card_value(c) + sum_cards(result)) > goal
                                  then c::result
                                  else run(ms, left, c::result)
  in
    score(run(moves, cards, []), goal)
  end

fun card_value_challenge(c) =
  case c of
      (_, Ace) => 1
    | (_, _)   => card_value(c)

fun sum_cards_challenge(cs) =
  let
    fun compute_sum(lst, result) =
      case lst of
          []    => result
        | x::xs => compute_sum(xs, result + card_value(x))
  in
    compute_sum(cs, 0)
  end

fun score_challenge(held_cards, goal) =
  let
    val sum = sum_cards(held_cards)
    val preliminary_score = if sum > goal then (3 * (sum - goal)) else (goal - sum)
  in
    if all_same_color(held_cards)
    then preliminary_score div 2
    else preliminary_score
  end

fun officiate_challenge(cards, moves, goal) =
  let
    fun run(ms, cs, result) =
      case (ms, cs) of
          ([], _)              => result
        | ((Discard c)::ms, _) => run(ms, cs, remove_card(result, c, IllegalMove))
        | (Draw::ms, [])       => result
        | (Draw::ms, c::left)  => if (card_value_challenge(c) + sum_cards_challenge(result)) > goal
                                  then c::result
                                  else run(ms, left, c::result)
  in
    score_challenge(run(moves, cards, []), goal)
  end

fun careful_player(cards, goal) =
  []

