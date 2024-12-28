//Then I heard the voice of the Lord saying "Whom shall I send? And who shall go for us?" And I said, "Here am I. send me!"
//Lord give me one more chance;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

constexpr auto numVAOs = 1;

GLuint renderingProgram;
GLuint vao[numVAOs];

using namespace std; //why do so many people avoid this one line of code and write std 100 times in there project?

GLuint createShaderProgram() 
{
    const char* vShaderSource = //vertex shader (easy/lazy way)
        "#version 430 \n"
        "void main(void) \n"
        "{gl_Position = vec4(0.0,0.0,0.0,1.0); }";

    const char* fShaderSource = //fragment shader (easy/lazy way)
        "#version 430 \n"
        "out vec4 color; \n"
        "void main(void) \n"
        "{color = vec4(0.0,0.0,1.0,1.0); }";

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vShaderSource, NULL);
    glShaderSource(fShader, 1, &fShaderSource, NULL);
    glCompileShader(vShader);
    glCompileShader(fShader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    return vfProgram;
}

void init(GLFWwindow* window) 
{
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}


void display(GLFWwindow* window, double currentTime)
{
    glUseProgram(renderingProgram);
    glDrawArrays(GL_POINTS, 0, 1);
}

int main(void)
{
    if (!glfwInit()) //if the GLFWinit workie it returns true :)
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //setting GLFW to version 4.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //width,height, title, isFullscreen, isResorceSharring; window is made a pointer because its much more efficent to just pass the address the the entire window object each cycle;
    GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGl Test0; Init(C01E);", NULL, NULL);
    glfwMakeContextCurrent(window); //linking GLFW to open GL

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSwapInterval(1); //this is required for Vsync
    init(window);

    while (!glfwWindowShouldClose(window))
    {
        display(window, glfwGetTime());
        glfwSwapBuffers(window); //this is also required for Vsync
        glfwPollEvents(); // this handles window events like keys being pressed;
    }
    //clear the allocated memory like a good programmer do :)
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}