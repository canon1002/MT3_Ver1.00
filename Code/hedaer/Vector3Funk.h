#pragma once
#include<Vector3.h>
#include<cmath>
#include<Novice.h>
#include"MathTool.h"

class Vector3Funk
{
public: //�����o�֐�(���\�b�h)

	

	

	

	/// <summary>
	/// �O�����s��̕\��
	/// </summary>
	/// <param name="posX"></param>
	/// <param name="posY"></param>
	/// <param name="v1"></param>
	/// <param name="ravel"></param>
	static void VectorScreenPrintf(int posX, int posY, const Vector3& v1,const char* ravel) 
	{
		Novice::ScreenPrintf(posX, posY, "%s : %.2f,%.2f,%.2f,", ravel, v1.x, v1.y, v1.z);
	}



};

