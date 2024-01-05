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

int dayOfMonth(int month) {
    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return 29;
    default:
        return -1;
    }
}
bool check(string n) {
    if (n[2] != '/' && n[2] != ':') return 0;
    for (int i = 0; i < n.length(); i++) {
        if (i == 2) continue;
        if ((n[i] < '0' || n[i] > '9') && n[i] != '?') return 0;
    }
    return 1;
}
bool check_question_mark(string n) {
    for (int i = 0; i < n.length(); i++) {
        if (n[i] == '?') return 1;
    }
    return 0;
}
bool consider_time_day_noQuestionMark(string day,string time){
    if (stoi(time.substr(3, 2)) >= 60 || stoi(time.substr(0, 2)) >= 24 || stoi(day.substr(3, 2)) > 12 || stoi(day.substr(0, 2)) > dayOfMonth(stoi(day.substr(3, 2))))
        return 0;
    return 1;
}
bool consider_time_day_wQuestionMark(string day, string time) {
    if (day.substr(0, 2) == "??" && time.substr(0, 2) == "??" && time.substr(3, 2) == "??" && day.substr(3, 2)=="??") return 1;
    if (day.substr(0, 1) != "?" && stoi(day.substr(0, 1)) > 3) return 0;
    if (time.substr(0, 1) != "?" && stoi(time.substr(0, 1)) > 2) return 0;
    if (day.substr(0, 2) != "??" && stoi(day.substr(0, 2)) > 31 || day.substr(3, 2) != "??" && stoi(day.substr(3, 2)) > 12) return 0;
    if (day.substr(0, 2) != "??" && day.substr(3, 2) != "??" && stoi(day.substr(0, 2)) > dayOfMonth(stoi(day.substr(3, 2)))) return 0;
    if (time.substr(0, 2) != "??" && stoi(time.substr(0, 2)) >= 24 || time.substr(3, 2) != "??" && stoi(time.substr(3, 2)) >= 60) return 0;
    return 1;
}
int invalidTime(string& schedule) {
    ifstream file;
    int no_ships;
    int valid_time = 0;
    file.open(schedule);
    string n;
    getline(file, n);
    n = n.substr(17, 3);
    for (int i = 0; i < 3; i++) {
        if (n[i] < '0' || n[i]>'9')
            return -1;
    }
    no_ships = stoi(n.substr(0, 3));
    if (no_ships == 0) return -1;
    while (no_ships--) {
        string day1, time1, day2, time2;
        file >> day1 >> day1 >> time1 >> day2 >> day2 >> time2;
        if (!check(day1) || !check(day2) || !check(time1) || !check(time2)) continue;
        if (!check_question_mark(day1) && !check_question_mark(day2) && !check_question_mark(time1) && !check_question_mark(time2)) {
            if (consider_time_day_noQuestionMark(day1, time1) && consider_time_day_noQuestionMark(day2, time2)) ++valid_time;
        }
        else {
            if (consider_time_day_wQuestionMark(day1, time1) && consider_time_day_wQuestionMark(day2, time2)) ++valid_time;
        }   
    }   
    file.close();
    return (valid_time==0) ? -1 : valid_time;
}

int compare_validTime_noQuestionMark(string day1, string day2, string time1, string time2) {
    if (time1 == time2 && day1 == day2) return 0;
    int day;
    int time;
    if (!consider_time_day_noQuestionMark(day1, time1) && !consider_time_day_noQuestionMark(day2, time2)) return -1;
    int durationDay1 = 1 + stoi(day1.substr(0, 2));
    for (int i = stoi(day1.substr(3, 2)) - 1; i >= 1; i--) {
        durationDay1 += dayOfMonth(i);
    }
    int durationDay2 = 1 + stoi(day2.substr(0, 2));
    for (int i = stoi(day2.substr(3, 2)) - 1; i >= 1; i--) {
        durationDay2 += dayOfMonth(i);
    }
    day = durationDay2 - durationDay1;
    if (day < 0) return -1;
    time = (stoi(time2.substr(0, 2)) * 60 + stoi(time2.substr(3, 2))) - (stoi(time1.substr(0, 2)) * 60 + stoi(time1.substr(3, 2)));
    return day * 24 * 60 + time;
}
string replace_QuestionMark1(string& s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '?') s[i] = '0';
    }
    return s;
}

string longestDuration(string& schedule) {
    if (invalidTime(schedule) == -1) return "";
    int max = 0;
    string n;
    int no_ship;
    fstream file;
    string ThelongestDurationShip = "";
    file.open(schedule);
    getline(file, n);
    no_ship = stoi(n.substr(17, 3));
    string name, day1, time1, day2, time2;
    while (no_ship--) { 
        file >> name >> day1 >> time1 >> day2 >> day2 >> time2;
        name.pop_back();
        //check_invalid
        if (!check_question_mark(day1) && !check_question_mark(day2) && !check_question_mark(time1) && !check_question_mark(time2)) {
            if (!consider_time_day_noQuestionMark(day1, time1) || !consider_time_day_noQuestionMark(day2, time2)) continue;
        }
        else {
            if (!consider_time_day_wQuestionMark(day1, time1) || !consider_time_day_wQuestionMark(day2, time2)) continue;
        }
        //valid
        if (check_question_mark(day1) || check_question_mark(day2) || check_question_mark(time1) || check_question_mark(time2)) {
            //replace first time
            replace_QuestionMark1(day1);
            if (day1.substr(0, 2) == "00") day1[1] = '1';
            if (day1.substr(3, 2) == "00") day1[4] = '1';
            replace_QuestionMark1(time1);
            //replace second day
            if (day2.substr(3, 2) == "??") day2.replace(3, 2, "12");
            if (day2[4] == '?') day2[4] = (day2[3] - '0' == 1) ? '2' : '9';
            if (day2[3] == '?') day2[3] = (day2[4] - '0' <= 2) ? '1' : '0';
            if (day2.substr(0, 2) == "??") day2.replace(0, 2, to_string(dayOfMonth(stoi(day2.substr(3, 2)))));
            if (day2[0] == '?') day2[0] = (day2.substr(3, 2) == "02" || day2[1] - '0' > 1) ? '2' : '3';
            if (day2[1] == '?') {
                for (char i = '3'; i >= '0'; i--) {
                    day2[1] = i;
                    if (stoi(day2.substr(0, 2)) <= dayOfMonth(stoi(day2.substr(3, 2)))) break;
                }
            }
            //replace second time
            if (time2.substr(0, 2) == "??") time2.replace(0, 2, "23");
            if (time2[1] == '?') time2[1] = (time2[0] - '0' == 2) ? '3' : '9';
            if (time2[0] == '?') time2[0] = (time2[1] - '0' <= 3) ? '2' : '1';
            if (time2[3] == '?') time2[3] = '5';
            if (time2[4] == '?') time2[4] = '9';
        }
        int time = compare_validTime_noQuestionMark(day1, day2, time1, time2);
        if (time >= 0 && time >= max) {
            max = time;
            ThelongestDurationShip = name;
        }
    }
    file.close();
    return ThelongestDurationShip;
}

bool investigateTemple(string& map, string moveStyle, int stamina, int outTime, string outPath) {
    int start_row, start_col;
    fstream file;
    char arr[10][10];
    file.open(map);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            file >> arr[i][j];
            if (arr[i][j] == 'S') {
                start_row = i;
                start_col = j;
            }
        }
    }
    string copyMove = moveStyle;
    if(stamina)
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
        int outTime;
        string outPath;

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
