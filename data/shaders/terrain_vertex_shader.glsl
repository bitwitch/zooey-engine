#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex_coords;
layout (location = 2) in vec3 normal;

out vec2 pass_tex_coords;
out vec3 surface_normal;
out vec3 to_light;
out vec3 to_camera;
out float visibility;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 light_position;

const float fog_density = 0.0035;
const float fog_gradient = 7.0;

void main(void) {
  vec4 world_position = transform * vec4(position, 1.0);
  vec4 position_relative_to_cam = view * world_position;
  gl_Position = projection * position_relative_to_cam;
  pass_tex_coords = tex_coords * 40.0;

  surface_normal = (transform * vec4(normal, 0.0)).xyz;
  to_light = light_position - world_position.xyz;

  to_camera = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz - world_position.xyz;

  float cam_distance = length(position_relative_to_cam);

  visibility = exp(-pow((cam_distance * fog_density), fog_gradient));
}
