/* FILE NAME: project4_Moreno_mem0282.cpp
 * Name: Melvin Moreno
 * Auburn UserID: mem0282
 * I received no help with this project.
 * Compile: g++ project2_Moreno_mem0282.cpp -o Project4.out
 * Run: ./Project4.out
 */

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
using namespace std;

//Reduced number of Global Variables
int totalPoints;
int lastPoints;
string lastAnswer;

struct TriviaNode {
    string question;
    string answer;
    int points;
    TriviaNode *next;
};

class linkedList {
public:
    TriviaNode *head;
    TriviaNode *tail;
    TriviaNode *current;
    int size;

    linkedList() {
    TriviaNode *q1 = new TriviaNode();
    q1->question = "How long was the shortest war on record? (Hint: How many minutes)";
    q1->answer = "38";
    q1->points = 100;

    TriviaNode *q2 = new TriviaNode();
    q2->question = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
    q2->answer = "Bank of Italy";
    q2->points = 50;

    TriviaNode *q3 = new TriviaNode();
    q3->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
    q3->answer = "Wii Sports";
    q3->points = 20;

    q1->next = q2;
    q2->next = q3;
    q3->next = NULL;

    head = q1;
    tail = q3;
    size = 3;

    current = NULL;

}

void addNode(string question, string answer, int points) {
    TriviaNode *newNode = new TriviaNode();
    newNode->question = question;
    newNode->answer = answer;
    newNode->points = points;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

TriviaNode* getNext() {
    if (current == NULL) {
        current = head;
    } else {
        current = current->next;
    }
    return current;
}
};

int askQuestion(linkedList& list, int numberOfQuestions);
int case_insensitive_match(string s1, string s2);
void testAskQuestion(void);

// **COMMENT OUT THE LINE BELOW TO REMOVE TESTING CODE**
#define UNIT_TESTING
#ifdef UNIT_TESTING

int main() {
    testAskQuestion();
}

#else
int main() {
    string question;
    string answer;
    string repeat;
    int points;
    linkedList list;

    cout << "*** Welcome to Melvin's trivia quiz game ***\n";
    bool repeatGame = true;

    while (repeatGame) {
        cout << "Enter a question: ";
        getline(cin, question);

        cout << "Enter an answer: ";
        getline(cin, answer);

        cout << "Enter award points: ";
        cin >> points;
        cin.ignore();

        list.addNode(question, answer, points);

        cout << "Continue? (Yes/No): ";
        getline(cin, repeat);
        if (repeat == "No" || repeat == "no") {
            repeatGame = false;
        }
}

for (int i = 0; i < list.size; i++) {
    askQuestion(list, 1);
}
cout << "\n\n*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
}
#endif

int askQuestion(linkedList& list, int numberOfQuestions) {

    string answer;
    string correctAnswer;

    if (numberOfQuestions < 1) {

        cout << "\nWarning - the number of trivia to be asked must equal to or be larger than 1.\n";
        return 0;

    }
    
    if (numberOfQuestions > list.size) {
        cout << "\nWarning - there are only " << list.size << " trivia in the list.\n";
        return 0;
    }
    
    for (int i = 0; i < numberOfQuestions; i++) {
            
            TriviaNode *current = list.getNext();
            cout << "\nQuestion: " << current->question << "\n";
            cout << "Answer: ";
            getline(cin, answer);
    
            if (case_insensitive_match(answer, current->answer)) {
                cout << "Your answer is correct! You receive " << current->points << " points.\n";
                totalPoints += current->points;
                lastPoints = current->points;
                lastAnswer = current->answer;
                cout << "Your total points: " << totalPoints << "\n";
            } else {
                cout << "Your answer is wrong. The correct answer is " << current->answer << ".\n";
                cout << "Your total points: " << totalPoints << "\n";
            }
    }
    return 1;
}

void testAskQuestion(void) {
    linkedList test1;
    linkedList test2;
    linkedList test3;
    linkedList test4;

    cout << "*** This is a debugging version ***";
    cout << "\nUnit Test Case 1: Ask no question. The program should give a warning message.";
    askQuestion(test1, 0);
    cout << "Case 1 Passed\n";

    cout << "\nUnit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer.";
    askQuestion(test1, 1);
    cout << "\nCase 2.1 Passed\n";
    totalPoints = 0;

    cout << "\nUnit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer.";
    assert(1 == askQuestion(test2, 1));
    cout << "\nCase 2.2 Passed\n";
    totalPoints = 0;

    cout << "\nUnit Test Case 3: Ask all the questions of the last trivia in the linked list.";
    assert (1 == askQuestion(test3, 3));
    cout << "\nCase 3 Passed\n";

    cout << "\nUnit Test Case 4: Ask 5 questions in the linked list.";
    assert (0 == askQuestion(test4, 5));
    cout << "\nCase 4 Passed\n";

    cout << "\n*** End of the Debugging Version ***\n\n";
    totalPoints = 0;
}
int case_insensitive_match(string s1, string s2) {
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    return s1 == s2;
}
