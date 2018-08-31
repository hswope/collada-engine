#version 410

uniform mat4 model;
uniform vec3 cameraPosition;

//material
uniform sampler2D materialTex;
uniform vec3 materialEmissionColor;
uniform vec3 materialAmbientColor;
uniform vec3 materialDiffuseColor;
uniform vec3 materialSpecularColor;
uniform float materialShininess;
uniform float materialRefractionIndex;

//point light
uniform vec3 pointLightPosition;
uniform vec3 pointLightColor;
uniform float pointLightAttenuation;
uniform float pointLightAmbientCoeficient;

//verts
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;

out vec4 finalColor;

void main() {
    //calculate normal in world coordinates
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * fragNormal);

    //calculate the location of this fragment (pixel) in world coordinates
    vec3 fragPosition = vec3(model * vec4(fragVert, 1));

    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = pointLightPosition - fragPosition;

    //calculate the cosine of the angle of incidence
    float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0, 1);

    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: brightness
    // 2. The color/intensities of the light: light.intensities
    // 3. The texture and texture coord: texture(tex, fragTexCoord)
    vec4 surfaceColor = texture(materialTex, fragTexCoord);
    finalColor = vec4(brightness * pointLightColor * surfaceColor.rgb, surfaceColor.a);
}
