#ifndef CCGCAMERA_H
#define CCGCAMERA_H
#pragma once

#include "CCGDefs.h"
#include "Vec3.h"
#include "CCGRay.h"

namespace CCG
{

	//! \brief �������
	class CCGCamera
	{
	public:
		//! \brief ���캯��
		CCGCamera();

		CCGRay GetRay(CCGdouble u, CCGdouble v);
		
	private:
		//! \brief ���Դ��
		CCGPoint3D m_pViewOrigin;

		//! \brief ��Ļ���½ǵ�
		CCGPoint3D m_pLeftCorner;

		//! \brief ��Ļˮƽƫ�Ʒ���
		CCGVec3 m_vHorizontial;

		//! \brief ��Ļ��ֱƫ�Ʒ���
		CCGVec3 m_vVertical;
	};
}

#endif