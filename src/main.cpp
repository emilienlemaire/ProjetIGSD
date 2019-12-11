#include <Log.h>
#include <42ngine/42ngine.h>
#include <data/Data.h>
#include <data/Cylinder.h>
#include <string>

int main() {

    Log::setLevel(Log::LevelDebug);

    std::unique_ptr<ftn::Application> app = std::make_unique<ftn::Application>();

    std::shared_ptr<ftn::Window> window = std::make_shared<ftn::Window>(cst::I_WIDTH, cst::I_HEIGHT, "Projet IGSD");

    app->enable(GL_DEPTH_TEST);
    app->setDepthFunc(GL_LEQUAL, 0.1f, -100.f);

    window->setInputMode(GLFW_STICKY_KEYS, GLFW_TRUE);
    window->setInputMode(GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    window->setEscapeToQuit(true);

    app->setClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    app->setWindow(window);

    Data* data = new Data("resources/data/rankspts.csv");

    std::shared_ptr<ftn::VertexArray> va = std::make_shared<ftn::VertexArray>(cst::NB_TEAMS);
    std::shared_ptr<ftn::VertexBuffer> vb = std::make_shared<ftn::VertexBuffer>(cst::NB_TEAMS);
    std::shared_ptr<ftn::IndexBuffer> ib = std::make_shared<ftn::IndexBuffer>(cst::NB_TEAMS);

    ftn::Renderer renderer(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)

    window->setVSync(true);

    std::vector<std::vector<GLfloat>> allTeams;
    std::vector<std::vector<GLfloat>> allNormals;

    for (int j = 0; j < cst::NB_TEAMS; ++j) {
        std::vector<GLfloat> team;
        std::vector<GLfloat> normals;
        const Cylinder cylinder(j, data);
        cylinder.makeCylinder(team);
        cylinder.makeNormals(team, normals);
        allTeams.push_back(team);
        allNormals.push_back(normals);
    }

    for (int i = 0; i < cst::NB_TEAMS; ++i) {

        glm::vec3 color;
        if (i == 0) {
            color.r = 0.f;
            color.g = 72.f / 255.f;
            color.b = 204.f / 255.f;
        } else if (i < 4) {
            color.r = 98.f / 255.f;
            color.g = 214.f / 255.f;
            color.b = 230.f / 255.f;
        } else if (i < 7) {
            color.r = 236.f / 255.f;
            color.g = 238.f / 255.f;
            color.b = 26.f / 255.f;
        } else if (i < 10) {
            color.r = 194.f / 255.f;
            color.g = 194.f / 255.f;
            color.b = 194.f / 255.f;
        } else if (i < 16) {
            color.r = 140.f / 255.f;
            color.g = 140.f / 255.f;
            color.b = 140.f / 255.f;
        } else {
            color.r = 204.f / 255.f;
            color.g = 72.f / 255.f;
            color.b = 0.f / 255.f;
        }
        ftn::Element element(allTeams[i], allNormals[i], i, i, i, ib, vb, va);
        element.setColor(color);
        renderer.addElement(element);
    }

    va->bind(0);
    ftn::Shader shader("resources/shaders/VertexShader.glsl", "resources/shaders/FragmentShader.glsl");
    GLfloat angle = 0.f;

    do {
        shader.bind();
        glm::mat4 rotation = glm::rotate(glm::mat4(1.f), glm::radians(angle), glm::vec3(0.f, 1.f, 0.f));
        shader.unbind();
        shader.addUniformMat4("u_Rotate", rotation);
        shader.addUniformMat4("u_FragRotate", rotation);
        renderer.clear();
        renderer.render(shader);
        window->update(&angle);
    } while (!window->shouldClose());

    delete data;
    return 0;
}