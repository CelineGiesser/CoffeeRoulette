#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm> 
#include "Person.h"

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
    else std::cout << "Error opening "<<namesListFile;
    return listOfPersons;
};

std::vector<Person> readAnswersFile(const std::string &answersFile, std::vector<Person> &listOfPersons){
    std::ifstream input(answersFile);
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
    else std::cout << "Error opening "<<answersFile;
    return listOfPersons;
};

int generateRandom(int max){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, max);
    return distr(gen);
}

std::vector<Person> generateGroup(std::vector<Person> &listOfPersons){
    std::vector<Person> listOfPersonByGroup{};
    std::vector<int> personsParticipatingNb{};
    for (std::size_t i=0; i<listOfPersons.size(); ++i){
       if (listOfPersons.at(i).getParticipate()==true){
           personsParticipatingNb.emplace_back(int(i));
       }
    }
    std::cout<<personsParticipatingNb.size()<<" persons participating."<<std::endl;
    if (personsParticipatingNb.size()<2) std::cout<<"There is less than two persons participating.";
    while(personsParticipatingNb.size()>=2){
        //Choose randomly one person in the persons participating
        std::size_t j=(std::size_t)generateRandom(personsParticipatingNb.size());
        int iFirstPerson= personsParticipatingNb.at(j);
        std::cout<<"Choosen person nb: "<<personsParticipatingNb.at(j)<<" i "<<iFirstPerson<<std::endl;
        listOfPersonByGroup.emplace_back(listOfPersons.at(std::size_t(iFirstPerson)));
        personsParticipatingNb.erase(personsParticipatingNb.begin()+j);
        //Set which persons have not been met yet
        std::vector<int> personsNotMet(personsParticipatingNb);
        bool oldestMet=false;
        int iOldestMet;
        for (int iMet:listOfPersons.at(std::size_t(iFirstPerson)).m_pastCoffeesNb){
            std::cout<<"Already met person nb: "<<iMet<<" ";
            std::vector<int>::iterator it;
            it = std::find(personsNotMet.begin(),personsNotMet.end(), iMet);
            if (it != personsNotMet.end()){ 
                personsNotMet.erase(it);
                if (oldestMet==false){
                    oldestMet=true;
                    iOldestMet=personsNotMet.at(iMet);
                }
            }
        }
        //Choose randonly a person in the persons not met (if not empty)
        int iSecondPerson;
        if (personsNotMet.size()>0){ 
            std::size_t k;
            k=(std::size_t)generateRandom(personsNotMet.size());
            iSecondPerson=personsNotMet.at(k);
        }
        //If all persons met, take the "oldest" met person
        else {
            iSecondPerson=iOldestMet;}
        personsParticipatingNb.erase(personsParticipatingNb.begin()+iSecondPerson);
        std::cout<< listOfPersons.at(std::size_t(iFirstPerson)).getFirstName() << " meets "
            << listOfPersons.at(std::size_t(iSecondPerson)).getFirstName() <<std::endl;
    }
return listOfPersonByGroup;};


int main()
{
    std::string namesListFile="NamesList.txt";
    std::string answersFile="AnswersList.txt";
    std::vector<Person> listOfPersons=readNamesListFile(namesListFile);
    listOfPersons=readAnswersFile(answersFile,listOfPersons);
    std::vector<Person> listOfPersonByGroup=generateGroup(listOfPersons);
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
