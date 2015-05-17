attribute float height;
attribute vec4 VertexTangent;

varying vec4 Position;
varying vec3 Normal;
varying vec2 TexCoords;
varying vec3 Tangent;

varying vec3[3] LightDir;
varying vec3 ViewDir;
varying vec3 ReflectDir;

uniform mat4 ModelView;


void main()
{
    TexCoords= vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
    Normal = normalize( gl_NormalMatrix * gl_Normal);
    Position = gl_ModelViewMatrix * gl_Vertex;
  
    
    Tangent = normalize(gl_NormalMatrix * vec3(VertexTangent));
    vec3 binormal = normalize(cross(Normal, Tangent)) * VertexTangent.w;
    mat3 toObjectLocal = mat3(
    Tangent.x, binormal.x, Normal.x,
    Tangent.y, binormal.y, Normal.y,
    Tangent.z, binormal.z, Normal.z);
    vec4 [3] LightPosition;
	LightPosition[0] =  vec4(0.0, 10.0, 20.0, 1.0);
	LightPosition[1] =  vec4(10,10,10,1.0);
	LightPosition[2] =  vec4(-10,10,-10,1.0);
    LightDir[0] = normalize(toObjectLocal * (LightPosition[0].xyz - Position.xyz));
	LightDir[1] = normalize(toObjectLocal * (LightPosition[1].xyz - Position.xyz));
	LightDir[2] = normalize(toObjectLocal * (LightPosition[2].xyz - Position.xyz));


	vec3 WorldCameraPosition = vec3(0, 0, 0);
    vec3 worldPos = vec3(ModelView * vec4(gl_Vertex.xyz,1.0));
    vec3 worldNorm = vec3(ModelView * vec4(gl_Normal.xyz,0.0));
    vec3 worldView = normalize( WorldCameraPosition - worldPos );

    ViewDir = toObjectLocal * normalize(-Position.xyz);
    ReflectDir = reflect(-worldView, worldNorm );
    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}