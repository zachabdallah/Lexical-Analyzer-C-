#include <iostream>
#include <sstream>
#include <iomanip> //this is an IO manipulator. It's for the setw() function below which sets the width by just adding a bunch of whitespace
#include <regex>
#include <map>
using namespace std;

int main() {
    string source_code = "int main()\n"
    "{\n"
    "    int x, y;\n"
    "    if (x < y)\n"
    "        printf(\"x is less than y\");\n"
    "    else\n"
    "        y=5; /* Assign value of 5 to y */\n"
    "    return 0;\n"
    "}";
    
    map<string, string> token_dictionary = {
        {"int", "Keyword"},
        {"x", "Identifier"},
        {"y", "Identifier"},
        {"main", "Identifier"},
        {"if", "Identifier"},
        {"else", "Identifier"},
        {"printf", "Identifier"},
        {"return", "Identifier"},
        {"is", "Value"},
        {"less", "Value"},
        {"than", "Value"},
        {"Assign", "Value"},
        {"value", "Value"},
        {"of", "Value"},
        {"5", "Value"},
        {"0", "Value"},
        {"to", "Value"},
        {"(", "LPAREN"},
        {")", "RPAREN"},
        {"{", "LBRACE"},
        {"}", "RBRACE"},
        {"<", "Operator"},
        {"=", "Operator"},
        {"\"", "Special_Symbol"},
        {"/", "Special_Symbol"},
        {",", "Special_Symbol"},
        {";", "Special_Symbol"},
        {"}", "Special_Symbol"},
        {"*", "Special_Symbol"}
    };
    
    istringstream source_stream(source_code); 
        //istringstream stands for input string stream. It is used for input operations on strings.
        //it allows you to treat a string as a "stream" and extract formatted data from it: you use it to read from strings.
        //just as a reminder, an input stream is a sequence of characters from which a program can read data sequentially. It is somewhat analogous to a queue
        //An input stream is connected to a data source like a file, a string, or console, and it reads data from this source as needed, storing it into its buffer. (It has a buffer, which btw is dynamically allocated by the stream, because having a buffer improves program performance by only  referencing the external data source when needed. In this way, it minimizes the amount of interactions it has with the source.
        //This buffer is not part of the stack, which means that buffer management is handled by the input stream. Input streams are typically compiler independent as well.
        //For future reference, output streams write to an external source as opposed to the input stream, which takes from it. It also uses a buffer. ex: cout sends data to the console, ofstream writes to a file, ostringstram constructs strings through formatted output.
        //A stream is a software abstraction that simplifies data handling. If you didn't have it, you would have to manange file pointers, handle buffer sizes, and performing manual formatting. C doesn't have a stream, but C++ does.
    string line;
    
    cout << "\nS. No.   Lexeme      Token       Line No.\n";
    int i = 1; // S. No. iterator
    int j = 0; // Line number iterator
    
    while (getline(source_stream, line)) {//getline(istream object, string to store the extracted line, [[optional]] delimiter)
            //getline() reads characters from the istream object and appends it to the string until the optional delimiter is encountered. It will extract and discard to delimiter from the input stream, and it is not added to the string. It will not continue extraction once the delimiter is encountered, which is why we use a loop because it continues where it left off.
        j++;
        istringstream word_stream(line);
        regex pattern("([[:alnum:]]+|[()\",;</*=])");
            //[[:alnum:]]+ is an character class that matches any alphanumerica character, and the '+' sign says it has to be one or more
            //"|" == or
            //[()\",;</*=] is the same as in the python code, where [xxxx] means anything in the brackets is allowed and is isolated into being it's own element
        
        for (sregex_iterator it(line.begin(), line.end(), pattern), end; it != end; ++it) {
            //sregex_iterator is an iterator provided by the C++ STL for iterating over matches of a regex in a string. "it" is of type sregex_iterator
            //"it" is initialized for the range [line.begin(), line.end()] using the regex pattern
            //", end" declares another sregex_iterator named end. It's used as the end condition for the loop.
            //as long as it != end, the loop will continue
            smatch match = *it; //smatch holds the results of a regex match. Its part of the regex library.
            string lexeme = match.str(); //str() extracts the string. This expression assigns it to "lexeme".
            string token = token_dictionary[lexeme]; //now we reference the token by using the map
            cout << i << ".       " << left << setw(11) << lexeme << setw(15) << token << "   " << j << "\n";
            i++;
        }
    }
    
    return 0;
}
