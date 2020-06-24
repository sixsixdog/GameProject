#ifndef _UGP_MATERAIL_H_
#define _UGP_MATERAIL_H_


struct stMaterial
{
	stMaterial()
	{
		diffuseR = diffuseG = diffuseB = diffuseA = 1;//漫射光
		ambientR = ambientG = ambientB = ambientA = 1;//环境光
		specularR = specularG = specularB = specularA = 0;//镜面光
		emissiveR = emissiveG = emissiveB = emissiveA = 0;//自发光
		power = 0;//高光
	}
	float ambientR, ambientG, ambientB, ambientA;
	float diffuseR, diffuseG, diffuseB, diffuseA;
	float specularR, specularG, specularB, specularA;
	float emissiveR, emissiveG, emissiveB, emissiveA;
	float power;

};

#endif