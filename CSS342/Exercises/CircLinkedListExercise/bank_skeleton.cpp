// =============================
// Bank Simulation
// =============================
//next we will implement an array based queue
#include <iostream>
#include "queue_clinkedlist.h"

#define SIMULATION_TIME 60 *8
#define ARRIVAL_PROBABILITY 25 //chance out of 100 to arrive
#define MAX_WAITINGTIME 4
#define MIN_WAITINGTIME 2

using namespace std;
using namespace lqueue;



int main() {
    
    srand(static_cast<unsigned>(time(0)));  // seed random generator

    ArrayQueue<int> line;
    

    bool isWorking = false;
    int totalArrived = 0;
    int customersServed = 0;
    int totalWaitTime = 0;
    int maxQueueLength = 0;
    int serviceTimeRemaining=0;
    

    // Simulation loop
    for (int minute = 0; minute < SIMULATION_TIME; minute++) {

        // 1. New customer arrival
        
        if(rand() % 100 < ARRIVAL_PROBABILITY){
            line.enqueue(minute);
            totalArrived++;
            cout << "Customer arrived at " << minute << endl;
        }

        // 2. If teller is busy, ...
        if(isWorking){
            
            serviceTimeRemaining--;
            if(serviceTimeRemaining == 0){
                customersServed++;
                isWorking = false;
            }
        }

        
        // 3. If teller is free and queue not empty, ...
        if(!isWorking && !line.empty()){
            totalWaitTime += minute - line.front();
            line.dequeue();
            serviceTimeRemaining = MIN_WAITINGTIME + rand() % MAX_WAITINGTIME;
            isWorking = true;
        }

        // 4. Track max queue length
        if(line.size() > maxQueueLength){
            maxQueueLength = line.size();
        }
    }

    // =============================
    // Simulation Results
    // =============================
    cout << "\nSimulation Results\n";
    cout << "--------------------------------\n";
    cout << "Total customers arrived: " << totalArrived << endl;
    cout << "Total customers served: " << customersServed << endl;
    if (customersServed > 0)
        cout << "Average wait time: " 
             << static_cast<double>(totalWaitTime) / customersServed 
             << " minutes\n";
    else
        cout << "Average wait time: 0 minutes\n";
    cout << "Maximum queue length: " << maxQueueLength << endl;
    
    return 0;
}