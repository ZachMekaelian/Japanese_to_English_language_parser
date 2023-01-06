#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 6 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Zach Mekaelian, Sonia Cheng, Christian Contreras
// RE:   (vowel | vowel n | consonant vowel | consonant vowel n |consonant-pair vowel | consonant-pair vowel n)^+

bool word(string s)
{

    int state = 0;
    int charpos = 0;
    /*char vowles[7] = {'a', 'e', 'i', 'o', 'u', 'I', 'E'};
    char consonant1[15] = { 'd', 'j', 'w', 'y', 'z'};
    char consonant2[15] = {'b', 'g', 'h', 'k', 'm', 'n', 'p', 'r', 's', 't'};
    string consonant_pair[11] = {"by", "gy", "hy", "ky",
    "my", "ny", "py", "ry", "ch", "sh", "ts"};*/

    //q0 = 0, q0q1 = 1, q0qy = 2, qc = 3, qt = 4, qy = 5, 
    //qsa = 6, qs = 7
      /* replace the following todo the word dfa  ** */
    while (s[charpos] != '\0')
    {
        if (state == 0) { //q0
            switch (s[charpos]) {
            case 'a': case 'e':case 'i':case 'o':case 'u':case 'I':case 'E':
                state = 1; break; //q0q1
            case 'd':case 'j':case 'w':case 'y':case 'z':
                state = 6; break;//qsa
            case 'b':case 'g':case 'h':case 'k':case 'm':case 'n':case 'p':case 'r': //**
                state = 5; break; //qy                            
            case 't': state = 4; break; //qt
            case 'c': state = 3; break; //qc
            case 's': state = 7; break; //qs
            default:
                return false;
            }
        }

        else if (state == 1) { //q0q1
            switch (s[charpos]) {
            case 'n': state = 2; break; //q0qy
            case 't': state = 4; break; //qt
            case 'a':case 'e':case 'i':case 'o':case 'u':case 'I':case 'E':
                state = 1; break;//q0q1
            case 'd':case 'w':case 'z':case 'y':case 'j':
                state = 6; break;//qsa
            case 'c': state = 3; break; //qc
            case 's': state = 7; break; //qs
            case 'b':case 'g':case 'h':case 'k':case 'm':case 'p':case 'r':
                state = 5; break; //qy
            default:
                return false;
            }
        }

        else if (state == 2) { //q0qy
            switch (s[charpos]) {
            case 'a': case 'e':case 'i':case 'o':case 'u':case 'I':case 'E':
                state = 1; break; //q0q1
            case 'd':case 'j':case 'w':case 'y':case 'z':
                state = 6; break; //qsa
            case 'b':case 'g':case 'k':case 'm':case 'p':case 'r':
                state = 5; break; //qy
            case 't': state = 4; break; //qt
            case 'c': state = 3; break; //qc
            case 's': state = 7; break; //qs
            case 'n': state = 5; break; //qy  
            case 'h': state = 5; break; //qy
            default:
                return false;
            }
        }

        else if (state == 3) { //qc
            switch (s[charpos]) {
            case 'h': state = 6; break;//qsa
            default:
                return false;
            }
        }

        else if (state == 4) { //qt
            switch (s[charpos]) {
            case 's': state = 6; break; //qsa
            case 'a': case 'e':case 'i':case 'o':case 'u':case 'I':case 'E':
                state = 1; break; //q0q1
            default:
                return false;
            }
        }

        else if (state == 5) { //qy
            switch (s[charpos]) {
            case 'y': state = 6; break; //qsa
            case 'a': case 'e':case 'i':case 'o':case 'u':case 'I':case 'E':
                state = 1; break; //q0q1
            default:
                return false;
            }
        }

        else if (state == 6) { //qsa
            switch (s[charpos]) {
            case 'a': case 'e':case 'i':case 'o':case 'u':case 'I':case 'E':
                state = 1; break; //q0q1
            default:
                return false;
            }
        }

        else if (state == 7) { //qs
            switch (s[charpos]) {
            case 'h': state = 6; break; //qsa
            case 'a': case 'e':case 'i':case 'o':case 'u':case 'I':case 'E':
                state = 1; break; //q0q1
            default:
                return false;
            }
        }
        else {
            cout << "STUCK HERE" << endl;
            return false;
        }
        charpos++;
    }

    /* if (state == 0 && s[charpos] == vowles[6])
     state = 1;
     else
     if (state == 0 && s[charpos] == 'c')
     state = 3;
     else
     if (state == 0 && s[charpos] == 't')
     state = 4;
     else
     if (state == 1 && s[charpos] == 'n')
     state = 2;
     return(false);
     charpos++;
   }//end of while
*/
// where did I end up????
    if (state == 0 || state == 1 || state == 2) return(true);  // end in a final state
    else return(false);
}
// PERIOD DFA 
// Done by: Zach, Christian, Sonia
bool period(string s)
{  // complete this **
    if (s == ".") return true;
    else return false;
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Christian, Sonia, Zach

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype { WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, ERROR, EOFM };

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[16] = { "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "ERROR", "EOFM" };

// ** Need the reservedwords table to be set up here. 
string reservedWords[38] = { "masu", "VERB", "masen", "VERBNEG", "mashita", "VERBPAST",
"masendeshita", "VERBPASTNEG", "desu", "IS", "deshita", "WAS",
"o", "OBJECT", "wa", "SUBJECT", "ni", "DESTINATION",
"watashi", "PRONOUN", "anata", "PRONOUN", "kare", "PRONOUN",
"kanojo", "PRONOUN", "sore", "PRONOUN", "mata", "CONNECTOR",
"soshite", "CONNECTOR", "shikashi", "CONNECTOR",
"dakara", "CONNECTOR", "eofm", "EOFM" };
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.




// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Christian, Sonia, Zach
int scanner(tokentype& tt, string& w)
{
    cout << endl;
    cout << "...Scanner was called..." << endl;

    // ** Grab the next word from the file via fin
    fin >> w;
    // 1. If it is eofm, return right now.   
    if (w == "eofm") return -1;
    /*
        2. Call the token functions (word and period)
           one after another (if-then-else).
           Generate a lexical error message if both DFAs failed.
           Let the tokentype be ERROR in that case.

        3. If it was a word,
           check against the reservedwords list.
           If not reserved, tokentype is WORD1 or WORD2
           decided based on the last character.
    */
    if (word(w))
    {
        if (w.length() - 1 == 'I' || w.length() - 1 == 'E')//check last character in word w
            tt = WORD2;
        else
            tt = WORD1;

        for (int i = 0; i < 38; i++) // Checking through the reserved words list
        {
            if (reservedWords[i] == w)
            {
                for (int j = 0; j <= 16; j++)
                {
                    if (tokenName[j] == reservedWords[i + 1])
                    {
                        tt = static_cast<tokentype>(j); //Static cast to enum tokentype from string
                        break;
                    }
                }
            }
        }
    }
    else if (period(w))
    {
        tt = PERIOD;
    }
    else
    {
        tt = ERROR;
        cout << "Lexical Error: " << w << " is not a valid token" << endl;

    }
    return 1;
    //    4. Return the token type & string  (pass by reference)
}//the end of scanner



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Louis
int main()
{
    tokentype thetype;
    string theword;
    string filename;

    cout << "Enter the input file name: ";
    cin >> filename;

    fin.open(filename.c_str());

    // the loop continues until eofm is returned.
    while (true)
    {
        scanner(thetype, theword);  // call the scanner which sets the arguments  
        if (theword == "eofm") break;  // stop now

        cout << "Type is:" << tokenName[thetype] << endl;
        cout << "Word is:" << theword << endl;
    }
    cout << "End of file is encountered." << endl;
    fin.close();

}// end

