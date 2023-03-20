#include "Person.h"
#include "ListOfPersons.h"

int main()
{
    //File names
    std::string namesListFile="NamesList.txt";  //Optional file with names (first and last) and a row of numbers of persons already met (history)
<<<<<<< HEAD
    std::string participantsFile="answers_CR.txt"; //Obligatory file generated from gmail with names (after "From:" first, last and email)
=======
    std::string participantsFile="ParticipantsList.txt"; //Obligatory file with names (first and last) and a boolean value, which is Yes: if the person wants to participate
>>>>>>> 451b0d57d518958c6cb958a0a7fb098dace153a1
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
