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
		CCGRay(const CCGPoint3D &pOrigin, const CCGVec3 &vDirection);

		//! \brief ��ȡ�������λ��
		CCGPoint3D GetOrigin() const;

		//! \brief ��ȡ���߷���
		CCGVec3 GetDirection() const;

		//! \brief ��ȡ������ĳһ���λ��
		CCGPoint3D PointAtParam(CCGdouble t) const;

	private:
		//! \brief �������λ��
		CCGPoint3D m_pOrigin;

		//! \brief ���߷�������
		CCGVec3 m_vDirection;
	};

	//! \brief �ж��Ƿ�ײ�����������Ƿ����䵽������
	//! \param rIn �������
	//! \param pCenter ���������
	//! \param dRadius ����İ뾶
	//! \return �����Ƿ�ײ�����������Ƿ����䵽�����ϣ��Ƿ���true���񷵻�false
	//CCGbool HitSphere(const CCGRay &rIn, CCGPoint3D &pCenter, CCGdouble dRadius);

	//! \brief �ж��Ƿ�ײ�����������Ƿ����䵽������
	//! \param rIn �������
	//! \param pCenter ���������
	//! \param dRadius ����İ뾶
	//! \return ����ײ���Ľ���Ĳ���ֵt
	CCGdouble HitSphere(const CCGRay &rIn, CCGPoint3D &pCenter, CCGdouble dRadius);

	//! \brief ��ȡ0-1֮���һ��double�������
	CCGdouble GetDBRand();

	//! \brief ��ȡ��λ�����ڵ�����һ��
	CCGPoint3D GetRandPointInUnitSphere();

	//! \brief ��ɫ���������ݷ�������õ���Ӧ��ɫ��
	//! \param rIn �������
	//! \param hList ������
	//! \return ����ײ���Ľ������ɫֵ
	//CCGColor3D Color(const CCGRay &rIn, CCGHitObject *hList);

	//! \brief ��ɫ���������ݷ�������õ���Ӧ��ɫ��
	//! \param rIn �������
	//! \param hList ������
	//! \param nDepth �ݹ���ȣ��������������
	//! \return ����ײ���Ľ������ɫֵ
	CCGColor3D Color(const CCGRay &rIn, const CCGHitObject& hList, CCGint nDepth);
}

#endif
