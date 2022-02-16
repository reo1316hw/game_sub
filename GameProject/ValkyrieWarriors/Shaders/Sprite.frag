// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330
layout (location = 0) out vec4 HDRBuffer;
layout (location = 1) out vec4 HiBrightBuffer;

// Tex coord input from vertex shader
in vec2 fragTexCoord;

// This is used for the texture sampling
uniform sampler2D uSpriteTexture;
uniform sampler2D uEmissiveMap;

// Ž©ŒÈ”­Œõ‹­“x
uniform float uLuminance;
// “§–¾“x
uniform float uAlpha;

void main()
{
	// Sample color from texture
    vec4 texColor =  texture(uSpriteTexture, fragTexCoord);

	float brightness = dot(texColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
    {
         //HiBrightBuffer = texColor + texture(uEmissiveMap,fragTexCoord) * uLuminance;
           HiBrightBuffer = texColor ;
    }
    else
    {
        HiBrightBuffer = vec4(0.0f);
    }

    HDRBuffer.rgb = texColor.rgb;
    HDRBuffer.a = texColor.a * uAlpha;
}

