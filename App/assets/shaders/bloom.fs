#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;

// Output fragment color
out vec4 finalColor;

const float KERNEL_SIZE = 5.0;
const vec2 TEXEL_SIZE = 1 / vec2(1280, 720);

void main() {

    vec4 samplesSum = vec4(0);
    vec4 sourceColor = texture(texture0, fragTexCoord);

    for (float x = -KERNEL_SIZE; x <= KERNEL_SIZE; x++) {

        for (float y = -KERNEL_SIZE; y <= KERNEL_SIZE; y++) {

            vec2 samplePoint = fragTexCoord + vec2(x, y) * TEXEL_SIZE;
            samplesSum += texture(texture0, clamp(samplePoint, 0.f, 1.f));
        }
    }

    samplesSum = samplesSum / pow(KERNEL_SIZE * 2.0 + 1.0, 2.0);

    finalColor = sourceColor + samplesSum;
}