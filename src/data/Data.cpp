//
// Created by Emilien Lemaire on 27/11/2019.
//
#include "Data.h"


Data::Data(const std::string& t_Path)
{
    Log::Debug("Projet IGSD", "Data constructing");

    //On récupère le fichier de données.
    std::ifstream file(t_Path);


    if (!file.good()){
        Log::Error("Projet IGSD", "The file " + t_Path + " couldn't be open");
        std::exit(EXIT_FAILURE);
    }

    std::string line;
    char comma = ',';

    GLuint team = 0;

    while (std::getline(file, line)){
        std::stringstream iss;
        iss << line;
        std::string column;
        std::vector<Day, std::allocator<Day>> days(cst::NB_DAYS);
        //On ignore la première colonne;
        std::getline(iss, column, comma);
        for (int i = 0; i < cst::NB_DAYS; ++i) {
            Day day{};

            //On récupère le rang
            std::getline(iss, column, comma);
            day.rank = std::stoi(column);

            //On récupère les points
            std::getline(iss, column, comma);
            day.points = std::stoi(column);

            //On ignore le reste des données pour l'instant
            std::getline(iss, column, comma);
            std::getline(iss, column, comma);
            std::getline(iss, column, comma);
            std::getline(iss, column, comma);

            days.at(i) = day;
        }
        m_RanksPoints->at(team) = days;
        team++;
    }
}

std::vector<Day> Data::getTeam(unsigned int t_Team) const {
    return m_RanksPoints->at(t_Team);
}

Data::~Data(){
    delete m_RanksPoints;
    Log::Debug("Projet IGSD", "Data destroyed");
}
