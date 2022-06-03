#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <algorithm> 
#include "Person.h"
#include "ListOfPersons.h"

//Constructor, destructor, copy and move constructor and assignement op.
ListOfPersons::ListOfPersons(){}
ListOfPersons::ListOfPersons(const std::string &namesListFile,const std::string &participantsFile){
    ListOfPersons::readNamesListFile(namesListFile);
    ListOfPersons::readParticipantsFile(participantsFile);}
ListOfPersons::~ListOfPersons(){}
ListOfPersons::ListOfPersons(const ListOfPersons &source){
m_listOfPersons=source.m_listOfPersons;}
ListOfPersons &ListOfPersons::operator=(const ListOfPersons &source){
    if (this==&source) return *this;
    m_listOfPersons.clear();
    m_listOfPersons=source.m_listOfPersons;}
ListOfPersons::ListOfPersons(ListOfPersons &&source){
    m_listOfPersons=source.m_listOfPersons;
    source.m_listOfPersons.clear();}
ListOfPersons &ListOfPersons::operator=(ListOfPersons &&source){
    if (this==&source) return *this;
    m_listOfPersons.clear();
    m_listOfPersons=source.m_listOfPersons;
    source.m_listOfPersons.clear();}


//Setter and getter
std::vector<Person> ListOfPersons::getListOfPersons() {return m_listOfPersons;};
void ListOfPersons::addPerson(Person &person){m_listOfPersons.emplace_back(person);};

//Read names (first and last) and a row of numbers of persons already met (history)
//This file is optional
void ListOfPersons::readNamesListFile(const std::string &namesListFile){
    std::ifstream input(namesListFile);
    if (!input.is_open()) std::cout << "Cannot open optional file: "<<namesListFile<<std::endl;
    else{
        std::string line;
        while(getline(input,line)){
            std::istringstream linestream(line);
            Person person(linestream);
            m_listOfPersons.emplace_back(std::move(person));     
        }
    }
};

//Read names (first and last) and a boolean value, which is true if the person wants to participate
//This file is obligatory
void ListOfPersons::readParticipantsFile(const std::string &participantsFile){
    std::ifstream input(participantsFile);
    std::vector<Person> listOfAnswers{};
    if (!input.is_open()) std::cout << "Cannot open file: "<<participantsFile<< ", error "<<std::endl;
    else{
        std::string line;
        int personNb= (m_listOfPersons.size()>0)? (m_listOfPersons.back().getNumber()+1):1;
        getline(input,line);
        while(getline(input,line)){
            std::replace(line.begin(), line.end(), ';', ' ');
            std::istringstream linestream(line);
            std::string firstName,lastName,partiStr;
            linestream >> lastName >> firstName >> partiStr;
            bool participate=partiStr=="Yes:";
            bool inList=false;
            for (auto &person : m_listOfPersons){
                if (person.compareNames(firstName,lastName)){
                    person.setParticipate(participate);
                    inList=true;
                    break;
                }
            }
            //If the person is not in listOfPersons, he is added at the end
            if (!inList){
                Person person(personNb,firstName,lastName);
                person.setParticipate(participate);
                m_listOfPersons.emplace_back(std::move(person));
                personNb++;}
        }
    }
};

//Generates a random number between 1 and max
int generateRandom(int max){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, max);
    return distr(gen);
}

//Generates random groups of two (ev. three) persons 
//The output is a vector with the two persons groups (last group ev. three) on the row
ListOfPersons ListOfPersons::generateGroup(){
    ListOfPersons listOfPersonByGroup;

    //Fill a vector with the participating persons
    std::vector<int> personsParticipatingNb{};
    for (auto person:m_listOfPersons){
        if (person.getParticipate()) 
            personsParticipatingNb.emplace_back(person.getNumber()-1);}
    std::cout<<personsParticipatingNb.size()<<" persons participating."<<std::endl;
    if (personsParticipatingNb.size()<2) std::cout<<"There is less than two persons participating.";

    //Loop over the participating persons
    bool foundOldestMet=false;
    while(personsParticipatingNb.size()>=2){

        //Choose randomly one person in the persons participating
        //erase the person from the list and add him in the listOfPersonByGroup
        int j=(int)generateRandom(personsParticipatingNb.size())-1;
        int iFirstPerson= personsParticipatingNb.at(j);
        //std::cout<<"Choosen person nb: "<<m_listOfPersons.at(std::size_t(iFirstPerson)).getFirstName()<<" ("<<iFirstPerson<<")"<<std::endl;
        listOfPersonByGroup.addPerson(m_listOfPersons.at(std::size_t(iFirstPerson)));
        personsParticipatingNb.erase(personsParticipatingNb.begin()+j);

        //From the file history, set which persons have not been met yet
        std::vector<int> personsNotMet(personsParticipatingNb);
        bool foundOldestMet=false;
        int iOldestMet; //in case all persons have been met, the "oldest" met is saved
        //std::cout<<"Already met : ";
        for (int iMet:m_listOfPersons.at(std::size_t(iFirstPerson)).getPastCoffeesNb()){
            //std::cout <<" "<<m_listOfPersons.at(std::size_t(iMet)).getFirstName()<<" ("<<iMet<<")"<<", ";
            std::vector<int>::iterator it;
            it = std::find(personsNotMet.begin(),personsNotMet.end(), iMet);
            if (it != personsNotMet.end()){ 
                if (foundOldestMet==false){
                    foundOldestMet=true;
                    iOldestMet=*it;
                }
                personsNotMet.erase(it);
            }
        }
        //std::cout<<std::endl;

        //Choose randomly a person in the list of persons not met (if not empty)
        int iSecondPerson;
        if (personsNotMet.size()>0){ 
            int k=(int)generateRandom(personsNotMet.size())-1;
            iSecondPerson=personsNotMet.at(k);
        }
        //If all participating persons already met, take the "oldest" met person
        else {
            iSecondPerson=iOldestMet;}
        //Erase the second person from the list and add him in the listOfPersonByGroup
        personsParticipatingNb.erase(std::find(personsParticipatingNb.begin(),personsParticipatingNb.end(), iSecondPerson));
        listOfPersonByGroup.addPerson(m_listOfPersons.at(std::size_t(iSecondPerson)));
        
        //Update the list of persons (nb) met
        m_listOfPersons.at(std::size_t(iFirstPerson)).addPastCoffeesNb(iSecondPerson);
        m_listOfPersons.at(std::size_t(iSecondPerson)).addPastCoffeesNb(iFirstPerson);

        //If the number of participating persons is odd, the last group has three persons
        //Update the list of persons (nb) for the last person
        if (personsParticipatingNb.size()==1){
            std::size_t iLastPerson=(std::size_t)personsParticipatingNb.at(0);
            m_listOfPersons.at(std::size_t(iFirstPerson)).addPastCoffeesNb(iLastPerson);
            m_listOfPersons.at(std::size_t(iSecondPerson)).addPastCoffeesNb(iLastPerson);
            m_listOfPersons.at(std::size_t(iLastPerson)).addPastCoffeesNb(iFirstPerson);
            m_listOfPersons.at(std::size_t(iLastPerson)).addPastCoffeesNb(iSecondPerson);
            listOfPersonByGroup.addPerson(m_listOfPersons.at(iLastPerson));

            //Cout
            std::cout<< m_listOfPersons.at(std::size_t(iFirstPerson)).getFirstName() << " meets "
            << m_listOfPersons.at(std::size_t(iSecondPerson)).getFirstName()<< " and " 
                << m_listOfPersons.at(iLastPerson).getFirstName()<<std::endl;}
        else std::cout<< m_listOfPersons.at(std::size_t(iFirstPerson)).getFirstName() << " meets "
            << m_listOfPersons.at(std::size_t(iSecondPerson)).getFirstName()<< std::endl;
    }
return listOfPersonByGroup;};

//Write names (first and last) and a row of numbers of persons already met (history)
void ListOfPersons::writeNamesListFile(const std::string namesListFile){
    std::ofstream output(namesListFile);
    if (!output.is_open()) std::cout << "Error opening "<<namesListFile;
    else{
        for (auto &person:m_listOfPersons){
            int nMax=person.getPastCoffeesNb().size();
            if (nMax>(m_listOfPersons.size()*0.8)) nMax=3;
            person.outputAll(output, nMax);
        }
    }
};

//Write the groups of persons
void ListOfPersons::writeGroupsFile(const std::string &outputFile){
    std::ofstream output(outputFile);
    if (!output.is_open()) std::cout << "Error opening "<<outputFile;
    else{
        int i=1;
        for (auto &person:m_listOfPersons){
            output<< person.getFirstName()<<" ";
            output<< person.getLastName()<<" ";
            if (i%2==0){ 
                if (i==m_listOfPersons.size()-1) output<<"and ";
                else output<<std::endl;
            }
            if ((i%2==1) && (i!=m_listOfPersons.size())) output<<"meets ";
            i++;
        }
    }
}