#version 330 core
in vec3 TexCoord0;
out vec4 FragColor;
uniform samplerCube gCubemapTexture;
void main()
{
	FragColor = texture(gCubemapTexture, TexCoord0);
}
