#version 330

in vec2 pass_tex_coords;

uniform sampler2D texture_sampler;

out vec4 out_color;

void main(void) {
  out_color = texture(texture_sampler, pass_tex_coords);
}
