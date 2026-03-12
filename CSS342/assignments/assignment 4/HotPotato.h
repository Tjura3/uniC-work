#include <iostream>
#include <string>
#include "queue_clinkedlist.h"

using namespace lqueue;
using namespace std;


class HotPotatoGame{
    public:

        void setParticipants(){ 
            string input;
            while(input != "done"){
                cin >> input;
                if(input != "done"){
                    a.enqueue(input);
                }
            }
        }

        void setMaxPas(const int& a){
            maxpas = a;
        }

        string playGame(){
            if(a.size() <= 0) return "No participants";
            while (a.size() != 1){
                int potato = rand() % maxpas;
                while(potato != 0){
                    string current = a.front();
                    a.dequeue();
                    a.enqueue(current);
                    potato--;
                }
                cout << "eliminated " << a.front() << endl;
                a.dequeue();
            }
            return a.front();
            
        }

    private:
        LinkedQueue<string> a;
        int maxpas;

};