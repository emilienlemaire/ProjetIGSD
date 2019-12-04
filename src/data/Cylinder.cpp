//
// Created by Emilien Lemaire on 04/12/2019.
//

#include "Cylinder.h"

Cylinder::Cylinder(GLuint t_TeamNumber, Data *t_Data) : m_TeamNumber(t_TeamNumber), m_Data(t_Data) {}

std::vector<GLfloat> Cylinder::makeBackface() {
    std::vector<GLfloat> backface;

    std::vector<Day> teamData = m_Data->getTeam(m_TeamNumber);

    GLfloat largeur = (cst::f_Width - 50.f) / (cst::nbDays * 2.f);
    GLfloat dx = 50.f;
    for (unsigned long i = 0; i < teamData.size(); ++i) {
        if (i == 20)
            dx += largeur;
        //Triangle 1
        //Bas gauche
        backface.push_back(dx + (2.f * (float)i) * largeur);
        backface.push_back(((19.f - (float)teamData[i].rank) / 19.f)
            + ((float)teamData[i].points / cst::maxPoints)
            * (cst::f_Height / 2.2f));
        backface.push_back(0);

        //Haut gauche
        backface.push_back(dx + (2.f * (float)i) * largeur);
        backface.push_back(((19.f - (float)teamData[i].rank) / 19.f)
                           + ((float)teamData[i].points / cst::maxPoints)
            * (cst::f_Height / 2.2f) + cst::lineHeight);
        backface.push_back(0);


        //Bas droite
        backface.push_back(dx + (2.f * (float)i + 1.f) * largeur);
        backface.push_back(((19.f - (float)teamData[i].rank) / 19.f)
            + ((float)teamData[i].points / cst::maxPoints)
            * (cst::f_Height / 2.2f));
        backface.push_back(0);


        //Triangle 2
        //Bas droite
        backface.push_back(dx + (2.f * (float)i + 1.f) * largeur);
        backface.push_back(((19.f - (float)teamData[i].rank) / 19.f)
            + ((float)teamData[i].points / cst::maxPoints)
            * (cst::f_Height / 2.2f));
        backface.push_back(0);


        //Haut gauche
        backface.push_back(dx + (2.f * (float)i) * largeur);
        backface.push_back(((19.f - (float)teamData[i].rank) / 19.f)
                           + ((float)teamData[i].points / cst::maxPoints)
            * (cst::f_Height / 2.2f) + cst::lineHeight);
        backface.push_back(0);

        //Haut droite
        backface.push_back(dx + (2.f * (float)i + 1.f) * largeur);
        backface.push_back(((19.f - (float)teamData[i].rank) / 19.f)
                           + ((float)teamData[i].points / cst::maxPoints)
            * (cst::f_Height / 2.2f) + cst::lineHeight);
        backface.push_back(0);
    }

    return backface;
}
