#ifndef CCGRAY_H
#define CCGRAY_H
#pragma once

#include "Vec3.h"
#include "CCGHitObjects.h"


namespace CCG
{
	class CCGHitObject;
	class CCGSphere;
	class CCGHitList;

	//! \brief ������Ҫ�õ���������
	class CCGVec3;

	//! \brief ������
	class CCGRay
	{
	public:
		//! \brief ���캯��
		CCGRay();

		//! \brief ���캯��
		CCGRay(const CCGPoint3D &pOrigin, const CCGVec3 &vDirection, CCGdouble dTime = 0.0);

		//! \brief ��ȡ�������λ��
		CCGPoint3D GetOrigin() const;

		//! \brief ��ȡ���߷���
		CCGVec3 GetDirection() const;

		//! \brief ��ȡʱ��
		CCGdouble GetTime() const;

		//! \brief ��ȡ������ĳһ���λ��
		CCGPoint3D PointAtParam(CCGdouble t) const;

	private:
		//! \brief �������λ��
		CCGPoint3D m_pOrigin;

		//! \brief ���߷�������
		CCGVec3 m_vDirection;

		//! \brief ����ʱ��
		CCGdouble m_time;
	};

	//! \brief ��ȡ��λ�����ڵ�����һ��
	CCGPoint3D GetRandPointInUnitSphere();
}

#endif
