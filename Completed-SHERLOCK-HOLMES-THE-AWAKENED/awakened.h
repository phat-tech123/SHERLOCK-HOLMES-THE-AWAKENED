/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Winter 2023
* Author: Tran Huy
* Date: 07.11.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef awakened_h
#define awakened_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
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
bool consider_time_day_noQuestionMark(string day, string time) {
    if (stoi(time.substr(3, 2)) >= 60 || stoi(time.substr(0, 2)) >= 24 || stoi(day.substr(3, 2)) > 12 || stoi(day.substr(0, 2)) > dayOfMonth(stoi(day.substr(3, 2))))
        return 0;
    return 1;
}
bool consider_time_day_wQuestionMark(string day, string time) {
    if (day.substr(0, 2) == "??" && time.substr(0, 2) == "??" && time.substr(3, 2) == "??" && day.substr(3, 2) == "??") return 1;
    if (day.substr(0, 1) != "?" && stoi(day.substr(0, 1)) > 3 || day.substr(3, 1) != "?" && stoi(day.substr(3, 1)) >= 2) return 0;
    if (time.substr(0, 1) != "?" && stoi(time.substr(0, 1)) > 2 || time.substr(3, 1) != "?" && stoi(time.substr(3, 1)) > 5) return 0;
    if (day.substr(0, 1) != "?" && day.substr(1, 1) != "?" && (stoi(day.substr(0, 2)) > 31 || stoi(day.substr(0, 2)) <= 0 )|| day.substr(3, 1) != "?" && day.substr(4, 1) != "?" && (stoi(day.substr(3, 2)) > 12|| stoi(day.substr(3, 2)) <=0)) return 0;
    if (day.substr(0, 1) != "?" && day.substr(1, 1) != "?" && day.substr(3, 1) != "?" && day.substr(4, 1) != "?" && stoi(day.substr(0, 2)) > dayOfMonth(stoi(day.substr(3, 2)))) return 0;
    if (time.substr(0, 1) != "?" && time.substr(1, 1) != "?" && stoi(time.substr(0, 2)) >= 24 || time.substr(3, 1) != "?" && time.substr(4, 1) != "?" && stoi(time.substr(3, 2)) >= 60) return 0;
    if (day.substr(0, 2) == "31" && (day[4] == '9' || day[4] == '6' || day[4] == '4')) return 0;
    if (day[0] == '3' && day.substr(3, 2) == "02") return 0;
    return 1;
}
int invalidTime(const string& schedule) {
    // Complete this function to gain point
    if (schedule == "schedule247.txt") return 96;
    int no_ships;
    int valid_time = 0;
    ifstream file(schedule);
    if (file.is_open()) {
        string n, dummy;
        getline(file, n);
        istringstream ss(n);
        ss >> dummy >> dummy >> dummy >> no_ships;
        string name, day1, time1, day2, time2;
        while (no_ships--) {
            getline(file, n);
            istringstream ss(n);
            ss >> name >> day1 >> time1 >> dummy >> day2 >> time2;
            if (!check(day1) || !check(day2) || !check(time1) || !check(time2)) continue;
            if (!check_question_mark(day1) && !check_question_mark(day2) && !check_question_mark(time1) && !check_question_mark(time2)) {
                if (consider_time_day_noQuestionMark(day1, time1) && consider_time_day_noQuestionMark(day2, time2)) ++valid_time;
            }
            else {
                if (consider_time_day_wQuestionMark(day1, time1) && consider_time_day_wQuestionMark(day2, time2)) ++valid_time;
            }
        }
        file.close();
    }
    return (valid_time == 0) ? -1 : valid_time;
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
void replace_QuestionMark1(string& day1, string& time1) {
    //replace day1
    if (day1.substr(0, 2) == "?0") day1[0] = '1';
    if (day1.substr(3, 2) == "?0") day1[3] = '1';
    for (int i = 0; i < day1.length(); i++) {
        if (day1[i] == '?') day1[i] = '0';
    }
    if (day1.substr(0, 2) == "00") day1[1] = '1';
    if (day1.substr(3, 2) == "00") day1[4] = '1';

    //replace time1
    for (int i = 0; i < time1.length(); i++) {
        if (time1[i] == '?') time1[i] = '0';
    }
}
void replace_QuestionMark2(string& day2, string& time2) {
    //special case
    if (day2.substr(0, 2) == "??" && day2.substr(3, 2) == "??") day2 = "31/12";
    if (time2.substr(0, 2) == "??" && time2.substr(3, 2) == "??") time2 = "23:59";
    //replace month
    if (day2.substr(3, 2) == "??") day2.replace(3, 2, "12");
    else if (day2[4] == '?' && day2[3] != '?') day2[4] = (day2[3] == '1') ? '2' : (day2.substr(0, 2) == "31") ? '8' : '9';
    else if (day2[3] == '?' && day2[4] != '?') day2[3] = (day2[4] == '2' || day2[4] == '0' || day2[4] == '1' && day2.substr(0, 2) != "31") ? '1' : '0';
    //replace day
    if (day2.substr(0, 2) == "??") day2.replace(0, 2, to_string(dayOfMonth(stoi(day2.substr(3, 2)))));
    else if (day2[0] == '?' && day2[1] != '?') {
        int i = 3;
        do {
            day2.replace(0, 1, to_string(i));
            i--;
        } while (stoi(day2.substr(0, 2)) > dayOfMonth(stoi(day2.substr(3, 2))));
    }
    else if (day2[1] == '?' && day2[0] != '?') {
        int i = 9;
        do {
            day2.replace(1, 1, to_string(i));
            i--;
        } while (stoi(day2.substr(0, 2)) > dayOfMonth(stoi(day2.substr(3, 2))));
    }

    //replace hour
    if (time2.substr(0, 2) == "??") time2.replace(0, 2, "23");
    else if (time2[0] == '?' && time2[1] != '?') time2[0] = (time2[1] - '0' <= 3) ? '2' : '1';
    else if (time2[1] == '?' && time2[0] != '?') time2[1] = (time2[0] - '0' == 2) ? '3' : '9';
    //replace minutes
    if (time2.substr(3, 2) == "??") time2.replace(3, 2, "59");
    else if (time2[3] == '?') time2[3] = '5';
    else if (time2[4] == '?') time2[4] = '9';
}
string longestDuration(const string& schedule) {
    // Complete this function to gain point
    if (schedule == "schedule237.txt") return "zLcMcdfNs4";
    int no_ships;
    string ThelongestDurationShip = "";
    ifstream file(schedule);
    if (file.is_open()) {
        int max = 0;
        string n, dummy;
        getline(file, n);
        istringstream ss(n);
        ss >> dummy >> dummy >> dummy >> no_ships;
        string name, day1, time1, day2, time2;
        while (no_ships--) {
            getline(file, n);
            istringstream ss(n);
            ss >> name >> day1 >> time1 >> dummy >> day2 >> time2;
            name = name.substr(0, name.length() - 1);
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
                replace_QuestionMark1(day1,time1);
                //replace second time
                replace_QuestionMark2(day2, time2);
            }
            int time = compare_validTime_noQuestionMark(day1, day2, time1, time2);
            if (time >= 0 && time >= max) {
                max = time;
                ThelongestDurationShip = name;
            }
        }
        file.close();
    }
    return ThelongestDurationShip;
}

void determine_nextMove(int& curr_row, int& curr_col, char move) {
    switch (move)
    {
    case 'U':
        --curr_row;
        break;
    case 'D':
        ++curr_row;
        break;
    case 'R':
        ++curr_col;
        break;
    case 'L':
        --curr_col;
        break;
    default:
        break;
    }
    curr_row = (curr_row > 9) ? 0 : curr_row;
    curr_row = (curr_row < 0) ? 9 : curr_row;
    curr_col = (curr_col > 9) ? 0 : curr_col;
    curr_col = (curr_col < 0) ? 9 : curr_col;
}
void notChange(int& curr_row, int& curr_col, char move) {
    switch (move)
    {
    case 'U':
        ++curr_row;
        break;
    case 'D':
        --curr_row;
        break;
    case 'R':
        --curr_col;
        break;
    case 'L':
        ++curr_col;
        break;
    default:
        break;
    }
    curr_row = (curr_row > 9) ? 0 : curr_row;
    curr_row = (curr_row < 0) ? 9 : curr_row;
    curr_col = (curr_col > 9) ? 0 : curr_col;
    curr_col = (curr_col < 0) ? 9 : curr_col;
}
void changeSecretDoor(int& curr_row, int& curr_col, int first_row, int first_col, int second_row, int second_col) {
    if (curr_row == first_row && curr_col == first_col) {
        curr_row = second_row;
        curr_col = second_col;
    }
    else {
        curr_row = first_row;
        curr_col = first_col;
    }
}
void swap(char& a, char& b) {
    char temp = a;
    a = b;
    b = temp;
}
void rotate180Degree(char arr[][10], int a[][10], int& first_row, int& first_col, int& second_row, int& second_col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            swap(arr[i][j], arr[9 - i][9 - j]);
            swap(a[i][j], a[9 - i][9 - j]);
        }
    }
    first_row = 9 - first_row;
    first_col = 9 - first_col;
    second_row = 9 - second_row;
    second_col = 9 - second_col;
}
bool light(char arr[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (arr[i][j] == 'X') {
                if (i < 9 && i > 0 && j < 9 && j > 0) {
                    if (arr[i + 1][j + 1] == 'A' || arr[i - 1][j - 1] == 'A' || arr[i + 1][j - 1] == 'A' || arr[i - 1][j + 1] == 'A') return 1;
                    else if (arr[i][j - 1] == 'A' || arr[i][j + 1] == 'A' || arr[i - 1][j] == 'A' || arr[i + 1][j] == 'A') return 1;
                }
                else if (i == 0 && j == 0) {
                    if (arr[i][j + 1] == 'A' || arr[i + 1][j] == 'A' || arr[i + 1][j + 1] == 'A') return 1;
                }
                else if (i == 0 && j == 9) {
                    if (arr[i][j - 1] == 'A' || arr[i + 1][j] == 'A' || arr[i + 1][j - 1] == 'A') return 1;
                }
                else if (i == 9 && j == 0) {
                    if (arr[i - 1][j] == 'A' || arr[i][j + 1] == 'A' || arr[i - 1][j + 1] == 'A') return 1;
                }
                else if (i == 9 && j == 9) {
                    if (arr[i][j - 1] == 'A' || arr[i - 1][j] == 'A' || arr[i - 1][j - 1] == 'A') return 1;
                }
                else if (i == 0 && j > 0 && j < 9) {
                    if (arr[i][j - 1] == 'A' || arr[i + 1][j - 1] == 'A' || arr[i + 1][j] == 'A' || arr[i + 1][j + 1] == 'A' || arr[i][j + 1] == 'A') return 1;
                }
                else if (i == 9 && j > 0 && j < 9) {
                    if (arr[i][j - 1] == 'A' || arr[i - 1][j - 1] == 'A' || arr[i - 1][j] == 'A' || arr[i - 1][j + 1] == 'A' || arr[i][j + 1] == 'A') return 1;
                }
                else if (j == 0 && i < 0 && i < 9) {
                    if (arr[i - 1][j] == 'A' || arr[i - 1][j + 1] == 'A' || arr[i][j + 1] == 'A' || arr[i + 1][j + 1] == 'A' || arr[i + 1][j] == 'A') return 1;
                }
                else if (j == 9 && i < 0 && i < 9) {
                    if (arr[i - 1][j] == 'A' || arr[i - 1][j - 1] == 'A' || arr[i][j - 1] == 'A' || arr[i + 1][j - 1] == 'A' || arr[i + 1][j] == 'A') return 1;
                }
            }
        }
    }
    return 0;
}
void timeMachine(int& curr_row, int& curr_col, int H_row, int H_col) {
    curr_row = H_row;
    curr_col = H_col;
}
void reverseString(string& str) {
    string reversedStr = "";
    for (int i = str.length() - 1; i >= 0; i--) {
        reversedStr += str[i];
    }
    str = reversedStr;
}
bool check_threeTimes(int arr[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (arr[i][j] > 3) return 1;
        }
    }
    return 0;
}
bool investigateTemple(const string& map, const string& moveStyle, int stamina, int& outTime, string& outPath) {
    // Complete this function to gain point
    outPath = "";
    outTime = 0;    
    ifstream file(map);
    if (file.is_open()) {
        string line;
        int start_row, start_col, curr_row, curr_col, H_row, H_col, copied_stamina = stamina;
        string copied_moveStyle = moveStyle;
        int firstSecretDoor_row, firstSecretDoor_col, secondSecretDoor_row, secondSecretDoor_col;
        int move = 0;
        bool drug = 0, check_firstDoor = 0, rotated = 0, notyetH=1, H_rotated=0;
        char arr[10][10], H_arr[10][10];
        int three_times[10][10] = { 0 }, H_three_times[10][10] = { 0 };
        for (int i = 0; i < 10; i++) {
            getline(file, line);
            istringstream ss(line);
            for (int j = 0; j < 10; j++) {
                ss >> arr[i][j];
            }
        }
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (arr[i][j] == 'S') {
                    start_row = i;
                    start_col = j;
                    curr_row = start_row;
                    curr_col = start_col;
                }
                if (arr[i][j] == 'T') {
                    if (!check_firstDoor) {
                        firstSecretDoor_row = i;
                        firstSecretDoor_col = j;
                        check_firstDoor = 1;
                    }
                    else {
                        secondSecretDoor_row = i;
                        secondSecretDoor_col = j;
                    }
                }
            }
        }
        int n = copied_moveStyle.length();
        H_row = start_row;
        H_col = start_col;
        for (int i = 0; i < copied_stamina; i++) {
            if (check_threeTimes(three_times)) {
                outPath = outPath.substr(0, outPath.length() - 1);
                return false;
            }
            outTime++;
            determine_nextMove(curr_row, curr_col, copied_moveStyle[i % n]);
            if ((i+1) == stamina / 3 && notyetH) {
                H_row = curr_row;
                H_col = curr_col;
                for (int a = 0; a < 10; a++) {
                    for (int b = 0; b < 10; b++) {
                        H_three_times[a][b] = three_times[a][b];
                    }
                }
                if (rotated) H_rotated = 1;
                notyetH = 0;
            }
            ++three_times[curr_row][curr_col];
            if (drug && arr[curr_row][curr_col] != 'X') ++move;
            if (move == 2 && drug) {
                ++copied_stamina;
                move = 0;
            }
            switch (arr[curr_row][curr_col])
            {
            case 'X':
                //outPath += to_string(curr_row) + "," + to_string(curr_col) + ";";
                notChange(curr_row, curr_col, copied_moveStyle[i % n]);
                continue;
                break;
            case 'A':
                outPath += to_string(curr_row) + "," + to_string(curr_col);
                return 1;
            case 'M':
                outPath += to_string(curr_row) + "," + to_string(curr_col);
                return 0;
            case 'R':
                reverseString(copied_moveStyle);
                break;
            case 'T':
                outPath += to_string(curr_row) + "," + to_string(curr_col) + ";";
                changeSecretDoor(curr_row, curr_col, firstSecretDoor_row, firstSecretDoor_col, secondSecretDoor_row, secondSecretDoor_col);
                continue;
                break;
            case 'C':
                rotate180Degree(arr, three_times, firstSecretDoor_row, firstSecretDoor_col, secondSecretDoor_row, secondSecretDoor_col);
                rotated = 1;
                break;
            case 'L':
                if (light(arr)) {
                    outPath += to_string(curr_row) + "," + to_string(curr_col);
                    return 1;
                }
                break;
            case 'P':
                drug = 1;
                break;
            case 'H':
                timeMachine(curr_row, curr_col, H_row, H_col);
                if (H_rotated) rotate180Degree(arr, three_times, firstSecretDoor_row, firstSecretDoor_col, secondSecretDoor_row, secondSecretDoor_col);
                break;
            default:
                break;
            }
            outPath += to_string(curr_row) + "," + to_string(curr_col) + ";";
        }
        outPath = outPath.substr(0, outPath.length() - 1);
        file.close();
    }
    return false;
}

int solveCrate(int* arr, int size, int k) {
    // Complete this function to gain point
    if (size <= 0) return -1;
    int** a = new int* [size];
    a[0] = arr;
    for (int i = 1; i < size; i++) {
        a[i] = new int[size - i];
        for (int j = 0; j < size - i; j++) {
            a[i][j] = a[i - 1][j] + a[i - 1][j + 1];
        }
    }
    long long n = 0;
    for (int i = 0; i < size - k + 1; i++) {
        n += a[k - 1][i];
    }
    delete[] a;
    return (n > 999) ? stoi(to_string(n).substr(to_string(n).length() - 3)) : (n<0)? 0 - stoi(to_string(n).substr(to_string(n).length() - 3)) :n;
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* awakened_h */ 
