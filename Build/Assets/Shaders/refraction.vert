#version 430

in layout(location = 0) vec3 vposition;
in layout(location = 2) vec3 vnormal;

out layout(location = 0) vec3 otexcoord;

uniform float ior = 1.55;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec3 vreflect(vec3 i, vec3 n){
	vec3 r = i - (n * dot(n,i)) * 2;
	return r;
}

void main()
{
	//transform vertex position/normal to world space
	vec3 position = vec3(model * vec4(vposition, 1));
	vec3 normal = normalize(mat3(model) * vnormal);

	//inverse of view space -> world space
	//last column of mat4 is position
	vec3 viewPosition = inverse(view)[3].xyz;
	vec3 viewDir = normalize(position - viewPosition);

	//reflect view direction about vertex normal
	otexcoord = refract(viewDir, normal, 1.0f/ior);

	mat4 vp = projection * view * model;
	gl_Position = vp * vec4(vposition, 1.0);
}
