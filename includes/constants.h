//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once

namespace cst {
    const int nbTeams = 20;
    const int nbDays = 40;

    const int i_Width = 1000;
    const int i_Height = 700;

    const float f_Width = 1000.f;
    const float f_Height = 700.f;
    const float lineHeight = (f_Height / 20.f) / 2.f;
    const float maxPoints = 92.f;
}

struct Day{
    int rank, points;
};