#version 330 core
out vec4 FragColor;
void main() {
vec4 color=vec4(1);
vec2 uv = gl_FragCoord.xy;
for (int i=0;i<900;i+=100) {
for (int j=0;j<900;j+=100) {
vec2 midCirc=vec2(i,j);
if(length(uv-midCirc)<=30)
{
color.rgb=vec3(0.2,0.3,0.5);
}
}
}
FragColor = color;
}