#version 420
// attribute
layout (location = 0) in vec3 a_pos;

uniform mat4 u_offset;
uniform mat4 u_view;
uniform mat4 u_projection;

out VS_OUT
{
	vec3 fragTexCoords;              // �e�N�X�`�����W
	vec3 fragNormal;                 // �@���i���[���h��ԁj
	vec3 fragWorldPos;               // ���_�ʒu�i���[���h��ԁj
}vs_out;

uniform mat4 u_invView;

void main()
{
	vs_out.fragTexCoords = a_pos;

	vec4 pos = vec4(a_pos, 1.0) * u_offset * u_invView * u_projection  ;

	gl_Position = vec4(pos.x, pos.y, pos.w, pos.w); 
}