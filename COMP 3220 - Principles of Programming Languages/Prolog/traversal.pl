%Austin Osborn
%aeo0015@auburn.edu
%COMP3320-002
%Project 3 - Prolog
%Facts% -----------------------------------------------------------------------------

%%room - one zone in the house
room(1).
room(2).
room(3).
room(4).
room(5).
room(6).
room(7).
room(8).
room(9).
room(10).
room(11).
room(12).
room(13).
room(14).
room(15).
room(16).

%connected - tells whether or not two rooms connect directly to each other
connected(1,2).
connected(1,7).
connected(2,8).
connected(3,8).
connected(4,8).
connected(4,9).
connected(5,6).
connected(5,9).
connected(6,9).
connected(7,8).
connected(7,9).
connected(7,10).
connected(7,11).
connected(7,12).
connected(7,13).
connected(7,14).
connected(14,15).
connected(15,16).
%phone - tells if room has a phone in it
phone(5).
phone(9).
phone(16).

%Predicates----------------------------------------------------------------------------------

%Inverse the connected list to prevent redundant facts
%Premise: If room X is connected to room Y, then room Y is also connected to room X
neighbors(X, Y):-(connected(X, Y); connected(Y, X)).

showPaths(StartRoom,DestRoom):-nonvar(StartRoom), nonvar(DestRoom),
	forall(generatePath(StartRoom, DestRoom), nl).


generatePath(Start,Dest):-nonvar(Start), nonvar(Dest),
	Tail = [],
	search(Start, Dest, Tail, Room),
	flip(Room,Route, []),
	write(Route).

%Search methods
%Base case handler (when current location and target are the same)
search(A,A,B,[A|B]).
%General recursive call to keep going if rooms are neighbors and not already in list
search(Current,Goal,Tail,Room):-
    neighbors(Current,NextRoom),
	\+(member(NextRoom,Tail)),
	search(NextRoom,Goal,[Current|Tail],Room).

%Utility method to flip the array for proper printing
flip([],Z,Z).
flip([Head|Tail],Z,Acc) :-flip(Tail,Z,[Head|Acc]).

%User predicates ----------------------------------------------------------------------

%Query contains start and end rooms
%Destination must have a phone in it
list_paths(Start,End):-nonvar(Start), nonvar(End),
	phone(End),
	showPaths(Start, End)
    ;
    \+phone(End),
    write("No").

%Query contains only the end room
%Returns every possible path to the destination room from any source.
%Destination must have a phone in it
list_paths(Start,End):-var(Start), nonvar(End),
	phone(End),
	forall(room(E), (showPaths(E, End)))
    ;
    \+phone(End),
    write("No").

%Query contains only the start room
%Returns every possible path to any room with a phone from a given room
list_paths(Start,End):-nonvar(Start), var(End),
	forall(phone(E), (showPaths(Start, E))).

%Query contains neither start or end room
%Returns all possible paths to a room with a phone from any other room
list_paths(Start,End):-var(Start), var(End),
	forall(phone(X), forall(room(Room), (showPaths(Room, X)))).
