#version 150
precision highp float;
uniform sampler2D tex0; // color map
uniform sampler2D tex1; // normal map
uniform vec4 light_diffuse;
uniform vec4 material_diffuse;
uniform vec4 light_specular;
uniform vec4 material_specular;
uniform float material_shininess;
in vec4 Vertex_UV;
in vec4 Vertex_Normal;
in vec4 Vertex_LightDir;
in vec4 Vertex_EyeVec;
out vec4 Out_Color;

// http://www.thetenthplanet.de/archives/1180
mat3 cotangent_frame(vec3 N, vec3 p, vec2 uv)
{
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );
 
    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
 
    // construct a scale-invariant frame 
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

vec3 perturb_normal( vec3 N, vec3 V, vec2 texcoord )
{
    // assume N, the interpolated vertex normal and 
    // V, the view vector (vertex to eye)
   vec3 map = texture(tex1, texcoord ).xyz;
   map = map * 255./127. - 128./127.;
    mat3 TBN = cotangent_frame(N, -V, texcoord);
    return normalize(TBN * map);
}

void main()
{
  vec2 uv = Vertex_UV.xy;
  
  vec3 N = normalize(Vertex_Normal.xyz);
  vec3 L = normalize(Vertex_LightDir.xyz);
  vec3 V = normalize(Vertex_EyeVec.xyz);
  vec3 PN = perturb_normal(N, V, uv);
  
  vec4 tex01_color = texture(tex0, uv).rgba;
  vec4 final_color = vec4(0.2, 0.15, 0.15, 1.0) * tex01_color; 
  
  float lambertTerm = dot(PN, L);
  if (lambertTerm > 0.0)
  {
    final_color += light_diffuse * material_diffuse * lambertTerm * tex01_color;  
    
    vec3 E = normalize(Vertex_EyeVec.xyz);
    vec3 R = reflect(-L, PN);
    float specular = pow( max(dot(R, E), 0.0), material_shininess);
    final_color += light_specular * material_specular * specular;  
  }
  Out_Color.rgb = final_color.rgb;
  //Out_Color.rgb = PN.rgb;
  //Out_Color.rgb = N.rgb;
  Out_Color.a = 1.0;
}