#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stack>
#include <sstream>

using namespace std;

class TableDriven
{
    public:
    int statetable[31][31] = 
    {
        {0, 1, 2, 3, 1, 5, 1, 7, 1, 9, 1, 11, 1, 1, 14, 1, 1, 17, 1, 1, 20, 21, 22, 23, 24, 1, 1, 27, 28, 29, 30}, /* whitespace state(b)*/
        {1, 1, 1, 1, 1,	1, 1, 1, 1,	1, 1, 1, 1,	1, 1, 1, 1,	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	1, 1}, /* error state*/
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 ,2 ,2 ,2}, /* <mop> state*/
        {4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, /* digit state */
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, /* integer state */
        {6, 6, 6, 5, 6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}, /* letter state */
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}, /* variable state */
        {10, 10, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, /* "/" (slash) state*/
        {8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8}, /* start of comment state */
        {8, 8, 8, 8, 8, 8, 8, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8}, /* end comment state*/
        {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, /* any "/" */
        {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 12, 13, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12}, /* "=" state */
        {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12}, /* any "=" state "*/
        {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13},  /* == state */
        {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15},  /* < state */
        {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15},  /* any < state */
        {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16},  /* <= state */
        {18, 18 ,18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18},  /* > state */
        {18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18},  /* any > state */
        {19, 19 ,19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19},  /* >= state */
        {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20}, /* "," state */
        {21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21}, /* semicolon state */
        {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22}, /* add state */
        {23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23}, /* "-" state */
        {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 26, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24}, /* ! state */
        {25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25}, /* any ! state */
        {26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26}, /* != state */
        {27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27}, /* leftparen state */
        {28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28}, /* rightparen state */
        {29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29}, /* leftbracket state */
        {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30} /* rightbracket state */
    };
    int nextState(int currentState, char columnInput)
    {
        return statetable[currentState][columnInput];
    }
};

class FSA2
{
    public:
    int symboltable[13][13] = 
    {
       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //  STATE 0
       {1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //  STATE 1
       {2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, //  STATE 2
       {3, 3, 3, 4, 10, 3, 3, 3, 10, 3, 8, 3, 3}, // STATE 3
       {4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 4, 4, 4}, //  STATE 4
       {5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5}, //  STATE 5 
       {6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6}, //  STATE 6
       {7, 7, 7, 7, 7, 7, 7, 4, 7, 3, 7, 7, 7}, //  STATE 7
       {8, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8}, //  STATE 8
       {9, 9, 9, 9, 9, 9, 9, 8, 9, 3, 9, 9, 9}, //  STATE 9 
       {10, 10, 10, 4, 10, 10, 11, 10, 3, 3, 8, 12, 10}, // STATE 10
       {11, 11, 11, 11, 11, 11, 11, 11, 3, 3, 11, 3, 10}, //STATE 11
       {12, 12, 3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12}

    };
    int nextSymbolState(int currentSymbolState, char columnSymbolInput)
    {
        return symboltable[currentSymbolState][columnSymbolInput];
    }
}; 

class PDA
{
    public:
    string OP[21][21] ={
    //     $    =    +    -    (    )    *    /    ;  ==  !=    >    <    >=    <=  IF THEN  WHILE  DO   {}    }
        // $
        {"0", "<", "<", "<", "<", "0", "<", "<", "0", "<", "<", "<", "<", "<", "<", "<", "0", "<", "0", "<", "0"},
        // =
        {">", "<", "<", "<", "<", "0", "<", "<", ">", "<", "<", "<", "<", "<", "<", "0", "0", "0", "0", "<", "0"},
        // +
        {">", "0", ">", ">", "<", ">", "<", "<", ">", ">", ">", ">", ">", ">", ">", "0", ">", "0", "0", "0", "0"},
        // -
        {">", "0", ">", ">", "<", ">", "<", "<", ">", ">", ">", ">", ">", ">", ">", "0", ">", "0", "0", "0", "0"},
        // (
        {"0", "0", "<", "<", "<", "=", "<", "<", "0", "<", "<", "<", "<", "<", "<", "0", "0", "0", "0", "0", "0"},
        // )
        {">", "0", ">", ">", "0", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">", "0", "0", "0", "0", "0", "0"},
        // *
        {">", "0", ">", ">", "<", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">", "0", ">", "0", "0", "0", "0"},
        // /
        {">", "0", ">", ">", "<", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">", "0", ">", "0", "0", "0", "0"},
        // ;
        {"0", "<", "<", "<", "<", "0", "<", "<", "0", "<", "<", "<", "<", "<", "<", "<", "0", "<", "0", "0", ">"}, 
        // ==
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0"},
        // !=
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0"},
        // >
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0"},
        // <
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0"},
        // >=
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0"},
        // <=
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0"},
        // IF
        {"<", "0", "<", "<", "<", "0", "<", "<", "<", "<", "<", "<", "<", "<", "<", "0", "=", "0", "0", "<", "0"},
        // THEN
        {">", "<", "0", "0", "0", "0", "0", "0", ">", "0", "0", "0", "0", "0", "0", "<", "0", "<", "0", "<", ">"},
        // WHILE
        {"<", "0", "<", "<", "<", "0", "<", "<", "<", "<", "<", "<", "<", "<", "<", "0", "0", "0", "=", "<", "0"},
        // DO
        {">", "<", "0", "0", "0", "0", "0", "0", ">", "0", "0", "0", "0", "0", "0", "<", "0", "<", "0", "<", ">"},
        // {
        {"0", "<", "<", "<", "<", "0", "<", "<", "=", "0", "0", "0", "0", "0", "0", "<", "<", "<", "<", "<", "="},
        // }
        {"0", "0", "0", "0", "0", "0", "0", "0", ">", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", ">"}
    };
    string PDAprecedence(int lastOperator, int pdacolumnInput) {
    // Debugging output to see the inputs
    cout << "lastOperator: " << lastOperator << ", pdacolumnInput: " << pdacolumnInput << endl;

    // Boundary check
    if (lastOperator < 0 || lastOperator >= 21 || pdacolumnInput < 0 || pdacolumnInput >= 21) {
        cerr << "Error: Operator index out of bounds!" << endl;
        return "Error"; // Return an error or handle the situation appropriately
    }

    return OP[lastOperator][pdacolumnInput];
}
};

int tokenSymbolT(string symbol) {
    if (symbol == "class") {
        return 0;
    } else if (symbol == "pgmname") {
        return 1;
    } else if (symbol == "LB") {
        return 2;
    } else if (symbol == "const") {
        return 3;
    } else if (symbol == "variable") {
        return 4;
    } else if (symbol == "assignop") {
        return 5;
    } else if (symbol == "Lit") {
        return 6;
    } else if (symbol == "comma"){
        return 7;
    } else if (symbol == "if" || symbol == "then" || symbol == "while" || symbol == "call" || symbol == "do" || symbol == "odd"){
        return 8;
    } else if (symbol == "semicolon"){
        return 9;
    } else if (symbol == "var"){
        return 10;
    } else if (symbol == "procedure"){
        return 11;
    }
    return 12; 
};

int tokenList(char ch) {
    if (isdigit(ch)) 
    {
        return 3;
    }
    if (isalnum(ch)) 
    {
        return 5;
    }

    switch (ch) {
        case '*': return 2;
        case '/': return 7;
        case '=': return 11;
        case '<': return 14;
        case '>': return 17;
        case ',': return 20;
        case ';': return 21;
        case '+': return 22;
        case '-': return 23;
        case '!': return 24;
        case '(': return 27;
        case ')': return 28;
        case '{': return 29;
        case '}': return 30;
    }
    return 1; // error handling
}

int tokenPDA(string token){
     if (token == "pgmname" || token == "variable" || token == "$") {
        return 0;
    } else if (token == "="){
        return 1;
    } else if (token == "+") {
        return 2;
    } else if (token == "-") {
        return 3;
    } else if (token == "(") {
        return 4;
    } else if (token == ")") {
        return 5;
    } else if (token == "*") {
        return 6;
    } else if (token == "/") {
        return 7;
    } else if (token == ";") {
        return 8;
    } else if (token == "==") {
        return 9;
    } else if (token == "!=") {
        return 10;
    } else if (token == ">") {
        return 11;
    } else if (token == "<") {
        return 12;
    } else if (token == ">=") {
        return 13;
    } else if (token == "<=") {
        return 14;
    } else if (token == "IF") {
        return 15;
    } else if (token == "THEN") {
        return 16;
    } else if (token == "WHILE") {
        return 17;
    } else if (token == "DO") {
        return 18;
    } else if (token == "{") {
        return 19;
    } else if (token == "}") {
        return 20;
    }
    return -1; // error handling
}

void printStack(stack<string> mystack) {
    stack<string> tempStack = mystack;  // Create a copy of the original stack
    cout << "Current Stack Contents (Top to Bottom): " << endl;
    while (!tempStack.empty()) {
        cout << tempStack.top() << endl; // Print the top element
        tempStack.pop();                          // Remove the top element
    }
    cout << "End of Stack." << endl;
}

void LexicalAnalyzer(ifstream& inputFile, ofstream& outputFile, TableDriven td) {
    char ch;
    string currentToken;
    bool isFinished = false;
    int currentState = 0;

    while (inputFile.get(ch)) {
        if (isspace(ch)){
            currentToken.clear();
             continue; 
        }
        int columnInput = tokenList(ch); 
        currentState = td.nextState(currentState,columnInput);
        
            while (!isFinished){
            switch (currentState) 
            {
                case 2: 
                    outputFile << ch << "  " << "mop" << endl; 
                    isFinished = true;
                    break;
                case 3:
                    if (isdigit(inputFile.peek()))
                    {
                        currentToken += ch;
                        inputFile.get(ch);
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                    }
                    else
                    {
                        currentToken += ch;
                        inputFile.get(ch);
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                        inputFile.unget();
                    }
                    break;
                case 4:
                    outputFile << currentToken << "  " << "Lit" << endl;
                    isFinished = true;
                    break;
                case 5:
                    if (isalnum(inputFile.peek()))
                    {
                        currentToken += ch;
                        inputFile.get(ch);
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                    }
                    else
                    {
                        currentToken += ch;
                        inputFile.get(ch);
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                        inputFile.unget();
                    }
                    break;
                case 6:
                    if (currentToken == "CLASS" || currentToken == "Class"){
                        outputFile << currentToken << "  " << "class" << endl;
                        currentToken.clear();
                        inputFile >> currentToken;
                        outputFile << currentToken << "  " << "pgmname" << endl;
                    } else if (currentToken == "VAR"){
                        outputFile << currentToken << "  " << "var" << endl;
                    } else if (currentToken == "IF"){
                        outputFile << currentToken << "  " << "if" << endl;
                    } else if (currentToken == "THEN"){
                        outputFile << currentToken << "  " << "then" << endl;
                    } else if (currentToken == "PROCEDURE"){
                        outputFile << currentToken << "  " << "procedure" << endl;
                    } else if (currentToken == "WHILE"){
                        outputFile << currentToken << "  " << "while" << endl;
                    } else if (currentToken == "CALL"){
                        outputFile << currentToken << "  " << "call" << endl;
                    } else if (currentToken == "DO"){
                        outputFile << currentToken << "  " << "do" << endl;
                    } else if (currentToken == "ODD"){
                        outputFile << currentToken << "  " << "odd" << endl;
                    } else if (currentToken == "CONST"){
                        outputFile << currentToken << "  " << "const" << endl;
                    } else {
                        outputFile << currentToken << "  " << "variable" << endl;
                    }
                    isFinished = true;
                    break;
                case 7:
                    currentToken += ch;
                    if (inputFile.peek() == '*')
                    {
                        inputFile.get(ch);
                        currentToken += ch;
                        columnInput = tokenList(ch);
                        currentToken.clear();
                        currentState = td.nextState(currentState, columnInput);
                    }
                    else
                    {
                        inputFile.get(ch);
                        currentToken += ch;
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                    }
                    break;
                case 8:
                    if (inputFile.peek() == '*')
                    {
                        inputFile.get(ch);
                        currentToken += ch;
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                    }
                    else
                    {
                        inputFile.get(ch);
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                    }
                    break;
                case 9:
                    if (inputFile.peek() == '/')
                    {
                        inputFile.get(ch);
                        currentToken += ch; /* 8*9 */
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                    }
                    else
                    {
                        inputFile.get(ch);
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                    }
                    break;
                case 10:
                    outputFile << currentToken << "  " << "divop" << endl;
                    isFinished = true;
                    break;
                case 11:
                    currentToken += ch;
                    if (inputFile.peek() == '=') 
                    {
                        inputFile.get(ch);
                        currentToken += ch; 
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                    } 
                    else 
                    {
                        inputFile.get(ch);
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                        inputFile.unget();
                    }
                    break;
                case 12:
                    outputFile << currentToken << "  " << "assignop" << endl;
                    isFinished = true;
                    break;
                case 13:
                    outputFile << currentToken << "  " << "relop" << endl;
                    isFinished = true;
                    break;
                case 14:
                    currentToken += ch;
                    if (inputFile.peek() == '=')
                    {
                        inputFile.get(ch);
                        currentToken += ch;
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                    }
                    else
                    {
                        inputFile.get(ch);
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                        inputFile.unget();
                    }
                    break;
                case 15:
                    outputFile << currentToken << "  " << "lessthanop" << endl;
                    isFinished = true;
                    break;
                case 16:
                    outputFile << currentToken << "  " << "lessthanequalop" << endl;
                    isFinished = true;
                    break;
                case 17:
                    currentToken += ch;
                    if (inputFile.peek() == '=')
                    {
                        inputFile.get(ch);
                        currentToken += ch;
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                    }
                    else
                    {
                        inputFile.get(ch);
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                        inputFile.unget();
                    }
                    break;
                case 18:
                    outputFile << currentToken << "  " << "greaterthanop" << endl;
                    isFinished = true;
                    break;
                case 19:
                    outputFile << currentToken << "  " << "greaterthanequalop" << endl;
                    isFinished = true;
                    break;
                case 20:
                    outputFile << ch << "  " << "comma" << endl;
                    isFinished = true;
                    break;
                case 21: 
                    outputFile << ch << "  " << "semicolon" << endl;
                    isFinished = true;
                    break;
                case 22: 
                    outputFile << ch << "  " << "addop" << endl; 
                    isFinished = true;
                    break;
                case 23: 
                    outputFile << ch << "  " << "subop" << endl; 
                    isFinished = true;
                    break;
                case 24:
                    currentToken += ch;
                    if (inputFile.peek() == '=')
                    {
                        inputFile.get(ch);
                        currentToken += ch;
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                    }
                    else
                    {
                        inputFile.get(ch);
                        columnInput = tokenList(ch);
                        currentState = td.nextState(currentState, columnInput);
                        inputFile.unget();
                    }
                    break;
                case 25:
                    outputFile << currentToken << "  " << "exclamationop" << endl;
                    isFinished = true;
                    break;
                case 26:
                    outputFile << currentToken << "  " << "notop" << endl;
                    isFinished = true;
                    break;
                case 27: 
                    outputFile << ch << "  " << "LP" << endl; 
                    isFinished = true;
                    break;
                case 28: 
                    outputFile << ch << "  " << "RP" << endl; 
                    isFinished = true;
                    break;
                case 29: 
                    outputFile << ch << "  " << "LB" << endl;
                    isFinished = true; 
                    break;
                case 30: 
                    outputFile << ch << "  " << "RB" << endl; 
                    isFinished = true;
                    break;
            }
        }
        if(isFinished)
        {
            currentState = 0;
            currentToken.clear();
            isFinished = false;
            
        }
    }
}

void SymbolTable(ifstream& inputTokensList, ofstream& outputSymbolTable, FSA2 st) {
    string symbol, classification;
    int codesegmentvalue = 0, datasegmentvalue = 0;
    int currentSymbolState = 0;
    string codesegment = "CS", datasegment = "DS", value = "";
    string temp1, temp2, temp3, temp4;

    while (inputTokensList >> symbol >> classification) {

        int columnSymbolInput = tokenSymbolT(classification);
        currentSymbolState = st.nextSymbolState(currentSymbolState, columnSymbolInput);
        switch(currentSymbolState) {
            case 0: // Start state
                break;
            case 1: // Class state
                break;
            case 2: // Pgmname state
                temp1 = symbol + " " + classification;
                outputSymbolTable << temp1 << " " << value << " " << codesegmentvalue << " " << codesegment << endl;
                temp1.clear();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                temp1 = symbol; 
                break;
            case 6:
                break;
            case 7:
                temp2 = symbol;
                outputSymbolTable << temp1 << " Constvar " << temp2 << " " << value << " " << datasegmentvalue << " " << datasegment << endl;
                temp1.clear();
                temp2.clear();
                datasegmentvalue+=2;
                break;
            case 8:
                break;
            case 9:
                temp1 = symbol;
                outputSymbolTable << temp1 << " var " << " ? " << " " << value << " " << datasegmentvalue << " " << datasegment << endl;
                datasegmentvalue+=2;
                temp1.clear();
                break;
            case 10:
            break;
            break;
            case 11:
            temp1 = symbol;
            temp2 = symbol;
            value = temp2;
            outputSymbolTable << temp1 << " " << classification << temp2 << " " << datasegmentvalue << " " << datasegment << endl;
            datasegmentvalue+=2;
            temp1.clear();
            temp2.clear();
            break;
            case 12:
            break;
        }
    }
        outputSymbolTable << "T1" << " Var (int) " << " ? "  << " " << datasegmentvalue << " " << datasegment << endl;
        datasegmentvalue+=2;
        outputSymbolTable << "T2" << " Var (int) " << " ? "  << " " << datasegmentvalue << " " << datasegment << endl;
        datasegmentvalue+=2;
        outputSymbolTable << "T3" << " Var (int) " << " ? "  << " " << datasegmentvalue << " " << datasegment << endl;
        datasegmentvalue+=2;
        outputSymbolTable << "T4" << " Var (int) " << " ? "  << " " << datasegmentvalue << " " << datasegment << endl;
        datasegmentvalue+=2;
        outputSymbolTable << "T5" << " Var (int) " << " ? "  << " " << datasegmentvalue << " " << datasegment << endl;
        datasegmentvalue+=2;
}

void PushDownAutomaton(ifstream& pdaInput, ofstream& outputPDA, PDA pd) {
    stack<string> mystack;
    mystack.push("$");
    string lastOperator = "$";
    int lastoperatorinput = tokenPDA(lastOperator);
    int i = 1;
    int j = 1;
    string op, op1, op2;
    string temp, temp2, temp3, temp4;
    string prevop;

    string token, classification;

    cout << "Starting Pushdown Automaton..." << endl;

    while (pdaInput >> token >> classification) {
        cout << "Token: " << token << ", Classification: " << classification << endl;

        if (classification == "class" || classification == "pgmname" || classification == "LB" || classification == "RB"){
            continue;
        }
        if (classification == "const"){
            while (classification != "semicolon"){
                pdaInput >> token >> classification;
            }
            pdaInput >> token >> classification;
        }

        if (classification == "var"){
            while (classification != "semicolon"){
                pdaInput >> token >> classification;
            }
            pdaInput >> token >> classification;
        }

        int pdacolumnInput;
        string currentPDAState;

        if (classification == "variable" || classification == "int") {
            mystack.push(token);
            cout << "pushing " << token << " onto stack" << endl;
            cout << "stack size: " << mystack.size() << endl;
            
        } else if (classification == "if" || classification == "while" ){
            mystack.push(token);
            cout << "pushing " << mystack.top() << " onto stack" << endl;
            cout << "stack size: " << mystack.size() << endl;
            cout << "QUAD ------------------------------------------ " << mystack.top() << " ? ? ? " << endl;
            outputPDA << mystack.top() <<  " ? ? ? " << endl;

        } else if (classification == "greaterthanop" || classification == "greaterthanequalop"){
            // ITS AN > or >= OPERATOR
            pdacolumnInput = tokenPDA(token);
            currentPDAState = pd.PDAprecedence(lastoperatorinput, pdacolumnInput);
            cout << "operator trying to be pushed into stack: " << "(" << token << ")" << " ------------- " << lastoperatorinput << " " << pdacolumnInput << " " << currentPDAState << endl;

        } else if (classification == "then" || classification == "do"){
            mystack.push(token);
            cout << "pushing " << mystack.top() << " onto stack" << endl;
            cout << "stack size: " << mystack.size() << endl;

            temp = mystack.top();
            mystack.pop();
            cout << "stack size: " << mystack.size() << endl;

            pdacolumnInput = tokenPDA(token);
            currentPDAState = pd.PDAprecedence(lastoperatorinput, pdacolumnInput);
            cout << "operator trying to be pushed into stack: " << "(" << token << ")" << " ------------- " << lastoperatorinput << " " << pdacolumnInput << " " << currentPDAState << endl;

        } else if (classification == "addop"){
            // ITS AN ADDITION OPERATOR
            pdacolumnInput = tokenPDA(token);
            currentPDAState = pd.PDAprecedence(lastoperatorinput, pdacolumnInput);
            cout << "operator trying to be pushed into stack: " << "(" << token << ")" << " ------------- " << lastoperatorinput << " " << pdacolumnInput << " " << currentPDAState << endl;

        } else if (classification == "subop"){
            // ITS A SUBTRACTION OPERATOR
            pdacolumnInput = tokenPDA(token);
            currentPDAState = pd.PDAprecedence(lastoperatorinput, pdacolumnInput);
            cout << "operator trying to be pushed into stack: " << "(" << token << ")" << " ------------- " << lastoperatorinput << " " << pdacolumnInput << " " << currentPDAState << endl;

        } else if (classification == "mop"){
            // ITS A MULTIPLICATION OPERATOR
            pdacolumnInput = tokenPDA(token);
            currentPDAState = pd.PDAprecedence(lastoperatorinput, pdacolumnInput);
            cout << "operator trying to be pushed into stack: " << "(" << token << ")" << " ------------- " << lastoperatorinput << " " << pdacolumnInput << " " << currentPDAState << endl;

        } else if (classification == "divop"){
            // ITS A DIVISION OPERATOR
            pdacolumnInput = tokenPDA(token);
            currentPDAState = pd.PDAprecedence(lastoperatorinput, pdacolumnInput);
            cout << "operator trying to be pushed into stack: " << "(" << token << ")" << " ------------- " << lastoperatorinput << " " << pdacolumnInput << " " << currentPDAState << endl;

        }else if (classification == "assignop"){ 
            // It's an operator
            pdacolumnInput = tokenPDA(token);
            currentPDAState = pd.PDAprecedence(lastoperatorinput, pdacolumnInput);
            cout << "operator trying to be pushed into stack: " << "(" << token << ")" << " ------------- " << lastoperatorinput << " " << pdacolumnInput << " " << currentPDAState << endl;

        } else {
            pdacolumnInput = tokenPDA(token);
            currentPDAState = pd.PDAprecedence(lastoperatorinput, pdacolumnInput);
            cout << "operator trying to be pushed into stack: " << "(" << token << ")" << " ------------- " << lastoperatorinput << " " << pdacolumnInput << " " << currentPDAState << endl;
        }


        if (currentPDAState == "<" || currentPDAState == "0" || currentPDAState == "=") {
            cout << "Current precedence: " << currentPDAState << endl;

            cout << "pushing " << token << " onto stack" << endl;

            mystack.push(token);

            cout << "stack size: " << mystack.size() << endl;

            printStack(mystack);

            lastOperator = token;

            cout << "Last Operator in stack: " << lastOperator << endl;
            
            lastoperatorinput = tokenPDA(lastOperator);
        } else if (currentPDAState == ">") {
            while (currentPDAState == ">") {

                cout << "greater precedence was detected. now in while loop..." << endl;

                if (mystack.top() == "THEN" || mystack.top() == "DO"){
                    cout << "THEN detected" << endl;
                    cout << "QUAD ------------------------------------------ " << mystack.top() << " L" << j << " LE ?" << endl;
                    outputPDA << mystack.top() << " L" << j << " LE ?" << endl;
                    break;

                } else {
                    op2 = mystack.top();
                    mystack.pop();
                    cout << "Popped from stack for op2: " << op2 << endl;
                    cout << "stack size: " << mystack.size() << endl;
                    printStack(mystack);
                }

                if (mystack.top() != "$" && mystack.top() != "IF" && mystack.top() != "$"){
                    op = mystack.top();
                    mystack.pop();
                    cout << "Popped from stack for operator: " << op << endl;
                    cout << "stack size: " << mystack.size() << endl;
                    printStack(mystack);

                } else if (op2 == "T5" || op2 == "IF"){
                        cout << "QUAD ------------------------------------------ " << "L" << j << " ? ? ?" << endl;
                        outputPDA << "L" << j << " ? ? ?" << endl;
                } else {
                    cout << "Stack underflow: expected operator missing." << endl;
                    break;
                }


                if (mystack.top() != "$" && mystack.top() != "IF"){
                    op1 = mystack.top();
                    mystack.pop();
                    cout << "Popped from stack for op1: " << op1 << endl;
                    cout << "stack size: " << mystack.size() << endl;
                    printStack(mystack);

                } else {
                    cout << "Stack underflow: expected first operand missing." << endl;
                    break;
                }

                cout << "<------------------------------------------------------------------------------------->" << endl;

                if (currentPDAState == ">" && op != "THEN" && op != "DO") {
                    cout << "popping quad out of stack..." << endl;
                    cout << "QUAD --------here---------------------------------- " << op << " " << op1 << " " << op2 << " T" << i << endl;
                    outputPDA << op << " " << op1 << " " << op2 << " T" << i << endl;

                    mystack.push("T" + to_string(i));
                    cout << "pushing T" << i << endl;
                    cout << "stack size " << mystack.size() << endl;
                    
                    printStack(mystack);
                    i++;

                    if (op == ">" || op == ">="){
                        mystack.push(temp);
                        cout << "pushing " << temp << " onto stack" << endl;
                        cout << "stack size: " << mystack.size() << endl;
                    } else {
                        ;
                    } 
                } else {
                    ;
                }
            }
        } 
    }

    cout << "End of Pushdown Automaton processing." << endl;
    if (!mystack.empty()) {
        cout << "Top of the final stack: " << mystack.top() << endl;
        cout << "Final Stack Size " << mystack.size() << endl;
    }

}


string quadToAssembly(const string& op, const string& arg1, const string& arg2, const string& result) {
    stringstream asmCode;

    // Helper function to format operands
    auto formatOperand = [](const string& operand) -> string {
        if (isdigit(operand[0]) || operand[0] == '-') {
            return operand; // Immediate value
        } else if (operand != "?") {
            return "[" + operand + "]"; // Memory access
        }
        return operand; // Placeholder or special operand
    };

    string formattedArg1 = formatOperand(arg1);
    string formattedArg2 = formatOperand(arg2);
    string formattedResult = formatOperand(result);

    if (op == "IF") {
        // No direct operation; assume condition follows
    } else if (op == ">") {
        asmCode << "    mov ax, " << formattedArg1 << "\n";
        asmCode << "    cmp ax, " << formattedArg2 << "\n";
        asmCode << "    jg " << formattedResult << "\n"; // Jump to result label
    } else if (op == ">=") {
        asmCode << "    mov ax, " << formattedArg1 << "\n";
        asmCode << "    cmp ax, " << formattedArg2 << "\n";
        asmCode << "    jge " << formattedResult << "\n"; // Jump if greater or equal
    } else if (op == "THEN") {
        asmCode << result << ":\n"; // Label for THEN block
    } else if (op == "+") {
        asmCode << "    mov ax, " << formattedArg1 << "\n";
        asmCode << "    add ax, " << formattedArg2 << "\n";
        asmCode << "    mov " << formattedResult << ", ax\n"; // Store sum in result
    } else if (op == "-") {
        asmCode << "    mov ax, " << formattedArg1 << "\n";
        asmCode << "    sub ax, " << formattedArg2 << "\n";
        asmCode << "    mov " << formattedResult << ", ax\n"; // Store difference in result
    } else if (op == "*") {
        asmCode << "    mov ax, " << formattedArg1 << "\n";
        asmCode << "    mul word " << formattedArg2.substr(1, formattedArg2.length() - 2) << "\n"; // Remove brackets
        asmCode << "    mov " << formattedResult << ", ax\n"; // Store product in result
    } else if (op == "/") {
        asmCode << "    mov ax, " << formattedArg1 << "\n";
        asmCode << "    xor dx, dx\n"; // Clear DX before division
        asmCode << "    div word " << formattedArg2.substr(1, formattedArg2.length() - 2) << "\n"; // Remove brackets
        asmCode << "    mov " << formattedResult << ", ax\n"; // Store quotient in result
    } else if (op == "=") {
        asmCode << "    mov " << formattedResult << ", " << formattedArg1 << "\n"; // Assignment
    } else if (op == "ENDIF") {
        asmCode << result << ": nop\n"; // Label for end of IF block
    } else {
        asmCode << "    ; ERROR: Unrecognized operation.\n";
    }

    return asmCode.str();
}

void processQuadsToAssembly(const string& inputPath, const string& outputPath, const string& symbolTablePath) {
    ifstream inFile(inputPath);
    ifstream symTableFile(symbolTablePath);
    ofstream outFile(outputPath);
    string line, symbol, type, value, segment;
    string op, arg1, arg2, result;
    int segmentValue;

    // Write the .data section
    outFile << "section .data\n";
    while (getline(symTableFile, line)) {
        stringstream ss(line);
        ss >> symbol >> type >> value >> segmentValue >> segment;

        if (segment == "DS") {
            if (type == "Constvar") {
                outFile << symbol << " dw " << value << "\n";
            }
        }
    }

    // Write the .bss section
    outFile << "section .bss\n";
    outFile << "X resw 1\nY resw 1\nZ resw 1\n";
    outFile << "T1 resw 1\nT2 resw 1\nT3 resw 1\nT4 resw 1\nT5 resw 1\n";

    // Write the .text section
    outFile << "section .text\n";
    outFile << "global _start\n";
    outFile << "_start:\n";

    // Process and write instructions
    while (getline(inFile, line)) {
        stringstream iss(line);
        if (iss >> op >> arg1 >> arg2 >> result) {
            string assemblyLine = quadToAssembly(op, arg1, arg2, result);
            if (!assemblyLine.empty()) {
                outFile << assemblyLine;
            }
        }
    }

    // Write NASM assembly exit sequence
    outFile << "    mov ax, 1\n";
    outFile << "    int 0x80\n";

    symTableFile.close();
    inFile.close();
    outFile.close();
    cout << "Assembly code generated successfully." << endl;
}

int main() {
    ifstream inputFile("C:\\Users\\Emmanuel\\Documents\\SAMPLECOMPILERPGM.txt");
    ofstream outputFile("C:\\Users\\Emmanuel\\Documents\\TOKENSLIST.txt");

    TableDriven td;
    FSA2 st;
    PDA pd;
    LexicalAnalyzer(inputFile, outputFile, td);
    inputFile.close();
    outputFile.close();

    ifstream inputTokensList("C:\\Users\\Emmanuel\\Documents\\TOKENSLIST.txt");
    ofstream outputSymbolTable("C:\\Users\\Emmanuel\\Documents\\SYMBOLTABLEOUTPUT.txt");
    SymbolTable(inputTokensList, outputSymbolTable, st);
    inputTokensList.close();
    outputSymbolTable.close();

    ifstream pdaInput("C:\\Users\\Emmanuel\\Documents\\TOKENSLIST.txt");
    ofstream outputPDA("C:\\Users\\Emmanuel\\Documents\\PDA.txt");
    PushDownAutomaton(pdaInput, outputPDA, pd);
    pdaInput.close();
    outputPDA.close();

     processQuadsToAssembly(
        "C:\\Users\\Emmanuel\\Documents\\PDA.txt",
        "C:\\Users\\Emmanuel\\Documents\\QUADTOASM.asm",
        "C:\\Users\\Emmanuel\\Documents\\SYMBOLTABLEOUTPUT.txt"
    );

    
    cout << "Token classification completed successfully." << endl;

    return 0;
}