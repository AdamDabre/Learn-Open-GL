#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "src/shaders/Shader.hpp"
#include "src/textures/stb_image.h"
#include "src/camera/Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


void initGLFW()
{
    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using 
    // In this case, we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* createWindowGFLW(int width, int height, const char* windowName)
{
    GLFWwindow* window = glfwCreateWindow(width, height, windowName, NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr; // Return null pointer to indicate failure
    }
    return window;
}



glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);



float pitch = 0;
float yaw = 0;
float fov = 45.0f;
    
    // Camera
Camera mainCamera;

bool firstMouse = true;
unsigned int windowWidth = 1920;
unsigned int windowHeight = 1080;

float lastX = windowWidth / 2;
float lastY = windowHeight / 2;


    // Time
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

void mouse_callback(GLFWwindow* window, double xInput, double yInput)
{
    float xPos = static_cast<float>(xInput);
    float yPos = static_cast<float>(yInput);
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    // calculate the offset movement between the last and current frame
    float xoffset = xPos - lastX;
    float yoffset = lastY - yPos; // reversed since y-coordinates range from bottom to top

    lastX = xPos;
    lastY = yPos;

    mainCamera.ProcessMouseMovement(xoffset, yoffset);
    
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    mainCamera.ProcessMouseScroll(yoffset);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        mainCamera.move(FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mainCamera.move(BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        mainCamera.move(LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        mainCamera.move(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        mainCamera.move(DOWN, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        mainCamera.move(UP, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
int main()
{
    // initialize GLFW 
    initGLFW();

    // Create a GLFWwindow with x and y pixels defined
   

    GLFWwindow* window = createWindowGFLW(windowWidth, windowHeight, "Learn OpenGL Window");
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);


    // Error check if window creation fails
    if (!window) {
        return -1;
    }

    // Introduce the window into the current context. Telling glfw that we are using this window
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // Load GLAD so it configures OpenGL
    gladLoadGL();

    // Specify the viewport of OpenGL in the Window
    // In this case, the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, windowWidth, windowHeight);
    // configure global opengl state
    
    glEnable(GL_DEPTH_TEST);
    // To draw something, we first need to define the points, in normal screen coordinates., and specify the indexes
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3,  // second triangle
     
    };
    Shader firstShader("shaders/default.vert", "shaders/default.frag");

        // Creating a VBO. It allows us to store a large number of vertices in the GPU's memory. So we can send large batches of data.
        // VBO is an unsigned int as that is its "ID"
    unsigned int VBO;
        // glGenBuffers generates the buffer object
    glGenBuffers(1, &VBO);
        // Now we are binding the VBO and telling OpenGL that it's of type array
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // Now we can apply the vertices data to the buffer memory.
        // glBufferData is a function that copies the vertices data into the bound buffer.
        // It takes in the type of buffer, then the size of the data in bytes, and then the actual data we are sending it.
        // Its last parameter specifies how we want the graphics card to manage the data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // The Vertex Array Object(VAO) in OpenGL serves as a container or state object that stores configurations for vertex attribute pointersand their associated vertex buffer objects(VBOs).
        // It helps organizeand encapsulate the setup of vertex data.
        
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

        // Telling OpenGL how to interpret the vertex data
        // glVertexAttribPointer params -> index of the vertex attribute in the VAO ,num components per atrrubite,the dta type, 
        // if the values are gonna be offeseted 0 means is tightly packed, 
        // 1. Bind Vertex Array Object
    glBindVertexArray(VAO);
        // 2. Copy our vertices array into a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // 3. Then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

        // setting the texture information
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Textures .
    int textureWidth, textureHeight, numChannels;
    unsigned char* textureData = stbi_load("textures/container.jpg", &textureWidth, &textureHeight, &numChannels, 0);
  
        // creating an ID , textures are openGL objects and thus need an ID to be genrated
    unsigned int texture;
    glGenTextures(1, &texture);
        // binding the ID to say that its a 2D texture
    glBindTexture(GL_TEXTURE_2D, texture);
        // Generate the texture.
        // - Target: GL_TEXTURE_2D indicates a 2D texture.
        // - Mipmap Level: 0 is the base level.
        // - Format: GL_RGB specifies the format of the texture data.
        // - Dimensions: Set the width and height of the texture using textureWidth and textureHeight.
        // - Border: 0 (no border).
        // - Data Format: GL_RGB again for the internal format.
        // - Data Type: GL_UNSIGNED_BYTE indicates RGB data in unsigned byte form.
        // - Texture Data: Provide the actual texture data.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);

        // Generate mipmaps for the texture to enable smoother transitions between different levels of detail.
    glGenerateMipmap(GL_TEXTURE_2D);

        // Free the image memory .
    stbi_image_free(textureData);


    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load("textures/awesomeface.png", &textureWidth, &textureHeight, &numChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


    

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        // Processing inputs from keys and mouse
        processInput(window);

        // Specify the color of the background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

        // Clear the back buffer of the background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //float time = glfwGetTime() * 2;
        //float xOffset = 0.2f * sin(time);
        //float yOffset = 0.2f * cos(time);  // Using cos for circular motion in the z-direction

        firstShader.activate();
        //firstShader.setFloat("xOffset", xOffset);
        //firstShader.setFloat("yOffset", yOffset);

        firstShader.setInt("texture2", 1);
       
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // Binding the texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::rotate(transform, (float)glfwGetTime()/2, glm::vec3(0.0f, 0.0f, 1.0f));

        transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));
        // setting the model matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model,-(float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        /*glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));*/

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(mainCamera.getCameraSettings().zoom), 16 / 9.0f, 0.1f, 100.0f);



        // activating the shader and telling it what our projection,model and view matrix is.
        firstShader.activate();
        firstShader.setMat4("projection", projection);
        firstShader.setMat4("model", model);
        
        // Bind the VAO before the draw call
        glBindVertexArray(VAO);
        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            if (i % 2 == 0)
            {
                model = glm::rotate(model, -(float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            }
            else {
                float angle = 90.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            }
            float angle = 90.0f * i;
            firstShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // The first param says we want to draw triangles, the second says to draw 6 indices, third is the type of indices
        glDrawArrays(GL_TRIANGLES, 0, 36);

            // When defining a camera, we need the position, the direction its looking at (target)
            // a vector point to the right and a vector pointing upwards

        glm::mat4 view;

        view = mainCamera.getViewMatrix();
        firstShader.setMat4("view", view);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Unbind the VAO after the draw cal
        glBindVertexArray(0);

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);

        // Take care of all GLFW events
        glfwPollEvents();
       
    }

        // Delete window before ending the program. We don't want it to linger around
    glfwDestroyWindow(window);
        // Terminate GLFW before ending the program
    glfwTerminate();

    return 0;
}
