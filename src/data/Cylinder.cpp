//
// Created by Emilien Lemaire on 04/12/2019.
//

#include "Cylinder.h"

Cylinder::Cylinder(int t_TeamNumber, Data *t_Data) : m_TeamNumber(t_TeamNumber), m_Data(t_Data) {
    Log::Debug("Cylinder constructed");
}

Cylinder::~Cylinder() {
    Log::Debug("Cylinder destructed");
}

void Cylinder::makeBackface(std::vector<GLfloat>& backface) const{
    Log::Debug("Making backface");
    backface.clear();
    std::vector<Day> teamData = m_Data->getTeam(m_TeamNumber);
    backface.reserve(2 * teamData.size() * 18 - 18);

    GLfloat largeur = (cst::f_Width - 50.f) / (cst::nbDays * 2.f);
    GLfloat dx = 50.f;
    for (unsigned long i = 0; i < teamData.size(); ++i) {
        Day day = teamData[i];
        Day nextDay = teamData[i + 1];
        if (i == 20)
            dx += largeur;
        //Triangle 1
        //Bas gauche
        backface.push_back(dx + (2.f * (float) i) * largeur);
        backface.push_back(
                (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::maxPoints)) * (cst::f_Height / 2.2f));
        backface.push_back(0);

        //Haut gauche
        backface.push_back(dx + (2.f * (float) i) * largeur);
        backface.push_back(
                (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::maxPoints)) * (cst::f_Height / 2.2f) +
                cst::lineHeight);
        backface.push_back(0);


        //Bas droite
        backface.push_back(dx + (2.f * (float) i + 1.f) * largeur);
        backface.push_back(
                (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::maxPoints)) * (cst::f_Height / 2.2f));
        backface.push_back(0);


        //Triangle 2
        //Bas droite
        backface.push_back(dx + (2.f * (float) i + 1.f) * largeur);
        backface.push_back(
                (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::maxPoints)) * (cst::f_Height / 2.2f));
        backface.push_back(0);


        //Haut gauche
        backface.push_back(dx + (2.f * (float) i) * largeur);
        backface.push_back(
                (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::maxPoints)) * (cst::f_Height / 2.2f) +
                cst::lineHeight);
        backface.push_back(0);

        //Haut droite
        backface.push_back(dx + (2.f * (float) i + 1.f) * largeur);
        backface.push_back(
                (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::maxPoints)) * (cst::f_Height / 2.2f) +
                cst::lineHeight);
        backface.push_back(0);
        if (i != teamData.size() - 1){
            GLfloat z = 0.f;
            if (nextDay.rank > day.rank) z = -0.1f;
            //Connexion suivant
            //Triangle 1
            //Bas gauche
            backface.push_back(dx + (2.f * (float) i + 1.f) * largeur);
            backface.push_back(
                    (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::maxPoints)) * (cst::f_Height / 2.2f));
            backface.push_back(z);

            //Haut gauche
            backface.push_back(dx + (2.f * (float) i + 1.f) * largeur);
            backface.push_back(
                    (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::maxPoints)) * (cst::f_Height / 2.2f) +
                    cst::lineHeight);
            backface.push_back(z);


            //Bas droite
            backface.push_back(dx + (2.f * (float) i + 2.f) * largeur);
            backface.push_back((((19.f - (float) nextDay.rank) / 19.f) + ((float) nextDay.points / cst::maxPoints)) *
                               (cst::f_Height / 2.2f));
            backface.push_back(z);


            //Triangle 2
            //Bas droite
            backface.push_back(dx + (2.f * (float) i + 2.f) * largeur);
            backface.push_back((((19.f - (float) nextDay.rank) / 19.f) + ((float) nextDay.points / cst::maxPoints)) *
                               (cst::f_Height / 2.2f));
            backface.push_back(z);


            //Haut gauche
            backface.push_back(dx + (2.f * (float) i + 1.f) * largeur);
            backface.push_back(
                    (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::maxPoints)) * (cst::f_Height / 2.2f) +
                    cst::lineHeight);
            backface.push_back(z);

            //Haut droite
            backface.push_back(dx + (2.f * (float) i + 2.f) * largeur);
            backface.push_back((((19.f - (float) nextDay.rank) / 19.f) + ((float) nextDay.points / cst::maxPoints)) *
                               (cst::f_Height / 2.2f) + cst::lineHeight);
            backface.push_back(z);
        }
    }
    Log::Debug("Backface created");
}
