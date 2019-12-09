#include <Log.h>
#include <42ngine/42ngine.h>

#include <data/Data.h>
#include <data/Cylinder.h>
#include <string>

int main() {

    Log::setLevel(Log::LevelDebug);

    auto* app = new ftn::Application();

    auto* window = new ftn::Window(cst::i_Width, cst::i_Height, "Projet IGSD");

    app->enable(GL_DEPTH_TEST);
    app->setDepthFunc(GL_LEQUAL, 1000.f, -10.f);

    window->setInputMode(GLFW_STICKY_KEYS, GLFW_TRUE);
    window->setInputMode(GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    window->setVSync(true);
    window->setEscapeToQuit(true);

    app->setClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    app->setWindow(window);

    Data* data = new Data("resources/data/rankspts.csv");

    ftn::VertexArray va(20);
    ftn::VertexBuffer vb(20);
    ftn::IndexBuffer ib(20);

    GLuint verticesSize[cst::nbTeams];
    GLuint indexSize[cst::nbTeams];

    for (int i = 0; i < cst::nbTeams; ++i) {
        va.bind(i);
        vb.bind(i);
        ib.bind(i);
        std::vector<GLfloat> team;
        std::vector<GLubyte> indices;
        std::vector<GLfloat> vertices;
        const Cylinder cylinder(i, data);
        cylinder.makeBackface(team);
        ib.indexData(team, indices, vertices);
        indexSize[i] = indices.size();
        Log::Info(indices.size());
        verticesSize[i] = vertices.size();
        va.push<GLfloat>(i, 3, vertices.size() * sizeof(GLfloat));
        vb.setData(vertices.size() * sizeof(GLfloat));
        vb.addSubData(vertices);
        ib.setData(indices.size() * sizeof(GLubyte));
        ib.addSubData(indices);
    }

    ftn::Shader shader("resources/shaders/VertexShader.glsl", "resources/shaders/FragmentShader.glsl");
    ftn::Renderer renderer(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)

    do {
        renderer.clear();
        shader.bind();
        shader.addUniformMat4("u_Model", glm::mat4(1.f) * glm::translate(glm::mat4(1.f), glm::vec3(-500.f, -350.f, 0.f)));
        shader.addUniformMat4("u_View", glm::lookAt(glm::vec3(0.0, .0, 650.f),
            glm::vec3(0.0, 0.0, .1),
            glm::vec3(0, 1., .0)));
        shader.addUniformMat4("u_Projection", glm::perspective(45.f, 1000.f/700.f, -10.f, 10.f));

        for (int i = 0; i < cst::nbTeams; ++i) {

        glm::vec3 color;
            if (i == 0){
                color.r = 0.f;
                color.g = 72.f / 255.f;
                color.b = 204.f / 255.f;
            } else if (i < 4){
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
            } else if (i < 16){
                color.r = 140.f / 255.f;
                color.g = 140.f / 255.f;
                color.b = 140.f / 255.f;
            } else {
                color.r = 204.f / 255.f;
                color.g = 72.f / 255.f;
                color.b = 0.f / 255.f;
            }
            va.bind(i);
            ib.bind(i);
            shader.addUniform3f("u_Color", color);
            glDrawElements(GL_TRIANGLES, indexSize[i], GL_UNSIGNED_BYTE, nullptr);
        }


        va.unbind();
        shader.unbind();
        window->update();
    } while (!window->shouldClose());

    delete data;
    delete window;
    delete app;
    return 0;
}