#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
using namespace std;
/* Function: OpenUserFile(ifstream& fileStream);
* Usage: OpenUserFile(myStream);
* -------------------------------------------------
* Prompts the user for a filename until a valid filename
* is entered, then sets fileStream to read from that file.
*/
void OpenUserFile(ifstream& fileStream);
/* Function: GetFileContents(ifstream& file);
* Usage: string contents = GetFileContents(ifstream& file);
* -------------------------------------------------
* Returns a string containing the contents of the file passed
* in as a parameter.
*/
string GetFileContents(ifstream& file);
/* Function: GenerateKeywordReport(string text);
* Usage: map<string, size_t> keywords = GenerateKeywordReport(contents);
* -------------------------------------------------
* Returns a map from keywords to the frequency at which those keywords
* appear in the input text string. Keywords not contained in the text will
* not appear in the map.
*/
map<string, size_t> GenerateKeywordReport(string contents);

void PreprocessString(string& text);

string GetLine() {
    string line;
    getline(cin, line);
    return line;
}

int main() {
    /* Prompt the user for a valid file and open it as a stream. */
    ifstream input;
    OpenUserFile(input);
    /* Generate the report based on the contents of the file. */
    map<string, size_t> report = GenerateKeywordReport(GetFileContents(input));
    /* Print a summary. */
    for (map<string, size_t>::iterator itr = report.begin(); itr != report.end(); ++itr)
        cout << "Keyword " << itr->first << " occurred " << itr->second << " times." << endl;
}

void OpenUserFile(ifstream& input){
    while(true) {
        cout << "Enter filename: ";
        string filename = GetLine();
        input.open(filename.c_str()); // See Chapter 3 for .c_str().
        if(input.is_open()) return;
        cout << "Sorry, I can't find the file " << filename << endl;
        input.clear();
    }
}

string GetFileContents(ifstream& input) {
    /* String which will hold the file contents. */
    string result;
    /* Keep reading a line of the file until no data remains. */
    string line;
    while (getline(input, line))
        result += line + "\n"; // Add the newline character; getline removes it
    return result;
}

set<string> LoadKeywords() {
    ifstream input("keywords.txt"); // No error checking for brevity's sake
    set<string> result;
    /* Keep reading strings out of the file until we cannot read any more.
* After reading each string, store it in the result set. We can either
* use getline or the stream extraction operator here, but the stream
* extraction operator is a bit more general.
*/
    string keyword;
    while (input >> keyword)
        result.insert(keyword);
    return result;
}

void PreprocessString(string& text) {
    for (size_t k = 0; k < text.size(); ++k)
        if (ispunct(text[k]) && text[k] != '_'){ // If we need to change it...
            text[k] = ' '; // ... replace it with a space.
        }
}

map<string, size_t> GenerateKeywordReport(string fileContents) {
    /* Load the set of keywords from disk. */
    set<string> keywords = LoadKeywords();
    /* Preprocess the string to allow for easier parsing. */
    PreprocessString(fileContents);
    /* Populate a stringstream with the file contents. */
    stringstream tokenizer;
    tokenizer << fileContents;
    /* Loop over the words in the file, building up the report. */
    map<string, size_t> result;
    string word;
    while (tokenizer >> word){
        if (keywords.count(word))
            ++ result[word];
    }
    return result;
}
