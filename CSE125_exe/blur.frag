uniform sampler2D tex;
uniform sampler2D norm;
uniform sampler2D gloss;
uniform sampler2D metallic;

varying vec4 Position;
varying vec3 Normal;
varying vec2 TexCoords;
varying vec3 Tangent;

varying vec3 LightDir;
varying vec3 ViewDir;

//for render pass
uniform int pass;
uniform sampler2D RenderTex;

uniform float width;
uniform float height;

vec3 phongModel(vec3 normal, vec3 diffR){
    vec3 Kd = vec3(0.64, 0.64, 0.64);
    vec3 Ld = vec3(1.0, 1.0, 1.0);
    vec3 Ka = vec3(0.0, 0.0, 0.0);
    vec3 La = vec3(0.4, 0.4, 0.4);
    vec3 Ks = vec3(0.5, 0.5, 0.5);
    vec3 Ls = vec3( 1.0, 1.0, 1.0);
    float Shininess = 100.0;
    vec4 LightPosition = vec4(0.0, 10.0, 20.0, 1.0);
    vec3 Intensity = vec3(0.9,0.9,0.9);
    
    
    vec3 r = reflect(-LightDir, normal);
    vec3 ambient = Intensity * Ka;
    float sDotN = max(dot(LightDir, normal), 0.0);
    
    vec3 diffuse = Intensity * diffR * sDotN;
    
    vec3 spec = vec3(0.0);
    if(sDotN > 0.0){
        spec = Intensity * Ks * pow(max(dot(r, ViewDir), 0.0), Shininess);
    }
    
    return ambient + diffuse + spec;
}

vec4 get_pixel(in vec2 coords, in float dx, in float dy) {
    return texture2D(RenderTex,coords + vec2(dx, dy));
}


vec4 pass2(){
    float dxtex = 1.0 / width /*image width*/;
    float dytex = 1.0 / height /*image height*/;

    vec2 pix = vec2(gl_FragCoord.x/width, gl_FragCoord.y/height);
    vec4 sum = get_pixel(pix, 0.0*dxtex, 0.0*dytex) * 0.2270270270;
    
    sum += get_pixel(pix, 0.0*dxtex, 1.0*dytex) * 0.1945945946;
    sum += get_pixel(pix, 0.0*dxtex, -1.0*dytex) * 0.1945945946;
        
    sum += get_pixel(pix, 0.0*dxtex, 2.0*dytex) * 0.1216216216;
    sum += get_pixel(pix, 0.0*dxtex, -2.0*dytex) * 0.1216216216;
        
    sum += get_pixel(pix, 0.0*dxtex, 3.0*dytex) * 0.0540540541;
    sum += get_pixel(pix, 0.0*dxtex, -3.0*dytex) * 0.0540540541;
        
    sum += get_pixel(pix, 0.0*dxtex, 4.0*dytex) * 0.0162162162;
    sum += get_pixel(pix, 0.0*dxtex, -4.0*dytex) * 0.0162162162;
    
    return sum;

}

void main()
{
    if(pass == 1){
		vec4 normal = 2.0 * texture2D(norm, TexCoords) - 1.0;
		vec4 texColor = texture2D(tex, TexCoords);
		gl_FragColor = vec4(phongModel(normal.xyz, texColor.rgb), 1.0);
    }
    else{
        gl_FragColor = pass2();
	}
    
}
