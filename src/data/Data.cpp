//
// Created by Emilien Lemaire on 27/11/2019.
//
#include "Data.h"


Data::Data(const std::string& path)
{
    Log::Debug("Data constructing");
    std::ifstream file(path);

    if (!file.good()){
        Log::Error("The file " + path + " couldn't be open");
        std::exit(EXIT_FAILURE);
    }

    std::string line;
    char comma = ',';

    GLuint team = 0;

    while (std::getline(file, line)){
        std::stringstream iss;
        iss << line;
        std::string column;
        std::vector<Day, std::allocator<Day>> days(cst::nbDays);
        //On ignore la première ligne;
        std::getline(iss, column, comma);
        for (int i = 0; i < cst::nbDays; ++i) {
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

std::vector<Day> Data::getTeam(GLuint team) const {
    return m_RanksPoints->at(team);
}

Data::~Data(){
    delete m_RanksPoints;
    Log::Debug("Data destructed");
}
