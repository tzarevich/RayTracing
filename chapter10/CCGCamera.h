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

		//CCGCamera(CCGPoint3D pLookfrom, CCGPoint3D pLookat, CCGVec3 vVup, CCGdouble dFov, CCGdouble dAspect)
		//! \brief ���캯��
		CCGCamera(CCGPoint3D pLookfrom, CCGPoint3D pLookat, CCGVec3 vVup, CCGdouble dFov, CCGdouble dAspect, CCGdouble dAperture, CCGdouble dFocusDist);

		//! \brief ��ȡ����
		//! \param  s ˮƽƫ����
		//! \param  t ��ֱƫ����
		//! \return ���ع���
		CCGRay GetRay(CCGdouble s, CCGdouble t);
		
	private:
		//! \brief ���Դ��
		CCGPoint3D m_pViewOrigin;

		//! \brief ��Ļ���½ǵ�
		CCGPoint3D m_pLeftCorner;

		//! \brief ��Ļˮƽƫ�Ʒ���
		CCGVec3 m_vHorizontial;

		//! \brief ��Ļ��ֱƫ�Ʒ���
		CCGVec3 m_vVertical;

		//! \brief �������ϵ
		CCGVec3 m_u, m_v, m_w;

		//! \brief ��Ȧ�뾶
		CCGdouble m_dLenRadius;
	};

	CCGPoint3D GetRandPointInUnitCircle();
}

#endif