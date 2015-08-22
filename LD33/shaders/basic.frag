#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
//uniform vec2 light_pos;
//uniform vec3 falloff;

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D textures[32];

/*
void main()
{
	vec2 lightdir = light_pos - fs_in.position.xy;
	float dist = length(lightdir);
		
	float atten = 1.0 / (1 + falloff.y * dist + falloff.z * dist * dist);
		
	vec4 texColor = fs_in.color;
	
	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		texColor = fs_in.color * texture(textures[tid], fs_in.uv);
	}

	color = texColor * atten;
}
*/

void main()
{
	//float intensity = 1.0 / length(light_pos - fs_in.position.xy);
	vec4 texColor = fs_in.color;

	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		texColor = fs_in.color * texture(textures[tid], fs_in.uv);
	}
	
	color = texColor;// * intensity;
}