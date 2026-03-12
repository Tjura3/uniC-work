//Thomas S. Juranich
//10-9-2025

#include <iostream>
#include <cmath>
#include <random>
using namespace std;

#define VALUENAME(a) #a

//A function to allocate memory for a vector, given its dimension as input, populate it with random integers in [-500, 500] and return it appropriately
int* allocateVector(int size);
//A function to print the elements of a given vector.
void printElements(int* a, int size, int name);
//A function to compute the 𝐿2-norm of a given vector.
float l2Normal(int* vector, int size);
//A function to receive two vectors and return the cosine similarity between them.
float cosineSimularity(int* vector1, int* vector2,float V1norm, float V2norm, int size);
//This function must utilize the other function for computing norms.

int main(){
    int size;
    cout << "Enter the number of elements in vectors : ";
    cin >> size; 

    int name = 1;
    int* v1 = allocateVector(size);
    printElements(v1, size, name);
    float v1normal = l2Normal(v1, size);

    name++;
    int* v2 = allocateVector(size);
    printElements(v2, size, name);
    float v2normal = l2Normal(v2, size);

    float cosinesim = cosineSimularity(v1, v2, v1normal, v2normal, size);
    cout << "Cosine similarity : " << cosinesim << endl;

    delete[] v1;
    v1 = nullptr;
    delete[] v2;
    v2 = nullptr;

    return 0;
}

int* allocateVector(int size){
    int* vector = new int[size];
    for (int i = 0; i < size; ++i) {
		*(vector + i) = ((rand() % 1000) - 500); 
	}
    return vector;
}

void printElements(int* a, int size, int name){
    cout << "v" << name << " =" << endl;
    for (int i = 0; i < size; ++i) {
		//                                                      cout << "[a+" << i << "] is initialized to " << *(a + i) << endl;
        cout << *(a + i) << " ";
	}
    cout << endl;
}

float l2Normal(int* vector, int size){
    float total = 0;
    for (int i = 0; i < size; ++i) {
		total += pow(*(vector + i), 2);
	}
    total = sqrt(total);
    cout << "L2 norm : "<< total << endl;
    return total;
}

float cosineSimularity(int* vector1, int* vector2,float V1norm, float V2norm, int size){
    int* holdvector = new int[size];
    for(int i = 0; i < size; ++i) {
		*(holdvector + i) = *(vector1 + i) * *(vector2 + i);
	}

    float sumOfVectors = 0;

    for(int i = 0; i < size; ++i){
        sumOfVectors += *(holdvector + i);
    }
    delete[] holdvector;
    holdvector = nullptr;

    //float cosinSimularity = (sumOfVectors)/(V1norm * V2norm);
    return (sumOfVectors)/(V1norm * V2norm);

}
