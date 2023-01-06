#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<stack>
#include<string>

using namespace std;

//---------------------------------------
// CS421 File ll1.cpp for HW3A LL1 Table-Driven Parser
// Your name: Zachary Mekaelian
//---------------------------------------

// Complete this to fit the HW3A specification - look for **
// Must have the same types of tracing couts as my demo program.

// Feel free to use a stack class or use a vector
// to implement your stack.  The stack will contain characters.
stack<char> stackC;
vector<char> M[3][2];  // the table of rules 
                       // 3 rows for S, A, B
                       // 2 rows for 2, 3
        // Each slot contains a rule's right side
        // which is a vector of characters

//  ------- conversion functions ------------------------


// to convert non-terms S, A, B to table rows 0, 1, 2
int toRow(char C) // rules for the language 
{
    //**  bunch of if then else
    if (C == 'S') 
    {
        return 0;
    }
    else if (C == 'A') 
    {
        return 1;
    }
    else if (C == 'B') 
    {
        return 2;
    }
    else {
        cout << "Invalid row." << endl;     //print error message for all other input
        exit(1);
    }
}

// to convert '2' and '3' to table columns 0 and 1 
int toCol(char c) 
{
    // ** bunch of if then else
    //
    // when c is 2 return a 0
    // when c is 3 return a 1
    if (c == '2') 
    {
        return 0;
    }
    else if (c == '3') 
    {
        return 1;
    }
    else {
        cout << "Invalid column." << endl;    //print error message for all other input
        return -1;
    }
}

// to convert row 0, 1, 2 to non-terms S, A and B
char toNonterm(int r) 
{
    // ** bunch of if then else
    if (r == 0) 
    {
        return 'S';
    }
    else if (r == 1) 
    {
        return 'A';
    }
    else if (r == 2)
    {
        return 'B';
    }
    else {
        cout << "Invalid row." << endl;       //print error message for all other input
        return -1;
    }
    }

// ** Then complete the following functions.-----------------------------

// to display a rule's rhs which is in vector V
void displayVector(vector<char> V)
{
    // ** display V horizontally e.g. 2 A 2
    cout << "\t";
    for (int i = 0; i < V.size(); i++) {
        cout << V[i] << " ";
    }
}

// to read in the rules into M, make sure ; is not stored
void readrules() {
    ifstream fin("rules", ios::in);
    char rule;
    int row;
    int col;
    while (fin >> rule) {
        int row = toRow(rule);
        fin >> rule; // get input to access S
        int col = toCol(rule); // convert character into index position

        // if the conversion algorithm returns a character that is not recognized
        if (row == -1 || col == -1) {
            cout << "Unknown character encountered" << endl;
            continue;
        }
        M[row][col].push_back(rule);
        while (fin >> rule) {
            if (rule == ';') {
                break; // break out the loop to process next line
            }
            M[row][col].push_back(rule); // push the character into the vector
        }
    }

    // display the table
    for (int i = 0; i < 3; i++) {
        cout << toNonterm(i) << "| ";
        for (int j = 0; j < 2; j++) {
            displayVector(M[i][j]);
        }
        cout << endl;
    }
}

//  pushes V contents to the stack 
void addtostack(vector<char> V)
{
    cout << "Pushing rhs of a rule to the stack." << endl;
    // **  be careful of the order
     // because 3 2 2 means 3 will be at the top of the stack
    for (int i = 0; i < V.size(); i++) {
        stackC.push(V[i]);
    }
}


void displayStack() {
    stack<char> stackCopy(stackC);
    while (!stackCopy.empty()) {
        cout << stackCopy.top() << endl;
        stackCopy.pop();
    }
    cout << "-------------------------" << endl;
}

void emptyStack() //message for when the stack is empty
{
    cout << "Stack" << endl <<
        "[ Empty ]" << endl <<
        "--------------------------" << endl;
}

bool isTerm(char c) //check to see if the character is a term
{
    return toCol(c) != -1;
}

int main() //main driver function
{
    char next;
    readrules();  // M is filled and displayed 

    string ss;
    cout << "Enter a string made of 2's and/or 3's: ";
    cin >> ss;

    // ** push 'S' onto the stack to start
    stackC.push('S');

    cout << "Stack:";
    // ** display the stack vertically from top to bottom
    displayStack();

    int i = 0;  // index for ss
    while (ss[i] != '\0')  // for each char of ss
    {
        // Based on ss[i] and 
        //    the top of stack, update the stack: 
        // ** note that empty stack will cause immediate failure  
        // ** note that top of stack terminal and ss[i] mismatching
        //    will cause immediate failure 
        // ** note that no entry in M for the top of stack (non-terminal)
        //    and ss[i] will cause immediate
        //    failure  (use toRow and toCol to look up M)
        // ** otherwise, addtoStack the M entry based on ss[i] and the top of stack 

        if (stackC.empty()) {
            emptyStack();
            cout << "current char is: " << ss[i] << endl;
            return(1);
        }
        else {
            displayStack();
        }

        next = stackC.top();
        stackC.pop();
        cout << "current char is:" << ss[i] << endl;

        if (toCol(ss[i]) == -1) {
            cout << "Invalid!" << endl;
            return 1;
        }

        if (toCol(next) == -1) {
            addtostack(M[toRow(next)][toCol(ss[i])]);
            continue;
        }

        else if (ss[i] == next) {
            cout << "match!" << endl;
        }
        else {
            cout << "mismatch" << endl;
            return 1;
        }
        cout << endl;
        i++;

    } // end of string


  // ** Here, check for success for failure based on stack empty or not
    if (stackC.empty()) {
        emptyStack();
        cout << "Great work!" << endl;
        return 0;
    }
    else {
        displayStack();
        cout << "Stack not empty" << endl;
        return 1;
    }
}// end of main