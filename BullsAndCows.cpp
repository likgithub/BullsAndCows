#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cmath>


using namespace std;



int main() {
    srand(std::chrono::duration_cast<std::chrono::milliseconds>
     (std::chrono::system_clock::now().time_since_epoch()).count()%2000000000); 

    int num; //stores number of digits
    int digit;
    int remain;
    int code;
    int codeDigits[5]; //stores code
    int indexNum = 10; //manipulated later to remove index numbers
    int digits[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; //stores available values for code
    int guess; //number with user guess
    int guessDigits[5]; //contains the guess of the user
    int compare = 0; //this number is used to detect if code is too long
    int bulls = 0;
    int cows = 0;
    int checker = 0;


    do {
        cout << "Enter number of digits in code (3, 4 or 5): ";
        cin  >> num;
    } while ((num != 0) && (num != 3) && (num != 4) && (num !=5));

    if (num == 0) { //cheat code
        cout << "Enter code: ";
        cin >> code;

        cout << "Enter number of digits in code: ";
        cin >> num;

        for (int i = 0; i < num; i++) {//breaks down code to store it
        remain = code % 10;
        code = code / 10;
        codeDigits[num - i - 1] = remain;

        }
    }
    else {
        for (int i = 0; i < num; ++i) {
            digit = digits[rand() % indexNum];
            codeDigits[i] = digit;
            for (int j = 0; j < 10; ++j) {//removes number so identical numbers may not be chosen 
                if (digit == digits[j]) {
                    digits[j] = digits[j+1];
                    digit = digits[j];
                }
            }
            indexNum = indexNum - 1; //changes iteration amount so index will onlly chose unused numbers
            
        }
    }

    cout << "Number to guess: "; //prints out in required format
    for (int k = 0; k < num; k++) {
        cout << codeDigits[k];
        if (k < num - 1) {
            cout << "-";
        }
        else {
            cout << endl;
        }
    }
    for (int i = 0; i < num; i++) { //creates number to compare with to ensure guess is not too long
        compare += 9 * pow(10, i);
        }

    do {
        do {
            cout << "Enter Guess: ";
            cin >> guess;
            if (guess > compare) {
                cout << "You can only enter " << num << " digits. " << endl;
                continue;
            }

            if (guess < 0) {
                cout << "You must guess a positive integer" << endl;
                continue;
            }

            for (int i = 0; i < num; i++) {//breaks down guess to store it
            remain = guess % 10;
            guess = guess / 10;
            guessDigits[num - i - 1] = remain;
            }

            checker = 0;
            
            for (int i = 0; i < num; i++) {

                for (int j = num - 1; j >= 0; j--) {
                    if (i == j) {
                        continue;
                    }
                    if (guessDigits[i] == guessDigits[j]) {
                        cout << "Each number must be different." << endl;
                        checker = 1;
                        break;
                    }
                } 
                if (checker == 1) {
                    break;
                }
            
            }
        } while ((guess > compare) || (checker == 1) || (guess < 0));
        
        

        bulls = 0;
        cows = 0; //both are reinitialized in the case of multple loops

        for (int i = 0; i < num; i++) { 
            if (guessDigits[i] == codeDigits[i]) {
                    bulls += 1;
                }
            for (int j = num - 1; j >= 0; j--) {
                if (i == j) {
                    continue;
                }
                if (guessDigits[i] == codeDigits[j]) {
                    cows += 1;
                }
            }
        }
        
        if (bulls == num) {
            cout << num << " bulls... ";
            for (int k = 0; k < num; k++) {
            cout << codeDigits[k];
                if (k < num - 1) {
                    cout << "-";
                }
                else {
                    cout << " is correct!" << endl;
                }
            }

        }
        else {
            cout << bulls << " bulls" << endl;
            cout << cows << " cows" << endl; 
        }
    } while (bulls != num);
    


    
}

