#include <Log.h>
#include <42ngine/Window.h>
#include <42ngine/VertexArray.h>

#include <data/Data.h>
#include <data/Cylinder.h>

int main() {

    Log::setLevel(Log::LevelDebug);

    Window window(1000, 700, "Projet IGSD");

    window.enable(GL_DEPTH_TEST);
    window.setDepthFunc(GL_LEQUAL, 1000.f, -10.f);
    window.setInputMode(GLFW_STICKY_KEYS, GLFW_TRUE);
    window.setEscapeToQuit(true);
    window.setClearColor(1.f, 1.f, 1.f, 1.f);

    Data *myData = new Data("resources/data/rankspts.csv");

    Cylinder myCylinder(0, myData);

    VertexArray va(1);

    std::vector<GLfloat> vector = myCylinder.makeBackface();

    window.show();

    delete myData;
    return 0;
}