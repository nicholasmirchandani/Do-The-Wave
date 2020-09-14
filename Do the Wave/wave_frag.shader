#version 450 core
#define SCREEN_X 1920
#define SCREEN_Y 1080

layout(location = 0) out vec4 color;

uniform float sinSpeed;
uniform float blueLoc;
uniform float numWaves;
void main() {
	
	//Using intermediary floats to reduce calculations
	float bigsin = abs(2 * sin(gl_FragCoord.x * 3.1415926535897932384626433832795 * numWaves / SCREEN_X));
	float waveMath = bigsin * (0.4 * sin(sinSpeed * 15 - (gl_FragCoord.x * 0.01)) - 0.5 * sin(gl_FragCoord.x / SCREEN_X * 10) + 1.1) / 2 / 2;

	//CLIP Above top Sin wave
	if (waveMath + 1.2 < gl_FragCoord.y / SCREEN_Y * 2 ) {
		discard;
	}

	//CLIP Below Bottom Sin Wave
	if (0.8 - (waveMath) > gl_FragCoord.y / SCREEN_Y * 2) {
		discard;
	}

	//Gradient set
	color.r = gl_FragCoord.y / SCREEN_Y;
	color.g = gl_FragCoord.x / SCREEN_X;

	//Move the blue around from side to side
	if (!(gl_FragCoord.x / SCREEN_X > blueLoc - 0.2 && (gl_FragCoord.x / SCREEN_X - blueLoc + 0.1) < 0.3)) {
		color.b = 0;
	} else {
		color.b = 1 - (abs(blueLoc - gl_FragCoord.x / SCREEN_X)) * 10;
	}

	//Final desaturation within wave

	//Above top Sin wave
	if (waveMath + 1 < gl_FragCoord.y / SCREEN_Y * 2) {
		color.rg = color.rg * (waveMath) * (1 - (gl_FragCoord.y/SCREEN_Y*2 - waveMath - 1) * 5);
		color.b *= (color.r + color.g);
	}

	//Below Bottom Sin Wave
	if (1 - (waveMath) > gl_FragCoord.y / SCREEN_Y * 2) {
		color.rg = color.rg * (waveMath) * (1 - ((1 - gl_FragCoord.y / SCREEN_Y) * 2 - waveMath - 1) * 5);
		color.b *= (color.r + color.g);
	}

	waveMath = bigsin * ((0.4 * sin(sinSpeed * 15 - (gl_FragCoord.x * 0.01)) - 0.5 * sin(gl_FragCoord.x / SCREEN_X * 10) + 0.9) / 2) / 2;
	if ((waveMath + 1 > gl_FragCoord.y / SCREEN_Y * 2) && 1 - (waveMath) < gl_FragCoord.y / SCREEN_Y * 2) {
		//TODO: Add linear interpolation here for rg
	color.rg /= 2;
	color.b *= abs(0.5-(gl_FragCoord.y/SCREEN_Y));
	}

	color.a = 0;
};
