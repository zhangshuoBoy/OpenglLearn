#version 330 core 
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
out vec4 FragColor;
struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	//vec3 diffuse;
	sampler2D specular;
	//vec3 specular;
	float shininess;
};
struct LightPoint
{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
	float constant;
	float linear;
	float quadratic;
};
struct LightSpot
{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
	float constant;
	float linear;
	float quadratic;
	float cosPhyInner;
	float cosPhyOutter;
};
struct LightDirectional
{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
};
uniform LightDirectional lightD;
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightS;

uniform LightPoint lightP;
uniform Material material;

//uniform sampler2D ourTexture; 
//uniform sampler2D ourFace; 
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightDirUniform ;
uniform vec3 lightColor; 
uniform vec3 cameraPos;
vec3 CalcLightDirectional(LightDirectional light,vec3 uNormal,vec3 dirToCamera)
{
	//diffuse
	float diffIntensity=max(dot(light.dirToLight,uNormal),0);
	vec3 diffColor=diffIntensity*light.color*texture(material.diffuse,TexCoord).rgb;

	//specular
	vec3 R=normalize(reflect(-light.dirToLight,uNormal));
	float specIntensity=pow(max(dot(R,dirToCamera),0),material.shininess);
	vec3 specColor=specIntensity*light.color*texture(material.specular,TexCoord).rgb;

	vec3 result=diffColor+specColor;
	return result;
}
vec3 CalcLightPoint(LightPoint light,vec3 uNormal,vec3 dirToCamera)
{
	//attenuation
	float dist=length(light.pos-FragPos);
	float attenuation=1/(light.constant+light.linear*dist+light.quadratic*(dist*dist));
	//diffuse
	float diffIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0)*attenuation;
	vec3 diffColor=diffIntensity*light.color*texture(material.diffuse,TexCoord).rgb;
	//specular
	vec3 R=normalize(reflect(-normalize(light.pos-FragPos),uNormal));
	float specIntensity=pow(max(dot(R,dirToCamera),0),material.shininess)*attenuation;
	vec3 specColor=specIntensity*light.color*texture(material.specular,TexCoord).rgb;

	vec3 result=diffColor+specColor;
	return result;
}
vec3 CalcLightSpot(LightSpot light,vec3 uNormal,vec3 dirToCamera)
{
	//attenuation
	float dist=length(light.pos-FragPos);
	float attenuation=1/(light.constant+light.linear*dist+light.quadratic*(dist*dist));
	float spotRatio;
	float CosTheta=dot(normalize(FragPos-light.pos),-light.dirToLight); 

	if(CosTheta>light.cosPhyInner)
	{
		spotRatio=1.0;
	}
	else if(CosTheta>light.cosPhyOutter)
	{
		spotRatio=(CosTheta-light.cosPhyOutter)/(light.cosPhyInner-light.cosPhyOutter); 
	}
	else{
		spotRatio=0;
	}
		//diffuse
	float diffIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0)*attenuation*spotRatio;
	vec3 diffColor=diffIntensity*light.color*texture(material.diffuse,TexCoord).rgb;
	//specular
	vec3 R=normalize(reflect(-normalize(light.pos-FragPos),uNormal));
	float specIntensity=pow(max(dot(R,dirToCamera),0),material.shininess)*attenuation*spotRatio;
	vec3 specColor=specIntensity*light.color*texture(material.specular,TexCoord).rgb;
	vec3 result=diffColor+specColor;
	return result;
}
void main(){

			vec3 finalResult=vec3(0,0,0);
			vec3 uNormal=normalize(Normal);
			vec3 dirToCamera=normalize(cameraPos-FragPos);

			finalResult+=CalcLightDirectional(lightD,uNormal,dirToCamera);
			finalResult+=CalcLightPoint(lightP0,uNormal,dirToCamera);
			finalResult+=CalcLightPoint(lightP1,uNormal,dirToCamera);
			finalResult+=CalcLightPoint(lightP2,uNormal,dirToCamera);
			finalResult+=CalcLightPoint(lightP3,uNormal,dirToCamera);
			finalResult+=CalcLightSpot(lightS,uNormal,dirToCamera);
			FragColor=vec4(finalResult,1.0);








			/*float dist    = length(lightPos - FragPos);
			float attenuation = 1.0 / (lightP.constant + lightP.linear * dist +lightP.quadratic * (dist * dist));
            vec3 lightDir=normalize(lightPos-FragPos);
			vec3 reflectVec=reflect(-lightDir,Normal);
			vec3 cameraVec=normalize(cameraPos-FragPos);
			//specular
			float specularAmount=pow(max(dot(reflectVec,cameraVec),0),material.shininess);
			vec3 specular=texture(material.specular,TexCoord).rgb*specularAmount*lightColor;
			//diffuse
			vec3 diffuse=texture(material.diffuse,TexCoord).rgb*max(dot(lightDir,Normal ),0)*lightColor;
			//vec3 diffuse=texture(material.diffuse,TexCoord).rgb; 
			//ambient
			vec3 ambient=texture(material.diffuse,TexCoord).rgb*ambientColor;

			float cosTheta=dot(normalize(FragPos-lightPos),-1*lightDirUniform);
			float spotRatio;
			if(cosTheta>lightS.cosPhyInner)
			{
				spotRatio=1.0f;
			}
			else if(cosTheta>lightS.cosPhyOutter)
			{
				spotRatio=1.0f-(cosTheta-lightS.cosPhyInner)/(lightS.cosPhyOutter-lightS.cosPhyInner);
			}
			else
			{
				spotRatio=0;
			}
			FragColor=vec4((ambient+(diffuse+specular)*spotRatio)*objColor,1.0);*/

}