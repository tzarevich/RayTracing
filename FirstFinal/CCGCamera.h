#ifndef CCGCAMERA_H
#define CCGCAMERA_H
#pragma once

#include "CCGdefs.h"
#include "CCGVec3.h"

namespace CCG
{
	class CCGRay;
	//! \brief ���
	class CCGCamera
	{
	public:
		//! \brief ���캯��
		CCGCamera();

		//! \brief ���캯��
		CCGCamera(CCGPoint3D &pLookfrom, CCGPoint3D &pLookat, CCGVec3 &vVup, CCGdouble dVof, CCGdouble dAspect, CCGdouble dAperture, CCGdouble dFocusDis);

		//! \brief ��������
		~CCGCamera();

		//! \brief ��ȡ���ߣ�������
		CCGRay GetRay(CCGdouble s, CCGdouble t);

	private:
		//! \brief ���Դ��
		CCGPoint3D m_ViewOrigin;

		//! \brief ��Ļ���½ǵ�
		CCGPoint3D m_LeftCorner;

		//! \brief ��Ļˮƽƫ����
		CCGVec3 m_Horizontial;

		//! \brief ��Ļ��ֱƫ����
		CCGVec3 m_Vertical;

		//! \brief �������ϵ��x�����
		CCGVec3 m_u;

		//! \brief �������ϵ��y�����
		CCGVec3 m_v;

		//! \brief �������ϵ��z�����
		CCGVec3 m_w;

		//! \brief ��Ȧ�뾶
		CCGdouble m_dLensRadius;
	};

	CCGPoint3D GetRandomPointInUnitCircle();
}

#endif
