#version 330

in vec2 pass_tex_coords;
in vec3 surface_normal;
in vec3 to_light;
in vec3 to_camera;

uniform sampler2D texture_sampler;
uniform vec3 light_color;
uniform float shine_damper;
uniform float reflectivity;

out vec4 out_color;

void main(void) {
  vec3 unit_normal = normalize(surface_normal);
  vec3 unit_to_light = normalize(to_light);
  float n_dot_l = dot(unit_normal, unit_to_light);
  float brightness = max(n_dot_l, 0.0);
  vec3 diffuse = brightness * light_color;

  vec3 unit_to_camera = normalize(to_camera);
  vec3 light_direction = -unit_to_light;
  vec3 reflected_light_direction = reflect(light_direction, unit_normal);

  float specular_factor = dot(reflected_light_direction, unit_to_camera);
  specular_factor = max(specular_factor, 0.0);
  float damped_factor = pow(specular_factor, shine_damper);
  vec3 final_specular = damped_factor * reflectivity * light_color;

  out_color = vec4(diffuse, 1.0) * texture(texture_sampler, pass_tex_coords) + vec4(final_specular, 1.0);
}
