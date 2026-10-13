#lang racket

(define CANTIDAD 1000000)

(define output-file "randomRacket_1_20.txt")

(call-with-output-file output-file
  (lambda (out)
    (for ([i (in-range CANTIDAD)])
      ;; random con límite genera enteros en [0, n-1]
      (define x (+ 1 (random 20))) ; [1, 20]
      (fprintf out "~a\n" x)))
  #:exists 'replace)

(displayln "Archivo generado correctamente.")
