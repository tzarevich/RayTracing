#ifndef CCGPERLIN_H
#define CCGPERLIN_H
#pragma once

#include "Vec3.h"

namespace CCG
{
	//! \brief ��������
	class CCGPerlin
	{
	public:
		//! \brief ���캯��
		CCGPerlin();

		//! \brief ��������
		~CCGPerlin();

	public:
		//! \brief ��������
		CCGdouble Noise(const CCGVec3 &p) const;

		CCGdouble Turb(const CCGVec3 &p, CCGint nDepth = 7) const;

	public:
		//! \brief �������ֵ
		//static CCGdouble *m_pRand;
		static CCGVec3 *m_pRand;

		//! \brief x�����������
		static CCGint *m_pPermX;

		//! \brief y�����������
		static CCGint *m_pPermY;

		//! \brief z�����������
		static CCGint *m_pPermZ;
	};

	//! \brief �����������
	//! \param pArray �����������ֵ����
	//! \param nCnt ���������������
	//! \return ��
	void Permute(CCGint *pArray, CCGint nCnt);

	//! \brief ������������ĺ���
	//static CCGdouble *PerlinGenerate();
	static CCGVec3 *PerlinGenerate();

	//! \brief ���������������
	static CCGint *PerlinGerPerm();

	//! \brief ���Ի��
	CCGdouble TrilinearInterp(CCGdouble c[2][2][2], CCGdouble u, CCGdouble v, CCGdouble w);

	//! \brief ���ֻ��
	CCGdouble PerlinInterp(CCGVec3 c[2][2][2], CCGdouble u, CCGdouble v, CCGdouble w);
}
#endif
