#lang racket
(require (planet dyoo/simply-scheme:1:2/simply-scheme))
  
;Return the value of a given ball
(define (ball-val ball)
  (cond ((equal? ball "R") 10)
        ((equal? ball "G") 15)
        ((equal? ball "B") 20)
        ((equal? ball "W") 1)
        )
)

;Return the number of balls of a given color in a given bucket
(define (count-balls color bucket)
  (count
   (keep
    (lambda (c)
      (equal? color c)) bucket)
   )
 )

;Return the number of (red, green, blue, white) balls in a given bucket
(define (color-counts bucket)
  (list (count-balls 'R bucket) (count-balls 'G bucket) (count-balls 'B bucket) (count-balls 'W bucket))
 )

;Return the total point value of a bucket
(define (bucket-val bucket)
  (apply + (map * (color-counts bucket) (list (ball-val 'R) (ball-val 'G) (ball-val 'B) (ball-val 'W))))
 )

;Judge function
(define (judge b1 b2)
  (cond ((= (bucket-val b1) (bucket-val b2)) "It's a TIE")
       ((> (bucket-val b1) (bucket-val b2)) "Bucket 1 WINS!")
       ((< (bucket-val b1) (bucket-val b2)) "Bucket 2 WINS!")
  )
 )

;Sample outputs
(display "SAMPLE OUTPUTS:\n\n")
(display "(judge '(R B G R R R B W R W) '(W R R R R G B B G W))\n")
(judge '(R B G R R R B W R W) '(W R R R R G B B G W))
;Bucket 1
(display "\nBucket 1:\n")
(display "(bucket-val '(R B G R R R B W R W))\n")
(bucket-val '(R B G R R R B W R W))
(display "(color-counts '(R B G R R R B W R W))\n")
(color-counts '(R B G R R R B W R W))
;Bucket 2
(display "\nBucket 2:\n")
(display "(bucket-val '(W R R R R G B B G W))\n")
(bucket-val '(W R R R R G B B G W))
(display "(color-counts '(W R R R R G B B G W))\n")
(color-counts '(W R R R R G B B G W)) 