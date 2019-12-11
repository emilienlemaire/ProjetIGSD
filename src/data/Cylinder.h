//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once


#include "Data.h"

class Cylinder {
private:
    int m_TeamNumber;
    Data* m_Data;
public:
    Cylinder(int t_TeamNumber, Data* t_Data);
    ~Cylinder();
    void makeBackface(std::vector<GLfloat>& t_Backface) const;
    void makeCylinder(std::vector<GLfloat>& t_Cylinder) const;
    void makeNormals(const std::vector<GLfloat>& t_Cylinder, std::vector<GLfloat>& t_OutNormals) const;
};



