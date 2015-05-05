uniform samplerCube skybox;

varying vec3 texCoords;

void main(){
	//gl_FragColor = vec4(1,0,0,1);
	gl_FragColor = texture(skybox, texCoords);
}