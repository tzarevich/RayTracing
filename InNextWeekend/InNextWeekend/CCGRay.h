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

	//! \brief 声明需要用到的其他类
	class CCGVec3;

	//! \brief 光线类
	class CCGRay
	{
	public:
		//! \brief 构造函数
		CCGRay();

		//! \brief 构造函数
		CCGRay(const CCGPoint3D &pOrigin, const CCGVec3 &vDirection, CCGdouble dTime = 0.0);

		//! \brief 获取光线起点位置
		CCGPoint3D GetOrigin() const;

		//! \brief 获取光线方向
		CCGVec3 GetDirection() const;

		//! \brief 获取时刻
		CCGdouble GetTime() const;

		//! \brief 获取光线上某一点的位置
		CCGPoint3D PointAtParam(CCGdouble t) const;

	private:
		//! \brief 光线起点位置
		CCGPoint3D m_pOrigin;

		//! \brief 光线方向向量
		CCGVec3 m_vDirection;

		//! \brief 光线时刻
		CCGdouble m_time;
	};

	//! \brief 获取单位球体内的任意一点
	CCGPoint3D GetRandPointInUnitSphere();
}

#endif
