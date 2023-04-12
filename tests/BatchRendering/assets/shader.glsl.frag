#version 330 core

in vec2  v_TexCoord;
in float v_TexID;

uniform sampler2D u_Textures[3];

out vec4 FragColor;

void main()
{
  int ID = int(v_TexID);
  FragColor = texture(u_Textures[ID], v_TexCoord);
}
