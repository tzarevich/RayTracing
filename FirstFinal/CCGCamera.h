#ifndef CCGCAMERA_H
#define CCGCAMERA_H
#pragma once

#include "CCGdefs.h"
#include "CCGVec3.h"

namespace CCG
{
	class CCGRay;
	//! \brief 相机
	class CCGCamera
	{
	public:
		//! \brief 构造函数
		CCGCamera();

		//! \brief 构造函数
		CCGCamera(CCGPoint3D &pLookfrom, CCGPoint3D &pLookat, CCGVec3 &vVup, CCGdouble dVof, CCGdouble dAspect, CCGdouble dAperture, CCGdouble dFocusDis);

		//! \brief 析构函数
		~CCGCamera();

		//! \brief 获取光线，即视线
		CCGRay GetRay(CCGdouble s, CCGdouble t);

	private:
		//! \brief 相机源点
		CCGPoint3D m_ViewOrigin;

		//! \brief 屏幕左下角点
		CCGPoint3D m_LeftCorner;

		//! \brief 屏幕水平偏移量
		CCGVec3 m_Horizontial;

		//! \brief 屏幕垂直偏移量
		CCGVec3 m_Vertical;

		//! \brief 相机坐标系的x轴分量
		CCGVec3 m_u;

		//! \brief 相机坐标系的y轴分量
		CCGVec3 m_v;

		//! \brief 相机坐标系的z轴分量
		CCGVec3 m_w;

		//! \brief 光圈半径
		CCGdouble m_dLensRadius;
	};

	CCGPoint3D GetRandomPointInUnitCircle();
}

#endif
