#version 330
// A texture is expected as program attribute
uniform sampler2D Texture;

uniform int CurrentNumberOfLights;

uniform vec3 LightPositions[5];

uniform vec4 LightColors[5];

uniform int LightTypes[5];

uniform vec3 CameraPosition;

uniform vec4 AmbientComponent;

uniform vec4 DiffuseComponent;

uniform vec4 SpecularComponent;

uniform vec3 LightRotation;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;

in vec2 texCoord;

// Wordspace normal passed from vertex shader
in vec4 normal;

in vec4 currentPosition;

// The final color
out vec4 FragmentColor;


vec4 directionalLight(){

    vec4 directionalLightColor = vec4(1,1,1,0);
    float directionalLightIntensity = 0.8f;

    float ambient = 0.40f;

    // Compute diffuse lighting
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 1.0f));
    float diffuse = max(dot(normal, vec4(lightDirection, 1.0f)), 0.0f);

    // specular light
    float specularLight = 0.25f;
    vec3 viewDirection = normalize(CameraPosition - vec3(currentPosition));
    vec3 reflectionDirection = reflect(-lightDirection, vec3(normal));
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8.0f);
    float specular = specularAmount * specularLight;

    return texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * directionalLightColor * (diffuse + ambient + specular) * directionalLightIntensity;

}

vec4 pointLight(int i){

    vec4 ambient = LightColors[i] * 0.30f * AmbientComponent;
    float specularLight = 0.4f;
    vec3 viewDirection = normalize(CameraPosition - vec3(currentPosition));

    // Prep
    vec3 lightVector = LightPositions[i] - vec3(currentPosition);
    vec3 lightDirection = normalize(lightVector);
    // Diffuse
    float diffuseLight = 1.5f;
    vec4 diffuse = LightColors[i] * max(dot(normal, vec4(lightDirection, 1.0f)), 0.0f) * diffuseLight * DiffuseComponent;
    //Specular
    vec3 reflectionDirection = reflect(-lightDirection, vec3(normal));
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8.0f);
//    vec4 specular = LightColors[i] * specularAmount * specularLight * SpecularComponent;
    vec4 specular = vec4(1,1,1,1) * specularAmount * specularLight * SpecularComponent;

    float distance = length(lightVector);
    float a = 0.05f;
    float b = 0.08f;
//    float a = 0.5f;
//    float b = 0.8f;
//    float a = 100;
//    float b = 100;
    float intensity = 1.0f / (a * distance * distance + b * distance + 1.0f);


    return texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * ((diffuse * intensity) + (ambient*intensity) + (specular * intensity));




//    float ambient = 0.20f;
//
//    vec3 lightVector = LightPositions[0] - vec3(currentPosition);
//    float distance = length(lightVector);
//    float a = 0.05f;
//    float b = 0.02f;
//    float intensity = 1.0f / (a * distance * distance + b * distance + 1.0f);
//
//    // Compute diffuse lighting
//    vec3 lightDirection = normalize(lightVector);
//    float diffuse = max(dot(normal, vec4(lightDirection, 1.0f)), 0.0f);
//
//    // specular light
//    float specularLight = 1.5f;
//    vec3 viewDirection = normalize(CameraPosition - vec3(currentPosition));
//    vec3 reflectionDirection = reflect(-lightDirection, vec3(normal));
//    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8.0f);
//    float specular = specularAmount * specularLight;
//
//    return texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * LightColors[0] * ((diffuse * intensity) + ambient + (specular * intensity));
}





vec4 spotLight(int i){

    vec4 ambient = LightColors[i] * 0.50f * AmbientComponent;
    float specularLight = 2.0f;
    vec3 viewDirection = normalize(CameraPosition - vec3(currentPosition));

    float outerCone = 0.90f;
    float innerCone = 0.95f;


    // Prep
    vec3 lightVector = LightPositions[i] - vec3(currentPosition);
    vec3 lightDirection = normalize(lightVector);
    // Diffuse
    float diffuseLight = 1.5f;
    vec4 diffuse = LightColors[i] * max(dot(normal, vec4(lightDirection, 1.0f)), 0.0f) * diffuseLight;
    //Specular
    vec3 reflectionDirection = reflect(-lightDirection, vec3(normal));
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8.0f);
    vec4 specular = LightColors[i] * specularAmount * specularLight;
    // Cone
    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
    float intensity = clamp((angle - outerCone) /(innerCone - outerCone), 0.0f,1.0f);



    //    return texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * LightColors[0] * ((totalDiffuse * totalIntensity) + ambient + (totalSpecular * totalIntensity));
    return texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * ((diffuse * intensity) + (ambient*intensity) + (specular * intensity));



//    float ambient = 0.20f;
//
//    vec3 lightVector = LightPositions[i] - vec3(currentPosition);
//
//    // Compute diffuse lighting
//    vec3 lightDirection = normalize(lightVector);
//    float diffuse = max(dot(normal, vec4(lightDirection, 1.0f)), 0.0f);
//
//    // specular light
//    float specularLight = 1.5f;
//    vec3 viewDirection = normalize(CameraPosition - vec3(currentPosition));
//    vec3 reflectionDirection = reflect(-lightDirection, vec3(normal));
//    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8.0f);
//    float specular = specularAmount * specularLight;
//
//    float outerCone = 0.90f;
//    float innerCone = 0.95f;
//
//    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
//    float intensity = clamp((angle - outerCone) /(innerCone - outerCone), 0.0f,1.0f);
//
//
//    return texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * LightColors[i] * ((diffuse * intensity) + ambient + (specular * intensity));




//    vec4 ambient = vec4(1, 1, 1, 1) * 0.20f;
//    float specularLight = 0.5f;
//    vec3 viewDirection = normalize(CameraPosition - vec3(currentPosition));
//
//    vec4 totalDiffuse = vec4(0, 0, 0, 0);
//    vec4 totalSpecular = vec4(0, 0, 0, 0);
//    float totalIntensity = 0;
//
//    float outerCone = 0.90f;
//    float innerCone = 0.95f;
//
//    for (int i = 0; i < 3; i++) {
//        // Prep
//        vec3 lightVector = LightPositions[i] - vec3(currentPosition);
//        vec3 lightDirection = normalize(lightVector);
//        // Diffuse
//        vec4 diffuse = LightColors[i] * max(dot(normal, vec4(lightDirection, 1.0f)), 0.0f);
//        totalDiffuse = totalDiffuse + diffuse;
//        //Specular
//        vec3 reflectionDirection = reflect(-lightDirection, vec3(normal));
//        float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8.0f);
//        vec4 specular = LightColors[i] * specularAmount * specularLight;
//        totalSpecular = totalSpecular + specular;
//        // Cone
//        float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
//        float intensity = clamp((angle - outerCone) /(innerCone - outerCone), 0.0f,1.0f);
//        totalIntensity = totalIntensity + intensity;
//    }
//
//
////    return texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * LightColors[0] * ((totalDiffuse * totalIntensity) + ambient + (totalSpecular * totalIntensity));
//    return texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * ((totalDiffuse * totalIntensity) + ambient + (totalSpecular * totalIntensity));





//    float ambient = 0.20f;
//
//    vec3 lightVector = LightPositions[0] - vec3(currentPosition);
//
//    // Compute diffuse lighting
//    vec3 lightDirection = normalize(lightVector);
//    float diffuse = max(dot(normal, vec4(lightDirection, 1.0f)), 0.0f);
//
//    // specular light
//    float specularLight = 1.5f;
//    vec3 viewDirection = normalize(CameraPosition - vec3(currentPosition));
//    vec3 reflectionDirection = reflect(-lightDirection, vec3(normal));
//    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8.0f);
//    float specular = specularAmount * specularLight;
//
//    float outerCone = 0.90f;
//    float innerCone = 0.95f;
//
//    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
//    float intensity =clamp((angle - outerCone) /(innerCone - outerCone), 0.0f,1.0f);
//
//    return texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * LightColors[0] * ((diffuse * intensity) + ambient + (specular * intensity));

}


void main() {

//    FragmentColor = pointLight();
//    FragmentColor = directionalLight();
//    FragmentColor = spotLight();

    vec4 ambient = vec4(1,1,1,1) * 0.20f;
    vec4 totalLight = directionalLight();
//    vec4 totalLight = vec4(0,0,0,0);

    totalLight += ambient;

    for (int i = 0; i < 5; i++) {
       if (LightTypes[i] == 1){
            totalLight += pointLight(i);
       }
       if (LightTypes[i] == 2){
           totalLight += spotLight(i);
       }
    }

//    for (int i = 0; i < 3; i++) {
//       totalLight += spotLight(i);
//    }

    FragmentColor = totalLight;
    FragmentColor.a = Transparency;
}
