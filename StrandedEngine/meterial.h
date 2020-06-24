#ifndef _UGP_MATERAIL_H_
#define _UGP_MATERAIL_H_


struct stMaterial
{
	stMaterial()
	{
		diffuseR = diffuseG = diffuseB = diffuseA = 1;//�����
		ambientR = ambientG = ambientB = ambientA = 1;//������
		specularR = specularG = specularB = specularA = 0;//�����
		emissiveR = emissiveG = emissiveB = emissiveA = 0;//�Է���
		power = 0;//�߹�
	}
	float ambientR, ambientG, ambientB, ambientA;
	float diffuseR, diffuseG, diffuseB, diffuseA;
	float specularR, specularG, specularB, specularA;
	float emissiveR, emissiveG, emissiveB, emissiveA;
	float power;

};

#endif