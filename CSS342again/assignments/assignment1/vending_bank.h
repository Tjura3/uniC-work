#ifndef VENDING_BANK_H_
#define VENDING_BANK_H_
#include <string>
#include <vector>
class VendingBank
{
public:
    VendingBank();
    VendingBank(int id);
    // getters-setters
    int id() const;
    int input_currency() const;
    // FILL IN FURTHER PUBLIC FUNCTIONS HERE
    void user_input();
    void get_item();
    void return_change();
    void refund_change();
    void clear_data();
    //maintnence panel for adding items
    void item_maintnence();
    void enjoy();
    bool out_of_item();

private:
    // id_ is a unique identifier for the VendingBank
    // much like a serial number
    int id_;
    // FILL IN FURTHER DATA MEMBERS HERE
    int total_currency;
    std::vector<int> item_location;
    
};
#endif