#version 330 core

layout(location = 0) in vec3 a_Pos;

uniform mat4 u_VP;
uniform mat4 u_Transform;

void main()
{
  gl_Position = u_Transform * u_VP * vec4(a_Pos, 1);
}
