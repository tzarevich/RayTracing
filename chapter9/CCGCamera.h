#ifndef CCGCAMERA_H
#define CCGCAMERA_H
#pragma once

#include "CCGDefs.h"
#include "Vec3.h"
#include "CCGRay.h"

namespace CCG
{

	//! \brief 简单相机类
	class CCGCamera
	{
	public:
		//! \brief 构造函数
		CCGCamera();

		CCGRay GetRay(CCGdouble u, CCGdouble v);
		
	private:
		//! \brief 相机源点
		CCGPoint3D m_pViewOrigin;

		//! \brief 屏幕左下角点
		CCGPoint3D m_pLeftCorner;

		//! \brief 屏幕水平偏移分量
		CCGVec3 m_vHorizontial;

		//! \brief 屏幕垂直偏移分量
		CCGVec3 m_vVertical;
	};
}

#endif