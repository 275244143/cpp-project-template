#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
void LinesFromFile();

int main() {
    LinesFromFile();
    return 0;
}


string GetLine() {
    string result;
    //cout << "Please, enter a real number: ";
    getline(cin, result);

    return result;
}

void LinesFromFile() {
    while(true) {
        ifstream input;
        cout << "Enter filename: ";
        string filename = GetLine();
        input.open(filename.c_str());
        if(input.is_open()) {
            vector<string> fileContent;
            string tmp;
            while(getline(input, tmp)) {
                fileContent.push_back(tmp);
            }
            for(int i=0; i < fileContent.size(); i++)
                cout<<fileContent[i]<<" " << endl;
            return;
        }
        cout << "Sorry, I can't find the file " << filename << endl;
        input.clear();
    }
}
