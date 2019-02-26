# Traversal with prolog!

We have a house with rooms. Rooms can be connected, or not. Rooms can have a phone in them. 
Our mission: Transverse the Home to find the ringiing phone.



# Table of Contents
* [Installing](#installing)
* [Running the app](#running-the-app)
* [License](#license)
* [Author](#author)


### Installing

This program was written in prolog.
You can run it online here.  [here](https://swish.swi-prolog.org/).
### Running the app

To execute run the following in the terminal or command line
The app is used through the query list_paths(Room1,Room2).
These can either be variables (denoted by an input that starts with a capital letter), or integer literals denoting room number.

___

#### API Intro
In our program, we'll use various forms of list_paths queries, denoted by the specs below.

1)If I give the program a starting room and an ending room, if there is a phone ringing in the ending room, the program should tell me how to get to that room (which rooms do I need to go through?).
2)Alternatively, if I give the program a starting room and an ending room, and there is no phone ringing in that room, the program should not return any output (actually, prolog should just print “no”).
3)If I only give the program a starting room. The program should give me every possible sequence of rooms that I could go through, starting from the starting room that I gave it, to reach any room with a phone ringing.
4)If I only give the program an ending room, if there is a ringing phone in that room, the program should give me every possible sequence of rooms that I could go through (including multiple starting rooms, and all sequences that start with each of those rooms), to reach that room. If there is no phone ringing, it should simply return “no”.
5)Finally, if I don’t give the program any starting or ending room, it should simply return every possible sequence of rooms I must go through to reach all of the rooms with phones ringing (should be a lot!).

Usage 1: Given a starting room and ending room with a phone ringing

```
?-list_paths(1,16)

[1, 2, 8, 4, 9, 7, 14, 15, 16]
[1, 2, 8, 7, 14, 15, 16]
[1, 7, 14, 15, 16]

```

Usage 2: Given a starting room and ending room with no phone ringing

```
?-list_paths(1,15)

No

```

Usage 3: Given a starting room, find every possible ending room

```
?-list_paths(1,X)

[1, 2, 8, 4, 9, 5]
[1, 2, 8, 4, 9, 6, 5]
[1, 2, 8, 7, 9, 5]
[1, 2, 8, 7, 9, 6, 5]
[1, 7, 8, 4, 9, 5]
[1, 7, 8, 4, 9, 6, 5]
[1, 7, 9, 5]
[1, 7, 9, 6, 5]
[1, 2, 8, 4, 9]
[1, 2, 8, 7, 9]
[1, 7, 8, 4, 9]
[1, 7, 9]
[1, 2, 8, 4, 9, 7, 14, 15, 16]
[1, 2, 8, 7, 14, 15, 16]
[1, 7, 14, 15, 16]

```

Usage 4: Given an ending room, find every possible starting rooms and routes to get there

```
?-list_paths(X,15)

No
```

```
?-list_paths(X,16)

[1, 2, 8, 4, 9, 7, 14, 15, 16]
[1, 2, 8, 7, 14, 15, 16]
[1, 7, 14, 15, 16]
[2, 8, 4, 9, 7, 14, 15, 16]
[2, 8, 7, 14, 15, 16]
[2, 1, 7, 14, 15, 16]
[3, 8, 2, 1, 7, 14, 15, 16]
[3, 8, 4, 9, 7, 14, 15, 16]
[3, 8, 7, 14, 15, 16]
[4, 8, 2, 1, 7, 14, 15, 16]
[4, 8, 7, 14, 15, 16]
[4, 9, 7, 14, 15, 16]
[5, 6, 9, 4, 8, 2, 1, 7, 14, 15, 16]
[5, 6, 9, 4, 8, 7, 14, 15, 16]
[5, 6, 9, 7, 14, 15, 16]
[5, 9, 4, 8, 2, 1, 7, 14, 15, 16]
[5, 9, 4, 8, 7, 14, 15, 16]
[5, 9, 7, 14, 15, 16]
[6, 9, 4, 8, 2, 1, 7, 14, 15, 16]
[6, 9, 4, 8, 7, 14, 15, 16]
[6, 9, 7, 14, 15, 16]
[6, 5, 9, 4, 8, 2, 1, 7, 14, 15, 16]
[6, 5, 9, 4, 8, 7, 14, 15, 16]
[6, 5, 9, 7, 14, 15, 16]
[7, 14, 15, 16]
[8, 2, 1, 7, 14, 15, 16]
[8, 4, 9, 7, 14, 15, 16]
[8, 7, 14, 15, 16]
[9, 4, 8, 2, 1, 7, 14, 15, 16]
[9, 4, 8, 7, 14, 15, 16]
[9, 7, 14, 15, 16]
[10, 7, 14, 15, 16]
[11, 7, 14, 15, 16]
[12, 7, 14, 15, 16]
[13, 7, 14, 15, 16]
[14, 15, 16]
[15, 16]
[16]
```

Usage 5: Given no start or end rooms, find every valid sequence from every starting room to every ending room.

```
?-list_paths(X,Y)

[1, 2, 8, 4, 9, 5]
[1, 2, 8, 4, 9, 6, 5]
[1, 2, 8, 7, 9, 5]
[1, 2, 8, 7, 9, 6, 5]
[1, 7, 8, 4, 9, 5]
[1, 7, 8, 4, 9, 6, 5]
[1, 7, 9, 5]
[1, 7, 9, 6, 5]
[2, 8, 4, 9, 5]
[2, 8, 4, 9, 6, 5]
[2, 8, 7, 9, 5]
[2, 8, 7, 9, 6, 5]
[2, 1, 7, 8, 4, 9, 5]
[2, 1, 7, 8, 4, 9, 6, 5]
[2, 1, 7, 9, 5]
[2, 1, 7, 9, 6, 5]
[3, 8, 2, 1, 7, 9, 5]
[3, 8, 2, 1, 7, 9, 6, 5]
[3, 8, 4, 9, 5]
[3, 8, 4, 9, 6, 5]
[3, 8, 7, 9, 5]
[3, 8, 7, 9, 6, 5]
[4, 8, 2, 1, 7, 9, 5]
[4, 8, 2, 1, 7, 9, 6, 5]
[4, 8, 7, 9, 5]
[4, 8, 7, 9, 6, 5]
[4, 9, 5]
[4, 9, 6, 5]
[5]
[6, 9, 5]
[6, 5]
[7, 8, 4, 9, 5]
[7, 8, 4, 9, 6, 5]
[7, 9, 5]
[7, 9, 6, 5]
[7, 1, 2, 8, 4, 9, 5]
[7, 1, 2, 8, 4, 9, 6, 5]
[8, 2, 1, 7, 9, 5]
[8, 2, 1, 7, 9, 6, 5]
[8, 4, 9, 5]
[8, 4, 9, 6, 5]
[8, 7, 9, 5]
[8, 7, 9, 6, 5]
[9, 5]
[9, 6, 5]
[10, 7, 8, 4, 9, 5]
[10, 7, 8, 4, 9, 6, 5]
[10, 7, 9, 5]
[10, 7, 9, 6, 5]
[10, 7, 1, 2, 8, 4, 9, 5]
[10, 7, 1, 2, 8, 4, 9, 6, 5]
[11, 7, 8, 4, 9, 5]
[11, 7, 8, 4, 9, 6, 5]
[11, 7, 9, 5]
[11, 7, 9, 6, 5]
[11, 7, 1, 2, 8, 4, 9, 5]
[11, 7, 1, 2, 8, 4, 9, 6, 5]
[12, 7, 8, 4, 9, 5]
[12, 7, 8, 4, 9, 6, 5]
[12, 7, 9, 5]
[12, 7, 9, 6, 5]
[12, 7, 1, 2, 8, 4, 9, 5]
[12, 7, 1, 2, 8, 4, 9, 6, 5]
[13, 7, 8, 4, 9, 5]
[13, 7, 8, 4, 9, 6, 5]
[13, 7, 9, 5]
[13, 7, 9, 6, 5]
[13, 7, 1, 2, 8, 4, 9, 5]
[13, 7, 1, 2, 8, 4, 9, 6, 5]
[14, 7, 8, 4, 9, 5]
[14, 7, 8, 4, 9, 6, 5]
[14, 7, 9, 5]
[14, 7, 9, 6, 5]
[14, 7, 1, 2, 8, 4, 9, 5]
[14, 7, 1, 2, 8, 4, 9, 6, 5]
[15, 14, 7, 8, 4, 9, 5]
[15, 14, 7, 8, 4, 9, 6, 5]
[15, 14, 7, 9, 5]
[15, 14, 7, 9, 6, 5]
[15, 14, 7, 1, 2, 8, 4, 9, 5]
[15, 14, 7, 1, 2, 8, 4, 9, 6, 5]
[16, 15, 14, 7, 8, 4, 9, 5]
[16, 15, 14, 7, 8, 4, 9, 6, 5]
[16, 15, 14, 7, 9, 5]
[16, 15, 14, 7, 9, 6, 5]
[16, 15, 14, 7, 1, 2, 8, 4, 9, 5]
[16, 15, 14, 7, 1, 2, 8, 4, 9, 6, 5]
[1, 2, 8, 4, 9]
[1, 2, 8, 7, 9]
[1, 7, 8, 4, 9]
[1, 7, 9]
[2, 8, 4, 9]
[2, 8, 7, 9]
[2, 1, 7, 8, 4, 9]
[2, 1, 7, 9]
[3, 8, 2, 1, 7, 9]
[3, 8, 4, 9]
[3, 8, 7, 9]
[4, 8, 2, 1, 7, 9]
[4, 8, 7, 9]
[4, 9]
[5, 6, 9]
[5, 9]
[6, 9]
[6, 5, 9]
[7, 8, 4, 9]
[7, 9]
[7, 1, 2, 8, 4, 9]
[8, 2, 1, 7, 9]
[8, 4, 9]
[8, 7, 9]
[9]
[10, 7, 8, 4, 9]
[10, 7, 9]
[10, 7, 1, 2, 8, 4, 9]
[11, 7, 8, 4, 9]
[11, 7, 9]
[11, 7, 1, 2, 8, 4, 9]
[12, 7, 8, 4, 9]
[12, 7, 9]
[12, 7, 1, 2, 8, 4, 9]
[13, 7, 8, 4, 9]
[13, 7, 9]
[13, 7, 1, 2, 8, 4, 9]
[14, 7, 8, 4, 9]
[14, 7, 9]
[14, 7, 1, 2, 8, 4, 9]
[15, 14, 7, 8, 4, 9]
[15, 14, 7, 9]
[15, 14, 7, 1, 2, 8, 4, 9]
[16, 15, 14, 7, 8, 4, 9]
[16, 15, 14, 7, 9]
[16, 15, 14, 7, 1, 2, 8, 4, 9]
[1, 2, 8, 4, 9, 7, 14, 15, 16]
[1, 2, 8, 7, 14, 15, 16]
[1, 7, 14, 15, 16]
[2, 8, 4, 9, 7, 14, 15, 16]
[2, 8, 7, 14, 15, 16]
[2, 1, 7, 14, 15, 16]
[3, 8, 2, 1, 7, 14, 15, 16]
[3, 8, 4, 9, 7, 14, 15, 16]
[3, 8, 7, 14, 15, 16]
[4, 8, 2, 1, 7, 14, 15, 16]
[4, 8, 7, 14, 15, 16]
[4, 9, 7, 14, 15, 16]
[5, 6, 9, 4, 8, 2, 1, 7, 14, 15, 16]
[5, 6, 9, 4, 8, 7, 14, 15, 16]
[5, 6, 9, 7, 14, 15, 16]
[5, 9, 4, 8, 2, 1, 7, 14, 15, 16]
[5, 9, 4, 8, 7, 14, 15, 16]
[5, 9, 7, 14, 15, 16]
[6, 9, 4, 8, 2, 1, 7, 14, 15, 16]
[6, 9, 4, 8, 7, 14, 15, 16]
[6, 9, 7, 14, 15, 16]
[6, 5, 9, 4, 8, 2, 1, 7, 14, 15, 16]
[6, 5, 9, 4, 8, 7, 14, 15, 16]
[6, 5, 9, 7, 14, 15, 16]
[7, 14, 15, 16]
[8, 2, 1, 7, 14, 15, 16]
[8, 4, 9, 7, 14, 15, 16]
[8, 7, 14, 15, 16]
[9, 4, 8, 2, 1, 7, 14, 15, 16]
[9, 4, 8, 7, 14, 15, 16]
[9, 7, 14, 15, 16]
[10, 7, 14, 15, 16]
[11, 7, 14, 15, 16]
[12, 7, 14, 15, 16]
[13, 7, 14, 15, 16]
[14, 15, 16]
[15, 16]
[16]
```
```


### License
Permission is hereby granted for any persons to use the code contained within this application
for any and all purposes without crediting the original creator.

___

### Author
Austin Osborn
aeo0015@auburn.edu
