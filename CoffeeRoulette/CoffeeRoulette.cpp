#include "Person.h"
#include "ListOfPersons.h"

int main()
{
    //File names
    std::string namesListFile="NamesList.txt";  //Optional file with names (first and last) and a row of numbers of persons already met (history)
    std::string participantsFile="ParticipantsList.txt"; //Obligatory file with names (first and last) and a boolean value, which is Yes: if the person wants to participate
    std::string outputFile="GroupList.txt";  //Output files with the groups of persons
    
    //Initiate a list of persons (read files)
    ListOfPersons listOfPersons(namesListFile,participantsFile);

    //Generate groups
    ListOfPersons listOfPersonByGroup=listOfPersons.generateGroup();

    //Write files
    listOfPersons.writeNamesListFile(namesListFile);
    listOfPersonByGroup.writeGroupsFile(outputFile);
    return 0;
}
