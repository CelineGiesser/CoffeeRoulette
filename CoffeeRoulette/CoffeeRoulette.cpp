#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm> 
#include "Person.h"

const int MaxNbOfPersonsInHistory=10;

//Read names (first and last) and a row of numbers of persons already met (history)
//This file is optional
std::vector<Person> readNamesListFile(const std::string namesListFile){
    std::ifstream input(namesListFile);
    std::vector<Person> listOfPersons{};
    if (input.is_open()){
        std::string line;
        while(getline(input,line)){
            std::istringstream linestream(line);
            std::string firstName,lastName;
            linestream >> firstName >> lastName;
            Person person(firstName,lastName);
            listOfPersons.emplace_back(std::move(person));
            int number;
            std::vector<int> listOfNumbers;
            while (linestream >> number){
                listOfNumbers.emplace_back(number);
            }
            listOfPersons.back().setPastCoffeesNb(std::move(listOfNumbers));
        }
    }
    else std::cout << "Cannot open file: "<<namesListFile<<std::endl;
    return listOfPersons;
};

//Read names (first and last) and a boolean value, which is true if the person wants to participate
//This file is obligatory
std::vector<Person> readParticipantsFile(const std::string &participantsFile, std::vector<Person> &listOfPersons){
    std::ifstream input(participantsFile);
    std::vector<Person> listOfAnswers{};
    if (input.is_open()){
        std::string line;
        while(getline(input,line)){
            std::istringstream linestream(line);
            std::string firstName,lastName,partiStr;
            linestream >> firstName >> lastName >> partiStr;
            bool participate=(partiStr=="true") ? true: false;
            bool inList=false;
            for (auto &person : listOfPersons){
                if ((person.getFirstName()==firstName)&&(person.getLastName()==lastName)){
                    person.setParticipate(participate);
                    inList=true;
                    break;
                }
            }
            if (inList==false){
                Person person(firstName,lastName);
                person.setParticipate(participate);
                listOfPersons.emplace_back(std::move(person));}
        }
    }
    else std::cout << "Cannot open file: "<<participantsFile<< ", error "<<std::endl;
    return listOfPersons;
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
std::vector<Person> generateGroup(std::vector<Person> &listOfPersons){
    std::vector<Person> listOfPersonByGroup{};
    //Fill in a vector of participating persons
    std::vector<int> personsParticipatingNb{};
    for (std::size_t i=0; i<listOfPersons.size(); ++i){
       if (listOfPersons.at(i).getParticipate()==true){
           personsParticipatingNb.emplace_back(int(i));
       }
    }
    std::cout<<personsParticipatingNb.size()<<" persons participating."<<std::endl;
    if (personsParticipatingNb.size()<2) std::cout<<"There is less than two persons participating.";
    //Loop over the participating persons
    bool foundOldestMet=false;
    while(personsParticipatingNb.size()>=2){
        //Choose randomly one person in the persons participating
        int j=(int)generateRandom(personsParticipatingNb.size())-1;
        int iFirstPerson= personsParticipatingNb.at(j);
        std::cout<<"Choosen person nb: "<<listOfPersons.at(std::size_t(iFirstPerson)).getFirstName()<<" ("<<iFirstPerson<<")"<<std::endl;
        listOfPersonByGroup.emplace_back(listOfPersons.at(std::size_t(iFirstPerson)));
        personsParticipatingNb.erase(personsParticipatingNb.begin()+j);
        //From the history, set which persons have not been met yet
        std::vector<int> personsNotMet(personsParticipatingNb);
        bool foundOldestMet=false;
        int iOldestMet;
        std::cout<<"Already met : ";
        for (int iMet:listOfPersons.at(std::size_t(iFirstPerson)).m_pastCoffeesNb){
            std::cout <<" "<<listOfPersons.at(std::size_t(iMet)).getFirstName()<<" ("<<iMet<<")"<<", ";
            std::vector<int>::iterator it;
            it = std::find(personsNotMet.begin(),personsNotMet.end(), iMet);
            //for (auto grr:personsNotMet) std::cout<<grr<<" ";
            if (it != personsNotMet.end()){ 
                if (foundOldestMet==false){
                    foundOldestMet=true;
                    //std::cout<<"Oldest met "<< *it <<std::endl;
                    iOldestMet=*it;
                }
                personsNotMet.erase(it);
            }
        }
        std::cout<<std::endl;
        //Choose randonly a person in the persons not met (if not empty)
        int iSecondPerson;
        if (personsNotMet.size()>0){ 
            int k=(int)generateRandom(personsNotMet.size())-1;
            iSecondPerson=personsNotMet.at(k);
        }
        //If all participating persons already met, take the "oldest" met person
        else {
            iSecondPerson=iOldestMet;}
        personsParticipatingNb.erase(std::find(personsParticipatingNb.begin(),personsParticipatingNb.end(), iSecondPerson));
        listOfPersonByGroup.emplace_back(listOfPersons.at(std::size_t(iSecondPerson)));
        //Update the list of persons (nb) already met
        listOfPersons.at(std::size_t(iFirstPerson)).m_pastCoffeesNb.emplace_back(iSecondPerson);
        listOfPersons.at(std::size_t(iSecondPerson)).m_pastCoffeesNb.emplace_back(iFirstPerson);
        if (personsParticipatingNb.size()==1){
            std::size_t iLastPerson=(std::size_t)personsParticipatingNb.at(0);
            listOfPersons.at(std::size_t(iFirstPerson)).m_pastCoffeesNb.emplace_back(iLastPerson);
            listOfPersons.at(std::size_t(iSecondPerson)).m_pastCoffeesNb.emplace_back(iLastPerson);
            listOfPersons.at(std::size_t(iLastPerson)).m_pastCoffeesNb.emplace_back(iFirstPerson);
            listOfPersons.at(std::size_t(iLastPerson)).m_pastCoffeesNb.emplace_back(iSecondPerson);
            listOfPersonByGroup.emplace_back(listOfPersons.at(iLastPerson));
            std::cout<< listOfPersons.at(std::size_t(iFirstPerson)).getFirstName() << " meets "
            << listOfPersons.at(std::size_t(iSecondPerson)).getFirstName()<< " and " 
                << listOfPersons.at(iLastPerson).getFirstName()<<std::endl;}
        else std::cout<< listOfPersons.at(std::size_t(iFirstPerson)).getFirstName() << " meets "
            << listOfPersons.at(std::size_t(iSecondPerson)).getFirstName()<< std::endl;
    }
return listOfPersonByGroup;};

//Write names (first and last) and a row of numbers of persons already met (history)
void writeNamesListFile(const std::string namesListFile, std::vector<Person> &listOfPersons){
    std::ofstream output(namesListFile);
    if (output.is_open()){
        for (auto &person:listOfPersons){
            output<< person.getFirstName()<<" ";
            output<< person.getLastName()<<" ";
            while (person.m_pastCoffeesNb.size()>MaxNbOfPersonsInHistory) person.m_pastCoffeesNb.erase(person.m_pastCoffeesNb.begin());
            for(int &i:person.m_pastCoffeesNb) output<<i<<" ";
            output<<std::endl;
        }
    }
    else std::cout << "Error opening "<<namesListFile;
};

//Write the groups of persons
void writeOutputFile(const std::string &outputFile, std::vector<Person> &listOfPersonByGroup){
    std::ofstream output(outputFile);
    if (output.is_open()){
        int i=1;
        for (auto &person:listOfPersonByGroup){
            output<< person.getFirstName()<<" ";
            output<< person.getLastName()<<" ";
            if (i%2==0){ 
                if (i==listOfPersonByGroup.size()-1) output<<"and ";
                else output<<std::endl;
            }
            if ((i%2==1) && (i!=listOfPersonByGroup.size())) output<<"meets ";
            i++;
        }
    }
    else std::cout << "Error opening "<<outputFile;
}


int main()
{
    //File names
    std::string namesListFile="NamesList.txt";  //Optional file with names (first and last) and a row of numbers of persons already met (history)
    std::string participantsFile="ParticipantsList.txt"; //Obligatory file with names (first and last) and a boolean value, which is true if the person wants to participate
    std::string outputFile="GroupList.txt";  //Output files with the groups of persons
    //Read files
    std::vector<Person> listOfPersons=readNamesListFile(namesListFile);
    listOfPersons=readParticipantsFile(participantsFile,listOfPersons);
    //Generate groups
    std::vector<Person> listOfPersonByGroup=generateGroup(listOfPersons);
    //Write files
    writeNamesListFile(namesListFile, listOfPersons);
    writeOutputFile(outputFile, listOfPersonByGroup);
    return 0;
}
