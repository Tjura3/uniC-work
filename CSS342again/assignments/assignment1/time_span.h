#ifndef TIME_SPAN_H_
#define TIME_SPAN_H_
#include <iostream>

class TimeSpan
{
    private:
    int counter_;
    public:
    //TimeSpan(float hours = 0.0f, float minutes = 0.0f, float seconds = 0.0f);  //this was the defult that worked...
    TimeSpan(float hours, float minutes, float seconds);
    TimeSpan(float minutes, float seconds);
    TimeSpan(float seconds);
    TimeSpan();

    
    int hours() const;                                  // return the number of hours as an int
    int minutes() const;                                // return the number of minutes as an int
    int seconds() const;                                // return the number of seconds as an int
    int getRawCount() const;
    void set_time(int hours, int minutes, int seconds); // set hours, minutes, seconds
    //=, !=, <, <=, >, >=. The class must implement += and -= assignment statements as well.
    TimeSpan operator+(const TimeSpan& t2) const;
    TimeSpan& operator+=(const TimeSpan& t2);
    TimeSpan operator-(const TimeSpan& t2) const;
    TimeSpan operator-() const;
    TimeSpan& operator-=(const TimeSpan& t2);
    
    bool operator==(const TimeSpan& t2) const;
    bool operator!=(const TimeSpan& t2) const;
    bool operator<(const TimeSpan& t2) const;
    bool operator<=(const TimeSpan& t2) const;
    bool operator>(const TimeSpan& t2) const; 
    bool operator>=(const TimeSpan& t2) const;

    friend std::ostream& operator<<(std::ostream& out, const TimeSpan& t_span);
    friend std::istream& operator>>(std::istream &in, TimeSpan& c);
};
#endif