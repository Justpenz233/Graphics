#include <iostream>
#include <fstream>
#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

using namespace std;

#define DebugP(x) std::cout << "Line" << __LINE__ << "	" << #x << "=" << x << std::endl



#define PATH_SHADER_VERT "VShader.vert"
#define PATH_SHADER_FRAG "FShader.frag"

GLuint VBO, VAO, EBO;
GLuint VertexShader;
GLuint FragmentShader;
GLuint ShaderProgram;

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

bool CreateVertexShader();
//Create and compile Vertex shader progarm

bool CreateFragmentShader();
//Create and compile Fragment shader

bool CreateProgram();
//Create program and bind shaders

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
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	//Vertices set
	

	if (!CreateVertexShader()) {
		cout << "Compile Vertex Shader Failed!\n Program shut down\n";
		system("pause");
		return 0;
	}

	if (!CreateFragmentShader()) {
		cout << "Compile Fragment Shader Failed!\n Program shut down\n";
		system("pause");
		return 0;
	}

	if (!CreateProgram()) {
		cout << "Compile Shader Program Failed!\n Program shut down\n";
		system("pause");
		return 0;
	}


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(0);



	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(ShaderProgram);
		glBindVertexArray(VAO);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}//Loop while Not quit

	glfwTerminate();
	//Release memeroy
	return 0;
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

void Work(GLFWwindow * window)
{
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
bool CreateVertexShader() {
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

/*
Create a vertex shader
Will report info log when Failed
*/
bool CreateFragmentShader()
{
	
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* t = readFileIntoString(PATH_SHADER_FRAG);
	glShaderSource(FragmentShader, 1, &t, NULL);
	glCompileShader(FragmentShader);
	//Check if compilation is all right
	int  success;
	char infoLog[512];
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}
	else {
		std::cout << "Compile Fragment shader success\n";
		return 1;
	}
}

/*
Create a Program bind VertexShader and FragmentShader
Will report info log when Failed
*/
bool CreateProgram()
{
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);
	int success;
	char infoLog[512];
	glGetShaderiv(ShaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(ShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PORGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}
	else {

		std::cout << "Compile Shader program success\n";

		return 1;
	}
}

