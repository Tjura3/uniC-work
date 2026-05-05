//singleton
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class MessageGenerator{
    private:
    vector<string> messages = {"not quite my type",
                                    "Are you sure you studied?",
                                    "are you sure you can read?",
                                    "wtf!?",
                                    "rushing or dragging"};
    int msgIdx = 0;

    MessageGenerator() = default;
    ~MessageGenerator() = default;

    inline static MessageGenerator* instance;
    //when we make a member variable static, all classes will use it? (confusing text)

    public:
    //this method is apart of the class, so it can call the constructor.
    static void init(){
        if(MessageGenerator::instance != nullptr){
            throw runtime_error("Already initialized");
        }
        MessageGenerator::instance = new MessageGenerator();
    }
    MessageGenerator* getInstance(){
        return MessageGenerator::instance;
    }
    string getNextMessage(){
        string retVal = messages[msgIdx];
        msgIdx = (msgIdx+1) % messages.size(); 
    }
};