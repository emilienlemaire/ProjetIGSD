//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once

namespace cst {
    const int NB_TEAMS = 20;
    const int NB_DAYS = 40;
    const int I_WIDTH = 1000;
    const int I_HEIGHT = 700;
    const int CYLINDER_DIVISION = 25;

    const float F_WIDTH = 1000.f;
    const float F_HEIGHT = 700.f;
    const float LINE_HEIGHT = (F_HEIGHT / 20.f) / 2.f;
    const float MAX_POINTS = 92.f;

}

struct Day{
    int rank, points;
};