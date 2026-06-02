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
    MINUS,
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
            } else if (regex_search(remaining, match, regex("^(\\-)"))) {
                token = Token(MINUS, match[1].str());
            } else if (regex_search(remaining, match, regex("^(\\s)"))) {
                token = Token(WHITESPACE, match[1].str());
                remaining = remaining.substr(token.value.size());      
            } else {
                token = Token(LEXICAL_ERROR, match[1].str()); 
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


int main() {
    /*
    ASTParser parser;
    vector<string> statements = {"1-2-3"};

    for(string stmt : statements) {
        ASTNode* ast = parser.parse(stmt);
        int val = ast->process();
        cout << "stmt: " << stmt << " result: " << val << "\n";
    }   
    return 0;
    */

    ASTParser parser;
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
        int val = ast->process();
        string formatStr = ast->toString();

        cout << "Statement: " << test.exprStr << "\n";
        cout << "AST:       " << formatStr << "\n";
        cout << "Result:    " << val << "\n";
        cout << "Expected:  " << test.expectedResult << "\n";

        if(val == test.expectedResult) {
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
}