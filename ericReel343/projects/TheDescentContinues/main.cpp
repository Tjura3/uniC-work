#include <regex>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

using std::cout;
using std::vector;
using std::regex;
using std::regex_search;
using std::smatch;
using std::string;
using std::to_string;


enum TokenType {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    WHITESPACE,
    NO_MORE_TOKENS,
    LEXICAL_ERROR
};

struct Token {
    TokenType type;
    string    value;
    Token() {;}
    Token(TokenType type, string value) 
        : type(type), value(value){;}
    bool operator==(const Token& other) const {
        return type == other.type && value == other.value;
    }        
};

class Lexer {
private:
    string input;    
    string remaining;    

public:
    Lexer(string input) 
        : input(input) {
        remaining = input.c_str();
    }

    Token getNextToken(){
        Token token;
        do {
            if(remaining.size() == 0) {
                token = Token(NO_MORE_TOKENS, "");
                break;
            }

            smatch match;
            if (regex_search(remaining, match, regex("^([0-9]+)"))) {
                token = Token(NUMBER, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\+)"))) {
                token = Token(PLUS, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\-)"))) {
                token = Token(MINUS, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\<small>\\*|\\*)"))) { // matches *
                token = Token(MULTIPLY, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\/)"))) {
                token = Token(DIVIDE, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\()"))) {
                token = Token(LPAREN, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\))"))) {
                token = Token(RPAREN, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\s)"))) {
                token = Token(WHITESPACE, match[1].str());
                remaining = remaining.substr(token.value.size());      
            } else {
                token = Token(LEXICAL_ERROR, ""); 
            }
        } while(token.type == WHITESPACE);

        return token;
    } 
    bool getNextToken(Token& token) { 
        token = getNextToken();
        return token.type != LEXICAL_ERROR;
    }

    void removeToken(Token token){
        remaining = remaining.substr(token.value.size());
    }

};

class KitchenSinkParser {
private:
    // expr -> term {+|- term}
    int expr(Lexer& lexer) {
        int val = term(lexer);
        Token token;

        while(lexer.getNextToken(token) && (token.type == PLUS || token.type == MINUS)) {
            lexer.removeToken(token);
            int rightTerm = term(lexer);
            if (token.type == PLUS) {
                val += rightTerm;
            } else {
                val -= rightTerm;
            }
        }
        return val;
    }

    // term -> factor {*|/ factor}
    int term(Lexer& lexer) {
        int val = factor(lexer);
        Token token;

        while(lexer.getNextToken(token) && (token.type == MULTIPLY || token.type == DIVIDE)) {
            lexer.removeToken(token);
            int rightFactor = factor(lexer);
            if (token.type == MULTIPLY) {
                val *= rightFactor;
            } else {
                if (rightFactor == 0) {
                    throw std::runtime_error("WARNING: DIVIDE BY ZERO DETECTED.");
                }
                val /= rightFactor;
            }
        }
        return val;
    }

    // factor -> NUMBER | ( expr )
    int factor(Lexer& lexer) {
        Token token;
        lexer.getNextToken(token);

        if (token.type == NUMBER) {
            lexer.removeToken(token);
            return std::stoi(token.value);
        } 
        
        // Parentheses matching
        else if (token.type == LPAREN) {
            lexer.removeToken(token); 
            
            int internalResult = expr(lexer); // Recursively parse internal
            
            Token closingToken;
            lexer.getNextToken(closingToken);
            if (closingToken.type == RPAREN) {
                lexer.removeToken(closingToken); 
                return internalResult;
            } else {
                throw std::runtime_error("Parse Error: Mismatched parentheses.");
            }
        } 
        else {            
            throw std::runtime_error("Parse Error: Unexpected token found in factor.");
        }
    }

public:
    KitchenSinkParser() {;}
    
    int parse(string statement) {
        Lexer lexer(statement);
        return expr(lexer);
    }
};

/* //AST parser and Eval parser exercises
// expr = factor {- factor}
// factor -> INTEGER 

class ASTNode {
public:    
    virtual int process() = 0;
    virtual ~ASTNode() {;}
    virtual string toString() = 0;
};

class ASTNodeSubtract : public ASTNode {
public:
    ASTNode* pLeft;
    ASTNode* pRight;

public:
    ASTNodeSubtract(ASTNode* pLeft, ASTNode* pRight)
        : pLeft(pLeft), pRight(pRight) {;}
    ~ASTNodeSubtract() {
        delete pLeft;
        delete pRight;
    }
    int process() override { 
        return pLeft->process() - pRight->process();
    }
    string toString() override {
        return "(" + pLeft->toString() + " - " + pRight->toString() + ")";
    }
};

class ASTNodeNumber : public ASTNode {
private:
    int number;
public:
    ASTNodeNumber(int number) 
        : number(number) {;}
    int process() override {
        return number;
    }
    string toString() override {
        return to_string(number);
    }
};     


// expr = factor - expr
// factor -> INTEGER 

class ASTParser {
private:
    
    ASTNode* expr(Lexer& lexer) {
        ASTNode* pLeft = factor(lexer);
        Token token; 
        while(lexer.getNextToken(token) && token.type == MINUS) {
            lexer.removeToken(token);
            ASTNode* pRight = factor(lexer);
            pLeft = new ASTNodeSubtract(pLeft, pRight);
        }
        
        return pLeft;
    }

    ASTNode* factor(Lexer& lexer) {
        Token token;
        lexer.getNextToken(token);
        ASTNode* pNode;
        if (token.type == NUMBER) {
            lexer.removeToken(token);
            pNode = new ASTNodeNumber(stoi(token.value));
        } else {            
            throw new std::runtime_error("parse error");
        }
        return pNode;
    }

public:
    ASTParser()    {;};
    ASTNode* parse(string statement){
        Lexer lexer(statement);
        return expr(lexer);
    }
};

class EvalParser{
    private:
    int expr(Lexer& lexer){
        int leftVal = factor(lexer);
        Token token;
        while(lexer.getNextToken(token) && token.type == MINUS) {
            lexer.removeToken(token);
            int rightVal = factor(lexer);
            leftVal = leftVal - rightVal; 
        }
        return leftVal;
    }

    int factor(Lexer& lexer) {
        Token token;
        lexer.getNextToken(token);
        
        if (token.type == NUMBER) {
            lexer.removeToken(token);
            return stoi(token.value);
        } else {            
            throw new std::runtime_error("parse error");
        }
    }

    public:
    EvalParser() {;}
    
    
    int parse(string statement) {
        Lexer lexer(statement);
        return expr(lexer);
    }
};

*/

int main() {

    KitchenSinkParser parser;
    struct CyborgTest {
        string exprStr;
        int expected;
    };
    vector<CyborgTest> testSuite = {
        {"10 + 2 * 3", 16},          // Multiplication + pemdas (10 + 6)
        {"(10 + 2) * 3", 36},        // Parentheses first (12 * 3)
        {"50 - 10 - 5 - 5", 30},     // Subtraction
        {"24 / 2 / 3", 4},           // Division
        {"100 / (2 * (3 + 2))", 10}, // Nested parentheses (100/(2*5))
        {"2 * 3 + 4 * 5", 26},       // Pemdas check
        {"2 / 0", 0}                 // Divide zero break
    };

    cout << "--- THE FINAL PROJECT --- \n\n";
    for(const auto& test : testSuite) {
        try {
            int result = parser.parse(test.exprStr);
            cout << "Input:    " << test.exprStr << "\n";
            cout << "Result:   " << result << " (Expected: " << test.expected << ")\n";
            if(result == test.expected) {
                cout << "_CLEAR._\n";
            } else {
                cout << "Wr0Ng__.\n";
            }
        } catch (const std::exception& e) {
            cout << "Something broke: " << e.what() << "\n";
        }
        cout << "__________________________________________________\n";
    }

    cout << "Testing Missing Bracket:\n";
    try {
        parser.parse("(5 + 5");
    } catch (const std::runtime_error& e) {
        cout << "Caught Expected Exception: " << e.what() << "\n";
    }

    return 0;

    /* //AST parser exercise
    ASTParser parser;
    vector<string> statements = {"1-2-3"};

    for(string stmt : statements) {
        ASTNode* ast = parser.parse(stmt);
        int val = ast->process();
        cout << "stmt: " << stmt << " result: " << val << "\n";
    }   
    return 0;
    */

    /* // Eval parser exercise
    ASTParser parser;
    EvalParser evalParser;
    // tried to use vector pair, but it was honestly easier to implement with a struct.
    struct TestCase {
        string exprStr;
        int expectedResult;
    };

    vector<TestCase> testSuite = {
        {"1-2-3", -4},          
        {"10-5", 5},            
        {"100-20-30-10-10", 30}, 
        {"0-0-5", -5},
        {"0-0-5-20", -25},          
        {"50", 50}              
    };

    bool allTestsPassed = true;

    for(const auto& test : testSuite) {
        ASTNode* ast = parser.parse(test.exprStr);
        int astVal = ast->process();
        string formatStr = ast->toString();

        int evalResult = evalParser.parse(test.exprStr);

        cout << "Statement:    " << test.exprStr << "\n";
        cout << "AST:          " << formatStr << "\n";
        cout << "Result:       " << astVal << "\n";
        cout << "Expected:     " << test.expectedResult << "\n";
        cout << "EvalParser:   " << evalResult << "\n";

        if(evalResult == test.expectedResult) {
            cout << ">>> SUCCESS\n";
        } else {
            cout << ">>> FAILURE\n";
            allTestsPassed = false;
        }
        cout << "____________________________________________________________________________\n";
        
        delete ast;
    }   

    if (allTestsPassed) {
        cout << "\nAll passed.\n";
    } else {
        cout << "\nFailed at least 1 test/\n";
    }

    return 0;
    */
    
}