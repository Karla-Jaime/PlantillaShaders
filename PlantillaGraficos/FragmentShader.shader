#version 330 core
//Primer línea siempre es la versión de openGL
//Objetivo:	Establecer valores de atributos de salida


//Atributos de entrada (Desde el Vertex Shader)
in vec4 fragmentColor;

//Atributos de Salida 
//1ro define la visualización del fragmento 
out vec4 salidaColor;

void main() {
	salidaColor = fragmentColor;
}