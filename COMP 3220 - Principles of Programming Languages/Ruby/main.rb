# Dr. Li, TA: Jay Patel(jsp0053@auburn.edu)
# COMP3220 - 002 : Programming Languages
# Project_1

require_relative 'search_controller.rb' 


# Initialize default list ...
defaultSearchList = ["toy story", 
						"spider man", 
						"star wars", 
						"harry potter", 
						"the hobbit", 
						"the hangover"]

# Let first search_controller get default list
controllerObject = SearchController.new(defaultSearchList)
puts "search_list: #{controllerObject.showList}"

##### 
#
# 1.create endless loop 
# 2.get an input from terminal(console)
# 3.update search suggestion list
# 4.loop should end when user write "exit"
# 5.save updated "searchSuggestionList" to "data.txt" file
#
#####


# Create endless loop
while true
  # Gets user input
  input = gets.chomp
  # Loop ends when user writes exit
  if input == "exit"
    break
  else
    #Otherwise update the list
    controllerObject.updateList(input)
  end
end
#After user ends, save the final list to a file called "data.txt"
controllerObject.saveListToFile