/*
 * Name: Melvin Moreno
 * Auburn UserID: mem0282
 * Collaborated with Nikhil Patel and Basil Moledina and referenced StackOverflow.
 * Compile: g++ project1_Moreno_mem0282.cpp -o Project1.out
 * Run: ./Project1.out
 */

#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    //Initialize variables
    double loan;
    double interestRate;
    double monthlyInterest;
    double interestRateC;
    double monthlyPaid;
    double principal;
    double totalPaid = 0;
    int currentMonth = 0;

    //Currency Formatting
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    //Ask for values & input values
    cout << "Loan Amount: ";
    cin >> loan;
    //Test case
    if (loan <= 0 || cin.fail()) {
        cout << "Invalid loan.";
        exit(0);
    }
    cout << "Interest Rate (% per year): ";
    cin >> interestRate;
    
    if (interestRate < 0 || cin.fail()) {
        cout << "Invalid interest rate";
        exit(0);
    }
    // Get proper interest rates for calculations
    
    interestRate /= 12;
    interestRateC = interestRate / 100;
    cout << "Monthly Payments: ";
    cin >> monthlyPaid;

    cout <<endl;

    //Test Case
    if (monthlyPaid <= loan * interestRateC) {
        cout << "Insufficient Payment.";
        exit(0);
    }

    if (monthlyPaid <= 0 || cin.fail()) {
        cout << "Invalid payment.";
        exit(0);
    }


    //Format output
    if (monthlyPaid >= loan) {
    cout << "*************************************************************************\n";
    cout << "\tAmortization Table\n";
    cout << "*************************************************************************\n";
    cout << "Month\tBalance\t\tPayment\t\tRate\tInterest\tPrincipal\n";
    cout << "0\t$" << loan << "\tNA\t\tN/A\tN/A\t\tN/A\n";
    }
    else {
    cout << "*****************************************************************\n";
    cout << "\tAmortization Table\n";
    cout << "*****************************************************************\n";
    cout << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";
    cout << "0\t$" << loan << "\tNA\tN/A\tN/A\t\tN/A\n";
    }

    //Loop to fill table
    while (loan > 0) {
        if (loan < monthlyPaid) {
            monthlyInterest = interestRateC * loan;
            principal = monthlyPaid - interestRateC;
            monthlyPaid = loan * (1 + interestRateC);
            principal = loan;
            totalPaid += monthlyInterest;
            loan = 0;
        }
        else {
            monthlyInterest = interestRateC * loan;
            principal = monthlyPaid - monthlyInterest;
            totalPaid += monthlyInterest;
            loan -= principal;
        }
        if (principal < 0) {
            cout <<"*****************************************************************\n";
            return 0;
        }
        if (loan <= 1000) {
        currentMonth++;
        cout << currentMonth << "\t$" << loan << "\t\t$" << monthlyPaid << "\t" << interestRate << "\t$" << monthlyInterest << "\t\t$" << principal << endl;
    }
        else if (loan <= monthlyPaid) {
            currentMonth++;
            cout << currentMonth << "\t$" << loan << "\t$" << monthlyPaid << "\t" << interestRate << "\t" << monthlyInterest << "\t$" << principal << endl;
        }
        else {
            currentMonth++;
            cout << currentMonth << "\t$" << loan << "\t$" << monthlyPaid << "\t" << interestRate << "\t$" << monthlyInterest << "\t\t$" << principal << endl; 
        }
    }
    if (currentMonth > 1) {
         cout <<"*****************************************************************\n";
         cout << "\nIt takes " << currentMonth << " months to pay off the loan.\n";
         cout << "Total interest paid is: $" << totalPaid << endl;
    }
    else { // If it takes one month to pay off it'll say "It takes one MONTH to pay off the loan."
        cout <<"*************************************************************************\n";
        cout << "\nIt takes " << currentMonth << " month to pay off the loan.\n";
        cout << "Total interest paid is: $" << totalPaid << endl;
    }

    return 0;
}