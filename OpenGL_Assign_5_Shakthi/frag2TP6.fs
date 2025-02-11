#version 330 core
out vec4 FragColor;
void main() {
	vec4 color=vec4(0.2f, 0.3f, 0.3f, 1);
	vec2 uv = gl_FragCoord.xy;
	vec2 midCirc=vec2(400, 400);
	if(length(uv - midCirc) > 317 && length(uv - midCirc) <= 320 && uv.y != 0)
	{
		color.rgb=vec3(0, uv[1] / 800, 0);
	}
	FragColor = color;
}