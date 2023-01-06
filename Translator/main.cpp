#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <cstdlib>

using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/
void s();
void noun();
void verb();
void tense();
void be();
void afterSubject();
void afterNoun();
void afterObject();
ofstream translate;
//=================================================
// File parser.cpp written by Group Number: 6
//=================================================

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 6 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Zach Mekaelian, Sonia Cheng, Christian Contreras
// RE:   (vowel | vowel n | consonant vowel | consonant vowel n |consonant-pair vowel | consonant-pair vowel n)^+

bool word(string s) {
    int state = 0;
    int charpos = 0;
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
int scanner(tokentype& tt, string& w) {
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
        if (w[w.length() - 1] == 'I' || w[w.length() - 1] == 'E')//check last character in word w
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
  fin.close();
}//the end of scanner

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// Type of error: syntax error
// Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian  
void syntaxerror1(tokentype expected, string saved_lexeme){    
   cout << "Syntax error: expected " << tokenName[expected] << " but found " << saved_lexeme << endl;
   exit(1);
}
// Type of error: lexical error
// Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian 
void syntaxerror2(string saved_lexeme, string parserFunction) {
   cout << "Syntax error: Unexpected " << saved_lexeme << " found in " << parserFunction << endl;
   exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

tokentype saved_token;
string saved_lexeme;
bool token_available = false;

// Purpose: token updates and is returned from the scanner functions
// Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian 
tokentype next_token() {
   if (!token_available) { 
      scanner(saved_token, saved_lexeme); 
      cout << "Scanner called using word: " << saved_lexeme <<endl;
      token_available = true; 
      }
      return saved_token; 
   }


// Purpose: update match type when successful
// Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian 
bool match(tokentype expected) {
if (next_token() != expected) {
	  syntaxerror1(expected, saved_lexeme);
        return false;
	} else {
		cout << "Matched " << tokenName[expected] << endl;
		token_available = false;
		return true;
	}
}

// ----- RDP functions - one per non-term -------------------
void getEword();
void gen(string);
// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <story> ::= <s>^*
// Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian 
void story() {
  cout << "Processing <Story>" << endl << endl;
  s();
  while (saved_lexeme !="eofm") {
        switch (next_token()) {
        case CONNECTOR:
        case WORD1: 
        case PRONOUN: s();
            break;
        default:
            break;  
        }
    }
    cout << endl;
    cout << "Successfully parsed <story>." << endl;
}

// Grammar: <s> ::= [CONNECTOR #getEword#  #gen(CONNECTOR)#] <noun> #getEword#  SUBJECT #gen(ACTOR)# <after subject>
// Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian 
void s() {
    cout << "Processing <S>" << endl;
    next_token();
    if(saved_lexeme != "eofm") {
        if(next_token() == CONNECTOR) {
          match(CONNECTOR);
          getEword();
          gen("CONNECTOR");
        }
      noun(); 
      getEword();
      match(SUBJECT); 
      gen("ACTOR");
      afterSubject();
    }
}

//Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian 
void noun() {
    cout << "Processing <noun>" << endl;
    switch(next_token()) {
        case WORD1: match(WORD1);
            break;
        case PRONOUN: match(PRONOUN);
            break;
        default:
            syntaxerror2(saved_lexeme, "noun");
    }
}

//Grammar: <verb> ::= WORD2
// Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian 
void verb() {
   cout << "Processing <verb>" << endl;
		switch (next_token()) {
			case WORD2:
				match(WORD2);
				break;
			default:
				syntaxerror2(saved_lexeme, "verb");
		}
}

//Grammar: <tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
// Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian 
void tense() {
   cout << "Processing <tense>" << endl;
	 switch(next_token()) {
     case VERBPAST: match(VERBPAST);
       break;
     case VERBPASTNEG: match(VERBPASTNEG);
       break;
     case VERB: match(VERB);
       break;
     case VERBNEG: match(VERBNEG);
       break;
     default:
       syntaxerror2(saved_lexeme, "tense");
   }
}

//Grammar <be> ::= IS | WAS
//Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian 
void be() {
	cout << "Processing <be> " << endl; 
	switch (next_token()){
	case IS:
		match(IS);
		break;
	case WAS:
		match(WAS);
		break;
	default: 
		syntaxerror2(tokenName[saved_token], "be");
	}
}

// Grammar: <after subject> ::= <verb> #getEword#  #gen(ACTION)# <tense> #gen(TENSE)# PERIOD | <noun> #getEword# <after noun>
// Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian 
void afterSubject() {
    cout << "Processing <afterSubject>" << endl;
    switch (next_token()) {
        //case VERB:
        case WORD2:
          verb(); 
          getEword();
          gen("ACTION");
          tense(); 
          gen("TENSE");
          match(PERIOD);
		break;
        case WORD1:
        case PRONOUN:
          noun(); 
          getEword();
          afterNoun();
            break;
        default:
            syntaxerror2(tokenName[saved_token], "afterSubject");
    }
}

// Grammar: <after noun> ::= <be> #gen(DESCRIPTION)# #gen(TENSE)# PERIOD |DESTINATION  #gen(TO)# <verb> #getEword#  #gen(ACTION)# <tense> #gen(TENSE)#  PERIOD |
// OBJECT #gen(OBJECT)# <after object>
// Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian 
void afterNoun() {
	cout << "Processing <afterNoun>" << endl;   
	switch (next_token()) {
	  case IS:
	  case WAS:
	    be();
      gen("DESCRIPTION");
      gen("TENSE");
      match(PERIOD);
	    break;
	  case DESTINATION:
	    match(DESTINATION);
      gen("TO");
	    verb(); 
      getEword();
      gen("ACTION");
      tense(); 
      gen("TENSE");
      match(PERIOD);
	    break;    
	  case OBJECT:
	    match(OBJECT);
      gen("OBJECT");
	    afterObject();
	    break;
	  default:
	    syntaxerror2(tokenName[saved_token], "<afterNoun>");
	  }
}

// Grammar: <after object> ::= <verb> #getEword#  #gen(ACTION)# <tense> #gen(TENSE)# PERIOD |<noun> #getEword# DESTINATION #gen(TO)# <verb> #getEword#  #gen(ACTION)# 
// <tense> #gen(TENSE)# PERIOD
// Done by: Sonia Cheng, Christian Contreras, Zach Mekaelian 
void afterObject() {
  cout << "Processing <afterObject>" << endl;
  switch(next_token()) {
    case WORD1:
      noun(); 
      getEword();
      match(DESTINATION);
      gen("TO");
      verb(); 
      getEword();
      gen("ACTION");
      tense(); 
      gen("TENSE");
      match(PERIOD);
      break;
    case WORD2:
      verb(); 
      getEword();
      gen("ACTION");
      tense(); 
      gen("TENSE");
      match(PERIOD);
      break;
    case PRONOUN:
      noun(); 
      getEword();
      match(DESTINATION);
      gen("TO");
      verb(); 
      getEword();
      gen("ACTION");
      tense(); 
      gen("TENSE");
      match(PERIOD);
      break;
    default:
      syntaxerror2(saved_lexeme, "<after object>");
    }
}
string filename;

//=================================================
// File translator.cpp written by Group Number: *6*
//=================================================

// ----- Additions to the parser.cpp ---------------------
// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt

class Lexicon {
  public: 
    string fname;
    vector <string> content;
}; 
Lexicon dictionary;
string lexWord;
string saved_E_word;

void readLexicon(ifstream& lexFile)
{
  while(lexFile >> lexWord)
  {
    dictionary.content.push_back(lexWord);
    }
}


// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: Sonia Cheng 


// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: Zach Mekaelian  
void getEword(){
for(int i = 0 ; i < dictionary.content.size(); i++)
  {
    if(saved_lexeme == dictionary.content[i])
      saved_E_word = dictionary.content[i+1];
    else if (saved_lexeme == "rika")
      saved_E_word = saved_lexeme;
    
  }
}

//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: Christian Contreras

void gen(string line_type){
  
  if(line_type == "TENSE"){
    translate << line_type << ":" << tokenName[saved_token] << endl;
  }
  else{
    translate << line_type << ":" << saved_E_word << endl;
  }
  
}

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.


// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  Sonia Cheng, Christian Contreras, Zach Mekaelian 
int main()
{
  //** opens the lexicon.txt file and reads it into Lexicon
  ifstream lexFile("lexicon.txt");
  readLexicon(lexFile);
  //** closes lexicon.txt 
  lexFile.close();

  //** opens the output file translated.txt
  translate.open("translated.txt");

  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  cout<<endl;
  //** closes the input file 
  fin.close();
  
  //** closes traslated.txt
  translate.close();
 
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

