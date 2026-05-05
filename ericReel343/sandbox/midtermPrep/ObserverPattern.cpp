//observer pattern
//making something that changes when stuff changes..?
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct IceCreamEvaluator{
    virtual void evaluate(string flavor) = 0;
};

//virtual methods, when the implementation is called, it will call the override method.
//you dont have to have the virtual on the second one, in fact you don't even need the override.
//it's still useful to make sure you are overriding the correct method name
struct ElsaEvaluator : public IceCreamEvaluator{
    void evaluate(string flavor) override{
        if(flavor == "mint"){
            cout << "Yum!\n";
        }else{
        cout << "Yuck!\n";
        }
    }
};

struct ReelEvaluator : public IceCreamEvaluator{
    void evaluate(string flavor) override{
        if(flavor != "mint"){
            cout << "Yum!\n";
        }else{
        cout << "Yuck!\n";
        }
    }
};




void evaluate(vector<string>& flavors, IceCreamEvaluator& eval){
    for(string flavor : flavors){
        eval.evaluate(flavor);
    }
}
void demoEvaluator(){
    vector<string> flavors = {"fish", "corn", "chili", "mint", "cheese"};
    ElsaEvaluator elsa;
    evaluate(flavors, elsa); 
    
    cout << endl;
    ReelEvaluator reel;
    evaluate(flavors, reel);
}

int main(){
    demoEvaluator();
    return 0;
}