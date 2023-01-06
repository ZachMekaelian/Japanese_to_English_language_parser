#include<iostream>
#include<string>
using namespace std;
//-------------------------------------------------------
// CS421 HW1 
// Write a recognizer in C++ for L = {x | x is any coombination of a's and b's}.
// Your name: Zachary Mekaelian
//-------------------------------------------------------
//  The recognizer function should return TRUE or FALSE 
//  checking each character
//  to make sure it is a or b.
bool recognizer(string s) {// function with a parameter that takes in a string
	{
		bool isAB = true;//boolean value set to true
		for (int i = 0; i < s.size(); i++)//go through the whole passed perameter s
		{
			if (s[i] == 'a' || s[i] == 'b')//if the value is a or b continue with true value
			{
				continue;
			}
			else
			{
				isAB = false;//or else set isAB to false and break out of the loop
				break;
			}
		}
		return isAB; //return the value
	}
}
//main: Given a string (from E) cined from the user, pass it to
//      the recognizer function.
//      Cout "YES IN L" or "NO NOT IN L" depending on what was returned.
int main() {
	// feel free to put it in a loop 
	while (1) { //infinite loop whie true
		string E; //declare string variable E
		cout << "Enter a's or b's: (or 'end' to end the program)";
		cin >> E; //user inputs into value e, hopefully a's or b's
		if (recognizer(E)) // if true, print "YES IN L" or else print "NO NOT IN L"
		{
			cout << "YES IN L" << endl;
		}
		else
		{
			cout << "NO NOT IN L" << endl;
		}
		if (E == "end") {// if the user types "end" then end the program
			return 0;
		}
	}
}