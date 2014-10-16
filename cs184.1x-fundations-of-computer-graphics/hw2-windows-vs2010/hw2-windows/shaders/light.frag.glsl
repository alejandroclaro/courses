# version 120 

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Mine is an old machine.  For version 130 or higher, do 
// in vec4 color;  
// in vec3 mynormal; 
// in vec4 myvertex;
// That is certainly more modern

varying vec4 color;
varying vec3 mynormal; 
varying vec4 myvertex; 

const int numLights = 10; 
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

// Now, set the material parameters.  These could be varying and/or bound to 
// a buffer.  But for now, I'll just make them uniform.  
// I use ambient, diffuse, specular, shininess as in OpenGL.  
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient; 
uniform vec4 diffuse; 
uniform vec4 specular; 
uniform vec4 emission; 
uniform float shininess; 

vec4 ComputeLight (const in vec3 direction, const in vec4 lightcolor, const in vec3 normal, const in vec3 halfvec, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess)
{
        float nDotL = dot(normal, direction)  ;
        vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0) ;

        float nDotH = dot(normal, halfvec) ;
        vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess) ;

        vec4 retval = lambert + phong ; 
        return retval ;
}

vec4 TestLight ()
{
        const vec4 light0 = vec4(0.6, 0, 0.1, 0);
        const vec4 light1 = vec4(0, -0.6, 0.1, 1);
        const vec4 specular0 = vec4(1, 0.5, 0, 1);
        const vec4 specular1 = vec4(0.5, 0.5, 1, 1);
        const vec4 one = vec4(1, 1, 1, 1);
        const vec4 medium = vec4(1, 1, 0.25, 1);
        const vec4 small = vec4(0.2, 0.2, 0.2, 1);
        int  high = 100;

        const vec3 eyepos = vec3(0,0,0) ;
        vec4 _mypos = gl_ModelViewMatrix * myvertex ; 
        vec3 mypos = _mypos.xyz / _mypos.w ; // Dehomogenize current location 
        vec3 eyedirn = normalize(eyepos - mypos) ; 

        // Compute normal, needed for shading. 
        // Simpler is vec3 normal = normalize(gl_NormalMatrix * mynormal) ; 
        vec3 _normal = (gl_ModelViewMatrixInverseTranspose*vec4(mynormal,0.0)).xyz ; 
        vec3 normal = normalize(_normal) ; 

        // Light 0, point
        vec3 position0 = light0.xyz / light0.w ; 
        vec3 direction0 = normalize (position0 - mypos) ; // no attenuation 
        vec3 half0 = normalize (direction0 + eyedirn) ;  
        vec4 col0 = ComputeLight(direction0, specular0, normal, half0, diffuse, specular, shininess) ;

        // Light 1, point 
        vec3 position1 = light1.xyz / light1.w ; 
        vec3 direction1 = normalize (position1 - mypos) ; // no attenuation 
        vec3 half1 = normalize (direction1 + eyedirn) ;  
        vec4 col1 = ComputeLight(direction1, specular1, normal, half1, diffuse, specular, shininess) ;
        
        vec4 result = (vec4(0, 0, 0, 1) + col0 + col1); 
        return result;
}

void main (void) 
{
    if (enablelighting)
    {
        //gl_FragColor = TestLight(); 

        vec4 finalcolor = vec4(0,0,0,1) + ambient + emission;

        const vec3 eyepos = vec3(0,0,0);
        vec4 _mypos  = gl_ModelViewMatrix * myvertex;
        vec3 mypos   = _mypos.xyz / _mypos.w;
        vec3 eyedirn = normalize(eyepos - mypos); 
        vec3 _normal = (gl_ModelViewMatrixInverseTranspose*vec4(mynormal,0.0)).xyz;
        vec3 normal  = normalize(_normal) ; 

        for (int i = 0; i < numused; ++i)
        {
          vec3 lpos = lightposn[i].xyz / lightposn[i].w ; 
          vec3 ldir  = normalize (lpos - mypos) ; // no attenuation 
          vec3 lhalf = normalize (ldir + eyedirn) ;  

          finalcolor += ComputeLight(ldir, lightcolor[i], normal, lhalf, diffuse, specular, shininess);
        }

        gl_FragColor = finalcolor;
    }
    else
    {
        gl_FragColor = color; 
    }
}
