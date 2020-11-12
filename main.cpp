//Use `bash run` to compile and run

#include <iostream>
#include <string>

#include "DataAccess.h"

using namespace std;

int main() {
    string fileName;
    int userSelection = 0;
    string userId;
    string userValue;
    DataAccess activeFile;

    cout << "Which file would you like to access?" << endl;
    getline(cin,fileName);

    if(fileName == "") {
        activeFile.Open();
    }
    else {
        activeFile.Open(fileName);
    }

    do {
        cout << "Menu Options:" << endl;
        cout << "0: Change File" << endl;
        cout << "1: SetValue" << endl;
        cout << "2: GetValue" << endl;
        cout << "3: Remove" << endl;
        cout << "4: Print" << endl;
        cout << "5: Size" << endl;
        cout << "-1: Quit" << endl;

        try {
            string input;
            cin >> input;
            userSelection = stoi(input);
            cin.ignore();
        } catch (invalid_argument& e) {
            userSelection = -2;
        }

        switch(userSelection){

            case 0:
                activeFile.Save();

                cout << "Which file would you like to access?" << endl;
                getline(cin,fileName);

                if(fileName == "") {
                    activeFile.Open();
                }
                else {
                    activeFile.Open(fileName);
                }
                break;

            case 1:
                cout << "What data point would you like to set? (ID)" << endl;
                cin >> userId;
                cin.ignore();

                cout << "What value would you like to store? (DATA)" << endl;
                getline(cin, userValue);

                activeFile.SetValue(userId, userValue);
                break;

            case 2:
                cout << "What data point would you like to retrieve? (ID)" << endl;
                cin >> userId;
                cout << activeFile.GetValue(userId) << endl;
                break;

            case 3:
                cout << "What data point would you like to remove? (ID)" << endl;
                cin >> userId;
                cin.ignore();

                if(activeFile.Remove(userId) == -1) {
                    cout << "ERROR: No data point of ID [" << userId << "] was found in " << fileName << endl;
                }
                break;

            case 4:
                activeFile.Print();
                break;

            case 5:
                cout << activeFile.Size() << endl;
                break;

            case -1:
                activeFile.Save();
                break;

            default:
                cout << "Input not recognised" << endl;
                cin.clear();
                continue;
        }
    } while (userSelection != -1);
}

