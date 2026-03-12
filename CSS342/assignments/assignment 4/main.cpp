//By Thomas Juranich
#include "HotPotato.h"
#include "ArrayPotato.h"
#include <iostream>
using namespace std;

void linkedBasedPotato();
void arrayBasedPotato();
bool isNumber(const std::string& s);

//set between the linked list and array based potato passing game.
int main()
{
    //linkedBasedPotato();
    arrayBasedPotato();
    return 0;
}


void linkedBasedPotato()
{
    string cont = "yes";
    while (cont == "yes")
    {
        system("clear");
        HotPotatoGame a;

        cout << "Enter player names (type 'done' to finish):" << endl;
        a.setParticipants();
        cout << "Enter maximum amount of passes: ";

        string uspas;  //user passes
        cin >> uspas;
        int pas;
        if(!isNumber(uspas)){
            cout << "invalid input, setting passes to 5" << endl;
            pas = 5; 
        }else{
            pas = stoi(uspas);
        }

        if (pas <= 1)
        { // zero or negative check
            pas = 1;
        }
        a.setMaxPas(pas);

        cout << "Starting Game" << endl;
        string winner = a.playGame();
        cout << "Winner is: " << winner << endl;
        cout << "Would you like to play again? type 'yes' to continue." << endl;
        cin >> cont;
    }
}

void arrayBasedPotato()
{
    string cont = "yes";
    while (cont == "yes")
    {
        // below is the remnants of me trying to allow the user to set the array.
        //
        /*int participants;
        cout<< "How many participants are there?" << endl;
        cin >> participants;

        if (participants <= 5){
            cout << "set participants to 5" << endl;
            participants = 5;
        }
        ArrayPotatoGame a(participants);
        */
        system("clear");
        cout << "Set array max" << endl;
        int max;
        cin >> max;
        ArrayPotatoGame a(max);
        //cout << "Creating an arrayqueue with a size of 20" << endl;
        cout << "Enter player names (type 'done' to finish):" << endl;
        a.setParticipants();
        cout << "Enter maximum amount of passes: ";

        string uspas;  //user passes
        cin >> uspas;
        int pas;
        if(!isNumber(uspas)){
            cout << "invalid input, setting passes to 5" << endl;
            pas = 5; 
        }else{
            pas = stoi(uspas);
        }
        { // zero or negative check
            pas = 1;
        }
        a.setMaxPas(pas);

        cout << "Starting Game" << endl;
        string winner = a.playGame();
        cout << "Winner is: " << winner << endl;
        cout << "Would you like to play again? type 'yes' to continue." << endl;
        cin >> cont;
    }
}

bool isNumber(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

