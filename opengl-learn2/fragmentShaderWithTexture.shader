#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float trans;
uniform float size;

void main() {
	FragColor = mix(texture(texture1, TexCoord * 2), texture(texture2, TexCoord / size), trans);
}