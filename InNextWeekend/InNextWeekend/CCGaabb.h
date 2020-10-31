#ifndef CCGAABB_H
#define CCGAABB_H
#pragma once

#include "Vec3.h"

namespace CCG
{
	class CCGRay;
	//! \brief ��Χ��
	class CCGaabb
	{
	public:
		//! \brief ���캯��
		CCGaabb();

		//! \brief ���캯��
		CCGaabb(const CCGVec3 &a, const CCGVec3 &b);

		//! \brief ��������
		~CCGaabb();

		//! \brief ��ȡ��С�߽�
		CCGVec3 GetMin() const;

		//! \brief ��ȡ���߽�
		CCGVec3 GetMax() const;

		//! \brief ײ���������жϹ����Ƿ����Χ���ཻ
		//! \brief rIn ����
		//! \brief tMin �߽���Сֵ
		//! \brief tMax �߽����ֵ
		//! \brief return �����Ƿ��ཻ
		CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax) const;

	public:
		//! \brief �߽���Сֵ
		CCGVec3 m_min;

		//! \brief �߽����ֵ
		CCGVec3 m_max;
	};

	//! \brief ���㹫����Χ��
	//! \param box0 �� 
	//! \param box1 ��
	//! \return ���ع�����Χ��
	CCGaabb SurroundingBox(CCGaabb box0, CCGaabb box1);
}

#endif
