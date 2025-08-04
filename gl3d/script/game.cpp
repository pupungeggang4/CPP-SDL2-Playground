#include "general.hpp"
#include "objs.hpp"

Game::Game() {
    gameGLInit();
    gameSDLInit();
    gameVarInit();
    run();
}

void Game::gameGLInit() {
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    // Window
    window = glfwCreateWindow(800, 600, "3D Game", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, cbWindowSizeChange);
    glfwSetKeyCallback(window, cbKey);
    gladLoadGL();

    // GL
    // Loading Shader
    std::ifstream f;
    f.open("shader/vertex.vert");
    std::stringstream vSourceSS;
    vSourceSS << f.rdbuf();
    std::string vSourceStr = vSourceSS.str();
    vSourceStr.append(1, 0); // Null-terminate
    const GLchar *vSource = vSourceStr.c_str();
    f.close();

    f.open("shader/fragment.frag");
    std::stringstream fSourceSS;
    fSourceSS << f.rdbuf();
    std::string fSourceStr = fSourceSS.str();
    fSourceStr.append(1, 0); // Null-terminate
    const GLchar *fSource = fSourceStr.c_str();
    f.close();

    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vSource, NULL);
    glCompileShader(vShader);
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fSource, NULL);
    glCompileShader(fShader);
    program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, 2048, NULL, infoLog);
        std::cout << "v " << infoLog << std::endl;
    }
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, 2048, NULL, infoLog);
        std::cout << "f " << infoLog << std::endl;
    }

    luModeV = glGetUniformLocation(program, "u_mode_v");
    luPPos = glGetUniformLocation(program, "u_p_pos");
    luPSize = glGetUniformLocation(program, "u_p_size");
    luPRot = glGetUniformLocation(program, "u_p_rot");
    luMPos = glGetUniformLocation(program, "u_m_pos");
    luMSize = glGetUniformLocation(program, "u_m_size");
    luMRot = glGetUniformLocation(program, "u_m_rot");
    luCPos = glGetUniformLocation(program, "u_c_pos");
    luCRot = glGetUniformLocation(program, "u_c_rot");
    luCProj = glGetUniformLocation(program, "u_c_proj");
    luModeF = glGetUniformLocation(program, "u_mode_f");
    luLightD = glGetUniformLocation(program, "u_light_d");
    luColor = glGetUniformLocation(program, "u_color");

    laPosition = glGetAttribLocation(program, "a_position");
    laTexcoord = glGetAttribLocation(program, "a_texcoord");
    laNormal = glGetAttribLocation(program, "a_normal");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &bTriangle);
    glGenBuffers(1, &bHUD);
    glGenBuffers(1, &bCuboid);
    glGenBuffers(1, &bCuboidIndex);

    std::cout << bTriangleData.size() << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, bTriangle);
    glBufferData(GL_ARRAY_BUFFER, bTriangleData.size() * sizeof(float), &bTriangleData[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, bHUD);
    glBufferData(GL_ARRAY_BUFFER, bHUDData.size() * sizeof(float), &bHUDData[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, bCuboid);
    glBufferData(GL_ARRAY_BUFFER, bCuboidData.size() * sizeof(float), &bCuboidData[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bCuboidIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bCuboidIndexData.size() * sizeof(unsigned int), &bCuboidIndexData[0], GL_STATIC_DRAW);
}

void Game::gameSDLInit() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_TIMER);
    SDL_Init(SDL_INIT_AUDIO);
}

void Game::gameVarInit() {
    camera = make_shared<Camera3>();
    world = make_shared<World>();
    std::array<float, 4> a = {0.0, 1.0, 1.0, 1.0};
    c = make_shared<ColorCuboid3>(
        make_shared<Vec3>(0.0, 0.0, 0.0), make_shared<Vec3>(0.5, 0.5, 0.5), make_shared<Vec3>(0.0, 0.0, 0.0), (std::array<float, 4>){0.0, 1.0, 1.0, 1.0}
    );
}

void Game::run() {
    while (!glfwWindowShouldClose(window)) {
        unsigned int start = SDL_GetTicks();
        loop();
        unsigned int end = SDL_GetTicks();
        delta = end - start;

        if (delta < fDelta) {
            delta = fDelta;
            SDL_Delay(fDelta - delta);
        }

        glfwPollEvents();
    }
}

void Game::loop() {
    c->rot->x += 0.5 * 16 / 1000;
    c->rot->y += 0.5 * 16 / 1000;

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(program);

    glBindVertexArray(vao);

    glEnable(GL_DEPTH_TEST);
    c->render(this, this->camera, this->world->lightD);
    
    glfwSwapBuffers(window);
}

void Game::cbWindowSizeChange(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void Game::cbKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
    std::cout << action << std::endl;
}