#ifndef CCGPERLIN_H
#define CCGPERLIN_H
#pragma once

#include "Vec3.h"

namespace CCG
{
	//! \brief 柏林噪声
	class CCGPerlin
	{
	public:
		//! \brief 构造函数
		CCGPerlin();

		//! \brief 析构函数
		~CCGPerlin();

	public:
		//! \brief 噪声函数
		CCGdouble Noise(const CCGVec3 &p) const;

		CCGdouble Turb(const CCGVec3 &p, CCGint nDepth = 7) const;

	public:
		//! \brief 随机噪声值
		//static CCGdouble *m_pRand;
		static CCGVec3 *m_pRand;

		//! \brief x分量随机噪声
		static CCGint *m_pPermX;

		//! \brief y分量随机噪声
		static CCGint *m_pPermY;

		//! \brief z分量随机噪声
		static CCGint *m_pPermZ;
	};

	//! \brief 产生随机噪声
	//! \param pArray 分量随机噪声值数组
	//! \param nCnt 分量随机噪声个数
	//! \return 。
	void Permute(CCGint *pArray, CCGint nCnt);

	//! \brief 产生随机噪声的函数
	//static CCGdouble *PerlinGenerate();
	static CCGVec3 *PerlinGenerate();

	//! \brief 产生分量随机噪声
	static CCGint *PerlinGerPerm();

	//! \brief 线性混合
	CCGdouble TrilinearInterp(CCGdouble c[2][2][2], CCGdouble u, CCGdouble v, CCGdouble w);

	//! \brief 柏林混合
	CCGdouble PerlinInterp(CCGVec3 c[2][2][2], CCGdouble u, CCGdouble v, CCGdouble w);
}
#endif
