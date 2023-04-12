#version 330 core

in vec2  v_TexCoord;
in vec4  v_Color;
in float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Textures[32];

out vec4 color;

void main()
{
  int id = int(v_TexIndex);
  switch(id)
    {
    case 0:   color = texture(u_Textures[0],  v_TexCoord * v_TilingFactor) * v_Color; break;
    case 1:   color = texture(u_Textures[1],  v_TexCoord * v_TilingFactor) * v_Color; break;
    case 2:   color = texture(u_Textures[2],  v_TexCoord * v_TilingFactor) * v_Color; break;
    case 3:   color = texture(u_Textures[3],  v_TexCoord * v_TilingFactor) * v_Color; break;
    case 4:   color = texture(u_Textures[4],  v_TexCoord * v_TilingFactor) * v_Color; break;
    case 5:   color = texture(u_Textures[5],  v_TexCoord * v_TilingFactor) * v_Color; break;
    case 6:   color = texture(u_Textures[6],  v_TexCoord * v_TilingFactor) * v_Color; break;
    case 7:   color = texture(u_Textures[7],  v_TexCoord * v_TilingFactor) * v_Color; break;
    case 8:   color = texture(u_Textures[8],  v_TexCoord * v_TilingFactor) * v_Color; break;
    case 9:   color = texture(u_Textures[9],  v_TexCoord * v_TilingFactor) * v_Color; break;
    case 10:  color = texture(u_Textures[10], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 11:  color = texture(u_Textures[11], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 12:  color = texture(u_Textures[12], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 13:  color = texture(u_Textures[13], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 14:  color = texture(u_Textures[14], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 15:  color = texture(u_Textures[15], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 16:  color = texture(u_Textures[16], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 17:  color = texture(u_Textures[17], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 18:  color = texture(u_Textures[18], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 19:  color = texture(u_Textures[19], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 20:  color = texture(u_Textures[20], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 21:  color = texture(u_Textures[21], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 22:  color = texture(u_Textures[22], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 23:  color = texture(u_Textures[23], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 24:  color = texture(u_Textures[24], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 25:  color = texture(u_Textures[25], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 26:  color = texture(u_Textures[26], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 27:  color = texture(u_Textures[27], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 28:  color = texture(u_Textures[28], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 29:  color = texture(u_Textures[29], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 30:  color = texture(u_Textures[30], v_TexCoord * v_TilingFactor) * v_Color; break;
    case 31:  color = texture(u_Textures[31], v_TexCoord * v_TilingFactor) * v_Color; break;
    }
}
