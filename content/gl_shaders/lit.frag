#version 330 core
in vec3 fPos;
in vec2 fUV;
in vec3 fNormal;

struct Material {
	vec4 base_color;
	sampler2D main_texture;
	float specular;
	sampler2D specular_texture;
};

uniform Material uMaterial;
uniform vec3 uViewPosition;
uniform mat4 uModel;
uniform int uLightsEnabled;
uniform vec4 uAmbientColor;
uniform float uAmbientStrength;
uniform vec4 uDirectionalLightColor;
uniform vec4 uDirectionalLightStrength;
uniform vec3 uDirectionalLightPosition;

out vec4 fColor;

vec4 calculate_dirlight() {
	vec3 norm = normalize(mat3(uModel) * normalize(fNormal));
	vec3 light_dir = normalize(uDirectionalLightPosition - vec3(uModel * vec4(fPos, 1.0)));

	float diff = max(dot(norm, light_dir), 0.0);
	vec4 diffuse = diff * uDirectionalLightColor;

	if (textureSize(uMaterial.main_texture, 0) != ivec2(1, 1)) {
		diffuse = diffuse * texture(uMaterial.main_texture, fUV);
	}

	vec3 view_dir = normalize(uViewPosition - vec3(uModel * vec4(fPos, 1.0)));
	vec3 reflect_dir = reflect(-light_dir, norm);  

	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
	vec4 specular = uMaterial.specular * spec * uDirectionalLightColor;

	if (textureSize(uMaterial.specular_texture, 0) != ivec2(1, 1)) {
		specular = specular * texture(uMaterial.specular_texture, fUV);
	}

	return diffuse + specular;
}

void main() {
	fColor = uMaterial.base_color;

	if (uLightsEnabled == 1) {
		vec4 ambient = uAmbientColor * uAmbientStrength;
		if (textureSize(uMaterial.main_texture, 0) != ivec2(1, 1)) {
			ambient = ambient * texture(uMaterial.main_texture, fUV);
		}
		fColor = (ambient + calculate_dirlight()) * fColor;
	}
	else if (textureSize(uMaterial.main_texture, 0) != ivec2(1, 1)) {
		fColor = fColor * texture(uMaterial.main_texture, fUV);
	}
}	