#version 330
layout(location = 0) in vec3 Position;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 TexCoord0;
void main()
{
	vec4 WVP_Pos = projection * view * model * vec4(Position, 1.0);
	gl_Position = WVP_Pos.xyww;
	TexCoord0 = Position;
}
