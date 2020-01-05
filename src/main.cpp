#include <42ngine/42ngine.h>
#include <data/Data.h>
#include <data/Cylinder.h>
#include <array>

int main() {

    //Création d'une console colorée pour le débuggage du projet
    Log::createConsole("Projet IGSD", Log::LevelDebug);

    //Initialisation puis création d'une fenêtre
    ftn::Application::Init();

    std::shared_ptr<ftn::Window> window = std::make_shared<ftn::Window>(cst::I_WIDTH, cst::I_HEIGHT, "Projet IGSD");

    //Définition de la depthFunc pour les croisements des lignes
    ftn::Application::Enable(GL_DEPTH_TEST);
    ftn::Application::SetDepthFunc(GL_LEQUAL, 0.1f, 100.f);

    //Définition de la blendFunc pour un bonne affichage des textures
    ftn::Application::Enable(GL_BLEND);
    ftn::Application::SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //On initialise la récupération des événements de la fenêtre.
    window->setInputMode(GLFW_STICKY_KEYS, GLFW_TRUE);
    window->setInputMode(GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    window->setInputMode(GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //On veut pouvoir quitter en appuyant sur escape.
    window->setEscapeToQuit(true);

    //Initialisation de glew et création d'un fond blanc.
    ftn::Application::InitGlew();
    ftn::Application::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    //On récupère les données pour les lignes
    Data* data = new Data("resources/data/rankspts.csv");

    window->setVSync(true);

    //Génération des buffer pour chaque ligne
    // 20 VAO, 1 VBO, 1 IBO et 1 texture par VAO
    ftn::VertexArray::Create(20);
    ftn::VertexBuffer::Create(20);
    ftn::IndexBuffer::Create(20);
    ftn::Texture::Create(20);
    std::array<int, 20> indicesSize{};

    //Cénération des données pour les cylindre
    for (int i = 0; i < cst::NB_TEAMS; ++i) {
        std::vector<GLfloat> team;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> depth;
        std::vector<GLfloat> texture;

        //Création du cylindre spécifique à l'équipe
        const Cylinder cylinder(i, data);

        //Récupération des coordonnées, de la profondeur et des coordonnées de la texture pour chaque point de la ligne
        cylinder.makeCylinder(team, depth, texture);
        //Récupération des normales pour chaque point de la ligne
        Cylinder::makeNormals(team, normals);

        std::vector<GLfloat> lane;
        //On combine toutes les informations dans un seul tableau: lane
        Cylinder::combineCylinder(team, normals, depth, texture, lane);

        std::vector<GLuint> indices;
        std::vector<GLfloat> vertices;
        //On crée un tableau d'indices et on supprime tous les points en doublon.
        ftn::IndexBuffer::IndexData(lane, indices, vertices);


        ftn::VertexArray::Bind(i);
        ftn::VertexBuffer::Bind(i);

        //On donne au VAO la forme des données
        //Le nom correspond au nom donné dans les shaders
        ftn::VertexArray::SetLayout(i, {
                {"in_Position", ftn::BufferAttribType::Float3},
                {"in_Normals", ftn::BufferAttribType::Float3},
                {"in_Depth", ftn::BufferAttribType::Float},
                {"in_Texture", ftn::BufferAttribType::Float2}
        });

        //On envoie les données dans le VBO
        ftn::VertexBuffer::Push<GLfloat>(vertices);

        ftn::IndexBuffer::Bind(i);

        //On donne à l'IBO les indices à dessiner
        ftn::IndexBuffer::Push<GLuint>(indices);

        //On récupère la taille du tableau d'indice pour la fonction draw.
        indicesSize[i] = indices.size();

        //On envoie la texture à la carte graphique grâce au numéro de l'équipe
        ftn::Texture::Push(i, Cylinder::texturePath(i));
    }

    glm::mat4 model(1.f);

    //On initialise les shaders, on les compile et on les lie au programme
    ftn::Shader shader("resources/shaders/VertexShader.glsl", "resources/shaders/FragmentShader.glsl");

    shader.bind();

    //On envoie certains uniforms aux shaders afin le model soit centré quand on lance l'application.
    shader.addUniformMat4("u_Translate", glm::translate(model, glm::vec3(-500.f, -250.f, 0.f)));
    shader.addUniformMat4("u_Scale", model);
    shader.addUniformMat4("u_FragModel", model * glm::translate(model, glm::vec3(-500.f, -350.f, 0.f)));

    //Initialisation de la caméra
    ftn::Camera camera(glm::vec3(0.f, 0.f, 1000.f), 1000.f / 700.f);
    camera.setWindow(window);

    GLfloat lastTime = glfwGetTime();
    GLfloat lastClick = glfwGetTime();

    //Au départ aucune équipe n'est sélectionnée.
    int teamSelected = -1;

    do {
        //On efface la frame précédente
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto now = (float)glfwGetTime();
        float timeStep = now - lastTime;
        lastTime = now;

        //Afin que la caméra soit plus fluide on lui envoie la différence de temps entre deux frames
        camera.onUpdate(timeStep);


        //Pour éviter de passer plusieurs équipe en 1 clique on définit une latence
        // minimale pour changer d'équipe sélectionnée
        if(glfwGetKey(window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS){
            GLfloat currentClick = glfwGetTime();
            if(currentClick - lastClick > 0.1){
                lastClick = currentClick;
                teamSelected--;
                if(teamSelected < - 1){
                    teamSelected = -1;
                }
            }
        }

        if(glfwGetKey(window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS){
            GLfloat currentClick = glfwGetTime();
            if(currentClick - lastClick > 0.1){
                lastClick = currentClick;
                teamSelected++;
                if(teamSelected > 20){
                    teamSelected = 20;
                }
            }
        }

        //On envoie les uniforms modifiés par le mouvement de la caméra pour le nouvel affichage
        shader.bind();
        shader.addUniformMat4("u_ViewProjection", camera.getViewProjection());
        shader.addUniform1i("u_Texture", 0);
        shader.addUniform3f("u_LightPos", camera.getPosition());
        shader.addUniform3f("u_ViewPos", camera.getPosition());

        glm::vec3 color(1.0f, 0.f, 0.f);

        //Chaque équipe à une couleur différente en fonction de son classement final
        for (int i = 0; i < cst::NB_TEAMS; ++i) {
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

            // Si l'équipe est sélectionnée on la met en avant et on modifie sa couleur
            if (i == teamSelected) {
                shader.addUniform3f("u_Color", glm::vec3(1.0f, 0.f, 1.0f));
                shader.addUniformMat4("u_Translate", glm::translate(model, glm::vec3(-500.f, -250.f, 200.f)));
            } else {
                shader.addUniform3f("u_Color", color);
                shader.addUniformMat4("u_Translate", glm::translate(model, glm::vec3(-500.f, -250.f, 0.f)));
            }

            //On dessine la ligne de l'équipe à partir des indices dans le vbo.
            ftn::VertexArray::Bind(i);
            ftn::Texture::Bind(i);
            glDrawElements(GL_TRIANGLES, indicesSize[i], GL_UNSIGNED_INT, nullptr);
        }
        window->update();
    } while (!window->shouldClose());

    //On supprime tous nos pointeurs pour éviter les fuites de mémoire
    delete data;
    ftn::Texture::Destroy();
    ftn::IndexBuffer::Destroy();
    ftn::VertexBuffer::Destroy();
    ftn::VertexArray::Destroy();
    ftn::Application::Destroy();
    return 0;
}