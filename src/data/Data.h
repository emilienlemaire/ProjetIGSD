#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Log/Log.h>

#include <constants.h>


class Data {
private:
    GLfloat m_Width;
    GLfloat m_Height;
    std::vector<std::vector<Day>> *m_RanksPoints = new std::vector<std::vector<Day>>(NB_TEAMS);
public:
    Data(const std::string& path, GLfloat t_Width, GLfloat t_Height);
    ~Data();

    std::vector<Day> *getTeam(GLuint team) const;
};
