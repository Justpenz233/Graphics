#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
using namespace std;
#define DebugP(x) std::cout << "Line" << __LINE__ << "	" << #x << "=" << x << std::endl
void framebuffer_size_callback
(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	//This area can add some code to do sth when windows were modified

	//DebugP(width);
	//DebugP(height);
}



int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Set the option
	GLFWwindow* window = glfwCreateWindow(800, 600, "TEST", NULL, NULL);
	if (window == NULL) {
		cout << "Create Windows Failed" << endl;
		return -1;
	}//Create a windows

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}//Dont know the function yet

	glViewport(0, 0, 800, 600);
	//Set viewport size

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//register a function

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}//Loop while Not quit

	glfwTerminate();
	//release memeroy
	return 0;
}