# Austin Osborn (aeo0015@auburn.edu)
# COMP3220 - 002 : Programming Languages
# Project_1

# Search controller class
class SearchController

  attr_accessor :searchSuggestionList

  def initialize(search_list = [])
    #Create a new search controller given an initial search list of movies
    @searchSuggestionList = search_list

  end

  def showList()
    #For each item in the list of movies, print the movie
    @searchSuggestionList.each do |movie|
      puts movie
    end
  end

  def updateList(movie_name)
    #Apply a map to the array to downcase every letter of every item
    downcased = searchSuggestionList.map(&:downcase)
    #See if the downcased version of user input is already in the map
    index = downcased.index(movie_name.downcase)
    #If the entered movie is already there, then remove it.
    if index != nil
      @searchSuggestionList.delete_at(index)
    end
    #Append the entered movie to the front of the list
    @searchSuggestionList.insert(0, movie_name)
  end

  def saveListToFile()
    #Use the file class to open 'data.txt' in current execution directory
    # (One will be created if it doesn't already exist)
    File.open('data.txt', "w") do |writer|
      #For each item in the list, write that item followed by a new line
      @searchSuggestionList.each do |movie|
        writer.write("#{movie}\n")
      end
    end
  end

end

