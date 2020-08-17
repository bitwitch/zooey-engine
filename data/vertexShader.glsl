#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex_coords;
layout (location = 2) in vec3 normal;

out vec2 pass_tex_coords;
out vec3 surface_normal;
out vec3 to_light;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 light_position;

void main(void) {
  vec4 world_position = transform * vec4(position, 1.0);
  gl_Position = projection * view * world_position;
  pass_tex_coords = tex_coords;

  surface_normal = (transform * vec4(normal, 0.0)).xyz;
  to_light = light_position - world_position.xyz;
}
