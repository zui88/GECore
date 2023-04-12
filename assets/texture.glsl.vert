#version 330 core

layout(location = 0) in vec3  a_Pos;
layout(location = 1) in vec2  a_TexCoord;
layout(location = 2) in vec4  a_Color;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;

uniform mat4 u_VP;
uniform mat4 u_Transform;

out vec2  v_TexCoord;
out vec4  v_Color;
out float v_TexIndex;
out float v_TilingFactor;

void main()
{
  v_TilingFactor = a_TilingFactor;
  v_TexIndex     = a_TexIndex;
  v_TexCoord     = a_TexCoord;
  v_Color        = a_Color;

  gl_Position = u_VP * u_Transform * vec4(a_Pos, 1);
}
