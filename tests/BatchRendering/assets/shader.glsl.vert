#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_TexID;

uniform mat4 u_MVP;

out vec2 v_TexCoord;
out float v_TexID;

void main()
{
  v_TexCoord = a_TexCoord;
  v_TexID = a_TexID;

  gl_Position = u_MVP * vec4(a_Pos.xyz, 1.0f);
}
