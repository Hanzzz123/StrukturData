#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

typedef struct person {
    std::string name;
    int total_age_in_days;
};

// declare a compare function to compare person a's age with person's by using the total_age_in_days, the smaller
//the total age in days the firstly it gets sorted.
int main()
{
    auto compare = [](person a, person b) { return a.total_age_in_days < b.total_age_in_days; };
    std::vector<person> people;

    //n = how many wifes there is to date. m = how many wifes he can date at the same time
    int n, m;

    //input n and m
    std::cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        std::string name;
        std::string day, month;

        //input waifus name day and month until as  much as n
        std::cin >> name >> day >> month;

        //formula to calculate which waifu is the youngest in days, stoi convertes
        // string to integer
        int total_age_in_days = std::stoi(day) + (std::stoi(month)* 31);

        // struct for the auto compare
        //struct to hold the waifu aswell
        struct person p = {
                name: name,
                total_age_in_days: total_age_in_days
        };

        //push the waifus into a vector
        people.push_back(p);
    }

    //if the waifus he dates at the same is the same as the amount of waifus to date, we output miko
    //top g
    if (n == m) {
        std::cout << "Miko TOP G";
        return 0;
    }

    //This sorts the waifu ascendingly based on the compare function
    std::sort(people.begin(), people.end(), compare);

    //This acceses the m-th waifu he can date
    std::cout << "Waifu selanjutnya adalah " << people[m].name << " chan";

    return 0;
}