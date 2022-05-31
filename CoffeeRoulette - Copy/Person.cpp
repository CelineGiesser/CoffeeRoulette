#include "Person.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

//Constructor, destructor, copy and move constructor and assignement op.
Person::Person(){}
Person::Person(int personNb, std::string firstName, std::string lastName)//, std::vector<Person> pastCoffees)
    : m_personNb(personNb), m_firstName(firstName), m_lastName(lastName) {
    m_pastCoffeesNb={};} //, m_pastCoffees(pastCoffees) {}
Person::~Person(){}
Person::Person(const Person &source){
    m_personNb=source.m_personNb;
    m_firstName=source.m_firstName; 
    m_lastName=source.m_lastName;
    m_pastCoffeesNb=source.m_pastCoffeesNb;
    m_participate=source.m_participate;}
Person &Person::operator=(const Person &source){
    if (this==&source) return *this;
    m_pastCoffeesNb.clear();
    m_personNb=source.m_personNb;
    m_firstName=source.m_firstName;
    m_lastName=source.m_lastName;
    m_pastCoffeesNb=source.m_pastCoffeesNb;
    m_participate=source.m_participate;}
Person::Person(Person &&source){
    m_personNb=source.m_personNb;
    m_firstName=source.m_firstName; 
    m_lastName=source.m_lastName;
    m_pastCoffeesNb=source.m_pastCoffeesNb;
    m_participate=source.m_participate;
    source.m_pastCoffeesNb.clear();}
Person &Person::operator=(Person &&source){
    if (this==&source) return *this;
    m_pastCoffeesNb.clear();
    m_personNb=source.m_personNb;
    m_firstName=source.m_firstName; 
    m_lastName=source.m_lastName;
    m_pastCoffeesNb=source.m_pastCoffeesNb;
    m_participate=source.m_participate;
    source.m_pastCoffeesNb.clear();}

//Setter and getter
void Person::setPastCoffeesNb(std::vector<int> &&pastCoffeesNb){
    m_pastCoffeesNb=std::move(pastCoffeesNb);};
void Person::setParticipate(bool participate){
    m_participate=participate;};
void Person::addPastCoffeesNb(int number){
    m_pastCoffeesNb.emplace_back(number);};
int Person::getNumber() const {return m_personNb;};
std::string Person::getFirstName() const {return m_firstName;};
std::string Person::getLastName() const {return m_lastName;};
std::vector<int> Person::getPastCoffeesNb(){return m_pastCoffeesNb;}
bool Person::getParticipate() const {return m_participate;};

/*std::istringstream &operator>>(std::istringstream& is, Person person){
    is >> person.m_personNb >> person.m_firstName >> person.m_lastName;
    return is;};*/