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

    /*std::vector<std::vector<GLfloat>> allTeams;
    std::vector<std::vector<GLuint>> allIndices;
    GLuint drawSize[20];

    for (int j = 0; j < cst::NB_TEAMS; ++j) {
        std::vector<GLfloat> team;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> depth;
        std::vector<GLuint> indices;
        const Cylinder cylinder(j, data);
        cylinder.makeCylinder(team, depth);
        cylinder.makeNormals(team, normals);

        std::vector<GLfloat> lane;

        Cylinder::combineCylinder(team, normals, depth, lane);

        ftn::IndexBuffer::indexData(lane, indices, team);
        allTeams.push_back(team);
        allIndices.push_back(indices);
        drawSize[j] = indices.size();
    }


    GLuint vao[20];
    GLuint vbo[20];
    GLuint ibo[20];

    glGenVertexArrays(20, &vao[0]);
    glGenBuffers(20, &vbo[0]);
    glGenBuffers(20, &ibo[0]);

    for (int i = 0; i < cst::NB_TEAMS; ++i) {
        Log::Info("Sending data");
        Log::Info(i);
        glBindVertexArray(vao[i]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                (7) * sizeof(GLfloat),
                nullptr
        );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
                1,
                3,
                GL_FLOAT,
                GL_FALSE,
                (7) * sizeof(GLfloat),
                (void*)(3 * sizeof(GLfloat))
        );

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
                2,
                1,
                GL_FLOAT,
                GL_FALSE,
                (7) * sizeof(GLfloat),
                (void*)(6 * sizeof(GLfloat))
        );

        glBufferData(
                GL_ARRAY_BUFFER,
                allTeams[i].size() * sizeof(GLfloat),
                &allTeams[i],
                GL_STATIC_DRAW
        );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                allIndices[i].size() * sizeof(GLuint),
                &allIndices[i],
                GL_STATIC_DRAW
        );
    }*/

    std::vector<GLfloat> vertexCoord = {
        -.5f, -.5f, 0.0f, 1.f, 0.f, 1.f, 1.00f,
        -.5f,  .5f, 0.0f, 0.f, 1.f, 1.f, 0.75f,
         .5f, -.5f, 0.0f, 0.f, 0.f, 1.f, 0.25f,
         .5f,  .5f, 0.0f, 1.f, 0.f, 0.f, 0.00f
    };

    GLuint indices[6] = {
            0, 1, 2,
            1, 2, 3
    };

    GLuint vao, vbo, ibo;

    ///-- Non implémenté --//////////////////////////////////////////////////////
    ftn::BufferLayout bl = {
            {"in_Position", ftn::BufferType::Float3},
            {"in_Normals", ftn::BufferType::Float3},
            {"in_Depth", ftn::BufferType::Float3}
    };

    ftn::VertexArray(nb, BufferLayout);
    ftn::VertexBuffer<GLfloat>(nb, data);
    ftn::IndexBuffer(nb, data);
    /////////////////////////////////////////////////////////////////////////////
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            7 * sizeof(GLfloat),
            nullptr
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            7 * sizeof(GLfloat),
            (void*)(3* sizeof(GLfloat))
    );

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
            2,
            3,
            GL_FLOAT,
            GL_FALSE,
            7 * sizeof(GLfloat),
            (void*)(6 * sizeof(GLfloat))
    );

    glBufferData(
            GL_ARRAY_BUFFER,
            vertexCoord.size() * sizeof(GLfloat),
            &vertexCoord[0],
            GL_STATIC_DRAW
    );

    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            sizeof(indices),
            indices,
            GL_STATIC_DRAW
    );


    ///--Pour la selection de l'equipe--////////////////////////////////////////////////////
    Rederer (va);
    ftn::Renderer::SetTransform(idx, transform);
    ftn::Renderer::DisableTransform(idx);
    ////////////////////////////////////////////////////////////////////////////////////////
    glm::mat4 model(1.f);
    ftn::Shader shader("resources/shaders/VertexShader.glsl", "resources/shaders/FragmentShader.glsl");

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

            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
            window->update();
    } while (!window->shouldClose());

    delete data;
    ftn::Application::Destroy();
    return 0;
}