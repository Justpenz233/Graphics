#include <iostream>
#include <fstream>
#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

using namespace std;

#define DebugP(x) std::cout << "Line" << __LINE__ << "	" << #x << "=" << x << std::endl



#define PATH_SHADER_VERT "VShader.vert"
#define PATH_SHADER_FRAG "Fshader.frag"

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
//Create and compile Vertex shader progarm

bool Init_FragmentShader();
//Create and compile Fragment shader

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
		cout << "Compile Vertex Shader Failed!\n Program shut down\n";
		system("pause");
		return 0;
	}
	if (!Init_FragmentShader()) {
		cout << "Compile Fragment Shader Failed!\n Program shut down\n";
		system("pause");
		return 0;
	}

	
	

	while (!glfwWindowShouldClose(window))
	{
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}//Loop while Not quit

	glfwTerminate();
	//Release memeroy
	return 0;
}


void Work(GLFWwindow *window) {
	
}

/*
Read a file into a string
return const char*
Used in create shaders
*/
const char *readFileIntoString(string filename)
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

/*
Create a buffer && bind to VBO
*/
void Init_VBO(GLfloat *vertices) {
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Bind a Buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Create a Vertices Buffer and allocate memory
}

/*
Create a vertex shader
Will report info log when Failed
*/
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
	else {
		std::cout << "Compile Vertex shader success\n";
		return 1;
	}
}

bool Init_FragmentShader()
{
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* t = readFileIntoString(PATH_SHADER_FRAG);
	glShaderSource(fragmentShader, 1, &t, NULL);
	glCompileShader(fragmentShader);
	//Check if compilation is all right
	int  success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}
	else {
		std::cout << "Compile Fragment shader success\n";
		return 1;
	}
}

