#include "general.hpp"
#include "objs.hpp"

Game::Game() {
    gameGLInit();
    gameSDLInit();
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

void Game::run() {
    while (!glfwWindowShouldClose(window)) {
        loop();
    }
}

void Game::loop() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(program);

    glBindVertexArray(vao);

    glUniform1i(luModeV, 1);
    glUniform1i(luModeF, 3);
    glUniform3f(luMPos, 0.0, 0.0, 0.0);
    glUniform3f(luMRot, 0.5, 0.5, 0.0);
    glUniform3f(luMSize, 1.0, 1.0, 1.0);
    glUniform3f(luColor, 1.0, 0.0, 1.0);
    glUniform3f(luCPos, 0.0, 0.0, -3.0);
    glUniform3f(luCRot, 0.0, 0.0, 0.0);
    glUniform4f(luCProj, 1.0, 4.0 / 3.0, 0.1, 10.0);
    glUniform3f(luLightD, 0.0, 0.0, 1.0);

    glBindBuffer(GL_ARRAY_BUFFER, bCuboid);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bCuboidIndex);
    glVertexAttribPointer(laPosition, 3, GL_FLOAT, false, sizeof(float) * 8, (void*)(0));
    glVertexAttribPointer(laTexcoord, 2, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glVertexAttribPointer(laNormal, 3, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 5));
    glEnableVertexAttribArray(laPosition);
    glEnableVertexAttribArray(laTexcoord);
    glEnableVertexAttribArray(laNormal);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*)(0));
    //std::cout << glGetError() << std::endl;
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Game::cbWindowSizeChange(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void Game::cbKey(GLFWwindow* window, int key, int scancode, int action, int mods) {

}