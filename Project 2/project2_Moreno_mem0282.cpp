/* FILE NAME: project2_Moreno_mem0282.cpp
 * Name: Melvin Moreno
 * Auburn UserID: mem0282
 * Utilized stack overflow to learn about asserts, test drivers, and const.
 * Compile: g++ project2_Moreno_mem0282.cpp -o Project2.out
 * Run: ./Project2.out
 */

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
#include <iomanip>
using namespace std;

//Variables
const double aaronAccuracy = (1.0/3.0) * 100.0;
const double bobAccuracy = (1.0/2.0) * 100.0;
const double charlieAccuracy = 100;
int aaronWins = 0;
int bobWins = 0;
int charlieWins = 0;
const int totalRuns = 10000;

/*
 * Input: Aaron_alive indicates Aaron is alive true for alive, false for dead
 * Bob_alive indicates Bob is alive
 * Charlie_alive indicates Charlie is alive
 * Return: true if at least two are alive otherwise return false
 */
bool at_least_two_alive(bool Aaron_alive, bool Bob_alive, bool Charlie_alive);

/*
 * Call by reference
 * Strategy 1: Everyone shoots to kill the highest accuracy player alive
 * Input: Bob_alive indicates Bob is alive or dead
 * Charlie_alive indicates Aaron is alive or dead
 * Return: ChangeBob_alive into false if Bob is killed
 * Change Charlie_alive into false if Charlie is killed
 */
void Aaron_shoots1(bool& Bob_alive, bool& Charlie_alive);

/*
 * Call by reference
 * Input: Aaron_alive indicates Aaron is alive or dead
 * Charlie_alive indicates Charlie is alive or dead
 * Return: Change Aaron_alive into false if Aaron is killed
 * Change Charlie_alive into false if Charlie is killed
 */
void Bob_shoots(bool& aarronAlive, bool& Charlie_alive);

/*
 * Call by reference
 * Input: Aaron_alive indicates Aaron is alive or dead
 * Bob_alive indicates Bob is alive or dead
 * Return: Change Aaron_alive into false if Aaron is killed
 * Change Bob_alive into false if Bob is killed
 */
void Charlie_shoots(bool& Aaron_alive, bool& Bob_alive);

/*
 * Call by reference
 * Strategy 2: Aaron intentionally misses if both are alive
 * Input: Bob_alive indicates Bob is alive or dead
 * Charlie_alive indicates Aaron is alive or dead
 * Return: Change Bob_alive into false if Bob is killed
 * Change Charlie_alive into false if Charlie is killed
 */
void Aaron_shoots2(bool& Bob_alive, bool& Charlie_alive);

/*
 * Uses Strategy 1
 * Input: None
 * Return: Changes playerWins variables depending on who wins. 
 */
void duel_strategy1(void);

/*
 * Uses Strategy 2
 * Input: None
 * Return: Changes playerWins variables depending on who wins.
 */
void duel_strategy2(void);

//Simple method to implement pause function in linux
void Press_any_key(void);

//TEST PROTOTYPES
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);


int main() {
    //Formatting
    cout.setf(ios::fixed | ios::showpoint);

    //Initializes Random number generator's seed and calls test functions
    cout << "*** Welcome to Melvin's Duel Simulator ***\n";
    srand(time(0));

    test_at_least_two_alive();
    Press_any_key();

    test_Aaron_shoots1();
    Press_any_key();

    test_Bob_shoots();
    Press_any_key();

    test_Charlie_shoots();
    Press_any_key();

    test_Aaron_shoots2();
    Press_any_key();

    //Starts strategy 1 and runs 10,000 times
    cout << "Ready to test strategy 1 (run 10000 times):\n";
    Press_any_key();
    for (int i = 0; i < totalRuns; i++) {
        duel_strategy1();
    }

    double aaronWinPercentage = (double) aaronWins / (double) totalRuns;
    double bobWinPercentage = (double) bobWins / (double) totalRuns;
    double charlieWinPercentage = (double) charlieWins / (double) totalRuns;
    int aaronWinsStrategy1 = aaronWins;
    cout << "Aaron won " << aaronWins << "/" << totalRuns << " duels or "
        << setprecision(2) << aaronWinPercentage * 100 << "%\n";
    cout << "Bob won " << bobWins << "/" << totalRuns << " duels or "
        << setprecision(2) << bobWinPercentage * 100 << "%\n";
    cout << "Charlie won " << charlieWins << "/" << totalRuns << " duels or "
        << setprecision(2) << charlieWinPercentage * 100 << "%\n";

    //Starts Strategy 2 and runs 10,000 times
    cout << "\nReady to test strategy 2 (run 10000 times):\n";
    Press_any_key();
    aaronWins = 0;
    bobWins = 0;
    charlieWins = 0;
    for (int i = 0; i < totalRuns; i++) {
        duel_strategy2();
    }
    aaronWinPercentage = (double) aaronWins / (double) totalRuns;
    bobWinPercentage = (double) bobWins / (double) totalRuns;
    charlieWinPercentage = (double) charlieWins / (double) totalRuns;
    cout << "Aaron won " << aaronWins << "/" << totalRuns << " duels or "
        << setprecision(2) << aaronWinPercentage * 100 << "%\n";
    cout << "Bob won " << bobWins << "/" << totalRuns << " duels or "
        << setprecision(2) << bobWinPercentage * 100 << "%\n";
    cout << "Charlie won " << charlieWins << "/" << totalRuns << " duels or "
        << setprecision(2) << charlieWinPercentage * 100 << "%\n";

    //Compare both strategies to see which is better
    if (aaronWins > aaronWinsStrategy1) {
        cout << "\nStrategy 2 is better than strategy 1.";
    }
    else if (aaronWins < aaronWinsStrategy1) {
        cout << "\nStrategy 1 is better than strategy 2.";
    }
    else {
        cout << "\nThe strategies have the same outcomes.";
    }
}

//Implementation of functions. Look above for documentation of them.
bool at_least_two_alive(bool Aaron_alive, bool Bob_alive, bool Charlie_alive) {
    if (Aaron_alive) {
        if (Bob_alive || Charlie_alive) {
            return true;
        }
    }
    else if (Bob_alive) {
        if (Charlie_alive) {
            return true;
        }
    }
    else {
        return false;
    }
}
void test_at_least_two_alive(void) {
    cout << "Unit Test 1: Function - at_least_two_alive()\n";

    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\tCase passed...\n";

    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed...\n";

    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\tCase passed...\n";

    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\tCase passed...\n";

    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed...\n";

    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\tCase passed...\n";

    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\tCase passed...\n"; 

    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\tCase passed...\n";
    }

void Aaron_shoots1(bool& Bob_alive, bool& Charlie_alive) {
    int shootTargetResult = rand()%100;
    if (shootTargetResult <= aaronAccuracy) {
        if (Charlie_alive) {
            Charlie_alive = false;
        }
        else {
            Bob_alive = false;
        }
    }
}
void test_Aaron_shoots1(void) {
    cout << "Unit Test 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
    bool Bob_alive;
    bool Charlie_alive;

    cout << "\tCase 1: Bob alive, Charlie alive\n";
    cout << "\t\tAaron is shooting at Charlie\n";
    Bob_alive = true;
    Charlie_alive = true;
    Aaron_shoots1(Bob_alive, Charlie_alive);
    assert(true == Bob_alive);

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    cout << "\t\tAaron is shooting at Charlie\n";
    Bob_alive = false;
    Charlie_alive = true;
    Aaron_shoots1(Bob_alive, Charlie_alive);
    assert(false == Bob_alive);

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    cout << "\t\tAaron is shooting at Bob\n";
    Bob_alive = true;
    Charlie_alive = false;
    Aaron_shoots1(Bob_alive, Charlie_alive);
    assert(false == Charlie_alive);
}

void Bob_shoots(bool& Aaron_alive, bool& Charlie_alive) {
    int shootTargetResult = rand()%100;
    if (shootTargetResult <= bobAccuracy) {
        if (Charlie_alive) {
            Charlie_alive = false;
        }
        else {
            Aaron_alive = false;
        }
    }
}
void test_Bob_shoots(void) {
    cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
    bool Aaron_alive;
    bool Charlie_alive;

    cout << "\tCase 1: Aaron alive, Charlie Alive\n";
    cout << "\t\tBob is shooting at Charlie\n";
    Aaron_alive = true;
    Charlie_alive = true;
    Bob_shoots(Aaron_alive, Charlie_alive);
    assert(true == Aaron_alive);

    cout << "\tCase 2: Aaron dead, Charlie alive\n";
    cout << "\t\tBob is shooting at Charlie\n";
    Aaron_alive = false;
    Charlie_alive = true;
    Bob_shoots(Aaron_alive, Charlie_alive);
    assert(false == Aaron_alive);

    cout << "\tCase 3: Aaron alive, Charlie dead\n";
    cout << "\t\tBob is shooting at Aaron\n";
    Aaron_alive = true;
    Charlie_alive = false;
    Bob_shoots(Aaron_alive, Charlie_alive);
    assert(false == Charlie_alive);
}

void Charlie_shoots(bool& Aaron_alive, bool& Bob_alive) {
    if (Bob_alive) {
        Bob_alive = false;
    }
    else {
        Aaron_alive = false;
    }
}

void test_Charlie_shoots(void) {
    cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
    bool Aaron_alive;
    bool Bob_alive;

    cout << "\tCase 1: Aaron alive, Bob alive\n";
    cout << "\t\tCharlie is shooting at Bob\n";
    Aaron_alive = true;
    Bob_alive = true;
    Charlie_shoots(Aaron_alive, Bob_alive);
    assert(true == Aaron_alive);
    assert(false == Bob_alive);

    cout << "\tCase 2: Aaron dead, Bob alive\n";
    cout << "\t\tCharlie is shooting at Bob\n";
    Aaron_alive = false;
    Bob_alive = true;
    Charlie_shoots(Aaron_alive, Bob_alive);
    assert(false == Aaron_alive);
    assert(false == Bob_alive);

    cout << "\tCase 3: Aaron alive, Bob dead\n";
    cout << "\t\tCharlie is shooting at Aaron\n";
    Aaron_alive = true;
    Bob_alive = false;
    Charlie_shoots(Aaron_alive, Bob_alive);
    assert(false == Bob_alive);
    assert(false == Aaron_alive);

}

void Aaron_shoots2(bool& Bob_alive, bool& Charlie_alive) {
    int shoot_target_result = rand()%100;
    if (!Bob_alive || !Charlie_alive) {
        if (shoot_target_result <= aaronAccuracy) {
            if (Charlie_alive) {
                Charlie_alive = false;
            }
            else {
                Bob_alive = false;
            }
        }
    }
}
void test_Aaron_shoots2(void) {
    cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
    bool Bob_alive;
    bool Charlie_alive;

    cout << "\tCase 1: Bob alive, Charlie alive\n";
    cout << "\t\tAaron intentionally misses his first shot\n";
    Bob_alive = true;
    Charlie_alive = true;
    Aaron_shoots2(Bob_alive, Charlie_alive);
    assert(true == Bob_alive);
    assert(true == Charlie_alive);
    cout << "\t\tBoth Bob and Charlie are alive\n";

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    cout << "\t\tAaron is shooting at Charlie\n";
    Bob_alive = false;
    Charlie_alive = true;
    Aaron_shoots2(Bob_alive, Charlie_alive);
    assert(false == Bob_alive);

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    cout << "\t\tAaron is shooting at Bob\n";
    Bob_alive = true;
    Charlie_alive = false;
    Aaron_shoots2(Bob_alive, Charlie_alive);
    assert(false == Charlie_alive);
}

void duel_strategy1(void) {
    bool Aaron_alive = true;
    bool Bob_alive = true;
    bool Charlie_alive = true;
    while (at_least_two_alive(Aaron_alive, Bob_alive, Charlie_alive)) {
        if (Aaron_alive) {
            Aaron_shoots1(Bob_alive, Charlie_alive);
        }
        if (Bob_alive) {
            Bob_shoots(Aaron_alive, Charlie_alive);
        }
        if (Charlie_alive) {
            Charlie_shoots(Aaron_alive, Bob_alive);
        }
    }
    if (Aaron_alive) {
        aaronWins++;
    }
    else if (Bob_alive) {
        bobWins++;
    }
    else {
        charlieWins++;
    }
}

void duel_strategy2(void) {
    bool Aaron_alive = true;
    bool Bob_alive = true;
    bool Charlie_alive = true;
    while (at_least_two_alive(Aaron_alive, Bob_alive, Charlie_alive)) {
        if (Aaron_alive) {
            Aaron_shoots2(Bob_alive, Charlie_alive);
        }
        if (Bob_alive) {
            Bob_shoots(Aaron_alive, Charlie_alive);
        }
        if (Charlie_alive) {
            Charlie_shoots(Aaron_alive, Bob_alive);
        }
    }
    if (Aaron_alive) {
        aaronWins++;
    }
    else if(Bob_alive) {
        bobWins++;
    }
    else {
        charlieWins++;
    }
}
    void Press_any_key(void) {
        cout << "Press any key to continue...";
        cin.ignore().get();
    }