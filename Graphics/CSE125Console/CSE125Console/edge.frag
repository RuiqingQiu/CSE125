varying vec4 Position;
varying vec3 Normal;
varying vec2 TexCoords;


uniform sampler2D tex;
uniform sampler2D norm;
uniform sampler2D gloss;
uniform sampler2D metallic;
uniform sampler2D RenderTex;

varying vec3 Tangent;

varying vec3 LightDir;
varying vec3 ViewDir;
uniform int pass;

const vec3 lum = vec3(0.2126, 0.7152, 0.0722);
uniform float width;
uniform float height;

vec3 phongModel(vec4 position, vec3 normal){
    vec3 Kd = vec3(0.64, 0.64, 0.64);
    vec3 Ld = vec3(1.0, 1.0, 1.0);
    vec3 Ka = vec3(0.0, 0.0, 0.0);
    vec3 La = vec3(0.4, 0.4, 0.4);
    vec3 Ks = vec3(0.5, 0.5, 0.5);
    vec3 Ls = vec3( 1.0, 1.0, 1.0);
    float Shininess = 100.0;
    vec4 LightPosition = vec4(0.0, 10.0, 20.0, 1.0);
    
    vec3 n = normalize(normal);
    vec3 s = normalize(vec3(LightPosition - position));
    vec3 v = normalize(-position.xyz);
    vec3 r = reflect(-s, n);
    vec3 ambient = La * Ka;
    float sDotN = max( dot(s,normal), 0.0 );
    vec3 diffuse = Ld * Kd * sDotN;
    vec3 spec = vec3(0.0);
    if( sDotN > 0.0 )
        spec = Ls * Ks * pow( max( dot(r,v), 0.0 ), Shininess );
    return ambient + diffuse + spec;
}

float threshold(in float thr1, in float thr2 , in float val) {
    if (val < thr1) {return 0.0;}
    if (val > thr2) {return 1.0;}
    return val;
}

// averaged pixel intensity from 3 color channels
float avg_intensity(in vec4 pix) {
    return  dot(lum, pix.rgb);
}

vec4 get_pixel(in vec2 coords, in float dx, in float dy) {
    return texture2D(RenderTex,coords + vec2(dx, dy));
}

// returns pixel color
float IsEdge(in vec2 coords){
    float dxtex = 1.0 / 512.0 /*image width*/;
    float dytex = 1.0 / 512.0 /*image height*/;
    float pix[9];
    int k = -1;
    float delta;
    
    // read neighboring pixel intensities
    for (int i=-1; i<2; i++) {
        for(int j=-1; j<2; j++) {
            k++;
            pix[k] = avg_intensity(get_pixel(coords,float(i)*dxtex,
                                             float(j)*dytex));
        }
    }
    
    // average color differences around neighboring pixels
    float sx = pix[0] + 2.0 * pix[3] + pix[6] - (pix[2] + 2.0 * pix[5] + pix[8]);
	float sy = pix[0] + 2.0 * pix[1] + pix[2] - (pix[6] + 2.0 * pix[7] + pix[8]);
	float g = sx * sx + sy * sy;
    
    return threshold(0.4,0.4,g);
}

vec3 phongModel2(vec3 normal, vec3 diffR){
    vec3 Kd = vec3(0.64, 0.64, 0.64);
    vec3 Ld = vec3(1.0, 1.0, 1.0);
    vec3 Ka = vec3(0.0, 0.0, 0.0);
    vec3 La = vec3(0.4, 0.4, 0.4);
    vec3 Ks = vec3(0.5, 0.5, 0.5);
    vec3 Ls = vec3( 1.0, 1.0, 1.0);
    float Shininess = 100.0;
    vec4 LightPosition = vec4(5.0, 10.0, 20.0, 1.0);
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

void main()
{
    if(pass == 1){
        gl_FragColor = vec4(phongModel(Position, Normal),1.0);
    }
    else{
        vec4 color = vec4(0.0,0.0,0.0,1.0);
        vec2 pix = vec2(gl_FragCoord.x/width, gl_FragCoord.y /height);
        color.g = IsEdge(pix);
        if(color.g == 0.0){
            vec4 normal = 2.0 * texture2D(norm, TexCoords) - 1.0;
			vec4 texColor = texture2D(tex, TexCoords);
			vec3 ambAndDiff, spec;
			vec4 shadeColor = vec4(phongModel2(normal.xyz, texColor.rgb), 1.0);
			gl_FragColor = shadeColor;
        }
        else{
            gl_FragColor = color;
        }
        
    }
}