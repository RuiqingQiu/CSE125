varying vec3 texCoords;

void main(){
	texCoords = gl_Vertex.xyz;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}