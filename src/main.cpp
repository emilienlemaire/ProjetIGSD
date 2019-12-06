#include <Log.h>
#include <42ngine/42ngine.h>

#include <utils.h>

#include <data/Data.h>
#include <data/Cylinder.h>

int main() {

    Log::setLevel(Log::LevelDebug);

    GLFWwindow* window = initGL(1000, 700);

    std::vector<GLfloat> triangle = {
            -1.f, -1.f, 0.f,
             1.f, -1.f, 0.f,
             0.f, 1.f, 0.f
    };

    std::vector<GLfloat> rectangle = {
            -0.5f, -0.5f, 0.f,
            -0.5f,  0.5f, 0.f,
             0.5f, -0.5f, 0.f,
            -0.5f,  0.5f, 0.f,
             0.5f, -0.5f, 0.f,
             0.5f,  0.5f, 0.f,
    };

    VertexArray va(2);
    va.bind(0);


    GLuint triangle_VB0;
    glGenBuffers(1, &triangle_VB0);
    glBindBuffer(GL_ARRAY_BUFFER, triangle_VB0);

    VertexBuffer vb(2);
    vb.bind(0);
    va.push<GLfloat>(0, 3, triangle.size() * sizeof(GLfloat));
    vb.setData(triangle.size() * sizeof(GLfloat));
    vb.addSubData(triangle);

    va.bind(1);

    GLuint rectangle_VBO;
    vb.bind(1);
    va.push<GLfloat>(1, 3, rectangle.size() * sizeof(GLfloat));
    vb.setData(rectangle.size() * sizeof(GLfloat));
    vb.addSubData(rectangle);



    Shader shader("resources/shaders/VertexShader.glsl", "resources/shaders/FragmentShader.glsl");

    GLuint i = 0;
    GLboolean drawTriangle = true;

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.bind();
        shader.addUniformMat4("u_MVP", glm::mat4(1.f));

        if(i == 1000){
            drawTriangle = !drawTriangle;
            i = 0;
        }
        if (drawTriangle){
            va.bind(0);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        } else {
            va.bind(1);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        va.unbind();
        shader.unbind();
        i++;
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

    return 0;
}