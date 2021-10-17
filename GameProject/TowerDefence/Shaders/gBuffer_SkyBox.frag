#version 330 core
layout (location = 0) out vec4 HDRBuffer;
layout (location = 1) out vec4 HiBrightBuffer;


in VS_OUT
{
	vec3 fragTexCoords;
	vec3 fragNormal;
	vec3 fragWorldPos;
}fs_in;

uniform samplerCube u_skybox;

uniform float u_skyLuminance = 1.5f;     

void main()
{
	HDRBuffer = texture(u_skybox, fs_in.fragTexCoords);

	float brightness = dot(HDRBuffer.xyz, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
    {
        HiBrightBuffer = vec4(HDRBuffer);
    }
    else
    {
        HiBrightBuffer = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }

}