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

void Cylinder::makeBackface(std::vector<GLfloat> &t_Backface, std::vector<GLfloat> &t_Depth) const{
    t_Backface.clear();
    t_Depth.clear();
    std::vector<Day> teamData = m_Data->getTeam(m_TeamNumber);
    t_Backface.reserve(2 * teamData.size() * 18 - 18);
    t_Depth.reserve(teamData.size() * 12 - 6);

    GLfloat largeur = (cst::F_WIDTH - 50.f) / (cst::NB_DAYS * 2.f);
    GLfloat dx = 50.f;
    for (unsigned long i = 0; i < teamData.size(); ++i) {
        Day day = teamData[i];
        Day nextDay = teamData[i + 1];
        if (i == 20)
            dx += largeur;
        //Triangle 1
        //Bas gauche
        t_Backface.push_back(dx + (2.f * (float) i) * largeur);
        t_Backface.push_back(
                (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f));
        t_Backface.push_back(0);
        t_Depth.push_back(0);

        //Haut gauche
        t_Backface.push_back(dx + (2.f * (float) i) * largeur);
        t_Backface.push_back(
                (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f) +
                cst::LINE_HEIGHT);
        t_Backface.push_back(0);
        t_Depth.push_back(0);


        //Bas droite
        t_Backface.push_back(dx + (2.f * (float) i + 1.f) * largeur);
        t_Backface.push_back(
                (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f));
        t_Backface.push_back(0);
        t_Depth.push_back(0);


        //Triangle 2
        //Bas droite
        t_Backface.push_back(dx + (2.f * (float) i + 1.f) * largeur);
        t_Backface.push_back(
                (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f));
        t_Backface.push_back(0);
        t_Depth.push_back(0);


        //Haut gauche
        t_Backface.push_back(dx + (2.f * (float) i) * largeur);
        t_Backface.push_back(
                (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f) +
                cst::LINE_HEIGHT);
        t_Backface.push_back(0);
        t_Depth.push_back(0);

        //Haut droite
        t_Backface.push_back(dx + (2.f * (float) i + 1.f) * largeur);
        t_Backface.push_back(
                (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f) +
                cst::LINE_HEIGHT);
        t_Backface.push_back(0);
        t_Depth.push_back(0);

        if (i != teamData.size() - 1){
            unsigned short depth = 0;
            if(nextDay.rank > day.rank)
                depth = 1;
            //Connexion suivant
            //Triangle 1
            //Bas gauche
            t_Backface.push_back(dx + (2.f * (float) i + 1.f) * largeur);
            t_Backface.push_back(
                    (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f));
            t_Backface.push_back(0);
            t_Depth.push_back(depth);

            //Haut gauche
            t_Backface.push_back(dx + (2.f * (float) i + 1.f) * largeur);
            t_Backface.push_back(
                    (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f) +
                    cst::LINE_HEIGHT);
            t_Backface.push_back(0);
            t_Depth.push_back(depth);


            //Bas droite
            t_Backface.push_back(dx + (2.f * (float) i + 2.f) * largeur);
            t_Backface.push_back((((19.f - (float) nextDay.rank) / 19.f) + ((float) nextDay.points / cst::MAX_POINTS)) *
                                 (cst::F_HEIGHT / 2.2f));
            t_Backface.push_back(0);
            t_Depth.push_back(depth);


            //Triangle 2
            //Bas droite
            t_Backface.push_back(dx + (2.f * (float) i + 2.f) * largeur);
            t_Backface.push_back((((19.f - (float) nextDay.rank) / 19.f) + ((float) nextDay.points / cst::MAX_POINTS)) *
                                 (cst::F_HEIGHT / 2.2f));
            t_Backface.push_back(0);
            t_Depth.push_back(depth);


            //Haut gauche
            t_Backface.push_back(dx + (2.f * (float) i + 1.f) * largeur);
            t_Backface.push_back(
                    (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f) +
                    cst::LINE_HEIGHT);
            t_Backface.push_back(0);
            t_Depth.push_back(depth);

            //Haut droite
            t_Backface.push_back(dx + (2.f * (float) i + 2.f) * largeur);
            t_Backface.push_back((((19.f - (float) nextDay.rank) / 19.f) + ((float) nextDay.points / cst::MAX_POINTS)) *
                                 (cst::F_HEIGHT / 2.2f) + cst::LINE_HEIGHT);
            t_Backface.push_back(0);
            t_Depth.push_back(depth);
        }
    }
}

void Cylinder::makeCylinder(std::vector<GLfloat> &t_Cylinder, std::vector<GLfloat> &t_Depth) const {

    makeBackface(t_Cylinder, t_Depth);

    t_Cylinder.reserve(t_Cylinder.size() + 4 * (9 * cst::CYLINDER_DIVISION) + 2 * (cst::NB_DAYS * cst::CYLINDER_DIVISION * 2 * 9) - 4 * 18);

    GLfloat radius = glm::abs(t_Cylinder[1] - t_Cylinder[4]) / 2.f;
    GLfloat angle = glm::pi<GLfloat>() / (GLfloat)cst::CYLINDER_DIVISION;

    //Cercle partie gauche extrémité
    GLfloat xCenter = (t_Cylinder[0] + t_Cylinder[3]) / 2.f;
    GLfloat yCenter = (t_Cylinder[1] + t_Cylinder[4]) / 2.f;

    for (int i = 0; i < cst::CYLINDER_DIVISION; ++i) {
        //1 Triangle par partie de cercle
        t_Cylinder.push_back(xCenter);
        t_Cylinder.push_back(yCenter);
        t_Cylinder.push_back(0.f);
        t_Depth.push_back(0);

        t_Cylinder.push_back(xCenter);
        t_Cylinder.push_back(yCenter + radius * glm::cos((float)(i) * angle));
        t_Cylinder.push_back(radius * glm::sin((float) i * angle));
        t_Depth.push_back(0);

        t_Cylinder.push_back(xCenter);
        t_Cylinder.push_back(yCenter + radius * glm::cos((float) (i + 1) * angle));
        t_Cylinder.push_back(radius * glm::sin((float) (i + 1) * angle));
        t_Depth.push_back(0);
    }

    //Cercle partie gauche centre

    xCenter = t_Cylinder[19 * (12 * 3) + (9 * 3)];
    yCenter = (t_Cylinder[19 * (12 * 3) + 1] + t_Cylinder[19 * (12 * 3) + 4]) / 2.f;

    for (int i = 0; i < cst::CYLINDER_DIVISION; ++i) {
        //1 Triangle par partie de cercle
        t_Cylinder.push_back(xCenter);
        t_Cylinder.push_back(yCenter);
        t_Cylinder.push_back(0.f);
        t_Depth.push_back(0);


        t_Cylinder.push_back(xCenter);
        t_Cylinder.push_back(yCenter + radius * glm::cos((float)(i) * angle));
        t_Cylinder.push_back(radius * glm::sin((float) i * angle));
        t_Depth.push_back(0);

        t_Cylinder.push_back(xCenter);
        t_Cylinder.push_back(yCenter + radius * glm::cos((float) (i + 1) * angle));
        t_Cylinder.push_back(radius * glm::sin((float) (i + 1) * angle));
        t_Depth.push_back(0);
    }

    //Cercle partie droite centre

    xCenter = t_Cylinder[20 * (12 * 3)];
    yCenter = (t_Cylinder[20 * (12 * 3) + 1] + t_Cylinder[20 * (12 * 3) + 4]) / 2.f;

    for (int i = 0; i < cst::CYLINDER_DIVISION; ++i) {
        //1 Triangle par partie de cercle
        t_Cylinder.push_back(xCenter);
        t_Cylinder.push_back(yCenter);
        t_Cylinder.push_back(0.f);
        t_Depth.push_back(0);


        t_Cylinder.push_back(xCenter);
        t_Cylinder.push_back(yCenter + radius * glm::cos((float)(i) * angle));
        t_Cylinder.push_back(radius * glm::sin((float) i * angle));
        t_Depth.push_back(0);

        t_Cylinder.push_back(xCenter);
        t_Cylinder.push_back(yCenter + radius * glm::cos((float) (i + 1) * angle));
        t_Cylinder.push_back(radius * glm::sin((float) (i + 1) * angle));
        t_Depth.push_back(0);
    }

    //Cercle partie droite extrémité

    xCenter = t_Cylinder[(cst::NB_DAYS - 1) * (12 * 3)  + (2 * 3)];
    yCenter = (t_Cylinder[(cst::NB_DAYS - 1) * (12 * 3) + 1] + t_Cylinder[(cst::NB_DAYS - 1) * (12 * 3) + 4]) / 2.f;

    for (int i = 0; i < cst::CYLINDER_DIVISION; ++i) {
        //1 Triangle par partie de cercle
        t_Cylinder.push_back(xCenter);
        t_Cylinder.push_back(yCenter);
        t_Cylinder.push_back(0.f);
        t_Depth.push_back(0);


        t_Cylinder.push_back(xCenter);
        t_Cylinder.push_back(yCenter + radius * glm::cos((float)(i) * angle));
        t_Cylinder.push_back(radius * glm::sin((float) i * angle));
        t_Depth.push_back(0);

        t_Cylinder.push_back(xCenter);
        t_Cylinder.push_back(yCenter + radius * glm::cos((float) (i + 1) * angle));
        t_Cylinder.push_back(radius * glm::sin((float) (i + 1) * angle));
        t_Depth.push_back(0);
    }

    //Corps du cylindre
    std::vector<Day> teamData = m_Data->getTeam(m_TeamNumber);

    GLfloat largeur = (cst::F_WIDTH - 50.f) / (cst::NB_DAYS * 2.f);
    GLfloat dx = 50.f;

    for (unsigned long i = 0; i < teamData.size(); ++i) {
        // Corps
        Day day = teamData[i];

        if (i == 20) dx += largeur;

        GLfloat xGauche = dx + (2.f * (float) i) * largeur;
        GLfloat xDroit = dx + (2.f * (float) i + 1.f) * largeur;

        GLfloat yBas = (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f);
        GLfloat yHaut = (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f) + cst::LINE_HEIGHT;
        yCenter = (yHaut + yBas) /  2.f;

        for (int j = 0; j < cst::CYLINDER_DIVISION ; ++j) {
            //Triangle 1
            //Bas gauche
            t_Cylinder.push_back(xGauche);
            t_Cylinder.push_back(yCenter + radius * glm::cos((float)j * angle));
            t_Cylinder.push_back(radius * glm::sin((float)j * angle));
            t_Depth.push_back(0);

            //Haut gauche
            t_Cylinder.push_back(xGauche);
            t_Cylinder.push_back(yCenter + radius * glm::cos((float)(j + 1) * angle));
            t_Cylinder.push_back(radius * glm::sin((float)(j + 1) * angle));
            t_Depth.push_back(0);

            //Bas droite
            t_Cylinder.push_back(xDroit);
            t_Cylinder.push_back(yCenter + radius * glm::cos((float)j * angle));
            t_Cylinder.push_back(radius * glm::sin((float)j * angle));
            t_Depth.push_back(0);

            //Triangle 2
            //Haut gauche
            t_Cylinder.push_back(xGauche);
            t_Cylinder.push_back(yCenter + radius * glm::cos((float)(j + 1) * angle));
            t_Cylinder.push_back(radius * glm::sin((float)(j + 1) * angle));
            t_Depth.push_back(0);

            //Bas droite
            t_Cylinder.push_back(xDroit);
            t_Cylinder.push_back(yCenter + radius * glm::cos((float)(j + 1) * angle));
            t_Cylinder.push_back(radius * glm::sin((float)(j + 1) * angle));
            t_Depth.push_back(0);

            //Haut droite
            t_Cylinder.push_back(xDroit);
            t_Cylinder.push_back(yCenter + radius * glm::cos((float)j * angle));
            t_Cylinder.push_back(radius * glm::sin((float)j * angle));
            t_Depth.push_back(0);
        }

        //Connexion avec le jour suivant


        if(i != teamData.size() - 1){
            Day nextDay = teamData[i + 1];
            xGauche = dx + (2.f * (float) i + 1.f) * largeur;
            xDroit = dx + (2.f * (float) i + 2.f) * largeur;

            GLfloat yHautGauche = (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f) + cst::LINE_HEIGHT;
            GLfloat yBasGauche = (((19.f - (float) day.rank) / 19.f) + ((float) day.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f);
            GLfloat yCentreGauche = (yHautGauche + yBasGauche) / 2.f;

            GLfloat yHautDroit = (((19.f - (float) nextDay.rank) / 19.f) + ((float) nextDay.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f) + cst::LINE_HEIGHT;
            GLfloat yBasDroit = (((19.f - (float) nextDay.rank) / 19.f) + ((float) nextDay.points / cst::MAX_POINTS)) * (cst::F_HEIGHT / 2.2f);
            GLfloat yCentreDroit = (yHautDroit + yBasDroit) / 2.f;

            unsigned short depth = 0;
            if( nextDay.rank > day.rank)
                depth = 1;

            for (int j = 0; j < cst::CYLINDER_DIVISION; ++j) {
                //Triangle 1
                t_Cylinder.push_back(xGauche);
                t_Cylinder.push_back(yCentreGauche + radius * glm::cos((float)j * angle));
                t_Cylinder.push_back(radius * glm::sin((float)j * angle));
                t_Depth.push_back(depth);

                t_Cylinder.push_back(xGauche);
                t_Cylinder.push_back(yCentreGauche + radius * glm::cos((float)(j + 1) * angle));
                t_Cylinder.push_back(radius * glm::sin((float)(j + 1) * angle));
                t_Depth.push_back(depth);

                t_Cylinder.push_back(xDroit);
                t_Cylinder.push_back(yCentreDroit + radius * glm::cos((float)j * angle));
                t_Cylinder.push_back(radius * glm::sin((float)j * angle));
                t_Depth.push_back(depth);

                //Triangle 2
                t_Cylinder.push_back(xGauche);
                t_Cylinder.push_back(yCentreGauche + radius * glm::cos((float)(j + 1) * angle));
                t_Cylinder.push_back(radius * glm::sin((float)(j + 1) * angle));
                t_Depth.push_back(depth);

                t_Cylinder.push_back(xDroit);
                t_Cylinder.push_back(yCentreDroit + radius * glm::cos((float)(j + 1) * angle));
                t_Cylinder.push_back(radius * glm::sin((float)(j + 1) * angle));
                t_Depth.push_back(depth);

                t_Cylinder.push_back(xDroit);
                t_Cylinder.push_back(yCentreDroit + radius * glm::cos((float)j * angle));
                t_Cylinder.push_back(radius * glm::sin((float)j * angle));
                t_Depth.push_back(depth);
            }
        }
    }
}

void Cylinder::makeNormals(const std::vector<GLfloat> &t_Cylinder, std::vector<GLfloat> &t_OutNormals) const {
    t_OutNormals.reserve(t_Cylinder.size());

    //1 triangle = 9 coordonnées
    for (int i = 0; i < t_Cylinder.size() / 9; ++i) {
        GLfloat x1 = t_Cylinder[(9 * i) + 0];
        GLfloat y1 = t_Cylinder[(9 * i) + 1];
        GLfloat z1 = t_Cylinder[(9 * i) + 2];

        GLfloat x2 = t_Cylinder[(9 * i) + 3];
        GLfloat y2 = t_Cylinder[(9 * i) + 4];
        GLfloat z2 = t_Cylinder[(9 * i) + 5];

        GLfloat x3 = t_Cylinder[(9 * i) + 6];
        GLfloat y3 = t_Cylinder[(9 * i) + 7];
        GLfloat z3 = t_Cylinder[(9 * i) + 8];

        if (i < 158){
            glm::vec3 A(x1, y1, z1), B(x2, y2, z2), C(x3, y3, z3);
            glm::vec3 normal = glm::cross(C - A, B - A);
            t_OutNormals.push_back(normal.x);
            t_OutNormals.push_back(normal.y);
            t_OutNormals.push_back(normal.z);

            normal = glm::cross(A - B, C - B);
            t_OutNormals.push_back(normal.x);
            t_OutNormals.push_back(normal.y);
            t_OutNormals.push_back(normal.z);

            normal = glm::cross(B - C, A - C);
            t_OutNormals.push_back(normal.x);
            t_OutNormals.push_back(normal.y);
            t_OutNormals.push_back(normal.z);
        } else {
            glm::vec3 A(x1, y1, z1), B(x2, y2, z2), C(x3, y3, z3);
            glm::vec3 normal = glm::cross(B - A, C - A);
            t_OutNormals.push_back(normal.x);
            t_OutNormals.push_back(normal.y);
            t_OutNormals.push_back(normal.z);

            normal = glm::cross(C - B, A - B);
            t_OutNormals.push_back(normal.x);
            t_OutNormals.push_back(normal.y);
            t_OutNormals.push_back(normal.z);

            normal = glm::cross(A - C, B - C);
            t_OutNormals.push_back(normal.x);
            t_OutNormals.push_back(normal.y);
            t_OutNormals.push_back(normal.z);
        }
    }
}

void Cylinder::combineCylinder(const std::vector<GLfloat> &t_Cylinder, const std::vector<GLfloat> &t_Normals,
                               const std::vector<GLfloat> &t_Depth, std::vector<GLfloat>& t_OutData) {
    t_OutData.clear();
    t_OutData.reserve(t_Cylinder.size() + t_Normals.size() + t_Depth.size());
    for (int i = 0; i < t_Cylinder.size(); i += 3) {
        t_OutData.push_back(t_Cylinder[i + 0]);
        t_OutData.push_back(t_Cylinder[i + 1]);
        t_OutData.push_back(t_Cylinder[i + 2]);

        t_OutData.push_back(t_Normals[i + 0]);
        t_OutData.push_back(t_Normals[i + 1]);
        t_OutData.push_back(t_Normals[i + 2]);

        t_OutData.push_back(t_Depth[i / 3]);
    }
}
