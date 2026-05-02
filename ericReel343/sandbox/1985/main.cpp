#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "SimpleSAXParser.h"
#include "data.h"
using namespace std;
class PopulationObserver : public SAXParserEventHandler{
    private:
    vector<string> path;
    vector<int> population;

    string formatPath() {
        string fullPath = "";
        for (int i = 0; i < path.size(); i++) {
            fullPath += path[i] + "/";
        }
        return fullPath;
    }

    public:
    void startElement(const string& name, map<string, string>& datamap){
        if (datamap.count("name")) {
            path.push_back(datamap["name"]);
        }

        int pop = 0;
        if (datamap.count("population")) {
            pop = std::stoi(datamap["population"]);
        }

        population.push_back(pop);
    }
    void endElement(const std::string& name){
        if (population.empty()) return;
        int currentTotal = population.back();
        string currentPath = formatPath();

        cout << currentPath << " : " << currentTotal << endl;
        population.pop_back();
        if (!population.empty()) {
            population.back() += currentTotal;
        }
        if (!path.empty()) {
            path.pop_back();
        }
    }

    void characters(const std::string& data) override {
        (void)data;
    }
};

int main(){
    PopulationObserver observer;
    parseXML(REGIONAL_DATA, observer); 
    return 0;
}