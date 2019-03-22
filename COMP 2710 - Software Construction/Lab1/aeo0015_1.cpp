// Lab 1:     TigerBook Social Network
// Name:      Austin Osborn
// Class:     COMP 2710-001
// Date:      10/12/2017
// Email:     aeo0015@auburn.edu
//
// Description: The TigerBook Social Network is a simple program
//              that simulates some functions of a social network
//              including text messages, groups, and users, wall
//              pages and home pages. Follow the prompts to preform
//              these actions. Program terminates when the quit option
//              is selected.
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Class Declarations (Descriptions of each member in implementation below main method)
class System; class User; class Menu; class MessageBuffer; class Group;

// Class:       Group
// Description: The Group class represents a group of users that can message all other users in that group.
class Group {
public:
    Group (string name);
    string groupname;
    vector<User> members;
};

// Class:        User
// Description:  The User class is used to represent one user on the network, including their name.
//               Users can be added to groups to get nontrivial messaging functionality.
class User {
public:
    User (string name);
    System * system;
    string username;
};

// Class:       Menu
// Description: The Menu function is used to give the user a selection menu prompt, as well as the functions
//              that handle each respective selection. Can call to the System to do more advanced operations.
//              Each member's information is described in detail under main() method in its implementation.

class Menu {
public:
    System * system;
    void selectionMenu();
    void newUser();
    void broadcast();
    void multicast();
    void unicast();
    void wallPage();
    void homePage();
    void newGroup();
    void joinGroup();
    void switchUser();
    void quit();
    void printBar(string message);
};

// Class:           MessageBuffer
// Description: The MessageBuffer class holds a single string that contains all messages of any type sent by the program.
//              It stores messages, and it parses the user, group, and message out of each message. It also is responsible
//              for printing home and wall pages (with calls from selection menu).
class MessageBuffer {
public:
    string messageBuffer = "";
    System * system;
    void addMessage(string username, string groupname, string message);
    void printWall(string username);
    void printHome(string username);
    string findMessage(int n);
    string findUser(int n);
    string findGroup(int n);
    int numberOfMessages = 0;
};

// Class:       System
// Description: The System class is an object used to manage the entire networking system. It contains a menu, universal message buffer
//              and list of all groups and users. It also provides methods to add users and groups to the system as well as some boolean
//              checks to ensure the program will validly process operations. Member functions described below in implrmrnysyion.
class System {
public:
    Menu menu = Menu();
    MessageBuffer messageBuffer = MessageBuffer();
    User activeUser = User("SYSTEM_INIT");
    vector<Group> groups;
    vector<User> users;
    bool inProgress = true;
    void execute();
    bool containsUser(string username);
    bool containsGroup(string groupname);
    void addUser(string username);
    void addGroup(string groupname);
    bool actualUser();
    bool userIsAMemberOf (string user, string group);
};


// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//MAIN METHOD
// Initializes a System, Menu, and shared MessageBuffer.
// Attaches Menu and MessageBuffer to system.
int main() {
    System mainSystem = System();
    mainSystem.menu.system = &mainSystem;
    mainSystem.messageBuffer.system = &mainSystem;
    mainSystem.execute();
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Implementation of Group Class
// Function:     Constructor
// Inputs:        Name of group
// Output:       Group object
// Description: Creates new Group object with a given name.
Group::Group(string name) {
    groupname = name;
};


// ///////////////////////////////////////////////////////////////////////////////
// User Class Implementation

// Function:     Constructor
// Inputs:       Name of user
// Output:       User object
// Description:  Creates new User object with a given name.

User::User(string name){
    username = name;
};


// ///////////////////////////////////////////////////////////////////////////////
// Menu Class Implementation

// Function:      selectionMenu()
// Description: Prints a menu list of all actions a user can choose from and handles user selection with switch statement
void Menu::selectionMenu() {
    cout << "\nCreate new user (n), Broadcast (b), Multicast (m), Unicast (u), Wall page (w),\nHome page (h), Create new group (g),Join a group (j), Switch user (s), Quit (q)\nEnter selection >> ";
    char user; string input; //string used here because recursive call with cin to char caused bugs
    cin >> input;
    user = input.at(0); //Safely get only first char of user input
    if (input.size() > 1)  {
        user = 'x';
    }

    //Menu handling all first letters of any case
    switch (user)  {
        case 'N':
        case 'n': {
            newUser();
            break;
        }
        case 'B':
        case 'b': {
            broadcast();
            break;
        }
        case 'M':
        case 'm': {
            multicast();
            break;
        }
        case 'U':
        case 'u': {
            unicast();
            break;
        }
        case 'W':
        case 'w': {
            wallPage();
            break;
        }
        case 'H':
        case 'h': {
            homePage();
            break;
        }
        case 'G':
        case 'g': {
            newGroup();
            break;
        }
        case 'J':
        case 'j': {
            joinGroup();
            break;
        }
        case 'S':
        case 's': {
            switchUser();
            break;
        }
        case 'Q':
        case 'q': {
            quit();
            break;
        }
        default:
            cout << "INPUT INVALID PLEASE TRY AGAIN\n";
            selectionMenu();
    }
};


// Function:    newUser
// Description: Menu handler for new user option. Allows user to input a name and adds that to the system's list of users (if not already present)
void Menu::newUser() {
    cout << "\nEnter new user name >> ";
    string name;
    cin >> name;
    if (system->containsUser(name)) {
        cout << "ERROR: User already exists. Try again.\n";
        newUser();
    }
    else {
        system->addUser(name);
        //Automatically switches to new user (Like example shows)
        system->activeUser = system->users.at(system->users.size()-1);
        printBar("Welcome to the TigerBook Social Network, " + system->activeUser.username);
    }
};


// Function:    broadCast
// Description: Menu handler to broadcast a message to all users. Allows user to type this message and adds it to the system message buffer.
void Menu::broadcast() {
    if (system->actualUser()) {
        string message, d; //d is dummY to catch whitespace and prevent bugs
        cout << "Enter your message >> ";
        getline(cin, d);
        while (1) {
            string line = "";
            getline(cin, line);
            if (int(line.find("^!")) != -1) {
                break; //breaks when ^! is entered as a message
            }
            message = message + "\n" + line;
        }
        system->messageBuffer.addMessage(system->activeUser.username, "All", message);
        system->messageBuffer.numberOfMessages += 1;
    }
    else {
        cout << "\nError! No currently active user!\n";
    }
};


// Function:    multicast
// Description: Menu handler to send a message towards one group. Allows user to type recieving group, message, and adds it to system message buffer.
void Menu::multicast() {
    if (system->actualUser()) {
        string group, d;
        string message = "";
        cout << "Enter group name >> #";
        cin >> group;
        getline(cin, d);
        if (system->containsGroup(group)) {
            cout << "Enter message >> ";
            while (1) {
                string line = "";
                getline(cin, line);
                if (int(line.find("^!")) != -1) {
                    break; //breaks when ^! is entered as a message
                }
                message = message + "\n" + line;
            }
            if (message == "") {
                cout << "Error. Message was empty";

            } else {
                system->messageBuffer.addMessage(system->activeUser.username, group, message);
                system->messageBuffer.numberOfMessages += 1;
            }
            cout << "\n";
        }
        else {
            char response; string d;
            cout << "\nGroup not found. Would you like to create it (y/n)? >> ";
            cin >> response;
            getline(cin, d);
            if (response == 'Y' || response == 'y') {
                system->addGroup(group);
                cout << "Enter message >> ";
                while (1) {
                    string line = "";
                    getline(cin, line);
                    if (int(line.find("^!")) != -1) {
                        break; //breaks when ^! is entered as a message
                    }
                    message = message + "\n" + line;
                }
                if (message == "") {
                    cout << "Error. Message was empty";

                } else {
                    system->messageBuffer.addMessage(system->activeUser.username, group, message);
                    system->messageBuffer.numberOfMessages += 1;
                }
                cout << "\n";
            }
            else {

            }
        }
    }
    else {
        cout << "\nError! No current active user!\n";
    }

};


// Function:     unicast
// Description:  Menu handler to send a message towards one user. Allows user to type recieving user name, message, and adds it to system message buffer.
void Menu::unicast() {
    if (system->actualUser()) {
        string group, message, d;
        cout << "Enter recipient name >> ";
        cin >> group;
        if (system->containsUser(group)) {
            cout << "Enter the message >> ";
            getline(cin, d);
            while (1) {
                string line;
                getline(cin, line);
                if (int(line.find("^!")) != -1) {
                    break; //breaks when ^! is entered as a message
                }
                message = message + "\n" + line;
            }
            system->messageBuffer.addMessage(system->activeUser.username, group, message);
            system->messageBuffer.numberOfMessages += 1;
        }
        else {
            char response;
            string d;
            cout << "\nUser not found. Would you like to create them (y/n)? >> ";
            cin >> response;
            getline(cin, d);
            if (response == 'Y' || response == 'y') {
                system->addUser(group);
                cout << "Enter the message >> ";
                while (1) {
                    string line;
                    getline(cin, line);
                    if (int(line.find("^!")) != -1) {
                        break; //breaks when ^! is entered as a message
                    }
                    message = message + "\n" + line;
                }
                system->messageBuffer.addMessage(system->activeUser.username, group, message);
                system->messageBuffer.numberOfMessages += 1;
            }
        }
    }
    else {
        cout << "\nError! No currently active user!\n";
    }

}


// Function:     wallPage
// Description:  Menu handler for printing a wall. Calls on the appropriate messageBuffer function to handle this.
void Menu::wallPage() {
    if (system->actualUser()) {
        printBar(system->activeUser.username + "'s Wall Page");
        system->messageBuffer.printWall(system->activeUser.username);
    }
    else {
        cout << "\nError! No active user!\n";
    }
};


// Function:     homePage
// Description:  Menu handler for print a home page. Calls on the appropriate messageBuffer function to handle this.
void Menu::homePage() {
    if (system->actualUser()) {
        printBar(system->activeUser.username + "'s Home Page");
        system->messageBuffer.printHome(system->activeUser.username);
    }
    else {
        cout << "\nError! No active user!\n";
    }
};


// Function:     newGroup
// Description:  Menu handler for creating a new group. Creates new group object. Adds the inputted group to the system's vector of groups.
void Menu::newGroup() {
    string group;
    cout << "Enter new group name >> #";
    cin >> group;
    if (!system->containsGroup(group)) {
        system->addGroup(group);
        printBar("#" + group + " group created");
    }
    else {
        cout << "Error creating group (Group already exists)\n";
    }
};

// Function:     joinGroup
// Description:  Menu handler for joining a group. User types desired name of group to join. If it doesn't exists, user is asked
//               if they would like to create it. If yes, then the group is created and the user is added to it.
void Menu::joinGroup() {
    if (system->actualUser()) {
        string group; string d;
        cout << "Enter name of group you would like to join >> #";
        cin >> group;
        getline(cin, d);
        if (system->containsGroup(group)) {
            //Goes through all groups
            for (int i = 0; i < system->groups.size(); i++) {
                //Checks if group is the correct one
                if (system->groups.at(i).groupname == group) {
                    //Adds user to Group vectoor members
                    system->groups.at(i).members.push_back(system->activeUser);
                }
            }
            printBar(system->activeUser.username + " is in #" + group + " group");
        }
        else {
            char response; string d;
            cout << "\nGroup not found. Would you like to create and join it (y/n)? >> ";
            cin >> response;
            getline (cin, d);
            if (response == 'Y' || response == 'y') {
                system->addGroup(group);
                printBar(system->activeUser.username + " is in #" + group + " group");
                for (int i = 0; i < system->groups.size(); i++) {
                    if (system->groups.at(i).groupname == group) {
                        system->groups.at(i).members.push_back(system->activeUser);
                    }
                }
            } else {
                system->menu.selectionMenu();
            }
        }
    }
    else {
        cout << "\nError! No current active user!\n";
    }

};


// Function:    switchUser
// Description: Menu handler for changing the active system user. User inputs desired user to make active. If they exist,
//                    then the active user is set to the user containing the name inputted.
void Menu::switchUser() {
    string name;
    cout << "\nEnter user name to switch to >> ";
    cin >> name;
    if (system->containsUser(name)) {
        for (int i = 0; i < system->users.size(); i++) {
            if (system->users.at(i).username == name) {
                system->activeUser = system->users.at(i);
                printBar("Welcome to TigerBook Social Network, " + system->activeUser.username);
                break;
            }
        }
    }
    else {
        cout << "\nUser doesn't exist. Please try again.\n";
    }
};

// Function:    quit
// Description: Menu handler to gracefully exit program. Tells the user goodbye and the program terminates.
void Menu::quit() {
    printBar("Thank you for using the TigerBook Social Network. War Eagle!");
    system->inProgress = false;
};

// Function:     printBar
// Input:        A message that you would like to print between bars for a menu. A
// Description:  Prints a message between two bars in the console. A utility function.
void Menu::printBar (string message) {
    int size = 2 * message.size();
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
            cout << message;
            cout << "\n";
        }
    }
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MessageBuffer Class Implementation

// Function:     addMessage
// Inputs:       A username, group name, and message content.
// Description:  Takes in element that composes a given message, formats it according to style dictated in lab
//               instructions and adds it to the system's message buffer.
void MessageBuffer::addMessage (string username, string groupname, string message) {
    messageBuffer = "<!" + username + ":#" + groupname + ">" + message + messageBuffer;
};


// Function:     printWall
// Input:        Username of currently active user
// Description:  Prints all messages that the active user has sent
void MessageBuffer::printWall(string username) {
    int current = 0;
    int messages = system->messageBuffer.numberOfMessages;
    for (int i = 0; i < messages; i++) {
        string group = system->messageBuffer.findGroup(i+1);
        string user = username;
        string message = system->messageBuffer.findMessage(i+1);
        if (current == 2) {
            char response;
            cout << "\n\n         Would you like to display all messages (y/n)? >> ";
            cin >> response;
            if (response != 'y' && response !='Y') {
                break;
            }
        }
        //Validate that a given message in the buffer was sent by the current user
        if (system->messageBuffer.findUser(i+1) == system->activeUser.username) {
            string d;
            if (system->containsUser(group)) {
                d = "";
            }
            else {
                d = "#";
            }
            current ++;
            cout << "\n(" + d + group + ") >" + message + "\n";
        }
    }

};


// Function:     printHome
// Input:        Username of currently active user
// Description:  Prints all messages that the active user has recieved, is a member of the group of, and all broadcasts.
void MessageBuffer::printHome(string username) {
    int current = 0;
    int messages = system->messageBuffer.numberOfMessages;
    bool asked = false;

    //For each message, do the following
    for (int i = 0; i < messages; i++) {

        //If there are 2 messages already displayed and potentially more, then ask to display more.
        if (current == 2 && !asked) {
            asked = true;
            char response;
            cout << "\n\n         Would you like to display all messages (y/n)? >> ";
            cin >> response;
            if (response != 'y' && response != 'Y') {
                break;
            }
        }

        //Gets the group, user, and message content of the current message being iterated over
        string group = system->messageBuffer.findGroup(i + 1);
        string user = system->messageBuffer.findUser(i + 1);
        string message = system->messageBuffer.findMessage(i + 1);

        //Prints all broadcast messages
        if (group == "All") {
            current++;
            cout << "\n\n" + user + " (#" + group + ") >"
                 << message;
            continue;
        }

        //Prints Messages straight to user
        if (group == system->activeUser.username) {
            current++;
            cout << "\n\n" + user + " (" + group + ") >" + message;
            continue;
        }

        //Prints message if a user is a member of the group of the particular message being parsed.
        if (system->userIsAMemberOf(system->activeUser.username, group)) {
            cout << "\n\n" + user + " (#" + group + ") >" + message;
            current++;
            continue;
        }
    }
    cout << "\n";

};

// Parsing Functions

// Function:    findGroup
// Input:       An integer n
// Output:      nth group in the buffer
// Description: From Homework 1. Finds the nth logical group (i.e n = 1 is "first" group) in the buffer.
string MessageBuffer::findGroup(int n) {
    string currentSubstring = messageBuffer;
    for (int i =0; i < n; i++) {
        int location = currentSubstring.find(":#");
        if (location == - 1){
            return ""; //returns empty string if not found
        }

        currentSubstring = currentSubstring.substr(location+2);
        if (i == n - 1){
            int endOfGroup = currentSubstring.find(">");
            return currentSubstring.substr(0,endOfGroup);
        }
    }
    return ""; //Should never reach, but not found if this hits
//    for (int i = 0; i < n; i++) {
//        int location = currentSubstring.find("<#");
//        cout << "Location - " + location;
//    }

};


// Function:    findUser
// Input:       An integer n
// Output:      nth user in the buffer
// Description: From Homework 1. Finds the nth logical user (i.e n = 1 is "first" user) in the buffer.
string MessageBuffer::findUser(int n) {
    string target = "<!";//Indicates start of username
    string currentSubstring = messageBuffer;
    for (int i = 0; i < n; i++) {
        if (int(currentSubstring.find("<!")) == -1) {
            return ""; //if nth username isn't found, returns empty string
        }
        if (i == n -1 ) {
            int location = currentSubstring.find(target);
            currentSubstring = currentSubstring.substr(location + 2);
            int lengthOfName = currentSubstring.find(":");
            return currentSubstring.substr(0, lengthOfName);
        }
        int location = currentSubstring.find(target);
        currentSubstring = currentSubstring.substr(location + 2);
    }
};

// Function:    findMessage
// Input:       An integer n
// Output:      nth message in the buffer
// Description: From Homework 1. Finds the nth logical group (i.e n = 1 is "first" message) in the buffer.
string MessageBuffer::findMessage(int n) {
    string currentSubstring = messageBuffer;
    for (int i =0; i < n; i++) {
        int location = currentSubstring.find(">");
        if (location == - 1){
            return ""; //returns empty string if not found
        }
        currentSubstring = currentSubstring.substr(location+1);
        if (i == n-1) {
            if (int(currentSubstring.find("<")) == -1) {
                return currentSubstring;
            }
            else {
                int endOfMessage = int(currentSubstring.find("<"));
                string finalString = currentSubstring.substr(0,endOfMessage);
                return finalString;
            }
        }
    }
};


// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// System Class Implementation

// Function:    actualUser
// Output  :    True if actual user is logged into system. False if default (SYSTEM_INIT) is active user.
// Description: Utility method to check if a valid user is operating the systrem. (i.e at least one new user has been made)
bool System::actualUser() {
    return (activeUser.username != "SYSTEM_INIT");
}

// Function:     userIsAMemberOf
// Inputs:       Username and Groupname
// Outputs:      True is the given user is a member of given group. False otherwise.
bool System::userIsAMemberOf(string user, string group) {
    //Goes through first each group
    for (int i = 0; i < groups.size(); i++) {
        Group g = groups.at(i);
        //Target group found.
        if (g.groupname == group) {
            //Goes through all users of the group
            for (int j = 0; j < g.members.size(); j++) {
                User u = g.members.at(j);
                //Target user found
                if (u.username == user) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Function:    execute
// Description: Main execution of system. Starts the system and ends when user selects to quit.
void System::execute() {
    menu.printBar("Welcome to the TigerBook Social Network!");
    while (inProgress) {
        menu.selectionMenu();
    }

};

// Function:     containsGroup
// Input:        A given groupname
// Output:       True if the input is a valid group in the system. False otherwise.
bool System::containsGroup(string groupname) {
    for (int i = 0; i < groups.size(); i++) {
        if (groups.at(i).groupname == groupname) {
            return true;
        }
    }
    return false;
};


// Function:     containsUser
// Input:        A given username
// Output:       True if the input is a valid user in the system. False otherwise.
 bool System::containsUser(string username) {
    for (int i = 0; i < users.size(); i++) {
        if (users.at(i).username == username) {
            return true;
        }
    }
    return false;
};

// Function:     addUser
// Input:        A given username
// Description:  Adds a new user to the system vector containing all users.
void System::addUser(string username) {
    users.push_back(User(username));
};


// Function:     addGroup
// Input:        A given groupname
// Description:  Adds a new group to the system vector containing all groups.
void System::addGroup(string groupname) {
    groups.push_back(Group(groupname));

};
