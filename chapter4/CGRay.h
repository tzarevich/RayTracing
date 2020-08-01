#ifndef CGRAY_H
#define CGRAY_H
#pragma once

#include "Vec3.h"

namespace CCG
{
	//! \brief 光线类
	class CCGRay
	{
	public:
		//! \brief 构造函数
		CCGRay();

		//! \brief 赋值构造函数
		CCGRay(const CCGVec3 &a, const CCGVec3 &b);

		//! \brief 析构函数
		~CCGRay();

		//! \brief 获取光线起始点位置
		CCGVec3 Origin() const;

		//! \brief 获取光线方向向量
		CCGVec3 Direction() const;

		//! \brief 获取光线上某一点位置
		//! \param t为光线函数的参数
		//! \return 返回光线上对应参数t的点的位置
		CCGVec3 PointAtParam(CCGdouble t) const;

	public:
		//! \brief 光线起点位置
		CCGVec3 A;

		//! \brief 光线方向向量
		CCGVec3 B;
	};

	//! \brief 根据光线计算对应的颜色
	//! \param r为光线
	//! \return 返回颜色RGB值
	CCGVec3 color(const CCGRay &r);
}
#endif
