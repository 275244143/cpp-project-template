#include <cctype>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
using namespace std;

struct DFA {
    map<pair<int, char>, int> transitions;
    set<int> acceptingStates;
    int startState;
};

bool SimulateDFA(DFA& d, string input);
bool IsEmailAddress(string input);
DFA LoadEmailDFA();

string GetLine() {
    string line;
    getline(cin, line);
    return line;
}

int main() {
    cout << "Enter a string: ";
    string emailAddress = GetLine();
    if(IsEmailAddress(emailAddress)) {
        cout << emailAddress << " is an valid email address" << endl;
    }
    else {
        cout << emailAddress << " is not an valid email address" << endl;
    }
}

bool SimulateDFA(DFA& d, string input) {
    int currState = d.startState;
    bool mustHaveAt;
    set<int> acceptedStates;
    for(string::iterator itr = input.begin(); itr != input.end(); ++itr){
        currState = d.transitions[make_pair(currState, *itr)];
        cout << currState << endl;        
        acceptedStates.insert(currState);
    }
    mustHaveAt = (acceptedStates.find(3) != acceptedStates.end());
    return mustHaveAt && (d.acceptingStates.find(currState) != d.acceptingStates.end());
}

bool IsEmailAddress(string input) {
    DFA emailChecker = LoadEmailDFA(); // Implemented elsewhere
    /* Transform the string one character at a time. */
    for(string::iterator itr = input.begin(); itr != input.end(); ++itr) {
        /* isalnum is exported by <cctype> and checks if the input is an
* alphanumeric character.
*/
        if(isalnum(*itr))
            *itr = 'a';
        /* If we don't have alphanumeric data, we have to be a dot or at-sign
* or the input is invalid.
*/
        else if(*itr != '.' && *itr != '@')
            return false;
    }
    cout << input << endl;
    return SimulateDFA(emailChecker, input);
}

DFA LoadEmailDFA() {
    DFA emailDFA;
    emailDFA.startState = 0;
    
    emailDFA.transitions[make_pair(0, 'a')] = 1;
    emailDFA.transitions[make_pair(0, '@')] = 7;
    emailDFA.transitions[make_pair(0, '.')] = 7;

    emailDFA.transitions[make_pair(1, 'a')] = 1;
    emailDFA.transitions[make_pair(1, '@')] = 3;
    emailDFA.transitions[make_pair(1, '.')] = 2;
    
    emailDFA.transitions[make_pair(2, 'a')] = 1;
    emailDFA.transitions[make_pair(2, '@')] = 7;
    emailDFA.transitions[make_pair(2, '.')] = 7;

    emailDFA.transitions[make_pair(3, 'a')] = 4;
    emailDFA.transitions[make_pair(3, '@')] = 7;
    emailDFA.transitions[make_pair(3, '.')] = 7;

    emailDFA.transitions[make_pair(4, 'a')] = 4;
    emailDFA.transitions[make_pair(4, '@')] = 7;
    emailDFA.transitions[make_pair(4, '.')] = 5;

    emailDFA.transitions[make_pair(5, 'a')] = 6;
    emailDFA.transitions[make_pair(5, '@')] = 7;
    emailDFA.transitions[make_pair(5, '.')] = 7;    

    emailDFA.transitions[make_pair(6, 'a')] = 6;
    emailDFA.transitions[make_pair(6, '@')] = 7;
    emailDFA.transitions[make_pair(6, '.')] = 5;      

    emailDFA.transitions[make_pair(7, 'a')] = 7;
    emailDFA.transitions[make_pair(7, '@')] = 7;
    emailDFA.transitions[make_pair(7, '.')] = 7;      

    for(int i=0;i<=6;i++)
    {
        emailDFA.acceptingStates.insert(i);
    }

    return emailDFA;
}
