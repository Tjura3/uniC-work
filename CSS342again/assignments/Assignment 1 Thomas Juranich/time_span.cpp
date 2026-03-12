#include "time_span.h"
#include <iostream>
#include <cmath>

using namespace std;

TimeSpan::TimeSpan(float hours, float minutes, float seconds){ //it says in the announcement that all values will be integers, but one of the tests has a float input.
    counter_ = 0;
    float temp_ = 0;
    temp_ += hours*3600;
    temp_ += minutes*60;
    temp_ += seconds;
    counter_ += static_cast<int>(temp_);
}

//I DID ALL OF THE ABOVE AND MADE SURE TO USE DEFULTS all.... for it to not matter in the end.......
//I need multiple constructors anyways........
//man...
TimeSpan::TimeSpan(float minutes, float seconds){ 
    counter_ = 0;
    float temp_ = 0;
    temp_ += minutes*60;
    temp_ += seconds;
    counter_ += static_cast<int>(temp_);
    
}
TimeSpan::TimeSpan(float seconds){ 
    counter_ = 0;
    counter_ += static_cast<int>(seconds);
}
TimeSpan::TimeSpan(){ 
    counter_ = 0;
}



int TimeSpan::hours() const{
    return counter_ / 3600;
}

int TimeSpan::minutes() const{
    return counter_ % 3600 / 60;
}

int TimeSpan::seconds() const{
    return counter_ % 3600 % 60;
}

int TimeSpan::getRawCount() const{
    return counter_;
}

TimeSpan TimeSpan::operator+(const TimeSpan& t2) const{
    return TimeSpan(hours() + t2.hours(), minutes() + t2.minutes(), seconds() + t2.seconds());
}
TimeSpan& TimeSpan::operator+=(const TimeSpan& t2){
    counter_ += t2.getRawCount();
    return *this;
} 

TimeSpan TimeSpan::operator-(const TimeSpan& t2) const{
    return TimeSpan(hours() - t2.hours(), minutes() - t2.minutes(), seconds() - t2.seconds());
}
TimeSpan TimeSpan::operator-() const{
    return TimeSpan(-hours(), -minutes(), -seconds());
}
TimeSpan& TimeSpan::operator-=(const TimeSpan& t2){
    counter_ -= t2.getRawCount();
    return *this;
}

bool TimeSpan::operator==(const TimeSpan& t2) const{
    return counter_ == t2.getRawCount();
}
bool TimeSpan::operator!=(const TimeSpan& t2) const{
    return counter_ != t2.getRawCount();
}
bool TimeSpan::operator<(const TimeSpan& t2) const{
    return counter_ < t2.getRawCount();
}
bool TimeSpan::operator<=(const TimeSpan& t2) const{
    return counter_ <= t2.getRawCount();
}
bool TimeSpan::operator>(const TimeSpan& t2) const{
    return counter_ > t2.getRawCount();
}
bool TimeSpan::operator>=(const TimeSpan& t2) const{
    return counter_ >= t2.getRawCount();
}

ostream& operator<<(ostream& out, const TimeSpan& t_span){
    out << "Hours: " << t_span.hours() << ", Minutes: " << t_span.minutes() << ", Seconds: " <<t_span.seconds() << endl;
    return out;
}
istream& operator>>(istream &in, TimeSpan& t_span){
    //inputs hours, minutes, seconds.
    int h_,m_,s_;
    in >> h_ >> m_ >> s_;
    t_span.counter_ += h_*3600;
    t_span.counter_ += m_*60;
    t_span.counter_ += s_;
    return in;
}
