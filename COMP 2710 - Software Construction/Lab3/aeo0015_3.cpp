// Lab 3:     Multiplayer Snakes and Ladders
// Class:     COMP 2710-001
// Date:      10/30/2017
// Email:     aeo0015@auburn.edu
//
// Description: The Snakes and Ladders multiplayer game pits multiple players on a grid with a defined start and end point.
//              Each person rolls and has that many moves per turn. They can choose to go north, south, east or west.
//              Be careful though! If you land on a space with a snake or ladder, it will transport you some place beyond
//              your control. The first player to reach the end wins. GLHF!
#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

//INPUT DIRECTORY TO FILE NAME HERE FOR TESTING.
const std::string fileName = "Maze 2.txt";

using namespace std;
//Foward Class Declarations
class Menu; class System; class Player; class Node;


// Class:       Node
// Description: The Node class is used to represent spaces on the board in this board game.
//              Each Node is a location that holds pointers to its potential neighbors. Together, these nodes abstract a graph.
//              Players will try to win the game by reaching the destination node. Nodes with Snake/Ladders attached will automatically be went to if a
//              player lands on the node, otherwise, they are given a choice of which direction to go.
class Node {
public:
    Node();
    explicit Node(string newname);
    string getNodeName();
    void attachNewNode(Node *newNode, int dir);
    Node *getAttachedNode(int dir);
    void attachSnakeLadderNode(Node *newNode);
    Node *getSnakeLadderNode();
private:
    string name;
    Node *attachedNodes[4];
    Node *snakeOrLadderNode;
};


// Class:       Player
// Description: The Player class will represent each user playing. It keeps track of their name, their current position on the board,
//              a list of nodes they've already been to, a number (denoting turn order)
class Player {
public:
    explicit Player(string name);
    string name;
    int number;
    vector<string> steps;
    Node* position;
};

// Class:       Menu
// Description: The Menu class handles all user inputs and is also responsible fpr outputting anything to the console
//              that is pertinent to system operation by the user.
class Menu {
public:
    void printBar(string text);
    void initializePlayers();
    void selection();
    string listChoices();
    void victory();
    System* system;
    int rng();
};

// Class:       System
// Description: The system class will be the main data store of the program. It will be responsible for pulling in and parsing
//              the graph from a .txt file. It will also generate and store a list of players. It will also have the roll utility
//              method and keep track of whether a player has reached the finished.
//
class System{
public:
    Node * finish;
    Node * start;
    Node * getNodeWithName(string target);
    vector<Node*> nodes;
    vector<Player*> players;
    bool inPlay = true;
    Player * currentPlayer;
    int turn = 0;
    void initializeBoard(string infile);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MAIN METHOD
int main() {
    System s = System();
    Menu m = Menu();
    m.system = &s;
    s.initializeBoard(fileName);
    m.initializePlayers();
    m.selection();
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of Node Class
//
// Function:     Constructors
// Output:       New Node object
// Description:  Creates new Node object (with a given name).
Node::Node() {
    name = "GENERIC";
    attachedNodes[0] = nullptr;
    attachedNodes[1] = nullptr;
    attachedNodes[2] = nullptr;
    attachedNodes[3] = nullptr;
    snakeOrLadderNode = nullptr;
}

Node::Node(string newname) {
    name = newname;
    attachedNodes[0] = nullptr;
    attachedNodes[1] = nullptr;
    attachedNodes[2] = nullptr;
    attachedNodes[3] = nullptr;
    snakeOrLadderNode = nullptr;
}

// Function:     getNodeName
// Description:  Returns the node's name
string Node::getNodeName() {
    return name;
}

// Function:     attachNewNode
// Inputs:       Node pointer, Direction integer
// Description:  Attaches a north(0), east(1), south(2), or west(3) node
void Node::attachNewNode(Node *newNode, int dir) {
    attachedNodes[dir] = newNode;
}

// Function:     getAttachedNode
// Inputs:       Direction integer
// Outputs:      Directional node
// Description:  Returns the node in the given direction. Null if it isn't there.
Node *Node::getAttachedNode(int dir) {
    return attachedNodes[dir];
}

// Function:     attachSnakeLadderNode
// Inputs:       Node to attach
// Description:  Attached an input node as a snake/ladder to current node.
void Node::attachSnakeLadderNode(Node *newNode) {
    snakeOrLadderNode = newNode;
}

// Function:     getSnakeLadderNode
// Outputs:      Snake/Ladder node
// Description:  Returns the snake/ladder node. Null if not present
Node * Node::getSnakeLadderNode() {
    return snakeOrLadderNode;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of Player Class
//
// Function:     Constructor
// Inputs:       Name of player
// Output:       player object
// Description:  Creates new Player object with a given name.
Player::Player(string name) {
    this->name = name;
    this->number = -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of Menu Class
//
// Function:     printBar
// Inputs:       Desired Text Output
// Description:  Prints a formatted message to the console. Utility method to make UI more readable.
void Menu::printBar (string text) {
    int size = 2 * text.size();
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < size; j++) {
                cout << "-";
            }
            cout << "\n";
        }
        else {
            double d = (double) size / 4;
            int newSize = (int) d;
            for (int j = 0; j < newSize; j ++) {
                cout << " ";
            }
            cout << text;
            cout << "\n";
        }
    }
};

// Function:     initalizePlayers
// Description:  Prompts user to enter number of player, then adds each player entered to the system. Handles faulty
//               input and duplicates.
void Menu::initializePlayers() {
    //Welcome message
    printBar("Welcome to Snakes and Ladders");
    //Gets a valid number of users
    string input; int n = -1;
    while (!((n>0) && (n<10))) {
        cout << "Please enter number of players: ";
        getline(cin, input);
        try {
            n = stoi(input);
        }
        catch (exception e) {
            cout << "Please enter a valid number" << endl;
        }
    }
    //Creates those users using names inputted.
    while (system->players.size() < n) {
        int currentPlayers = (int) system->players.size();
        cout << "\nEnter player #" << currentPlayers + 1 << " name: ";
        string input;
        getline(cin, input);
        //Ensures no duplicates player names
        bool dupe = false;
        for (Player * p : system->players) {
            if (p->name == input) {
                dupe = true;
            }
        }
        //Adds player object
        if (!dupe) {
            Player *p = new Player(input);
            p->number = system->players.size();
            system->players.push_back(p);
        }
    }
    //Put first node into each players list of visited
    for (Player * p : system->players) {
        string name = system->start->getNodeName();
        p->steps.push_back(name);
        p->position = system->start;
    }
    //Sets up first turn
    system->currentPlayer = system->players.at(0);
}


// Function:     selection
// Description:  Continually prompts user with roll/select direction loop until a player wins.
void Menu::selection() {
    //Initialize who's turn and keep track
    int turn = 0;
    //While nobody has achieved victory...
    while (system->inPlay) {
        //UI Implementation
        string currentName = system->currentPlayer->name;
        printBar(currentName + "'s turn");
        cout << currentName + "'s turn to throw the dice. Hit enter";
        cin.get();
        int roll = rng();
        cout << "\n" << currentName +" rolled a " << roll << endl << endl;
        //For the number of turns the player rolled...
        for (int i = 0; i < roll; i++) {
            //UI Implementation
            Node *currentNode = system->currentPlayer->position;
            cout << currentName << " is currently at node " << currentNode->getNodeName();
            //Moves along snake or ladder if the current position has one.
            while (currentNode->getSnakeLadderNode() != NULL) {
                currentNode = system->currentPlayer->position;
                system->currentPlayer->position = currentNode->getSnakeLadderNode();
                currentNode = system->currentPlayer->position;
                cout << ". You have taken a ladder to " + system->currentPlayer->position->getNodeName();
                //Pushes the players new location to the end of their list of visited nodes
                system->currentPlayer->steps.push_back(system->currentPlayer->position->getNodeName());
            }
            //Gives user a list of their standard Node move choices
            cout << listChoices();
            bool enteredValidDirection = false;
            //Switch statement to handle input and move player on board
            while (!enteredValidDirection) {
                string input;
                getline(cin, input);
                if (input.size() == 0) {
                    cout << "Invalid input. Please try again: ";
                    continue;
                }
                switch (input.at(0)) {
                    // Each case checks first letter of user input and ensures that the node has a valid neighbor.
                    // Also adds the new location to the list of visited nodes
                    case 'N':
                    case 'n':
                        if (system->currentPlayer->position->getAttachedNode(0) != NULL) {
                            system->currentPlayer->position = system->currentPlayer->position->getAttachedNode(0);
                            //Pushes the players new location to the end of their list of visited nodes
                            system->currentPlayer->steps.push_back(system->currentPlayer->position->getNodeName());
                            enteredValidDirection = true;
                        }
                        else {
                            cout << "Invalid input. Please try again: ";
                        }
                        break;
                    case 'E':
                    case 'e':
                        if (system->currentPlayer->position->getAttachedNode(1) != NULL) {
                            system->currentPlayer->position = system->currentPlayer->position->getAttachedNode(1);
                            system->currentPlayer->steps.push_back(system->currentPlayer->position->getNodeName());
                            enteredValidDirection = true;
                        }
                        else {
                            cout << "Invalid input. Please try again: ";
                        }
                        break;
                    case 'S':
                    case 's':
                        if (system->currentPlayer->position->getAttachedNode(2) != NULL) {
                            system->currentPlayer->position = system->currentPlayer->position->getAttachedNode(2);
                            system->currentPlayer->steps.push_back(system->currentPlayer->position->getNodeName());
                            enteredValidDirection = true;
                        }
                        else {
                            cout << "Invalid input. Please try again: ";
                        }
                        break;
                    case 'W':
                    case 'w':
                        if (system->currentPlayer->position->getAttachedNode(3) != NULL) {
                            system->currentPlayer->position = system->currentPlayer->position->getAttachedNode(3);
                            system->currentPlayer->steps.push_back(system->currentPlayer->position->getNodeName());
                            enteredValidDirection = true;
                        }
                        else {
                            cout << "Invalid input. Please try again: ";
                        }
                        break;
                    default:
                        cout << "Invalid input. Please try again: ";
                }
            }
            //Check for victory
            string position = system->currentPlayer->position->getNodeName();
            string endgoal = system->finish->getNodeName();
            if (position == endgoal) {
                victory();
                system->inPlay = false;
                break;
            }
        }
        //Select next player to go
        turn++;
        if (turn == system->players.size()) {
            turn = 0;
        }
        system->currentPlayer = system->players.at(turn);
    }
}

// Function:     victory
// Description:  Prints victory message with list of nodes a player took.
void Menu::victory() {
    printBar("Congratulations " + system->currentPlayer->name);
    cout << "YOU'RE WINNER :)" << endl; //Ref: http://knowyourmeme.com/memes/big-rigs-over-the-road-racing :)
    cout << "  .__.\n"
            " (|  |)\n"
            "  (  )\n"
            "  _)(_\n";
    cout << "The steps you took were: ";
    for (string s : system->currentPlayer->steps) {
        cout << s << " ";
    }
    cout << endl;

}

// Function:     listChoices
// Description:  Prints list of all valid options for user to move to.
string Menu::listChoices() {
    string choices = ". You can go";
    if (system->currentPlayer->position->getAttachedNode(0) != NULL) {
        choices += " North(n)";
    }
    if (system->currentPlayer->position->getAttachedNode(1) != NULL) {
        choices += " East(e)";
    }
    if (system->currentPlayer->position->getAttachedNode(2) != NULL) {
        choices += " South(s)";
    }
    if (system->currentPlayer->position->getAttachedNode(3) != NULL) {
        choices += " West(w)";
    }
    choices += ". Please make a choice: ";
    return choices;
}

// Function:     rng
// Output:       Dice roll between 1 and 6.
// Description:  Random number generator for dice roll
int Menu::rng() {
    srand ((unsigned int) time(0));
    return (rand() % 6) + 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of System Class

// Function:     initalize(string infile)
// Inputs:       Name of txt file describing grid
// Description:  Parses the text file of the maze into the system and links everything appropriately.
void System::initializeBoard(string infile) {
    //File reading setup
    ifstream input; string temp;
    input.open(infile);
    if (input.fail()) {
        cout << "ERROR PARSING INPUT FILE. PLEASE ENSURE THE FILE EXISTS" << endl;
        return;
    }
    string start, finish, lastNode;
    int turn = 0; int numNodes = 0;

    //Gets start and finish nodes (as strings, will set later on).
    while (getline(input, temp)) {
        if (turn == 0) {
            numNodes = stoi(temp);
        }
        if (turn == 1) {
            start = temp.substr(0,2);
        }
        if (turn == 2) {
            finish = temp.substr(0,2);
        }
        if (turn == numNodes + 2) {
            lastNode = temp.substr(0,2);
        }
        turn++;
    }
    input.close();

    //Create all node objects (guaranteed mxn board, temp contains "highest" node)
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string numbers = "123456789";
    char alphaTarget = lastNode.at(0);
    char numberTarget = lastNode.at(1);
    int alphaStop = (int) alphabet.find(alphaTarget);
    int numberStop = (int) numbers.find(numberTarget);
    for (int i = 0; i <= alphaStop; i++) {
        for (int j = 0; j <= numberStop; j++) {
            stringstream ss; string name = "";
            char currentLetter = alphabet.at(i);
            char currentNumber = numbers.at(j);
            name.push_back(currentLetter);
            name.push_back(currentNumber);
            Node * n = new Node(name);
            nodes.emplace_back(n);
            ss.clear();
        }
    }

    //Set start and finish
    this->start = getNodeWithName(start);
    this->finish = getNodeWithName(finish);

    //Attach node objects as appropriate.
    turn = 0;
    input.open(infile);
    while (getline(input, temp)) {
        //Ignores top 3 lines
        if (turn < 3) {
            turn++;
            continue;
        }
        //Turn the line into pieces separated by " ".
        istringstream buf(temp);
        istream_iterator<string> beg(buf), end;
        vector<string> tokens(beg, end); // done!
        //Initialize components of token vector
        string target = tokens[0];
        string north = tokens[1];
        string east = tokens[2];
        string south = tokens[3];
        string west = tokens[4];
        string ladder = tokens[5];

        Node * currentNode = getNodeWithName(target);
        //Assignments
        if (north != "*") {
            Node * northNode = getNodeWithName(north);
            currentNode->attachNewNode(northNode, 0);
        }
        if (east != "*") {
            Node * eastNode = getNodeWithName(east);
            currentNode->attachNewNode(eastNode, 1);
        }
        if (south != "*") {
            Node * southNode = getNodeWithName(south);
            currentNode->attachNewNode(southNode, 2);
        }
        if (west != "*") {
            Node * westNode = getNodeWithName(west);
            currentNode->attachNewNode(westNode, 3);
        }
        if (ladder != "*") {
            Node * ladderNode = getNodeWithName(ladder);
            currentNode->attachSnakeLadderNode(ladderNode);
        }
    }
}

// Function:    getNodeWithName (string target)
// Input:       name of target node
// Output:      node pointer to target-named node
// Description: Utility method to access a node with a given name
Node * System::getNodeWithName(string target) {
    for (Node * n : nodes) {
        if (n->getNodeName() == target) {
            return n;
        }
    }
}
