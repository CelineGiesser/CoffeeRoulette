#pragma once

#include <string>
#include <vector>
#include "Person.h"

class ListOfPersons {
public:
    //Constructor, destructor, copy and move constructor and assignement
    ListOfPersons();
	ListOfPersons(const std::string &namesListFile,const std::string &participantsFile);
    ~ListOfPersons();
    ListOfPersons(const ListOfPersons &source);
    ListOfPersons &operator=(const ListOfPersons &source);
    ListOfPersons(ListOfPersons &&source);
    ListOfPersons &operator=(ListOfPersons &&source);

    //Setter and getter
    //void setListOfPersons(std::vector<Persons> listOfPersons);
    std::vector<Person> getListOfPersons();
    void addPerson(Person &person);

    void readNamesListFile(const std::string &namesListFile);
    void readParticipantsFile(const std::string &participantsFile);
    ListOfPersons generateGroup();
    void writeNamesListFile(const std::string namesListFile);
    void writeGroupsFile(const std::string &outputFile);
        
private:
    std::vector<Person> m_listOfPersons;
};