# Most Recent Search Project

This program simulates a search engine. It has a static initial list of movies every time it starts.
Every time the user enters a string it is added to the top/front of their searches.
Entries into this list contain no duplicates and are case insensitive.
Entry continues until the user types "exit".
The user's search list is then saved to a local file 'data.txt' that can be found in the directory of execution.

* One minor quark of the program is that it prints the list twice on the initial call to showList.

### Quick start
Make sure you have Ruby installed on your computer.
If you are having problems, Ruby 2.5.1 was used in the creation and testing of this project.

```

# For Linux/Mac/Windows
> Clone/Download the zip file from canvas
> Uncompress the files into some directory
> Navigate in terminal or cmd prompt to this directory
> In terminal, execute the following...
$ ruby main.rb

```

# Table of Contents
* [Running the app](#running-the-app)
* [License](#license)
* [Author](#author)


#### API Intro

SearchController is a controller that manages the users searches.
It handles entering the user searches into a list, printing the list, and saving the list to a file.

```
Class SearchController
  #String array of movie searches
  attr_accessor :searchSuggestionList
  #Functions (detailed below)
  def showList()
  def updateList(movie_name)
  def saveListToFile()
end
```

SearchController API

```
#   @param movie_name (Search input of user)
#   Moves most recent search to front of searchSuggestionList
#   Removes any duplicates (case insensitive)
def updateList(movie_name)

#  Prints the current user search list (One movie per line)
def showList()

#  Saves current user search list to 'data.txt'
#  'data.txt' will be stored in the directory of execution
def updateList(movie_name)
```
___

#### Implementation of SearchController

The Most Recent Search program is implemented with MVC architecture. The view is the terminal. The model is searchSuggestionList. The SearchController acts as the mediator between the view and model.

___

#### Program Time Complexity

The program runs with at most O(n) time complexity in its public API methods.

___

#### Result of Sample Test Case
Terminal execution
-------------------------------------------------------------------------------------------------------------
austin@austin-Aspire-E5-575:~/RubymineProjects/Project1$ cd '/home/austin/RubymineProjects/Project1'
austin@austin-Aspire-E5-575:~/RubymineProjects/Project1$ ruby main.rb
toy story
spider man
star wars
harry potter
the hobbit
the hangover
search_list: ["toy story", "spider man", "star wars", "harry potter", "the hobbit", "the hangover"]
The Incredible Hulk
StAR WaRs
exit
austin@austin-Aspire-E5-575:~/RubymineProjects/Project1$

data.txt output
-------------------------------------------------------------------------------------------------------------
StAR WaRs
The Incredible Hulk
toy story
spider man
harry potter
the hobbit
the hangover
___

#### License
 Permission is hereby granted to any and all people to use this code in whatever application they desire.

___


#### Author
  Austin Osborn
  aeo0015@auburn.edu
