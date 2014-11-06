#lang racket

(provide (all-defined-out)) ;; so we can put tests in a second file

;; put your code below

; Problem 1
(define (sequence low high stride)
  (if (> low high)
      null
      (cons low (sequence (+ low stride) high stride))))

; Problem 2
(define (string-append-map xs suffix)
  (map (lambda (x) (string-append x suffix)) xs))

; Problem 3
(define (list-nth-mod xs n)
  (cond [(< n 0)    (error "list-nth-mod: negative number")]
        [(null? xs) (error "list-nth-mod: empty list")]
        [#t         (list-ref xs (remainder n (length xs)))]))
      
; Problem 4
(define (stream-for-n-steps s n)
  (let ([pr (s)])
    (if (< n 2)
        (list (car pr))
        (cons (car pr) (stream-for-n-steps (cdr pr) (- n 1))))))

; Problem 5
(define funny-number-stream 
  (letrec ([divisible-by? (lambda (n m) (= 0 (modulo n m)))]
           [funny-number (lambda (x) (if (divisible-by? x 5) (- x) x))]
           [stream (lambda (x) (cons (funny-number x) (lambda () (stream (+ x 1)))))])
    (lambda () (stream 1))))

; Problem 6
(define dan-then-dog
  (letrec ([dan (cons "dan.jpg" (lambda () dog))] [dog (cons "dog.jpg" (lambda () dan))])
    (lambda () dan)))

; Problem 7
(define (stream-add-zero s)
  (lambda ()
    (let ([pr (s)])
      (cons (cons 0 (car pr)) (stream-add-zero (cdr pr))))))
  
; Problem 8
(define (cycle-lists xs ys)
  (letrec ([make-pair (lambda (n) (cons (list-nth-mod xs n) (list-nth-mod ys n)))]
           [stream (lambda (n) (cons (make-pair n) (lambda () (stream (+ n 1)))))])
    (lambda () (stream 0))))

; Problem 9
(define (vector-assoc v vec)
  (letrec ([find (lambda (n)
      (if (= n (vector-length vec))
          #f
          (let ([pair (vector-ref vec n)])
            (cond [(not (pair? pair)) (find (+ n 1))]
                  [(equal? v (car pair)) pair]
                  [#t(find (+ n 1))]))))])
    (find 0))) 

; Problem 10
(define (cached-assoc xs n)
  (letrec([memo (make-vector n #f)]
          [position 0]
          [f (lambda (v)
            (let ([ans (vector-assoc v memo)])
              (if ans
                  (cdr ans)
                  (let ([new-ans (assoc v xs)])
                    (begin
                      (vector-set! memo position new-ans)
                      (set! position (remainder (+ position 1) n))
                      new-ans)))))])
    f))
