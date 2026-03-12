#include <string>

class Car{
    private:
    std::string make_;
    std::string model_;
    int year_;
    double speed_;
    public:
    Car(const std::string& make, const std::string& model, const int& year, const double& speed) : make_(make), model_(model), year_(year), speed_(speed){}
    double getSpeed();
    void changeSpeed(const int& new_speed);
    void accelerate(const double& amount_);
};