#include "Shader.h"

GLuint Shader::getID() {
	return shaderID;
}

//constructor

Shader::Shader(const char* rutaVertexShader, const char* rutaFragmentShader) {
	//LecturadeArchivos

	string codigoVertexShader;
	ifstream vertexShaderStream(rutaVertexShader, ios::in);

	if (vertexShaderStream.is_open()) {
		string linea;
		while (getline(vertexShaderStream, linea)) {
			codigoVertexShader += linea + "\n";
		}
		vertexShaderStream.close();
	}
	else {
		cout << "No se pudo abrir el archivo: " <<
			rutaVertexShader << endl;
	}
	string codigoFragmentShader;
	ifstream fragmentShaderStream(rutaFragmentShader, ios::in);

	if (fragmentShaderStream.is_open()) {
		string linea;
		while (getline(fragmentShaderStream, linea)) {
			codigoFragmentShader += linea + "\n";
		}
		fragmentShaderStream.close();
	}
	else {
		cout << "No se pudo abrir el archivo: " << rutaFragmentShader << endl;
	}
	//Cambio de formato string a char
	const char* cadenaCodigoVertexShader = codigoVertexShader.c_str();
	const char* cadenaCodigoFragmentShader = codigoFragmentShader.c_str();

	//1.- Crear el programa de Shader
	shaderID= glCreateProgram();
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//2.- Cagar el código del Shader
	glShaderSource(vertexShaderID, 1,&cadenaCodigoVertexShader,NULL);
	glShaderSource(fragmentShaderID, 1, &cadenaCodigoFragmentShader, NULL);

	//3.- Compilar los Shaders
	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	//4.- Verificar errores de compilacion
	verificarCompilaicion(vertexShaderID);
	verificarCompilaicion(fragmentShaderID);

	//5.- Adjuntar  los shaders al programa
	glAttachShader(shaderID,vertexShaderID);
	glAttachShader(shaderID, fragmentShaderID);

	//6.- Vincular el programa 
	glLinkProgram(shaderID);

	//7.- Verificar si hubo error de vinculación 
	verificarVinculacion(shaderID);

	//8.- Usar el programa
	glUseProgram(shaderID);
}
//Parte del paso 4
void Shader::verificarCompilaicion(GLuint id) {
	GLint resultado;
	GLint longitudLog;

	glGetShaderiv(id, GL_COMPILE_STATUS, &resultado);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &longitudLog);

	if (resultado == GL_FALSE) {
		cout << "No se pudo compilar shader" << endl;

	}
	if (longitudLog > 0) {
		//Inicia una lista de char con el numero de elem. indicados en longitud
		vector <char> mensajeError(longitudLog);
		//Obtener mensajes del compilador y los guarda en la variable mensaje error
		glGetShaderInfoLog(id,longitudLog,NULL, &mensajeError[0]);
		//Recorrer el vector e imprimir los elementos
		//
		for (vector<char>::const_iterator i = mensajeError.begin(); i != mensajeError.end(); i++) {
			cout << *i;
		} 
	}
}
//Parte del paso 7
void Shader::verificarVinculacion(GLuint id) {
	GLint estadoVinculacion, estadoValidacion;
	glGetProgramiv(id, GL_LINK_STATUS,&estadoVinculacion);
	if (estadoVinculacion == GL_FALSE) {
		cout << "No se pudo vincular el programa" << endl;
	}
	glGetProgramiv(id, GL_VALIDATE_STATUS, &estadoValidacion);
	if (estadoValidacion == GL_FALSE) {
		cout << "No se pudo validar  vinculacion" << endl;
	}
}

void Shader::enlazar() {
	glUseProgram(shaderID);
}

void Shader::desenlazar() {
	glUseProgram(0);
}