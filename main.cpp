#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include "json.hpp"
using json = nlohmann::json;

std::string prepareWord(std::string& mot) {
    std::string accents[] = {"é", "è", "ê", "ë", "à", "â", "î", "ï", "ô", "ù", "û", "ç"};
    std::string sansAccents[] = {"e", "e", "e", "e", "a", "a", "i", "i", "o", "u", "u", "c"};

    for (int i = 0; i < 12; i++) {
        size_t pos = 0;
        while ((pos = mot.find(accents[i], pos)) != std::string::npos) {
            mot.replace(pos, accents[i].length(), sansAccents[i]);
        }
    }

    for (int i = 0; i < mot.length(); i++) {
        mot[i] = toupper(mot[i]);
    }
    return mot;
}

int main() {
    int life = 10;
    int attempt = 0;

    json JSONdata;
    std::ifstream file("mots.json");

    if (!file.is_open())
    {
        std::cout << "Error : Unable to open the dictionary file !" << std::endl;
        return 1;
    }

    file >> JSONdata;

    std::vector<std::string> dictionary = JSONdata.get<std::vector<std::string>>();


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long> dis(0, dictionary.size() - 1);

    std::string name = dictionary[dis(gen)];
    name = prepareWord(name);
    //std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    int Letter = name.length();
    std::string undercore;

     for (int i = 0; i < Letter; i++)
     {
         undercore.append("_");
     }

    while (life > 0)
    {
    std::cout << "Life : " << life << std::endl;
    std::cout << "Attempt : " << attempt << std::endl;
    std::cout << undercore << std::endl;

    std::cout << "Enter a letter :"<< std::endl;
    char Enter;
    std::cin >> Enter;
    Enter = toupper(Enter);
    if (name.find_first_of(Enter) != std::string::npos)
    {
        for (int i = 0; i < name.length(); i++)
        {
            if (name[i] == Enter)
            {
             undercore[i] = name[i];
            }
        }

        if (undercore.find("_") == std::string::npos)
        {
            std::cout << "You Won ! Attempt : " << attempt << std::endl;
            std::cout << "The word was " << name << std::endl;
            break;
        }
    }
    else
    {
        life--;
    }
        attempt++;
    }

    std::string wait;

    if (life == 0)
    {
    std::cout << "Game Over ! the word was " << name << std::endl;
    std::cout << "Attempt : " << attempt << std::endl;
    std::cin >> wait;
    }

    return 0;
}