#version 330 core

in vec2  v_TexCoord;
in float v_TexID;

uniform sampler2D u_Textures[3];

out vec4 FragColor;

void main()
{
  int ID = int(v_TexID);
  switch(ID)
    {
    case 0:  FragColor = texture(u_Textures[0], v_TexCoord); break;
    case 1:  FragColor = texture(u_Textures[1], v_TexCoord); break;
    case 2:  FragColor = texture(u_Textures[2], v_TexCoord); break;
    }
}
