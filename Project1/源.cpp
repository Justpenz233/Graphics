#include <iostream>
#include <fstream>
#include <string>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

using namespace std;

#define DebugP(x) std::cout << "Line" << __LINE__ << "	" << #x << "=" << x << std::endl



#define PATH_SHADER_VERT "VShader.vert"
#define PATH_SHADER_FRAG

GLuint VBO, VAO;
GLuint VertexShader;
GLuint FragmentShader;

void Work(GLFWwindow *window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	//This area can add some code to do sth when windows were modified

	//DebugP(width);
	//DebugP(height);
}
//Called when windows'size changed

void Init_VBO(GLfloat *vertices);
//Create a VBO

bool Init_VertexShader();
//Create Vertex shader progarm

const char *readFileIntoString(string filename);
// Read a file into string


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //OpenGL V3.3
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
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//Register a function
	//Called when frame size were changed


	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
	//Vertices set
	Init_VBO(vertices);
	if (!Init_VertexShader()) {
		printf("Compile Vertex Shader Failed!\n Program shut down\n");
		return 0;
	}
	
	

	while (!glfwWindowShouldClose(window))
	{
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}//Loop while Not quit







	glfwTerminate();
	//release memeroy
	return 0;
}


void Work(GLFWwindow *window) {
	
}

const char * readFileIntoString(string filename)
{
	string s;
	ifstream ifile(filename);
	char ch;
	s.clear();
	while (!ifile.eof() && ifile.get(ch)) {
		s += ch;
	}
	return s.c_str();
}


void Init_VBO(GLfloat *vertices) {
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Bind a Buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Create a Vertices Buffer and allocate memory
}

bool Init_VertexShader() {

	//Create shader and compile
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char *vertexShaderSource = readFileIntoString(PATH_SHADER_VERT);
	glShaderSource(VertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(VertexShader);
	
	//Check if compilation is all right
	int  success;
	char infoLog[512];
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}
	else return 1;
}

