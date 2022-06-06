#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Person {
public:
    //Constructor, destructor, copy and move constructor and assignement
    Person();
    Person(std::istringstream &linestream);
	Person(int personNb, std::string firstName, std::string lastName); //, std::vector<Person> pastCoffees);
    ~Person();
    Person(const Person &source);
    Person &operator=(const Person &source);
    Person(Person &&source);
    Person &operator=(Person &&source);

    //Setter and getter
    void setPastCoffeesNb(std::vector<int> &&pastCoffeesNb);
    void setParticipate(bool participate);
    void addPastCoffeesNb(int number);
    int getNumber() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::vector<int> getPastCoffeesNb();
    bool getParticipate() const;
    bool compareNames(std::string& firstName,std::string& lastName);
    void outputAll(std::ofstream &output, const int &nMaxHistory);
    
private:
    int m_personNb;
    std::string m_firstName;
    std::string m_lastName;
    std::vector<int> m_pastCoffeesNb;
    bool m_participate=false;
};