#include "Person.h"
#include <string>
#include <vector>
#include <iostream>

//Constructor, destructor, copy and move constructor and assignement op.
Person::Person(std::string firstName, std::string lastName)//, std::vector<Person> pastCoffees)
      : m_firstName(firstName), m_lastName(lastName) {m_pastCoffeesNb.emplace_back(10000000);} //, m_pastCoffees(pastCoffees) {}
Person::~Person(){}
Person::Person(const Person &source){
    m_firstName=source.m_firstName; 
    m_lastName=source.m_lastName;
    m_pastCoffeesNb=source.m_pastCoffeesNb;
    m_participate=source.m_participate;}
Person &Person::operator=(const Person &source){
    if (this==&source) return *this;
    m_pastCoffeesNb.clear();
    m_firstName=source.m_firstName;
    m_lastName=source.m_lastName;
    m_pastCoffeesNb=source.m_pastCoffeesNb;
    m_participate=source.m_participate;}
Person::Person(Person &&source){
    m_firstName=source.m_firstName; 
    m_lastName=source.m_lastName;
    m_pastCoffeesNb=source.m_pastCoffeesNb;
    m_participate=source.m_participate;
    source.m_pastCoffeesNb.clear();}
Person &Person::operator=(Person &&source){
    if (this==&source) return *this;
    m_pastCoffeesNb.clear();
    m_firstName=source.m_firstName; 
    m_lastName=source.m_lastName;
    m_pastCoffeesNb=source.m_pastCoffeesNb;
    m_participate=source.m_participate;
    source.m_pastCoffeesNb.clear();}

void Person::setPastCoffeesNb(std::vector<int> &&pastCoffeesNb){
    m_pastCoffeesNb=std::move(pastCoffeesNb);};
void Person::setParticipate(bool &participate){
    m_participate=participate;};
const std::string Person::getFirstName() {return m_firstName;};
const std::string Person::getLastName() {return m_lastName;};
//std::vector<int> getPastCoffeesNb(){return m_pastCoffeesNb;}
const bool Person::getParticipate(){return m_participate;};