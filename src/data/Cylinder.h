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
    Cylinder(int t_TeamNumber, Data *t_Data);
    ~Cylinder();
    void makeBackface(std::vector<GLfloat>&) const;
};



