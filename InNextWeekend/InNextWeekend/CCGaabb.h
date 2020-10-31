#ifndef CCGAABB_H
#define CCGAABB_H
#pragma once

#include "Vec3.h"

namespace CCG
{
	class CCGRay;
	//! \brief 包围盒
	class CCGaabb
	{
	public:
		//! \brief 构造函数
		CCGaabb();

		//! \brief 构造函数
		CCGaabb(const CCGVec3 &a, const CCGVec3 &b);

		//! \brief 析构函数
		~CCGaabb();

		//! \brief 获取最小边界
		CCGVec3 GetMin() const;

		//! \brief 获取最大边界
		CCGVec3 GetMax() const;

		//! \brief 撞击函数，判断光线是否与包围盒相交
		//! \brief rIn 光线
		//! \brief tMin 边界最小值
		//! \brief tMax 边界最大值
		//! \brief return 返回是否相交
		CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax) const;

	public:
		//! \brief 边界最小值
		CCGVec3 m_min;

		//! \brief 边界最大值
		CCGVec3 m_max;
	};

	//! \brief 计算公共包围盒
	//! \param box0 。 
	//! \param box1 。
	//! \return 返回公共包围盒
	CCGaabb SurroundingBox(CCGaabb box0, CCGaabb box1);
}

#endif
