#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

//--------------------------------------
// CS421 File td.cpp for HW2B Table-Driven Scanner
// Your name: Zach Mekaelian
//--------------------------------------

// Complete this to fit the HW2B specification - look for **
// Must have the same types of tracing couts as my demo program.


// info on each DFA
struct info
{
    string name;  // token name
    int startstate;
    int finalstate;
};

info DFAs[4];     // store up to 4 dfas' start and final

int  TRS[10][4];  // store all trs's - states 0-9 and chars a b c d -- all dfas transitions are in here 

// ----- utility functions -----------------------

int readTables() { 
    int dfaCounter = 0, i = 0, a = 0; 
    ifstream fin("trs.txt", ios::in); 
    ifstream fin2("dfas.txt", ios::in);
    while (fin2 >> DFAs[dfaCounter].name) { 
        fin2 >> DFAs[dfaCounter].startstate >> DFAs[dfaCounter].finalstate; 
        dfaCounter++;
    }
    while (true) {
        fin >> TRS[i][a];
        a++;
        if (a == 4) { 
            a = 0; 
            i++; 
        }
        if (i == 10)
            break;
    }
    return dfaCounter; 
}

void displayTables(int numDFAs)
{
    // ** display DFAs nicely labeled
    // ** display TRS nicely labeled
    cout << "a b c d" << endl; 
    for (int i = 0; i < 10; i++) {
        cout << "State " << i << ":";
        for (int a = 0; a < 4; a++) {
            if (TRS[i][a] != -1)
                cout << TRS[i][a] << ' ' ;
                
        }
        cout << endl;
    }
    for (int i = 0; i < numDFAs; i++)
        cout << DFAs[i].name << ": " << DFAs[i].startstate << " is start and ends in " << DFAs[i].finalstate << endl;
}


bool accept(info dfa, string word)
{
    // ** Does the dfa accept the word?
    // Start with the start state of the DFA and
    // look up the next state in TRS for each char in word.
    // At the end of the word, make sure you are in the 
    // final state of the DFA.
    // Use a formula to convert chars to TRS col numbers.
    int state = dfa.startstate, c = 0; 

    while (state < dfa.finalstate and state >= dfa.startstate) {
        cout << "state: ";
        cout << state << " ";
        char letter = word[c];
        cout << "char: ";
        cout << letter << " " << endl;
        int numWord = int(letter) - 97;      
        state = TRS[state][numWord];
        cout << "new state: "; 
        cout << state << " " << endl;
        c++; 
    }
    if (c == word.length() and state == dfa.finalstate)
        return true; 
    else 
        return false;
}


int main()
{
    cout << "This is a table driven scanner. Needs trs.txt and dfas.txt." << endl;
    cout << "States are 0 to 9 and chars are a to d" << endl;

    int numDFA = readTables(); // how many DFAs were read
    displayTables(numDFA);     // DISPLAY TABLES
    cout << ".....done reading tables...." << endl;

    string word;
    while (true)
    {
        cout << "@@Enter a string: ";
        cin >> word;
        // ** try the DFAs one by one and see 
        //      if the word is accepted
        //      if so, display the word and the token name
        // ** if no DFA does, generate a lexical error message.
        cout << endl << "----Trying DFA 0----" << endl;

        if (accept(DFAs[0], word))
            cout << endl << "Found token " << DFAs[0].name << endl; 
        else 
        { 
            cout << "----Trying DFA 1----" << endl; 
        
            if (accept(DFAs[1], word))
            cout << "Found token " << DFAs[1].name << endl;
        
            else 
            cout << "Lexical Error!" << endl; 
        }
        cout << "do control-C to quit" << endl;
    }
}//the end
