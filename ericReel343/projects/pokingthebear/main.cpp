#include <iostream>
#include <string>

using namespace std;

enum BearState {
    INDIFFERENT,
    ANNOYED,
    ANGRY,
    VERY_ANGRY,
    EXTREME_ANGER,
    FINAL
};

string getStateName(BearState state) {
    switch (state) {
        case INDIFFERENT:   return "Indifferent";
        case ANNOYED:       return "Annoyed";
        case ANGRY:         return "Angry";
        case VERY_ANGRY:    return "Very Angry";
        case EXTREME_ANGER: return "Extreme Anger";
        default:            return "Error. Bear broke.";
    }
}

void bearStateGame(){
    BearState currentState = INDIFFERENT;
    string action;

    cout << "--- Welcome to Grizzly ---\n";
    cout << "Pro tip: Poking a bear is ill-advized.\n\n";

    while (currentState != FINAL) {
        cout << "> The bear is currently: " << getStateName(currentState) << "\n";
        cout << "> Actions: poke, pet, feed, other\n>>";
        
        cin >> action;
        for (char& c : action){
            c = tolower(c);
        }
        
        if (action == "feed") {
            cout << "> The bear seems somewhat satisfied.";
            currentState = INDIFFERENT;
        }
        else if (action == "pet") {
            cout << "> You pet the bear.\n> It seems to have calmed down slightly.";
            if (currentState == ANNOYED)       currentState = INDIFFERENT;
            else if (currentState == ANGRY)     currentState = ANNOYED;
            else if (currentState == VERY_ANGRY) currentState = ANGRY;
            else if (currentState == EXTREME_ANGER) currentState = VERY_ANGRY;
        }
        else if (action == "poke") {
            switch (currentState) {
                case INDIFFERENT:
                    cout << "> The bear growls.";
                    currentState = ANNOYED;
                    break;
                case ANNOYED:
                    cout << "> The bear gives you a nasty scratch.";
                    currentState = ANGRY;
                    break;
                case ANGRY:
                    cout << "> The bear gives you a savage bite.";
                    currentState = VERY_ANGRY;
                    break;
                case VERY_ANGRY:
                    cout << "> The bear gives you a severe mauling.";
                    currentState = EXTREME_ANGER;
                    break;
                case EXTREME_ANGER:
                    cout << "> The bear reduces you to bits and pieces.";
                    currentState = FINAL; 
                    break;
                default:
                    break;
            }
        }
        else {
            cout << "> The bear failed to understand you as tensions rise.";
            switch (currentState) {
                case INDIFFERENT:   currentState = ANNOYED; break;
                case ANNOYED:       currentState = ANGRY; break;
                case ANGRY:         currentState = VERY_ANGRY; break;
                case VERY_ANGRY:    currentState = EXTREME_ANGER; break;
                case EXTREME_ANGER: currentState = EXTREME_ANGER; break; 
                default: break;
            }
        }
        cout << "\n\n";
    }

    cout << "\n========================================\n";
    cout << "GAME OVER!\n";
    cout << "Timothy Treadwell would be disappointed. You are now bear food.\n";
    cout << "========================================\n";
}

int main() {
    bearStateGame();
    return 0;
}