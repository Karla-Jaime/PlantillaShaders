#version 330 core
//Primer l�nea siempre es la versi�n de openGL
//Objetivo:	Establecer valores de atributos de salida


//Atributos de entrada (Desde el Vertex Shader)
in vec4 fragmentColor;

//Atributos de Salida 
//1ro define la visualizaci�n del fragmento 
out vec4 salidaColor;

void main() {
	salidaColor = fragmentColor;
}