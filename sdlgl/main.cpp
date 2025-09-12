#include <glad/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

const char *vSource = R"(#version 330
    uniform int u_mode_v;
    in vec4 a_position;
    in vec2 a_texcoord;
    in vec3 a_color;
    out vec3 p_color;
    out vec2 p_texcoord;

    void main() {
        gl_Position = a_position;
        if (u_mode_v == 0) {
            p_texcoord = a_texcoord;
        } else {
            p_color = a_color;
        }
    }
)";
const char *fSource = R"(#version 330
    precision highp float;
    uniform int u_mode_f;
    uniform sampler2D u_texture;
    in vec3 p_color;
    in vec2 p_texcoord;
    out vec4 o_color;

    void main() {
        if (u_mode_f == 0) {
            o_color = texture(u_texture, p_texcoord);
        } else {
            o_color = vec4(p_color, 1.0);
        }
    }
)";

int main() {
    float scale = 1.25;
    const float bColorData[9] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    const float bTriangleData[9] = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0};
    const float bHUDData[24] {
        -1.0, -1.0, 0.0, 1.0, 1.0, -1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 0.0, -1.0, -1.0, 0.0, 1.0,
        1.0, 1.0, 1.0, 0.0, -1.0, 1.0, 0.0, 0.0
    };

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("font/neodgm.ttf", 32);
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, "Hello, SDL Mesh!", {255, 255, 255});

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_Window *window = SDL_CreateWindow("Triangle Example", 0, 0, 800, 600, SDL_WINDOW_OPENGL);
    SDL_SetWindowSize(window, 800 * scale, 600 * scale);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_Surface *surface = SDL_CreateRGBSurface(0, 800, 600, 32, 0, 0, 0, 0);
    SDL_Rect d = SDL_Rect({24, 24});

    gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vSource, NULL);
    glCompileShader(vertexShader);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fSource, NULL);
    glCompileShader(fragmentShader);
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[2048];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 2048, NULL, infoLog);
        std::cout << "v " << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 2048, NULL, infoLog);
        std::cout << "f " << infoLog << std::endl;
    }

    GLint luModeV = glGetUniformLocation(shaderProgram, "u_mode_v");
    GLint luModeF = glGetUniformLocation(shaderProgram, "u_mode_f");
    GLint laPosition = glGetAttribLocation(shaderProgram, "a_position");
    GLint laColor =  glGetAttribLocation(shaderProgram, "a_color");
    GLint laTexcoord = glGetAttribLocation(shaderProgram, "a_texcoord");
    GLuint vao, bColor, bTriangle, bHUD;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &bColor);
    glGenBuffers(1, &bTriangle);
    glGenBuffers(1, &bHUD);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, bColor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bColorData), bColorData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, bTriangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bTriangleData), bTriangleData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, bHUD);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bHUDData), bHUDData, GL_STATIC_DRAW);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    std::cout << glGetString(GL_VERSION) << std::endl;

    int running = 1;
    while (running) {
        SDL_FillRect(surface, NULL, 0);
        SDL_BlitSurface(textSurface, NULL, surface, &d);

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);

        glUniform1i(luModeV, 0);
        glUniform1i(luModeF, 0);
        glBindBuffer(GL_ARRAY_BUFFER, bHUD);
        glVertexAttribPointer(laPosition, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
        glVertexAttribPointer(laTexcoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(laPosition);
        glDisableVertexAttribArray(laColor);
        glEnableVertexAttribArray(laTexcoord);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
        
        glUniform1i(luModeV, 1);
        glUniform1i(luModeF, 1);
        glBindBuffer(GL_ARRAY_BUFFER, bTriangle);
        glVertexAttribPointer(laPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        glBindBuffer(GL_ARRAY_BUFFER, bColor);
        glVertexAttribPointer(laColor, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(laPosition);
        glEnableVertexAttribArray(laColor);
        glDisableVertexAttribArray(laTexcoord);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }
    return 0;
}
