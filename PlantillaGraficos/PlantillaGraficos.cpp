// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h> 
#include <stdlib.h> 
#define GLEW_STATIC 
 
#include"GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "Shader.h"
#include "vertice.h"
#include <vector>


using namespace std;
//Como una Lista de C#
vector<Vertice> triangulo;
//Cada elem. que queramos renderear necesita 
//Un vertex array y un buffer;
GLuint vertexArrayTrianguloID;
GLuint bufferTrianguloID;

vector <Vertice> cuadrado;
GLuint vertexArrayCuadradoID;
GLuint bufferCuadradoID;
//Para usar shader
//Instancia del Shader
Shader *shader;
//Identificadores para mapeo de atributos
//de entrada del vertex Shader
GLuint posicionID;
GLuint colorID;

void inicializarCuadrado() {
	Vertice V1 = {
		vec3(-1.0f,-0.6f,0.0f),
		vec4(0.15f,0.30f,0.00f,1.0f)
	};
	Vertice V2 = {
		vec3(1.0f,-0.6f,0.0f),
		vec4(0.15f,0.30f,0.00f,1.0f)
	};
	Vertice V3 = {
		vec3(1.0f,-1.0f,0.0f),
		vec4(0.15f,0.30f,0.00f,1.0f)

	};
	Vertice V4 = {
		vec3(-1.0f,-1.0f,0.0f),
		vec4(0.15f,0.30f,0.00f,1.0f)
	};


	cuadrado.push_back(V1);
	cuadrado.push_back(V2);
	cuadrado.push_back(V3);
	cuadrado.push_back(V4);

}

void inicializarTriangulo() {
	Vertice v1 = {
		vec3(0.25f,0.3f,0.0f),
		vec4(0.8f,0.1f,0.0f,1.0f)
	};
	Vertice v2 = {
		vec3(-0.25,0.3f,0.0f),
		vec4(0.8f,0.1f,0.0f,1.0f)
	};
	Vertice v3 = {
		vec3(-0.8,-0.6f,0.0f),
		vec4(0.8f,0.1f,0.0f,1.0f)
	};
	Vertice v4 = {
		vec3(0.8,-0.6f,0.0f),
		vec4(0.8f,0.1f,0.0f,1.0f)
	};
	triangulo.push_back(v1);
	triangulo.push_back(v2);
	triangulo.push_back(v3);
	triangulo.push_back(v4);
	//


}

void dibujar() {
	//Elegir shader
	shader->enlazar();
	//Elegir el vertexArray 
	glBindVertexArray(vertexArrayTrianguloID);
	//Llamar la funcion de dibujo-Dibujar
	glDrawArrays(GL_QUADS, 0, triangulo.size());

	//Cuadrado
	glBindVertexArray(vertexArrayCuadradoID);
	glDrawArrays(GL_QUADS,0, cuadrado.size());

	//Soltar Bind
	glBindVertexArray(0);
	//Soltar/desenlazar Shader
	shader->desenlazar();

}

int main()
{
	//Declarar una ventana 
	GLFWwindow* window;


	//Si no se pudo inicializar GLFW  //Terminamos Ejecución 
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(600, 600, "Ventana Cookie", NULL, NULL);
	
	//Si no se pudo crear la ventana
	//Terminamos ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Si se pudo inicializar GLFW
	//Inicializams la ventana


	//Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);
	//UsarFuncionesdeOpengl
	//Una vez establecido el contexto. Se activan las funciones "modernas" (gpu)
	glewExperimental = true;
	
	GLenum errores = glewInit();
	if (errores != GLEW_OK) {
		glewGetErrorString(errores);
	}

	const GLubyte  *versionGL = glGetString(GL_VERSION);

	cout << "Version OpenGl: " << versionGL;
	//Inicializar
	inicializarTriangulo();
	inicializarCuadrado();


	const char* rutaVertexShader = "Vertex.shader";
	const char* rutaFragmentShader = "FragmentShader.shader";

	
	shader = new Shader(rutaVertexShader,rutaFragmentShader);

	//Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");

	shader->desenlazar();


	//Crear el vertex array del triangulo
	glGenVertexArrays(1, &vertexArrayTrianguloID);
	glBindVertexArray(vertexArrayTrianguloID);
	//Vertex buffer
	glGenBuffers(1, &bufferTrianguloID);
	glBindBuffer(GL_ARRAY_BUFFER,bufferTrianguloID);
	//Asociar datos al buffer 
	glBufferData(GL_ARRAY_BUFFER,sizeof(Vertice) * triangulo.size(), triangulo.data(),GL_STATIC_DRAW);
	//Habilitar atributos de shader 
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	//Especificar a OpenGl como comunicarse posicion
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE,sizeof(Vertice),0);
	//Especificar a OpenGl como comunicarse con el color
	glVertexAttribPointer(colorID,4,GL_FLOAT,GL_FALSE,sizeof(Vertice),(void*)sizeof(vec3));	

	//Proceso para inicializa el Vertex para el Cuadrado
	glGenVertexArrays(1, &vertexArrayCuadradoID);
	glBindVertexArray(vertexArrayCuadradoID);
	glGenBuffers(1, &bufferCuadradoID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferCuadradoID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * cuadrado.size(), cuadrado.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice),0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));

	//Soltar el vertexArray y el buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	

	


	//Clilo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {

		//Establecer región de dibujo 
		glViewport(0, 0, 600, 600);
		//Establecemos el color de borrado
		glClearColor(0.49, 0.73, 0.91,1);
		//Borrar
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		dibujar();
		//Se comunica con los dispositivos de entrada
		glfwPollEvents();
		// Actualizar los valores y dibujar 
		glfwSwapBuffers(window);
	}
	//Despues del ciclo de dibujo Eliminamos ventana y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();
}