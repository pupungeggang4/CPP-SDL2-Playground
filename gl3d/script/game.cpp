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
    vSourceStr.append(1, 0);
    const GLchar *vSource = vSourceStr.c_str();
    f.close();

    f.open("shader/fragment.frag");
    std::stringstream fSourceSS;
    fSourceSS << f.rdbuf();
    std::string fSourceStr = fSourceSS.str();
    fSourceStr.append(1, 0);
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

    laPosition = glGetAttribLocation(program, "a_position");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &bTriangle);

    glBindBuffer(GL_ARRAY_BUFFER, bTriangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, &bTriangleData[0], GL_STATIC_DRAW);

    std::vector<int> a = {1};
    a.push_back(2);
    std::cout << a[1] << std::endl;
}

void Game::gameSDLInit() {
    //SDL_Init(SDL_INIT_EVERYTHING);
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
    glBindBuffer(GL_ARRAY_BUFFER, bTriangle);
    glVertexAttribPointer(laPosition, 3, GL_FLOAT, false, sizeof(float) * 3, (void*)(0));
    glEnableVertexAttribArray(laPosition);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
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