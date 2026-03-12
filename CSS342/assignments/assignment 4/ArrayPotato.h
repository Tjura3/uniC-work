#include <iostream>
#include <string>
#include "queue_array.h"

using namespace aqueue;
using namespace std;


class ArrayPotatoGame{
    public:

        /*ArrayPotatoGame(int& arraymax){
            ArrayQueue<string> t(arraymax);
            a = t;
        }*/
        ArrayPotatoGame(int c){
            a = ArrayQueue<string>(c);
        }
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
        ArrayQueue<string> a;
        int maxpas;

};