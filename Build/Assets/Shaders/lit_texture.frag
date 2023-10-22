#version 430

in layout(location = 0) vec3 fposition;
in layout(location = 1) vec3 fnormal;
in layout(location = 2) vec2 ftexcoord;


out layout(location = 0) vec4 ocolor;

uniform struct Material
{
	vec3 diffuse;
	vec3 specular;
	float shininess;

	vec2 offset;
	vec2 tiling;
} material;


uniform vec3 ambientLight;

uniform struct Light
{

	vec3 position;
	vec3 color;

} light;

layout(binding = 0) uniform sampler2D tex;

vec3 ads(in vec3 position, in vec3 normal)
{
	//AMBIENT
	vec3 ambient = ambientLight;

	//DIFFUSE
	// find the direction the light is moveing in by subtracting the fragment position from the light source position and then normalize it
	vec3 lightDirection = normalize(light.position - position);
	// find the intensity by doing the dot product of the light direction with the fragment normal then we clampp this value between 0 and 1
	float intensity = max(dot(lightDirection, normal), 0);	
	//finally we get the diffuse color by multiplying the light color by the intensity and then multiplying that product by the materials diffuse
	vec3 diffuse = material.diffuse * (light.color * intensity);

	//SPECULAR
	vec3 specular = vec3(0);
	//first we check to see if the intensity is greater then 0 or not
	if(intensity > 0){
	//if it is then we find the reflection by using reflect on the inverse of our light direction and the fragment normal
		vec3 reflection = reflect(-lightDirection, normal);
		//we find the view direction by normalizing the inverse of the fragment normal
		vec3 viewDirection = normalize(-position);
		// then we find the intensity by doing the dot product of the reflection and view direction and then we clamp it
		intensity = max(dot(reflection, viewDirection), 0);
		//next we raise intensity by the power of shininess
		intensity = pow(intensity, material.shininess);
		//then we multiply the material specular by the intesity
		specular = material.specular * intensity;
	}
	//finally we add all of our lights and return the sum
	return ambient + diffuse + specular;
}

void main()
{
	vec4 texcolor = texture(tex, ftexcoord);
	ocolor = texcolor * vec4(ads(fposition,fnormal), 1);
}
