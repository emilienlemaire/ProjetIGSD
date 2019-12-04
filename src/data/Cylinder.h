//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once


#include "Data.h"

class Cylinder {
private:
    GLuint m_TeamNumber;
    Data* m_Data;
public:
    Cylinder(GLuint t_TeamNumber, Data *t_Data);
    std::vector<GLfloat> makeBackface();
};



