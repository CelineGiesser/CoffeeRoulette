#include "Person.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

//Constructor, destructor, copy and move constructor and assignement op.
Person::Person(){}
Person::Person(std::istringstream &linestream){
    linestream >> m_personNb >> m_firstName >> m_lastName >> m_email;
    int number;
    while (linestream >> number){
        m_pastCoffeesNb.emplace_back(number);}}
Person::Person(int personNb, std::string firstName, std::string lastName,std::string email)//, std::vector<Person> pastCoffees)
    : m_personNb(personNb), m_firstName(firstName), m_lastName(lastName), m_email(email) {
    m_pastCoffeesNb={};} //, m_pastCoffees(pastCoffees) {}
Person::~Person(){m_pastCoffeesNb.clear();}
Person::Person(const Person &source){
    m_personNb=source.m_personNb;
    m_firstName=source.m_firstName; 
    m_lastName=source.m_lastName;
    m_email=source.m_email;
    m_pastCoffeesNb=source.m_pastCoffeesNb;
    m_participate=source.m_participate;}
Person &Person::operator=(const Person &source){
    if (this==&source) return *this;
    m_pastCoffeesNb.clear();
    m_personNb=source.m_personNb;
    m_firstName=source.m_firstName;
    m_lastName=source.m_lastName;
    m_email=source.m_email;
    m_pastCoffeesNb=source.m_pastCoffeesNb;
    m_participate=source.m_participate;}
Person::Person(Person &&source){
    m_personNb=source.m_personNb;
    m_firstName=source.m_firstName; 
    m_lastName=source.m_lastName;
    m_email=source.m_email;
    m_pastCoffeesNb=source.m_pastCoffeesNb;
    m_participate=source.m_participate;
    source.m_pastCoffeesNb.clear();}
Person &Person::operator=(Person &&source){
    if (this==&source) return *this;
    m_pastCoffeesNb.clear();
    m_personNb=source.m_personNb;
    m_firstName=source.m_firstName; 
    m_lastName=source.m_lastName;
    m_email=source.m_email;
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
std::string Person::getEmail() const {return m_email;};
std::vector<int> Person::getPastCoffeesNb(){return m_pastCoffeesNb;}
bool Person::getParticipate() const {return m_participate;};
bool Person::compareNames(std::string& firstName,std::string& lastName){
    if ((m_firstName==firstName)&&(m_lastName==lastName)){
        return true;}
    else return false;
};

//Output the number, names and a list of numbers of persons already met.
//The length of list is limited by nMaxHistory to avoid that the persons meet 
//in the same row (given by the list) once they have met all the persons.
void Person::outputAll(std::ofstream &output, const int &nMaxHistory){
    output<< m_personNb <<" ";
    output<< m_firstName <<" ";
    output<< m_lastName <<" ";
<<<<<<< HEAD
    output<< m_email <<" ";
=======
>>>>>>> 451b0d57d518958c6cb958a0a7fb098dace153a1
    int nPastCoffees=m_pastCoffeesNb.size();
    if (nPastCoffees<nMaxHistory){
        for(int i=0; i<nPastCoffees;i++){
            output<<m_pastCoffeesNb.at(i)<<" ";};
    }
    else{
        for(int i=(nPastCoffees-3); i<nPastCoffees;i++){
            output<<m_pastCoffeesNb.at(i)<<" ";};
    }
    output<<std::endl;
}
