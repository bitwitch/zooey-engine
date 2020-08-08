#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex_coords;

out vec2 pass_tex_coords;

uniform mat4 transform;
uniform mat4 projection;

void main(void) {
  gl_Position = projection * transform * vec4(position, 1.0);
  pass_tex_coords = tex_coords;
}
