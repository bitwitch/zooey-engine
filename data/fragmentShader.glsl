#version 330

in vec2 pass_tex_coords;
in vec3 surface_normal;
in vec3 to_light;


uniform sampler2D texture_sampler;
uniform vec3 light_color;

out vec4 out_color;

void main(void) {
  vec3 unit_normal = normalize(surface_normal);
  vec3 unit_to_light = normalize(to_light);
  float n_dot_l = dot(unit_normal, unit_to_light);
  float brightness = max(n_dot_l, 0.0);
  vec3 diffuse = brightness * light_color;
  out_color = vec4(diffuse, 1.0) * texture(texture_sampler, pass_tex_coords);
}
