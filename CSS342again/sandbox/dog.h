#include <string>
class Dog{
    private:
    std::string color_;
    int height_;
    public:
    //constructor
    Dog(const std::string& color = "brown", int height = 3) : color_(color), height_(height){} //changed it slightly, added '= value'
};