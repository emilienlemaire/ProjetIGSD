#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <42ngine/42ngine.h>

#include <constants.h>


class Data {
private:
    std::vector<std::vector<Day>> *m_RanksPoints = new std::vector<std::vector<Day>>(cst::nbTeams);
public:
    explicit Data(const std::string& T_Path);
    ~Data();

    std::vector<Day> getTeam(GLuint t_Team) const;
};
