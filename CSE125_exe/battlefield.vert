attribute vec4 VertexTangent;

varying vec4 Position;
varying vec3 Normal;
varying vec2 TexCoords;
varying vec3 Tangent;

varying vec3 LightDir;
varying vec3 ViewDir;
varying mat3 toObjectLocal;
uniform mat4 ModelView;

varying vec3 ReflectDir;


void main()
{
    TexCoords= vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
    Normal = normalize( gl_NormalMatrix * gl_Normal);
    Position = gl_ModelViewMatrix * gl_Vertex;
  
    Tangent = normalize(gl_NormalMatrix * vec3(VertexTangent));
    vec3 binormal = normalize(cross(Normal, Tangent)) * VertexTangent.w;
    toObjectLocal = mat3(
    Tangent.x, binormal.x, Normal.x,
    Tangent.y, binormal.y, Normal.y,
    Tangent.z, binormal.z, Normal.z);
    
	vec4 LightPosition = vec4(0.0, 10.0, -20.0, 1.0);
    LightDir = normalize(toObjectLocal * (LightPosition.xyz - Position.xyz));
    ViewDir = toObjectLocal * normalize(-Position.xyz);
    
	//reflect
	//Reflection
    mat4 tmp = mat4(1.0);
    vec3 WorldCameraPosition = vec3(0, 0, 0);
    vec3 worldPos = vec3(ModelView * vec4(gl_Vertex.xyz,1.0));
    vec3 worldNorm = vec3(ModelView * vec4(gl_Normal.xyz,0.0));
    vec3 worldView = normalize( WorldCameraPosition - worldPos );
    ReflectDir = reflect(-worldView, worldNorm );
    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}