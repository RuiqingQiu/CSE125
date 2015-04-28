

varying vec3 ReflectDir;

uniform samplerCube CubeMapTex;

float ReflectFactor;
vec4 MaterialColor;

layout( location = 0 ) out vec4 FragColor;

void main() {
	ReflectFactor = 0.85;
	MaterialColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
    // Access the cube map texture
    vec4 cubeMapColor = texture(CubeMapTex, ReflectDir);
    gl_FragColor = mix( MaterialColor, cubeMapColor, ReflectFactor);
}