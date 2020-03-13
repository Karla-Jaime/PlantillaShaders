#version 330 core
//Version de openGL-->Siempre es la primera linea

/*
2 Objetivos principales
  -Establecer valor para gl_Position
  -Enviar valores al fragment shader
*/

//Atributos de entrada (son los que vienen desde c++)
in vec4 posicion;
in vec4 color;
//Uniforms
uniform mat4 transformaciones;

//Atributos de salida (Van hacia el fragment shader)
out vec4 fragmentColor;

//Funcion Main 
void main() {
	//Posicion del vertice (vec4)
	gl_Position = transformaciones * posicion;


	//Establecer valores de atributos de salida
	fragmentColor = color;


}

