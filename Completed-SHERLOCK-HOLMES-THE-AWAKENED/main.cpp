/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals 2023
* Author: Huy Tran
* Date: 07.11.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "awakened.h"
using namespace std;

int readFile(
    const string & filename,
    string & schedule,
    string & map,
    string & moveStyle,
    int & stamina,
    int & size,
    int & k,
    int* arr
) {
//This function is used to read the input file,
//DO NOT MODIFY THIS FUNCTION
    ifstream myFile(filename);
    if (myFile.is_open()) {
        myFile >> schedule
               >> map
               >> moveStyle
               >> stamina
               >> size
               >> k;
        for(int i = 0; i < size; i++){
            myFile >> arr[i];
        }
        return 1;
    }
    else return 0;
}

int main() {
    string filename = "input1.txt";
    string schedule, map, moveStyle;
    int stamina, size, k;
    int arr[50];

    bool isRead = readFile(filename, schedule, map, moveStyle,
                           stamina, size, k, arr);
    if (isRead){
        cout << schedule << endl;
        cout << map << endl;
        cout << moveStyle << endl;
        cout << stamina << endl;
        cout << size << endl;
        cout << k << endl;
        for(int i = 0; i < size; i++){
            cout << arr[i];
            if(i == size - 1) cout << endl;
            else cout << " ";
        }

        // The first case
        int numInvalid = invalidTime(schedule);
        string longestDurationShip = longestDuration(schedule);
        cout << "numInvalid: " << numInvalid << endl;
        cout << "longestDurationShip: " << longestDurationShip << endl;

        // The second case
        int outTime=0;
        string outPath="";

        bool foundAltar = investigateTemple(map, moveStyle, stamina, outTime, outPath);
        cout << "Found altar: " << foundAltar << endl;
        cout << "outTime: " << outTime << endl;
        cout << "outPath: " << outPath << endl;

        // Task 3
        int password = solveCrate(arr, size, k);
        cout << password << endl;
    }
    else{
        cout << "Cannot read input file";
    }
    return 0;
}
