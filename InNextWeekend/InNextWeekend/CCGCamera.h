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
		CCGCamera::CCGCamera();

		//! \brief ���캯��
		CCGCamera(CCGPoint3D pLookfrom, CCGPoint3D pLookat, CCGVec3 vVup, CCGdouble dFov, 
			CCGdouble dAspect, CCGdouble dAperture, CCGdouble dFocusDist, CCGdouble dT0, CCGdouble dT1);

		//! \brief ��ȡ����
		//! \param  s ˮƽƫ����
		//! \param  t ��ֱƫ����
		//! \return ���ع���
		CCGRay GetRay(CCGdouble u, CCGdouble v);
		
	private:
		//! \brief ���Դ��
		CCGPoint3D m_ViewOrigin;

		//! \brief ��Ļ���½ǵ�
		CCGPoint3D m_LeftCorner;

		//! \brief ��Ļˮƽƫ�Ʒ���
		CCGVec3 m_Horizontial;

		//! \brief ��Ļ��ֱƫ�Ʒ���
		CCGVec3 m_Vertical;

		//! \brief �������ϵ
		CCGVec3 m_u, m_v, m_w;

		//! \brief ��Ȧ�뾶
		CCGdouble m_dLenRadius;

		//! \brief ���ʱ��
		CCGdouble m_t0, m_t1;
	};

	CCGPoint3D GetRandPointInUnitCircle();
}

#endif