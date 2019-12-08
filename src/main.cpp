#include <Log.h>
#include <42ngine/42ngine.h>

#include <utils.h>

#include <data/Data.h>
#include <data/Cylinder.h>
#include <42ngine/src/IndexBuffer.h>
#include <string>

int main() {

    Log::setLevel(Log::LevelDebug);

    GLFWwindow* window = initGL(cst::i_Width, cst::i_Height);

    Data* data = new Data("resources/data/rankspts.csv");

    VertexArray va(20);
    VertexBuffer vb(20);
    IndexBuffer ib(20);

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
        ib.setData(indices.size() * sizeof(GLuint));
        ib.addSubData(indices);
    }

    std::vector<int> test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    Log::Info(std::to_string(test.size()));
    Log::Info(std::to_string(test.capacity()));

    test.reserve(test.size() + 5);

    Log::Info(std::to_string(test.size()));

    Log::Info(std::to_string(test.capacity()));

    int sz = test.capacity();

    for (int j = 0; j < 5; ++j) {
        test.push_back(j);
        if(test.capacity() != sz) {
            sz = test.capacity();
            Log::Warn(std::to_string(test.capacity()));
        }
    }

    for (int k : test) {
        Log::Debug(std::to_string(k));
    }

    Shader shader("resources/shaders/VertexShader.glsl", "resources/shaders/FragmentShader.glsl");

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)
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
            //ib.bind(i);
            shader.addUniform3f("u_Color", color);
            glDrawElements(GL_TRIANGLES, indexSize[i], GL_UNSIGNED_BYTE, nullptr);
        }


        va.unbind();
        shader.unbind();
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

    delete data;

    return 0;
}