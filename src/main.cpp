#include <Log.h>
#include <42ngine/42ngine.h>

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
    std::vector<GLfloat> vector = myCylinder.makeBackface();

    VertexArray va(1);
    va.bind(0);

    Shader shader("resources/shaders/VertexShader.glsl","resources/shaders/FragmentShader.glsl");

    VertexBuffer vb(1);
    vb.bind(0);
    vb.setData(vector.size() * sizeof(GLfloat));
    vb.addSubData(vector);
    va.Push<GLfloat>(3, vector.size() * sizeof(GLfloat));

    window.show(shader, va);

    delete myData;
    return 0;
}