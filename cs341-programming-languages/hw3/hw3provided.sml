(* Coursera Programming Languages, Homework 3, Provided Code *)

exception NoAnswer

datatype pattern = Wildcard
  | Variable of string
  | UnitP
  | ConstP of int
  | TupleP of pattern list
  | ConstructorP of string * pattern

datatype valu = Const of int
  | Unit
  | Tuple of valu list
  | Constructor of string * valu

fun g f1 f2 p =
    let
  val r = g f1 f2
    in
  case p of
      Wildcard          => f1 ()
    | Variable x        => f2 x
    | TupleP ps         => List.foldl (fn (p,i) => (r p) + i) 0 ps
    | ConstructorP(_,p) => r p
    | _                 => 0
  end

(**** for the challenge problem only ****)

datatype typ = Anything
  | UnitT
  | IntT
  | TupleT of typ list
  | Datatype of string

(**** you can put all your code here ****)
fun only_capitals lst =
  List.filter (fn x => Char.isUpper(String.sub(x, 0))) lst

fun longest_string1 lst =
  List.foldl (fn (x, y) => if String.size(x) > String.size(y) then x else y) "" lst

fun longest_string2 lst =
  List.foldl (fn (x, y) => if String.size(x) >= String.size(y) then x else y) "" lst

fun longest_string_helper f lst =
  List.foldl (fn (x, y) => if f(String.size(x), String.size(y)) then x else y) "" lst

val longest_string3 = longest_string_helper (fn (x, y) => (x > y))

val longest_string4 = longest_string_helper (fn (x, y) => (x >= y))

val longest_capitalized = longest_string1 o only_capitals

val rev_string = String.implode o List.rev o String.explode

fun first_answer f lst =
  case (List.mapPartial f lst) of
      []   => raise NoAnswer
    | x::_ => x

fun all_answers f lst =
  let
    fun generate_all_answers([], result)           = SOME result
    |   generate_all_answers(NONE::_, result)      = NONE
    |   generate_all_answers((SOME x)::xs, result) = generate_all_answers(xs, result @ x)
  in
    generate_all_answers(List.map f lst, [])
  end

val count_wildcards = g (fn _ => 1) (fn _ => 0)

val count_wild_and_variable_lengths = g (fn _ => 1) (fn x => String.size x)

fun count_some_var (str, p) =
  g (fn _ => 0) (fn x => if str = x then 1 else 0) p

fun check_pat x =
  let
    fun get_strings (TupleP y)          = List.foldl (fn (z, zs) => get_strings(z) @ zs) [] y
    |   get_strings (Variable y)        = [y]
    |   get_strings (ConstructorP(_,y)) = get_strings y
    |   get_strings (_)                 = []

    fun has_duplicates []      = false
    |   has_duplicates (y::ys) = (List.exists (fn z => z = y) ys) orelse (has_duplicates ys)
  in
    not(has_duplicates(get_strings(x)))
  end

fun match(_, Wildcard)                             = SOME []
|   match(Unit, UnitP)                             = SOME []
|   match(v, Variable s)                           = SOME [(s, v)]
|   match(Const v, ConstP s)                       = if v = s then SOME [] else NONE
|   match(Constructor(s2, v), ConstructorP(s1, s)) = if s1 = s2 then match(v, s) else NONE
|   match(Tuple v, TupleP s) =
      if List.length v <> List.length s
      then NONE
      else all_answers (fn (x, y) => match(x, y)) (ListPair.zip(v, s))
|   match(_, _) = NONE

fun first_match v lst =
  SOME (first_answer (fn p => match(v, p)) lst) handle NoAnswer => NONE
