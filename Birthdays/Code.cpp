#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Date{
    private:
        // member function number_of_days returns the number of days of month by number of month and year
        int number_of_days(int m, int y){
            if (m == 2){
                if (is_leap(y)){
                    return 29;
                } else{
                    return 28;
                }
            } else if (m == 4 || m == 6 || m == 9 || m == 11){
                return 30;
            } else{
                return 31;
            }
        }
        // member function is_leap checks if year is leap or not
        bool is_leap(int y){
            if ((y % 4 == 0 && y % 100 != 0) ||  (y % 400 == 0)){
                return true;
            }
            return false;
        }
    public:
        int d;
        int m;
        int y;
        Date(int d, int m, int y){
            this->d = d;
            this->m = m;
            this->y = y;
        }
        // member function isValid checks if provided date is correct
        bool isValid(){
            if (this->m > 12 || this->m < 1){
                return false;
            }
            if (this->d > number_of_days(this->m, this->y) || this->d < 1){
                return false;
            }
            return true;
        }
        // function operator- returns the difference in days between two dates
        int operator-(Date date2){
            int days1 = 0;
            int days2 = 0;
            // Summ all days from the years of the date
            for (int i = 1; i < this->y; ++i){
                if (is_leap(i)){
                    days1 += 366;
                } else{
                    days1 += 365;
                }
            }
            for (int i = 1; i < date2.y; ++i){
                if (is_leap(i)){
                    days2 += 366;
                } else{
                    days2 += 365;
                }
            }
            // Summ all days from the monthes of the date
            for (int i = 1; i < this->m; ++i){
                days1 += number_of_days(i, this->y);
            }
            for (int i = 1; i < date2.m; ++i){
                days2 += number_of_days(i, date2.y);
            }
            days1 += this->d;
            days2 += date2.d;
            return days1 - days2;
        }
};

bool cmp(Date date1, Date date2){
    return ((date2 - date1) > 0);
}

int main() {
    int d1, m1, y1, d2, m2, y2, d3, m3, y3;
    cin >> d1 >> m1 >> y1 >> d2 >> m2 >> y2 >> d3 >> m3 >> y3;
    
    Date a(d1, m1, y1);
    Date b(d2, m2, y2);
    Date c(d3, m3, y3);

    vector<Date> v = {a, b, c};
    
    if(!a.isValid() || !b.isValid() || !c.isValid()) {
        cout << "Invalid Input" << endl; 
        return 0;
    }
 
    // define your comparator function globally
    sort(v.begin(), v.end(), cmp); 
    
    // overload the - operator for this to work
    cout << v[2] - v[0] << endl;
    return 0;
}