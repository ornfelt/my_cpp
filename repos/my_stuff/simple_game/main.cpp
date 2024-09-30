#include <SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>

// Vertex shader source code
const GLchar* vertexSource = R"glsl(
    #version 330 core
    layout(location = 0) in vec2 position;
    uniform vec2 offset;
    void main()
    {
        gl_Position = vec4(position + offset, 0.0, 1.0);
    }
)glsl";

// Fragment shader source code
//const GLchar* fragmentSource = R"glsl(
//    #version 330 core
//    out vec4 color;
//    void main()
//    {
//        color = vec4(0.0, 1.0, 0.0, 1.0); // Green color
//    }
//)glsl";
const GLchar* fragmentSource = R"glsl(
    #version 330 core
    out vec4 color;
    uniform vec4 rectColor;
    void main()
    {
        color = rectColor;
    }
)glsl";


// Vertex shader for the triangle obstacle
const GLchar* obstacleVertexSource = R"glsl(
    #version 330 core
    layout(location = 0) in vec2 position;
    uniform vec2 offset;
    void main()
    {
        gl_Position = vec4(position + offset, 0.0, 1.0);
    }
)glsl";

// Fragment shader for the triangle obstacle
const GLchar* obstacleFragmentSource = R"glsl(
    #version 330 core
    out vec4 color;
    void main()
    {
        color = vec4(1.0, 0.0, 0.0, 1.0); // Red color
    }
)glsl";

void checkShaderCompileStatus(GLuint shader) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
    }
}

void checkProgramLinkStatus(GLuint program) {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("ERROR::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
}

bool checkCollision(float rectX, float rectY, float triX, float triY, float triSize) {
    // Check if the rectangle and triangle intersect (simple bounding box collision detection)
    float halfSize = 0.1f; // Size of the rectangle
    if (rectX + halfSize > triX - triSize && rectX - halfSize < triX + triSize &&
        rectY + halfSize > triY - triSize && rectY - halfSize < triY + triSize) {
        return true;
    }
    return false;
}

int main(int argc, char* argv[])
{
    srand(time(NULL)); // Seed the random number generator

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Set OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create a window
    SDL_Window* window = SDL_CreateWindow("OpenGL Window", 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          800, 600, 
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create OpenGL context
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        printf("Could not create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("Could not initialize GLEW\n");
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompileStatus(vertexShader);

    // Compile fragment shader for the rectangle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompileStatus(fragmentShader);

    // Link shaders into a program for the rectangle
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLinkStatus(shaderProgram);

    // Compile vertex shader for the triangle obstacle
    GLuint obstacleVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(obstacleVertexShader, 1, &obstacleVertexSource, NULL);
    glCompileShader(obstacleVertexShader);
    checkShaderCompileStatus(obstacleVertexShader);

    // Compile fragment shader for the triangle obstacle
    GLuint obstacleFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(obstacleFragmentShader, 1, &obstacleFragmentSource, NULL);
    glCompileShader(obstacleFragmentShader);
    checkShaderCompileStatus(obstacleFragmentShader);

    // Link shaders into a program for the triangle obstacle
    GLuint obstacleShaderProgram = glCreateProgram();
    glAttachShader(obstacleShaderProgram, obstacleVertexShader);
    glAttachShader(obstacleShaderProgram, obstacleFragmentShader);
    glLinkProgram(obstacleShaderProgram);
    checkProgramLinkStatus(obstacleShaderProgram);

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(obstacleVertexShader);
    glDeleteShader(obstacleFragmentShader);

    // Set up vertex data (and buffer(s)) and configure vertex attributes for the rectangle
    GLfloat vertices[] = {
        -0.1f, -0.1f,
         0.1f, -0.1f,
         0.1f,  0.1f,
        -0.1f,  0.1f
    };
    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    // Set up vertex data (and buffer(s)) and configure vertex attributes for the triangle obstacle
    GLfloat triangleVertices[] = {
        0.0f,  0.1f,
        -0.1f, -0.1f,
        0.1f, -0.1f
    };

    GLuint triangleVBO, triangleVAO;
    glGenVertexArrays(1, &triangleVAO);
    glGenBuffers(1, &triangleVBO);

    glBindVertexArray(triangleVAO);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    // Main loop
    int running = 1;
    SDL_Event event;
    float x_offset = 0.0f, y_offset = 0.0f;
    float move_speed = 0.01f;

    // Initial position of the triangle obstacle
    float triangleX = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
    float triangleY = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
    float triangleMoveSpeed = 0.005f;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: running = 0; break;
                    case SDLK_w: y_offset += move_speed; break;
                    case SDLK_s: y_offset -= move_speed; break;
                    case SDLK_a: x_offset -= move_speed; break;
                    case SDLK_d: x_offset += move_speed; break;
                }
            }
        }

        // Check for collision
        bool isColliding = checkCollision(x_offset, y_offset, triangleX, triangleY, 0.1f);

        // Change the color of the rectangle based on collision
        GLfloat rectColor[4];
        if (isColliding) {
            rectColor[0] = 1.0f; // Red
            rectColor[1] = 0.0f;
            rectColor[2] = 0.0f;
            rectColor[3] = 1.0f;
        } else {
            rectColor[0] = 0.0f; // Green
            rectColor[1] = 1.0f;
            rectColor[2] = 0.0f;
            rectColor[3] = 1.0f;
        }

        // Prevent movement through the obstacle
        if (isColliding) {
            //std::cout << "Collision!" << std::endl; 
            switch (event.key.keysym.sym) {
                case SDLK_w: y_offset -= move_speed; break;
                case SDLK_s: y_offset += move_speed; break;
                case SDLK_a: x_offset += move_speed; break;
                case SDLK_d: x_offset -= move_speed; break;
            }
        }

        // Move the triangle obstacle randomly
        triangleX += (rand() % 3 - 1) * triangleMoveSpeed;
        triangleY += (rand() % 3 - 1) * triangleMoveSpeed;

        // Keep the triangle within the window bounds
        if (triangleX > 1.0f || triangleX < -1.0f) triangleX = 0.0f;
        if (triangleY > 1.0f || triangleY < -1.0f) triangleY = 0.0f;

        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program for the rectangle
        glUseProgram(shaderProgram);

        // Update the offset and color uniform for the rectangle
        GLint offsetLocation = glGetUniformLocation(shaderProgram, "offset");
        glUniform2f(offsetLocation, x_offset, y_offset);
        GLint colorLocation = glGetUniformLocation(shaderProgram, "rectColor");
        glUniform4fv(colorLocation, 1, rectColor);

        // Draw the rectangle
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Use the shader program for the triangle obstacle
        glUseProgram(obstacleShaderProgram);

        // Update the offset uniform for the triangle obstacle
        GLint triangleOffsetLocation = glGetUniformLocation(obstacleShaderProgram, "offset");
        glUniform2f(triangleOffsetLocation, triangleX, triangleY);

        // Draw the triangle obstacle
        glBindVertexArray(triangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &triangleVAO);
    glDeleteBuffers(1, &triangleVBO);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(obstacleShaderProgram);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

