#pragma once

#include <string>
#include <vector>

class Person {
public:
    //Constructor, destructor, copy and move constructor and assignement
	Person(std::string firstName, std::string lastName); //, std::vector<Person> pastCoffees);
    ~Person();
    Person(const Person &source);
    Person &operator=(const Person &source);
    Person(Person &&source);
    Person &operator=(Person &&source);

    //Setter and getter
    void setPastCoffeesNb(std::vector<int> &&pastCoffeesNb);
    void setParticipate(bool participate);
    std::string getFirstName() const;
    std::string getLastName() const;
    std::vector<int> getPastCoffeesNb();
    bool getParticipate() const;

    //Vector of nb representing the persons already met
   std::vector<int> m_pastCoffeesNb; 
        
private:
    std::string m_firstName;
    std::string m_lastName;
    //std::vector<int> m_pastCoffeesNb;
    bool m_participate=false;
};