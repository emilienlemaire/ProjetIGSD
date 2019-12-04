
#include <iostream>
#include <CppLogger/Log.h>
#include <utils.h>

#include <data/Data.h>
#include <data/Cylinder.h>

int main() {

    Log::setLevel(Log::LevelDebug);

    GLFWwindow* window = initGL(cst::i_Width, cst::i_Height);

    Data *myData = new Data("resources/data/rankspts.csv");

    Cylinder myCylinder(0, myData);

    std::vector<GLfloat> vector = myCylinder.makeBackface();

    std::string str = std::to_string(vector.size());

    Log::Debug(str);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

    delete myData;
    return 0;
}