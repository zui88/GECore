#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_TexID;

uniform mat4 u_VP;
uniform mat4 u_Transform;

out vec2 v_TexCoord;
out float v_TexID;

void main()
{
  v_TexCoord = a_TexCoord;
  v_TexID = a_TexID;

  gl_Position = u_VP * u_Transform * vec4(a_Pos.xyz, 1.0f);
}
