#include <Log.h>
#include <42ngine/42ngine.h>
#include <data/Data.h>
#include <data/Cylinder.h>
#include <string>


int main() {

    Log::setLevel(Log::LevelDebug);

    ftn::Application::Init();

    std::shared_ptr<ftn::Window> window = std::make_shared<ftn::Window>(cst::I_WIDTH, cst::I_HEIGHT, "Projet IGSD");

    ftn::Application::Enable(GL_DEPTH_TEST);
    ftn::Application::Enable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ftn::Application::SetDepthFunc(GL_LEQUAL, 0.1f, 2000.f);

    window->setInputMode(GLFW_STICKY_KEYS, GLFW_TRUE);
    window->setInputMode(GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    window->setInputMode(GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    //window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    window->setEscapeToQuit(true);

    ftn::Application::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    ftn::Application::SetWindow(window);

    Data* data = new Data("resources/data/rankspts.csv");

    window->setVSync(true);

    std::vector<GLfloat> team;
    std::vector<GLfloat> depth;
    std::vector<GLfloat> normals;
    const Cylinder cylinder(0, data);
    cylinder.makeCylinder(team, depth);
    cylinder.makeNormals(team, normals);

    std::vector<GLfloat> lane;
    Cylinder::combineCylinder(team, normals, depth, lane);


    std::vector<GLuint> indices;
    std::vector<GLfloat> vertices;
    ftn::IndexBuffer::IndexData(lane, indices, vertices);

    ftn::VertexArray::Create(1);

    ftn::VertexBuffer::Create(1);
    ftn::IndexBuffer::Create(1);

    ftn::VertexArray::Bind(0);
    ftn::VertexBuffer::Bind(0);

    ftn::VertexArray::SetLayout(0, {
            {"in_Position", ftn::BufferAttribType::Float3},
            {"in_Normals", ftn::BufferAttribType::Float3},
            {"in_Depth", ftn::BufferAttribType::Float}
    });

    ftn::VertexBuffer::Push<GLfloat>(vertices);

    ftn::IndexBuffer::Bind(0);
    ftn::IndexBuffer::Push<GLuint>(indices);


    ///--Pour la selection de l'equipe--////////////////////////////////////////////////////
    //TODO
    /*Rederer (va);
    ftn::Renderer::SetTransform(idx, transform);
    ftn::Renderer::DisableTransform(idx);*/
    ////////////////////////////////////////////////////////////////////////////////////////
    glm::mat4 model(1.f);
    ftn::Shader shader("resources/shaders/VertexShader.glsl", "resources/shaders/FragmentShader.glsl");

    shader.bind();
    shader.addUniformMat4("u_ViewProjection", glm::perspective(glm::radians(45.f), 1000.f / 700.f, 0.1f, 2000.f)
                                                                * glm::lookAt(
                                                                        glm::vec3(0.f, 0.f, 1000.f),
                                                                        glm::vec3(0.f, 0.f, 0.f),
                                                                        glm::vec3(0.f, 1.f, 0.f)
                                                                        ));

    shader.addUniformMat4("u_Translate", glm::translate(model, glm::vec3(-500.f, -250.f, 0.f)));
    shader.addUniformMat4("u_Scale", model);

    shader.addUniform3f("u_LightPos", glm::vec3(0.0, .0, 1000.f));
    shader.addUniform3f("u_ViewPos", glm::vec3(0.0, .0, 1000.f));
    shader.addUniformMat4("u_FragModel", model * glm::translate(model, glm::vec3(-500.f, -350.f, 0.f)));

    do {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.bind();
            glm::vec3 color(1.0f, 0.f, 0.f);
            /*if (i == 0) {
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
            }*/
            shader.addUniform3f("u_Color", color);

            ftn::VertexArray::Bind(0);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
            window->update();
    } while (!window->shouldClose());

    delete data;
    ftn::VertexArray::Destroy();
    ftn::Application::Destroy();
    return 0;
}