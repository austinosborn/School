# Welcome to the Lee County Funfair!

Lee county is organizing a county fair over the upcoming summer. You along with one other friend plan to participate in several games including the bucket ball game. Each player will be assigned a bucket to start with and the player that gets the bucket with the highest worth wins the game. The worth of each bucket is calculated as per the rules below.

A bucket contains 10 balls of four different colors – red, blue, white, and green. Each red is worth 10 points, each green is worth 15 points, each blue ball is worth 20 points, and each white ball is worth 1 point.

# Table of Contents
* [Installing](#installing)
* [Running the app](#running-the-app)
* [License](#license)
* [Author](#author)


### Installing

In order to run this program, you must install Racket on your computer.
The latest version can be downloaded  [here](https://racket-lang.org/download/).
### Running the app

To execute run the following in the terminal or command line
```
racket funfair_scheme.rkt
```

___

#### API Intro
In our program, we'll represent a ball by a word like R (red ball) or B (blue ball). A bucket will be a sentence of balls, like this: (R B G R R R B W W R)

There are five functions in this scheme program. They all build on top of the previous. They are (in order) ...
```
*Ball-val

A procedure ball-val that takes a single ball as its argument and returns the value of that ball.

> (ball-val 'B)
20
```

```
*Count-balls

A procedure count-balls that takes a color and a bucket as arguments and
returns the number of balls in the bucket with the given color.

> (count-balls 'W '(W R R R R G B B G W))
2
```

```
*Color-counts

A procedure color-counts that takes a bucket as its argument and
returns a sentence containing the number of reds, the number of green,
the number of blues, and the number of whites in the bucket.

> (color-counts '(R B G R R R B W R W))
'(5 1 2 2)
```
```
*Bucket-val

A procedure bucket-val that takes a bucket as its argument and
returns the total number of points that the bucket is worth.

> (bucket-val '(R B G R R R B W R W))
107
```
```
*Judge

A procedure judge that takes two argument buckets
and returns who won the game.

> (judge '(R B G R R R B W R W) '(W R R R R G B B G W))
Bucket 2 WINS!
> (judge '(R B G R G W B B R W) '(R B R G R W B B G W))
It's a TIE
```

___

### License
Permission is hereby granted for any persons to use the code contained within this application
for any and all purposes without crediting the original creator.

___

### Author
Austin Osborn
aeo0015@auburn.edu
