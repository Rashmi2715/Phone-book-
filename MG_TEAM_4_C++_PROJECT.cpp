// Importing input output operations file 
#include <iostream> 
// Importing file class 
#include <fstream> 
// Importing standard library file 
#include <stdlib.h> 
  
using namespace std; 

// Contact class
class Contact {
    string fname, lname, phone_num;

public:
    // Constructor
    Contact(string fname, string lname, string phone_num) {
        this->fname = fname;
        this->lname = lname;
        this->phone_num = phone_num;
    }

    // Getter methods
    string getFirstName() {
        return fname;
    }

    string getLastName() {
        return lname;
    }

    string getPhoneNumber() {
        return phone_num;
    }
};

// ContactManager class
class ContactManager {
    string filename;

public:
    // Constructor
    ContactManager(string filename) {
        this->filename = filename;
    }

    // Method to add a contact
    void addContact(Contact contact) {
    ofstream phone(filename, ios::app);// opening file in append mode and phone is object for the filename
    if (phone.is_open()) { //checks whether the file is open or not
        string phoneNumber = contact.getPhoneNumber(); 
        if (phoneNumber.length() == 10 && (phoneNumber[0] == '6' || phoneNumber[0] == '7' || phoneNumber[0] == '8' || phoneNumber[0] == '9')) 
        {
            phone << contact.getFirstName() << " " << contact.getLastName() << " " << phoneNumber << endl;  //used to write data to an output file stream phone
            cout << "\n\tContact saved successfully!";
        }
        else {
            cout << "\n\tInvalid phone number! Phone number should start with 6, 7, 8, or 9 and have at least 10 digits.";
        }
    }
    else {
        cout << "\n\tError in opening record!";
    }
    cout << endl << endl;
    system("pause");
    system("cls");
    phone.close();
}

    // Method to search for a contact by phone number
    void searchContactByNumber(string keyword) {
        bool found = false;
        ifstream myfile(filename); //to read the contents of the file
        string fname, lname, phone_num;
        while (myfile >> fname >> lname >> phone_num) { //check whether the contents are present and reads the data from the file and storing it in the variables
            if (keyword == phone_num) {
                system("cls");
                cout << "\n\n\n\t\tCONTACT DETAILS";
                cout << "\n\nFirst Name : " << fname;
                cout << "\nLast Name : " << lname;
                cout << "\nPhone Number : " << phone_num;
                found = true;
                break;
            }
        }
        if (found == false)
            cout << "\nNo such contact is found!";
        cout << endl << endl;
        system("pause");
        system("cls");
    }

    // Method to search for a contact by name
    void searchContactByName(string keyword) {
        bool found = false;
        ifstream myfile(filename); //to read the contents of the file
        string fname, lname, phone_num;
        while (myfile >> fname >> lname >> phone_num) {
            if (keyword == fname || keyword == lname) {
                system("cls");
                cout << "\n\n\n\t\tCONTACT DETAILS";
                cout << "\n\nFirst Name : " << fname;
                cout << "\nLast Name : " << lname;
                cout << "\nPhone Number : " << phone_num;
                found = true;
                break;
            }
        }
        if (found == false)
            cout << "\nNo such contact is found!";
        cout << endl << endl;
        system("pause");
        system("cls");
    }

    // Method to display the entire contact list
    void display() {
    ifstream myfile(filename);

    // Check if the file is empty
    if (myfile.peek() == ifstream::traits_type::eof()) {
        cout << "\n\n\n\t\tCONTACT DETAILS\n\n";
        cout << "Content is empty.\n";
        return;
    }

    string fname, lname, phone_num;
    cout << "\n\n\n\t\tCONTACT DETAILS";
    while (myfile >> fname >> lname >> phone_num) {
        cout << "\n\nFirst Name : " << fname;
        cout << "\nLast Name : " << lname;
        cout << "\nPhone Number : " << phone_num;
    }
}

    // Method to remove a contact by name
    void removeContact(string phoneToRemove) {
        ifstream inFile(filename);
        ofstream tempFile("temp.txt", ios::app);  //temporary file to append

        bool contactFound = false;
        string fname, lname, phone_num;

        while (inFile >> fname >> lname >> phone_num) {
            if (fname == phoneToRemove || lname==phoneToRemove) {
                contactFound = true;
                cout << "\n\nContact removed successfully!";
            }
            else {
                tempFile << fname << " " << lname << " " << phone_num << endl; // writing the contents into the temporary file
            }
        }

        inFile.close();  //closing files
        tempFile.close(); 

        // Delete the original file
        remove(filename.c_str()); //c_str() converts the std::string(sequence of characters) to const char *(array of characters) i.e., null terminating character array

        // Rename the temporary file to the original file
        rename("temp.txt", filename.c_str());

        if (!contactFound) {
            cout << "\nNo contact with the given phone number was found.";
        }

        cout << endl << endl;
        system("pause");
        system("cls");
    }
};

// Main driver method
int main() {
    int choice;
    string filename = "number.txt";
    ContactManager contactManager(filename);

    system("cls");
    system("color 09");

    while (1) {
        cout << "\n\n\n\t\t\tCONTACT SAVER"<<endl;
        cout << "\nWhat do you want to do?" << endl;
        cout << "\n\t1. Add Contact";
        cout << "\n\t2. Search By Name Contact";
        cout << "\n\t3. Search By Number";
        cout << "\n\t4. Contact List";
        cout<< "\n\t5. Remove Contact";
        cout<< "\n\t0. Exit\n";

        cin >> choice;

        // Switch case
        switch (choice) {
        case 1: {
            string fname, lname, phone_num;
            cout << "\n\n\tEnter First Name : ";
            cin >> fname;

            cout << "\n\tEnter Last Name : ";
            cin >> lname;
            cout << "\n\tEnter Phone Number : ";
            cin >> phone_num;
            Contact contact(fname, lname, phone_num);
            contactManager.addContact(contact);
            break;
        }

        case 2: {
            string keyword;
            cout << "\n\tEnter Name to search : ";
            cin >> keyword;
            contactManager.searchContactByName(keyword);
            break;
        }

        case 3: {
            string keyword;
            cout << "\n\tEnter Number to search: ";
            cin >> keyword;
            contactManager.searchContactByNumber(keyword);
            break;
        }

        case 4:
            contactManager.display();
            break;

        case 5: {
            string phoneToRemove;
            cout << "\n\tEnter the Name of the contact to remove: ";
            cin >> phoneToRemove;
            contactManager.removeContact(phoneToRemove);
            break;
        }

        case 0:
            system("cls");
            cout << "\n\n\n\t\tThank You for using Contact-Saver!";
            exit(1);

        default:
            cout << "\n\n\tInvalid Input!";
        }
    }

    return 0;
}