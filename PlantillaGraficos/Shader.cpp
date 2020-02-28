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

	
}
//Parte del paso 4
void Shader::verificarCompilaicion(GLuint id) {
	GLint resultado;
	GLint longitudLog;

	glGetShaderiv(id, GL_COMPILE_STATUS, &resultado);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &longitudLog);


}