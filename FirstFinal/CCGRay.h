#ifndef CCGRAY_H
#define CCGRAY_H
#pragma once

#include "CCGVec3.h"

namespace CCG
{
	//! \brief ����
	class CCGRay
	{
	public:
		//! \brief ���캯��
		CCGRay();

		//! \brief ���캯��
		CCGRay(const CCGPoint3D &pO, const CCGVec3 &vDir);

		//! \brief ��������
		~CCGRay();

		//! \brief ��ȡ����Դ��
		CCGPoint3D GetOrigin() const;

		//! \brief ��ȡ���߷���
		CCGVec3 GetDirection() const;

		//! \brief ��ȡ������ĳһ��
		CCGPoint3D GetPointAtParam(CCGdouble t) const;

	private:
		//! \brief ����Դ��
		CCGPoint3D m_pOrigin;

		//! \brief ���߷���
		CCGVec3 m_vDirection;

	};

}
#endif

