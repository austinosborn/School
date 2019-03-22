// Lab 4:     Simple Cash Register
// Class:     COMP 2710-001
// Date:      12/08/2017
// Email:     aeo0015@auburn.edu
//
// Description: A simple cash register application taking advantage of inheritance.
//

#include <iostream>
#include <vector>
#include <iomanip>

//Class Declarations
class System; class Sale; class RegularSale; class ContractorSale;
class RegularCash; class RegularCheck; class RegularCreditCard;
class ContractCash; class ContractCheck; class ContractCreditCard;

using namespace std;

struct Item {
    string name;
    double amount;
    Item(string name, double amount) {
        this->name = name;
        this->amount = amount;
    }
};
// Class:       System
// Description: System Class holds vector of all sales and various utility methods.
class System {
public:
    vector<Sale*> sales;
    void printBar(string text);
    void prompt();
    bool inProgress = true;
};

class Sale {
public:
    double subtotal;
    double tax;
    double total;
    vector<Item *> items;
    virtual void process_sale()= 0;
    virtual void process_payment() = 0;
    virtual void print_sale() = 0;
};

class RegularSale : public Sale {
public:
    void process_sale() override;
    virtual void process_payment() = 0;
    virtual void print_sale() = 0;
};

class ContractorSale : public Sale {
public:
    string id;
    double discount;
    double discountedSubtotal;
    void process_sale() override;
    virtual void process_payment() = 0;
    virtual void print_sale() = 0;
};

class RegularCash : public RegularSale {
public:
    double recieved;
    double change;
    void process_payment() override;
    void print_sale() override;
};

class RegularCheck : public RegularSale {
public:
    void process_payment() override;
    void print_sale() override;
    string name;
    long long int dlNumber;
};

class RegularCreditCard : public RegularSale {
public:
    void process_payment() override;
    void print_sale() override;
    string name;
    long long int ccNumber;
    string expiration;
};

class ContractCash : public ContractorSale {
public:
    double recieved;
    double change;
    void process_payment() override;
    void print_sale() override;
};

class ContractCheck : public ContractorSale {
public:
    void process_payment() override;
    void print_sale() override;
    string name;
    long long int dlNumber;

};

class ContractCreditCard : public ContractorSale {
public:
    void process_payment() override;
    void print_sale() override;
    string name;
    long long int ccNumber;
    string expiration;

};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MAIN METHOD
int main() {
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    System s = System();
    s.prompt();
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of System Class

// Function:     printBar(string text)
// Input:        Desired text output
// Description:  Prints a formatted message to the console. Utility method to make UI more readable.
void System::printBar (string text) {
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

// Function:     prompt
// Description:  Continuously prompts user for sales until they quit. Handles errors.
void System::prompt() {
    while (inProgress) {
        printBar("Welcome to the Tiger Store!");
        cout
                << "Select an option. (1) Regular Cash, (2) Regular Check, (3) Regular Credit Card, (4) Contract Cash, (5) Contract Check, (6) Contract Credit Card, (7) Print all sales, or (8) Quit"
                << endl;
        string choiceString;
        int choice = -1;
        while (!(choice > 0) || !(choice < 9)) {
            cout << "Enter choice: ";
            getline(cin, choiceString);
            try {
                choice = stoi(choiceString);
            }
            catch (exception e) {
                cout << "\nPlease make a valid choice.\n";
            }
        }
        switch (choice) {
            case 1 : {
                auto *regularCash = new RegularCash();
                regularCash->process_sale();
                regularCash->process_payment();
                sales.emplace_back(regularCash);
                break;
            }
            case 2 : {
                auto *regularCheck = new RegularCheck();
                regularCheck->process_sale();
                regularCheck->process_payment();
                sales.emplace_back(regularCheck);
                break;
            }
            case 3 : {
                auto *regularCreditCard = new RegularCreditCard();
                regularCreditCard->process_sale();
                regularCreditCard->process_payment();
                sales.emplace_back(regularCreditCard);
                break;
            }
            case 4 : {
                auto *contractCash = new ContractCash();
                contractCash->process_sale();
                contractCash->process_payment();
                sales.emplace_back(contractCash);
                break;
            }
            case 5 : {
                auto *contractCheck = new ContractCheck();
                contractCheck->process_sale();
                contractCheck->process_payment();
                sales.emplace_back(contractCheck);
                break;
            }
            case 6 : {
                auto *contractCreditCard = new ContractCreditCard();
                contractCreditCard->process_sale();
                contractCreditCard->process_payment();
                sales.emplace_back(contractCreditCard);
                break;
            }
            case 7: {
                int i = 1;
                for (Sale * s: sales) {
                    cout << "Sale #" << i << endl;
                    s->print_sale();
                    i++;
                }
                break;
            }
            case 8: {
                inProgress = false;
                break;
            }
            default:
                cout << "ERROR";
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of RegularSale Class
//
// Function:     process_sale()
// Description:  Prompts for sale information stores
void RegularSale::process_sale() {
    bool stillEntering = true;
    double price = -1; string name;
    string input;
    while (stillEntering) {
        bool enteredValidPrice = false;
        cout << "Enter item: ";
        getline(cin, input);
        //Case for * input (end of items)
        if ((int) input.find('*') != -1) {
            if (this->items.size() == 0) {
                cout << "You must enter at least one item." << endl;
                continue;
            }
            else {
                stillEntering = false;
                continue;
            }
        }
        //
        name = input;
        while (!enteredValidPrice) {
            cout << "Enter amount: $ ";
            getline(cin, input);
            try {
                price = stod(input);
                enteredValidPrice = true;
            }
            catch (exception e) {
            }
        }
        Item * item = new Item(name, price);
        this->items.emplace_back(item);
    }
    //Calculate total and tax
    double total = 0;
    for (Item * i : this->items) {
        total += i->amount;
    }
    double tax = total * 0.08;
    this->subtotal = total;
    this->tax = tax;
    this->total = this->tax + this->subtotal;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of ContractorSale Class
//
// Function:     process_sale()
// Description:  Prompts for sale information stores
void ContractorSale::process_sale() {
    bool stillEntering = true;
    double price = -1; string name;
    string input;
    while (stillEntering) {
        bool enteredValidPrice = false;
        cout << "Enter item: ";
        getline(cin, input);
        //Case for * input (end of items)
        if ((int) input.find('*') != -1) {
            if (this->items.size() == 0) {
                cout << "You must enter at least one item." << endl;
                continue;
            }
            else {
                break;
            }
        }
        //
        name = input;
        while (!enteredValidPrice) {
            cout << "Enter amount: $ ";
            getline(cin, input);
            try {
                price = stod(input);
                enteredValidPrice = true;
            }
            catch (exception e) {
                cout << "Enter valid amount";
            }
        }
        Item * item = new Item(name, price);
        this->items.emplace_back(item);
    }
    //Total info
    double total = 0;
    for (Item * i : this->items) {
        total += i->amount;
    }
    this->subtotal = total;
    this->discount = (0.15*this->subtotal);
    this->discountedSubtotal = total - this->discount;
    this->tax = this->discountedSubtotal * 0.08;
    this->total = this->tax + this->discountedSubtotal;
    cout << "Subtotal: " << this->subtotal << endl;
    cout << "Contractor Sale" << endl;
    cout << "Enter Contractor ID: ";
    getline(cin, this->id);
    cout << "Discount: $" << this->discount << endl;
    cout << "Subtotal: " << this->discountedSubtotal << endl;
    cout << "Tax: $" << this->tax << endl;
    cout << "Total Amount: $" << this->total << endl;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of RegularCash Class
//
// Function:     process_payment()
// Description:  Prompts for sale information stores
void RegularCash::process_payment() {
    cout << "Sub-total: " << this->subtotal << endl;
    cout << "Regular Sale" << endl;
    cout << "Tax: $" << this->tax << endl;
    cout << "Total amount: $ " << this->total << endl;
    while (1) {
        cout << "Amount recieved: $ ";
        string input;
        getline(cin, input);
        try {
            this->recieved = stod(input);
            break;
        }
        catch (exception e) {
            "\nEnter a valid total: $ ";
        }
    }
    this->change = this->recieved - this->total;
    cout << "Change: $" << this->change << endl;
}

// Function:     process_payment()
// Description:  Prompts for sale information stores
void RegularCash::print_sale() {
    int index = 1;
    for (Item * i : items) {
        cout << "   " << index << ". " << i->name << " $" << i->amount << endl;
        index++;
    }
    cout << "      Subtotal: $" << this->subtotal << endl;
    cout << "      Regular Sale" << endl;
    cout << "      Tsx: " << this->tax << endl;
    cout << "      Total Amount: $" << this->total << endl;
    cout << "      CASH" << endl;
    cout << "      Amount Received: $" << this->recieved << endl;
    cout << "      Change: $" << this->change << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of RegularCheck Class
//
// Function:     process_payment()
// Description:  Prompts for sale information stores
void RegularCheck::process_payment() {
    cout << "Sub-total: " << this->subtotal << endl;
    cout << "Regular Sale" << endl;
    cout << "Tax: $" << this->tax << endl;
    cout << "Total amount: $ " << this->total << endl;
    cout << "Enter name on the check: ";
    getline (cin, this->name);
    while (1) {
        cout << "Enter Drivers License Number: ";
        string input;
        getline(cin, input);
        try {
            this->dlNumber = stoll(input);
            break;
        }
        catch (exception e) {
        }
    }
}

// Function:     process_payment()
// Description:  Prompts for sale information stores
void RegularCheck::print_sale() {
    int index = 1;
    for (Item * i : items) {
        cout << "   " << index << ". " << i->name << " $" << i->amount << endl;
        index++;
    }
    cout << "      Subtotal: $" << this->subtotal << endl;
    cout << "      Regular Sale" << endl;
    cout << "      Tax: " << this->tax << endl;
    cout << "      Total Amount: $" << this->total << endl;
    cout << "      CHECK " << this->name << " " << this->dlNumber << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of RegularCreditCard Class
//
// Function:     process_payment()
// Description:  Prompts for sale information stores
void RegularCreditCard::process_payment() {
    cout << "Sub-total: " << this->subtotal << endl << endl;
    cout << "Regular Sale" << endl << endl;
    cout << "Tax: $" << this->tax << endl << endl;
    cout << "Total amount: $ " << this->total << endl;
    cout << "Enter name on credit card: ";
    getline(cin, this->name);
    while (1) {
        cout << "Enter credit card number: ";
        string input;
        getline(cin, input);
        try {
            this->ccNumber = stoll(input);
            break;
        }
        catch (exception e) {
        }
    }
    cout << "Enter expiration date: ";
    getline(cin, this->expiration);
}

// Function:     process_payment()
// Description:  Prompts for sale information stores
void RegularCreditCard::print_sale() {
    int index = 1;
    for (Item * i : items) {
        cout << "   " << index << ". " << i->name << " $" << i->amount << endl;
        index++;
    }
    cout << "      Subtotal: $" << this->subtotal << endl;
    cout << "      Regular Sale" << endl;
    cout << "      Tax: " << this->tax << endl;
    cout << "      Total Amount: $" << this->total << endl;
    cout << "      CREDIT CARD " << this->name << " "<< " " << this->ccNumber << " " << this->expiration << endl;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of ContractCash Class
//
// Function:     process_payment()
// Description:  Prompts for sale information stores
void ContractCash::process_payment() {
    cout << "Amount received: $ ";
    while (1) {
        string input;
        getline(cin, input);
        try {
            this->recieved = stod(input);
            break;
        }
        catch (exception e) {
            "\nEnter a valid total: $ ";
        }
    }
    this->change = this->recieved - this->total;
    cout << "\nChange: $" << this->change << endl;
}

// Function:     print_sale()
// Description:  Prints sale information.
void ContractCash::print_sale() {
    int index = 1;
    for (Item *i : items) {
        cout << "   " << index << ". " << i->name << " $" << i->amount << endl;
        index++;
    }
    cout << "      Subtotal: $" << this->subtotal << endl;
    cout << "      Contractor Sale" << endl;
    cout << "      Contractor ID: " << this->id << endl;
    cout << "      Discount: " << this->discount << endl;
    cout << "      Subtotal: $" << this->discountedSubtotal << endl;
    cout << "      Tax: $" << this->tax << endl;
    cout << "      Total Amount: $" << this->total << endl;
    cout << "      CASH" << endl;
    cout << "      Amount Received: $" << this->recieved << endl;
    cout << "      Change: $" << this->change << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of ContractCheck Class
//
// Function:     process_payment()
// Description:  Prompts for sale information stores
void ContractCheck::process_payment() {
    cout << "Enter name on the check: ";
    getline (cin, this->name);
    while (1) {
        cout << "Enter Drivers License Number: ";
        string input;
        getline(cin, input);
        try {
            this->dlNumber = stoll(input);
            break;
        }
        catch (exception e) {
        }
    }
}

// Function:     print_sale()
// Description:  Prints sale information.
void ContractCheck::print_sale() {
    int index = 1;
    for (Item *i : items) {
        cout << "   " << index << ". " << i->name << " $" << i->amount << endl;
        index++;
    }
    cout << "      Subtotal: $" << this->subtotal << endl;
    cout << "      Contractor Sale" << endl;
    cout << "      Contractor ID: " << this->id << endl;
    cout << "      Discount: $" << this->discount << endl;
    cout << "      Subtotal: $" << this->discountedSubtotal << endl;
    cout << "      Tax: $" << this->tax << endl;
    cout << "      Total Amount: $" << this->total << endl;
    cout << "      CHECK " << this->name << " " << this->dlNumber << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation of ContractCreditCard Class
//
// Function:     process_payment()
// Description:  Prompts for sale information stores
void ContractCreditCard::process_payment() {
    cout << "Enter name on credit card: ";
    getline(cin, this->name);
    while (1) {
        cout << "Enter credit card number: ";
        string input;
        getline(cin, input);
        try {
            this->ccNumber = stoll(input);
            break;
        }
        catch (exception e) {
        }
    }
    cout << "Enter expiration date: ";
    getline(cin, this->expiration);
}

// Function:     print_sale()
// Description:  Prints sale information.
void ContractCreditCard::print_sale() {
    int index = 1;
    for (Item *i : items) {
        cout << "   " << index << ". " << i->name << " $" << i->amount << endl;
        index++;
    }
    cout << "      Subtotal: $" << this->subtotal << endl;
    cout << "      Contractor Sale" << endl;
    cout << "      Contractor ID: " << this->id << endl;
    cout << "      Discount: " << this->discount << endl;
    cout << "      Subtotal: $" << this->discountedSubtotal << endl;
    cout << "      Tax: $" << this->tax << endl;
    cout << "      Total Amount: $" << this->total << endl;
    cout << "      CREDIT CARD " << this->name << " " << this->ccNumber << " " << this->expiration << endl;
}



