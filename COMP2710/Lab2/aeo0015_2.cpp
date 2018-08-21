// Lab 2:     Distributed TigerBook Social Network
// Name:      Austin Osborn
// Class:     COMP 2710-001
// Date:      10/30/2017
// Email:     aeo0015@auburn.edu
//
// Description: The Distributed TigerBook Social Network is a simple program
//              that simulates some functions of a social network
//              including text messages, groups, and users, wall
//              pages and home pages. Follow the prompts to preform
//              these actions. Program terminates when the quit option
//              is selected. System is persistent with multiple (even simultaneous)
//              instances with the only limitation of the same exact file being written to
//              at the exact same time.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>

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
    vector<string> getGroups();
    vector<string> memberOf;
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

// Class:       Message
// Description: The Message class is a way to coherently structure messages that are being parsed. This class will act as
//              mostly a convenience class to make sorting and printing messages easier to do. Messages are still being stored
//              in .txt files in the appropriate format as specified in Lab 2 handout.

class Message {

public:
    Message(string sender, string recipient, string content, string time);
    string sender, recipient, content, time;
    string format();
};

// Class:       MessageBuffer
// Description: The MessageBuffer class holds a single string that contains all messages of any type sent by the program.
//              It stores messages, and it parses and prints both wall and home pages.
class MessageBuffer {
public:
    System * system;
    void broadcastMessage(string sender, string message);
    void multicastMessage(string sender, string group, string message);
    void unicastMessage(string sender, string user, string message);
    void parseAndPrintWall(string username);
    void parseAndPrintHome(string username);
    vector<Message> sortMessages(vector<Message> messages);
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
    void addUser(string username);
    void addGroup(string groupname);
    void addUserToGroup(string username, string groupname);
    bool actualUser();
    bool userExists(string username);
    bool groupExists(string groupname);
    void refresh();
    void newFile(string title);
    User getUser(string name);
};


// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//MAIN METHOD
// Initializes a System, Menu, and shared MessageBuffer.
// Attaches Menu and MessageBuffer to system.
int main() {
    System mainSystem = System();
    mainSystem.refresh();
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


// Function:     getGroups
// Inputs:       N/A
// Output:       Vector<String> containing list of groups the user is part of
// Description:  Returns a list of groups the user is a member of in string format.
vector<string> User::getGroups() {
    fstream fileStream; ifstream inputStream; ofstream outputStream; stringstream stringStream; string input;
    inputStream.open("SYSTEM_USERS.txt");
    vector<string> temp;
    while (getline(inputStream, input)) {
        if ((int) input.find(username) != -1) {
            int pos = (int) input.find_first_of(':');
            string groups = input.substr(pos + 1, input.size() - 1);
            while (groups.size() > 1) {
                int endOfGroup = (int) groups.find("|");
                string currentGroup = groups.substr(0, endOfGroup);
                temp.push_back(currentGroup);
                groups = groups.substr(endOfGroup + 1, groups.size() - 1);
            }
        }
    }
    return temp;
}


// ///////////////////////////////////////////////////////////////////////////////
// Menu Class Implementation

// Function:    selectionMenu()
// Description: Prints a menu list of all actions a user can choose from and handles user selection with switch statement.
void Menu::selectionMenu() {
    system->refresh();
    cout << "\nCreate new user (n), Broadcast (b), Multicast (m), Unicast (u), Wall page (w),\nHome page (h), Create new group (g),Join a group (j), Switch user (s), Quit (q)\nEnter selection >> ";
    char user; string input; //string used here because recursive call with cin to char caused bugs
    getline(cin, input);
    cin.clear();
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
    system->refresh();
    cout << "\nEnter new user name >> ";
    string name;
    getline(cin, name);
    cin.clear();
    if (system->userExists(name)) {
        cout << "ERROR: User already exists. Try again.\n";
        newUser();
    }
    if ((int) name.find('{') != -1 || (int) name.find('#') != -1 || (int) name.find(':') != -1) {
        cout << "ERROR: Invalid characters. Try again.\n";
    }
    else {
        system->addUser(name);
        system->refresh();
        //Automatically switches to new user (Like example shows)
        system->activeUser = system->users.at(0);
        printBar("Welcome to the TigerBook Social Network, " + system->activeUser.username);
    }
};


// Function:    broadCast
// Description: Menu handler to broadcast a message to all users. Allows user to type this message and adds it to the system message buffer.
void Menu::broadcast() {
    system->refresh();
    if (system->actualUser()) {
        string message = "";
        string d;//d is dummY to catch whitespace and prevent bugs
        cout << "Enter your message >> ";
        while (1) {
            string line = "";
            getline(cin, line);
            if (int(line.find("^!")) != -1) {
                break; //breaks when ^! is entered as a message
            }
            message = message + line + "\n";
        }
        if (message == "" || message == "\n" || (int) message.find('{') != -1) {
            cout << "Invalid message. \n";
        }
        else {
            system->messageBuffer.broadcastMessage(system->activeUser.username, message);
        }
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
        getline(cin, group);
        cin.clear();
        if (system->groupExists(group)) {
            cout << "Enter message >> ";
            while (1) {
                string line = "";
                getline(cin, line);
                if (int(line.find("^!")) != -1) {
                    break; //breaks when ^! is entered as a message
                }
                message = message + line + "\n";
            }
            if (message == "" || message == "\n" || (int) message.find('{') != -1) {
                cout << "Error. Invalid message";

            } else {
                system->messageBuffer.multicastMessage(system->activeUser.username, group, message);
            }
            cout << "\n";
        }
        else {
            cout << "Error! Group does not exist" << endl;
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
        getline(cin, group);
        cin.clear();
        if (system->containsUser(group)) {
            cout << "Enter the message >> ";
            while (1) {
                string line;
                getline(cin, line);
                if (int(line.find("^!")) != -1) {
                    break; //breaks when ^! is entered as a message
                }
                message = message + line + "\n";
            }
            if (message == "" || message == "\n" || (int) message.find('{') != -1) {
                cout << "Invalid message. \n";
            }
            else {
                system->messageBuffer.unicastMessage(system->activeUser.username, group, message);
            }
        }
        else {
            cout << "Error: User does not exist" << endl;
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
        system->messageBuffer.parseAndPrintWall(system->activeUser.username);
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
        system->messageBuffer.parseAndPrintHome(system->activeUser.username);
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
    getline(cin, group);
    cin.clear();
    int find = group.find(':');
    if ((int) group.find(':') == -1)
        if (!system->groupExists(group)) {
            system->addGroup(group);
            printBar("#" + group + " group created");
        }
        else {
            cout << "Error creating group (Group already exists)\n";
        }
};


// Function:     joinGroup
// Description:  Menu handler for joining a group. User types desired name of group to join. If it exists, they join it.
void Menu::joinGroup() {
    system->refresh();
    if (system->actualUser()) {
        string group;
        cout << "Enter name of group you would like to join >> #";
        getline(cin, group);
        cin.clear();
        if (system->groupExists(group)) {
            system->addUserToGroup(system->activeUser.username, group);
            printBar(system->activeUser.username + " is in #" + group + " group");
        }
        else {
            cout << "Error! Group does not exist" << endl;
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
    getline(cin, name);
    cin.clear();
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
// Message Class Implementation

// Function:     Constructor
// Inputs:       Name of sender, name of recipient, content, and timestamp (epoch time)
// Output:       User object
// Description:  Creates new Message object.
Message::Message(string sender, string recipient, string content, string time) {
    this->sender = sender;
    this->recipient = recipient;
    this->content = content;
    this->time = time;
}

// Function:     format
// Inputs:       N/A
// Output:       string with proper formatting to print a wall or home page message
// Description:  Utility method to print a message on a wall or home page.
string Message::format() {
    return "\n" + sender + " (" + recipient + ") >\n" + content + "\n";
}

// Function:     sortMessages(vector<Message> messages
// Inputs:       Vector of unsorted message objects (in order they are parsed)
// Output:       Vector of message objects sorted by timestamp.
// Description:  Algorithm to sort messages by timestamp before printing them.
vector<Message> MessageBuffer::sortMessages(vector<Message> messages) {
    // Strategy: Find max timestamp each pass (most recent to be posted).
    //           Append this message to the sorted array and remove it from input array.
    //           Repeat this until input array is empty. Return sorted array.
    double max = 0;
    stringstream stringStream;
    int maxIndex = 0;
    vector<Message> returnArray;
    while (messages.size() > 0) {
        for (int i = 0; i < messages.size(); i++) {
            stringStream << messages.at(i).time;
            double time;
            stringStream >> time;
            if (time > max) {
                max = time;
                maxIndex = i;
            }
            stringStream.clear();
        }
        Message m = messages.at(maxIndex);
        returnArray.push_back(m);
        messages.erase(messages.begin() + maxIndex);
        max = 0;

    }
    return returnArray;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MessageBuffer Class Implementation

// Function:     broadcastMessage(string sender, string message)
// Inputs:       A username and message content.
// Description:  Takes in a sender and message contents and saves a it to the _All.txt file in the appropriate format
void MessageBuffer::broadcastMessage(string sender, string message) {
    fstream fileStream; ifstream inputStream; ofstream outputStream; stringstream stringStream; string input;
    //Get time as epoch string
    std::time_t result = std::time(nullptr);
    stringstream ss;
    ss << result;
    string time = ss.str();
    //Opens appropriate file
    inputStream.open("_All.txt");
    //Copy file contents the stringstream
    while (getline(inputStream, input)) {
        stringStream << input << endl;
    }
    inputStream.close();
    outputStream.open("_All.txt");
    //Append new message at the beginning of file
    string append = "{!" + time + "!}<!" + sender + "!>" + message;
    outputStream << append;
    //Paste the rest of previous contents after appended message.
    while(getline(stringStream, input)) {
        outputStream << input << endl;
    }
    outputStream.flush();
    outputStream.close();
    system->menu.printBar(sender + " has broadcasted a new message.");

}


// Function:     multicastMessage(string sender, string group, string message)
// Inputs:       A sender's username, recieving groupname and message content.
// Description:  Takes in a sender and message contents and saves a it to the appropriate _group.txt file in the appropriate format.
void MessageBuffer::multicastMessage(string sender, string group, string message) {
    fstream fileStream; ifstream inputStream; ofstream outputStream; stringstream stringStream; string input;
    //Get time as epoch string
    std::time_t result = std::time(nullptr);
    stringstream ss;
    ss << result;
    string time = ss.str();
    //Open correct file
    inputStream.open("_" + group + ".txt");
    if (inputStream.fail()) {
        cout << "Multicast error. Failed to load file:_" + group + ".txt";
        return;
    }
    //Copy its contents into stringsream
    while (getline(inputStream, input)) {
        stringStream << input << endl;
    }
    inputStream.close();
    outputStream.open("_" + group + ".txt");
    //Append new message to start of txt file
    string append = "{!" + time + "!}<!" + sender + "!>" + message;
    outputStream << append;
    //Paste the rest of previous contents after appended message
    while(getline(stringStream, input)) {
        outputStream << input << endl;
    }
    outputStream.flush();
    outputStream.close();
    system->menu.printBar(sender + " has multicasted a new message to #" + group + " group.");


}


// Function:     multicastMessage(string sender, string group, string message)
// Inputs:       A sender's username, recieving username and message content.
// Description:  Takes in a sender and message contents and saves a it to the appropriate user.txt file in the appropriate format.
void MessageBuffer::unicastMessage(string sender, string user, string message) {
    fstream fileStream; ifstream inputStream; ofstream outputStream; stringstream stringStream; string input;
    //Get time as epoch string
    std::time_t result = std::time(nullptr);
    stringstream ss;
    ss << result;
    string time = ss.str();
    //Open appropriate txt file
    inputStream.open(user + ".txt");
    if (inputStream.fail()) {
        cout << "Multicast error. Failed to load file:" + user + ".txt";
        return;
    }
    //Copy txt file contents
    while (getline(inputStream, input)) {
        stringStream << input << endl;
    }
    inputStream.close();
    outputStream.open(user + ".txt");
    //Append new message to start of file
    string append = "{!" + time + "!}<!" + sender + "!>" + message;
    outputStream << append;
    //Paste the rest of previous contents after appended message
    while(getline(stringStream, input)) {
        outputStream << input << endl;
    }
    outputStream.flush();
    outputStream.close();
    system->menu.printBar(sender + " has unicasted a new message to " + user);


}

// Function:     parseAndPrintWall(string username)
// Inputs:       Active user's name
// Output:       N/A
// Description:  Parses through all message files. Adds any message sent by user to array.
//               Sorts that array by timestamp. Prints wall page in correct format.
void MessageBuffer::parseAndPrintWall(string username) {
    system->refresh();
    //Initialize utility objects
    ifstream inputStream; string input;
    string time = ""; string sender = ""; string content = "";
    vector<Message> messages;

    //First parse all messages from Broadcast sent by user.
    inputStream.open("_All.txt");
    while (getline(inputStream, input)) {
        //This if statement writes final message at end of file if user sent it.
        if (input.length() == 0 && sender == system->activeUser.username) {
            Message m = Message(sender, "#All", content, time);
            messages.push_back(m);
            break;
        }
        //This writes message if current line being read is start of a new message
        if (input.at(0) == '{') {
            //Generates previous message object (if it exists) and current user sent it
            if (time != "" && sender != "" && content != "" && sender == system->activeUser.username) {
                Message m = Message(sender, "#All", content, time);
                messages.push_back(m);
            }
            //Clear out identifier variables
            time.clear(); sender.clear(); content.clear();
            // Parse time
            int endTimePos = (int) input.find('}');
            time = input.substr(2,endTimePos - 3);
            input = input.substr(endTimePos + 1, input.length() - 1);
            //Parse sender
            int endSenderPos = (int) input.find(">");
            sender = input.substr(2, endSenderPos - 3);
            input = input.substr(endSenderPos + 1, input.length() - 1);
            //Add content
            content += input;
            input.clear();
        }
            //Adds to content of next message if line is only part of a message
        else {
            content+= "\n" + input;
            input.clear();
        }
    }
    //Parse final message
    if (content != "" && sender == system->activeUser.username) {
        Message m = Message(sender, "#All", content, time);
        messages.push_back(m);
    }
    inputStream.close();
    content.clear(); time.clear(); sender.clear();

    //Parsing for each group in the system, adding messages sent by user.
    for (Group g : system->groups) {
        string currentGroup = g.groupname;
        if (g.groupname == "All") {
            continue;
        }
        //Open appropriate file
        inputStream.open("_" + currentGroup + ".txt");
        //Parse through file
        while (getline(inputStream, input)) {
            if (input == "") {
                break;
            }
            //Writes last message (if getline returns "")
            if (input.length() == 0 && sender == system->activeUser.username) {
                Message m = Message(sender, "#" + currentGroup, content, time);
                messages.push_back(m);
                break;
            }
            //Writing previous message and parsing members for next one
            if (input.at(0) == '{') {
                //Generates previous message object (if it exists)
                if (time != "" && sender != "" && content != "" && sender == system->activeUser.username) {
                    Message m = Message(sender, "#" + currentGroup, content, time);
                    messages.push_back(m);
                }
                time.clear();
                sender.clear();
                content.clear();
                // Parse time
                int endTimePos = (int) input.find('}');
                time = input.substr(2, endTimePos - 3);
                input = input.substr(endTimePos + 1, input.length() - 1);
                //Parse sender
                int endSenderPos = (int) input.find(">");
                sender = input.substr(2, endSenderPos - 3);
                input = input.substr(endSenderPos + 1, input.length() - 1);
                //Add content
                content += input;
            }
            else {
                content += "\n" + input;
            }
        }
        //Adds final message and clears temp variables
        if (sender == system->activeUser.username && content != "") {
            Message m = Message(sender, "#" + currentGroup, content, time);
            messages.push_back(m);
        }
        inputStream.close();
        content.clear(); time.clear(); sender.clear();
    }

    //Parsing for unicasted messages sent by user
    for (User u : system->users) {
        string currentUser = u.username;
        //Open appropriate file
        inputStream.open(currentUser + ".txt");
        //Parse through file
        while (getline(inputStream, input)) {
            //Writes last message (if getline returns "")
            if (input.length() == 0 && sender == system->activeUser.username) {
                Message m = Message(sender, currentUser, content, time);
                messages.push_back(m);
                break;
            }
            //Writing previous message and parsing members for next one
            if (input.at(0) == '{') {
                //Generates previous message object (if it exists)
                if (time != "" && sender != "" && content != "" && sender == system->activeUser.username) {
                    Message m = Message(sender, currentUser, content, time);
                    messages.push_back(m);
                }
                time.clear();
                sender.clear();
                content.clear();
                // Parse time
                int endTimePos = (int) input.find('}');
                time = input.substr(2, endTimePos - 3);
                input = input.substr(endTimePos + 1, input.length() - 1);
                //Parse sender
                int endSenderPos = (int) input.find(">");
                sender = input.substr(2, endSenderPos - 3);
                input = input.substr(endSenderPos + 1, input.length() - 1);
                //Add content
                content += input;
            } else {
                content += "\n" + input;
            }
        }
        //Adds final message and clears temp variables
        if (sender == system->activeUser.username && content != "") {
            Message m = Message(sender, currentUser, content, time);
            messages.push_back(m);
        }
        input.clear();
        content.clear();
        inputStream.close();
    }

    int numPrinted = 0;
    //Sort messages by timestamp
    vector<Message> sorted = sortMessages(messages);
    //For each message, print it. When 2 are printed prompt to see all.
    for (Message m : sorted) {
        if (numPrinted == 2) {
            cout << "                      Would you like to view all (y/n)? : ";
            string response;
            getline(cin, response);
            cin.clear();
            if ((int) response.find('Y') == -1 && (int) response.find('y') == -1){
                break;
            }
        }
        cout << m.format();
        numPrinted++;
    }
    system->menu.printBar("End of " + username + "'s Wall Page");

}

// Function:     parseAndPrintHome(string username)
// Inputs:       Active user's name
// Output:       N/A
// Description:  Parses through all message files. Adds any broacast message, multicast message of any group the user
//               is in, and any message in their unicast file. Sorts that array by timestamp. Prints home page in correct format.
void MessageBuffer::parseAndPrintHome(string username) {
    system->refresh();
    ifstream inputStream; string input;
    string time = ""; string sender = ""; string content = "";
    vector<Message> messages;

    //First parse all messages from Broadcast
    inputStream.open("_All.txt");
    while (getline(inputStream, input)) {
        //This if statement writes final message at end of file
        if (input.length() == 0) {
            Message m = Message(sender, "#All", content, time);
            messages.push_back(m);
            break;
        }
        //This writes message if current line being read is start of a new message
        if (input.at(0) == '{') {
            //Generates previous message object (if it exists
            if (time != "" && sender != "" && content != "") {
                Message m = Message(sender, "#All", content, time);
                messages.push_back(m);
            }
            //Clear out identifier variables
            time.clear(); sender.clear(); content.clear();
            // Parse time
            int endTimePos = (int) input.find('}');
            time = input.substr(2,endTimePos - 3);
            input = input.substr(endTimePos + 1, input.length() - 1);
            //Parse sender
            int endSenderPos = (int) input.find(">");
            sender = input.substr(2, endSenderPos - 3);
            input = input.substr(endSenderPos + 1, input.length() - 1);
            //Add content
            content += input;
            input.clear();
        }
            //Adds to content of next message if line is only part of a message
        else {
            content+= "\n" + input;
            input.clear();
        }
    }
    if (content != "") {
        Message m = Message(sender, "#All", content, time);
        messages.push_back(m);
    }
    content.clear(); time.clear(); sender.clear();
    inputStream.close();

    //Parsing for each group the user is a member of.
    vector<string> groups = system->activeUser.getGroups();
    //Go through each group
    for (const string &currentGroup : groups) {
        //Open appropriate file
        inputStream.open("_" + currentGroup + ".txt");
        //Parse through file
        while (getline(inputStream, input)) {
            //Writes last message (if getline returns "")
            if (input.length() == 0) {
                Message m = Message(sender, "#" + currentGroup, content, time);
                messages.push_back(m);
                break;
            }
            //Writing previous message and parsing members for next one
            if (input.at(0) == '{') {
                //Generates previous message object (if it exists)
                if (time != "" && sender != "" && content != "") {
                    Message m = Message(sender, "#" + currentGroup, content, time);
                    messages.push_back(m);
                }
                time.clear();
                sender.clear();
                content.clear();
                // Parse time
                int endTimePos = (int) input.find('}');
                time = input.substr(2, endTimePos - 3);
                input = input.substr(endTimePos + 1, input.length() - 1);
                //Parse sender
                int endSenderPos = (int) input.find(">");
                sender = input.substr(2, endSenderPos - 3);
                input = input.substr(endSenderPos + 1, input.length() - 1);
                //Add content
                content += input;
            }
            else {
                content += "\n" + input;
            }
        }
        //Adds final message and clears temp variables
        if (content != "") {
            Message m = Message(sender, "#" + currentGroup, content, time);
            messages.push_back(m);
        }
        inputStream.close();
        content.clear(); time.clear(); sender.clear();
    }
//////////////////////////////////////////////////////
    //Paring for unicasted messages at user
    inputStream.open(system->activeUser.username + ".txt");
    while (getline(inputStream, input)) {
        if (input.length() == 0) {
            Message m = Message(sender, system->activeUser.username, content, time);
            messages.push_back(m);
            break;
        }
        if (input.at(0) == '{') {
            //Generates previous message object (if it exists
            if (time != "" && sender != "" && content != "") {
                Message m = Message(sender, system->activeUser.username, content, time);
                messages.push_back(m);
            }
            time.clear();
            sender.clear();
            content.clear();
            // Parse time
            int endTimePos = (int) input.find('}');
            time = input.substr(2, endTimePos - 3);
            input = input.substr(endTimePos + 1, input.length() - 1);
            //Parse sender
            int endSenderPos = (int) input.find(">");
            sender = input.substr(2, endSenderPos - 3);
            input = input.substr(endSenderPos + 1, input.length() - 1);
            //Add content
            content += input;
        }
        else{
            content += "\n" + input;
        }
    }
    //Adds final message and clears temp variables
    if (content != "") {
        Message m = Message(sender, system->activeUser.username, content, time);
        messages.push_back(m);
    }
    inputStream.close();
    content.clear(); time.clear(); sender.clear();


    vector<Message> sorted = sortMessages(messages);
    int numPrinted = 0;
    for (Message m : sorted) {
        if (numPrinted == 2) {
            cout << "                      Would you like to view all (y/n)? : ";
            string response;
            getline(cin, response);
            cin.clear();
            if ((int) response.find('Y') == -1 && (int) response.find('y') == -1){
                break;
            }
        }
        cout << m.format();
        numPrinted++;
    }

    system->menu.printBar("End of " + username + "'s Home Page");
}

// Function:    actualUser
// Output  :    True if actual user is logged into system. False if default (SYSTEM_INIT) is active user.
// Description: Utility method to check if a valid user is operating the systrem. (i.e at least one new user has been made)
//              In the new system of entering user at start, this should never happen. More of a redundant check in case the unthinkable happens.
bool System::actualUser() {
    return (activeUser.username != "SYSTEM_INIT");
}


// Function:    execute
// Description: Main execution of system. Starts the system and ends when user selects to quit. Initializes files as needed.
void System::execute() {
    refresh();
    //Setup system files if they don't exist
    fstream fileStream; ifstream inputStream; ofstream outputStream; stringstream stringStream; string input;
    inputStream.open("SYSTEM_USERS.txt");
    if (inputStream.fail()){
        newFile("SYSTEM_USERS");
    }
    inputStream.close();
    inputStream.open("SYSTEM_GROUPS.txt");
    if (inputStream.fail()) {
        newFile("SYSTEM_GROUPS");
        addGroup("All");
    }
    inputStream.close();
    inputStream.open("_All.txt");
    if (inputStream.fail()) {
        newFile("_All");
    }
    //Used to check if a user has signed in or not.
    activeUser = User("SYSTEM_INIT");

    //Welcome messaage and loops that continues until user quits.
    menu.printBar("Welcome to the Distributed TigerBook Social Network!");
    cout << "\nPlease enter username: ";
    getline(cin, input);

    //If user exists, log them in
    if (containsUser(input)) {
        for (int i = 0; i < users.size(); i++) {
            if (users.at(i).username == input) {
                activeUser = users.at(i);
                menu.printBar("Welcome to TigerBook Social Network, " + activeUser.username);
                break;
            }
        }
    }
        //Otherwise create new user
    else {
        addUser(input);
        refresh();
        for (int i = 0; i < users.size(); i++) {
            if (users.at(i).username == input) {
                activeUser = users.at(i);
                menu.printBar("Welcome to TigerBook Social Network, " + activeUser.username);
                break;
            }
        }
    }

    //Continue execution until user selects to quit
    while (inProgress) {
        menu.selectionMenu();
    }
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
    refresh();
    //Check if user exists
    if (userExists(username)) {
        cout << "Error. User already exists" << endl;
        return;
    }
    //Create new file for user and add them to broadcast channel
    newFile(username);
    addUserToGroup(username, "All");
    //Initialze utilty objects
    fstream fileStream; ifstream inputStream; ofstream outputStream; stringstream stringStream; string input;
    //Open user file.
    inputStream.open("SYSTEM_USERS.txt");
    //Copy current contents (list of users/groups they are in).
    while (getline(inputStream, input)) {
        stringStream << input << endl;
        if ((int) input.find(username) != -1) {
            cout << "USER ALREADY EXISTS";
            return;
        }
    }
    inputStream.close();
    outputStream.open("SYSTEM_USERS.txt");
    //Append the new user
    outputStream << username + ":\n";
    //Paste previous list of users
    while(getline(stringStream, input)) {
        outputStream << input << endl;
    }
    outputStream.flush();
    outputStream.close();
    //Refresh system (ensure persistancy across mutliple instances of program)
    refresh();
}


// Function:     addGroup
// Input:        A given groupname
// Description:  Adds a new group to the system vector containing all groups.
void System::addGroup(string groupname) {
    refresh();
    //Check if group already exists.
    if (groupExists(groupname)) {
        cout << "Error. Group already exists." << endl;
        return;
    }
    //Initialze file for the new group
    newFile("_" + groupname);
    fstream fileStream; ifstream inputStream; ofstream outputStream; stringstream stringStream; string input;
    //Open and copy all current groups/list of users in them
    inputStream.open("SYSTEM_GROUPS.txt");
    while (getline(inputStream, input)) {
        stringStream << input << endl;
        if ((int) input.find(groupname) != -1) {
            cout << "USER ALREADY EXISTS";
            return;
        }
    }
    inputStream.close();
    outputStream.open("SYSTEM_GROUPS.txt");
    //Append new group
    outputStream << groupname + ":\n";
    //Paste previous group file contents
    while(getline(stringStream, input)) {
        outputStream << input << endl;
    }
    outputStream.flush();
    outputStream.close();
};

void System::addUserToGroup(string username, string groupname) {
    //Refresh system and initialize utility objects
    refresh();
    fstream fileStream; ifstream inputStream; ofstream outputStream; stringstream stringStream; string input;
    //Check for exceptions
    if ((!groupExists(groupname) || !userExists(username)) && groupname != "All") {
        cout << "Error user or group does not exist.";
        return;
    }
    //Open and copy current groups
    inputStream.open("SYSTEM_GROUPS.txt");
    while(getline(inputStream, input)) {
        stringStream << input << endl;
    }
    inputStream.close();
    //If group exists, then append the username to the end of the line of the correct group
    outputStream.open("SYSTEM_GROUPS.txt");
    while (getline(stringStream, input)) {
        if ((int) input.find(groupname) != -1) {
            outputStream << input + username + "|" << endl;
        }
        else {
            outputStream << input << endl;
        }
    }
    outputStream.flush();
    outputStream.close();
    stringStream.clear();

    //Adds group to user's list of groups they are a member of.
    inputStream.open("SYSTEM_USERS.txt");
    while(getline(inputStream, input)) {
        stringStream << input << endl;
    }
    inputStream.close();
    //If group exists, then append the username to the end of the line of the correct group
    outputStream.open("SYSTEM_USERS.txt");
    while (getline(stringStream, input)) {
        if ((int) input.find(username) != -1) {
            outputStream << input + groupname + "|" << endl;
        }
        else {
            outputStream << input << endl;

        }
    }
    outputStream.flush();
    outputStream.close();
    refresh();
}

// Function:     userExists(string username)
// Inputs:       Active user's name
// Output:       Boolean indicating if user is in system
// Description:  Returns true if user is in system. False otherwise.
bool System::userExists(string username) {
    refresh();
    for (User u : users) {
        if (u.username == username) {
            return true;
        }
    }
    return false;
}

bool System::groupExists(string groupname) {
    refresh();
    for (Group g : groups) {
        if (g.groupname == groupname) {
            return true;
        }
    }
    return false;
}

// Function:     refresh
// Description:  The function that keeps the system's list of user and group info up to the second with any and all other
//               instances of the program as well as any previous instances ever ran. Ensures consistency of system. Called
//               at least once per menu selection and sometimes more for extra redundancy.
void System::refresh() {
    //Clear system's users and group vectors
    users.clear();
    groups.clear();
    //Initialze utility objects
    fstream fileStream;
    ifstream inputStream;
    ofstream outputStream;
    stringstream stringStream;
    string input;
    //Goes through each user. Creates their object, including the vector of all groups they are part of. Parsing with my
    //personal syntax of storing users. View the txt file to see format.
    inputStream.open("SYSTEM_USERS.txt");
    while(getline(inputStream, input)) {
        stringStream << input;
        int pos = (int) input.find_first_of(':');
        string username = input.substr(0,pos);
        User temp = User(username);
        string groups = input.substr(pos + 1,input.size()-1);
        while (groups.size() > 1) {
            int endOfGroup = (int) groups.find("|");
            string currentGroup = groups.substr(0,endOfGroup);
            temp.memberOf.push_back(currentGroup);
            groups = groups.substr(endOfGroup + 1, groups.size()-1);
        }
        users.push_back(temp);
    }
    inputStream.close();
    //Goes through each group. Creates their object, including the vector of all users that are member. Parsing with my
    //personal syntax of storing groups. View the txt file to see format.
    inputStream.open("SYSTEM_GROUPS.txt");
    while(getline(inputStream, input)) {
        stringStream << input;
        int pos = (int) input.find_first_of(':');
        string groupname = input.substr(0,pos);
        Group temp = Group(groupname);
        string users = input.substr(pos + 1,input.size()-1);
        while (users.size() > 1) {
            int endOfUser = (int) users.find("|");
            string currentUser = users.substr(0,endOfUser);
            temp.members.push_back(getUser(currentUser));
            users = users.substr(endOfUser + 1, groups.size() -1);
        }
        groups.push_back(temp);
    }
    inputStream.close();
}

// Function:     newFile(string title)
// Inputs:       name of file desired to be created (without .txt extension)
// Description:  Utility function to create a new blank file. Automatically stored as txt file.
void System::newFile(string title) {
    fstream fileStream; ifstream inputStream; ofstream outputStream;
    //Generic fstream opens, and creates if it does exist
    fileStream.open(title + ".txt",fstream::out);
    if (fileStream.fail()) {
        cout << "FAILURE";
    }
    fileStream.close();
}

// Function:     getUser(string name)
// Inputs:       name of user
// Description:  Utility function to return appropriate user object any purpose necessary.
User System::getUser(string name) {
    //Go through all users in system
    for (User u : users) {
        //If the name matches username, return that user object
        if (u.username == name) {
            return u;
        }
    }
    //Should never reach this statement. Used for debugging.
    return User("INVALID PROBLEM");
}
