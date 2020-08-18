#ifndef CCGRAY_H
#define CCGRAY_H
#pragma once

#include "CCGVec3.h"

namespace CCG
{
	//! \brief 光线
	class CCGRay
	{
	public:
		//! \brief 构造函数
		CCGRay();

		//! \brief 构造函数
		CCGRay(const CCGPoint3D &pO, const CCGVec3 &vDir);

		//! \brief 析构函数
		~CCGRay();

		//! \brief 获取光线源点
		CCGPoint3D GetOrigin() const;

		//! \brief 获取光线方向
		CCGVec3 GetDirection() const;

		//! \brief 获取光线上某一点
		CCGPoint3D GetPointAtParam(CCGdouble t) const;

	private:
		//! \brief 光线源点
		CCGPoint3D m_pOrigin;

		//! \brief 光线方向
		CCGVec3 m_vDirection;

	};

}
#endif

