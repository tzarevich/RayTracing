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
		CCGCamera::CCGCamera();

		//CCGCamera(CCGPoint3D pLookfrom, CCGPoint3D pLookat, CCGVec3 vVup, CCGdouble dFov, CCGdouble dAspect)
		//! \brief 构造函数
		CCGCamera(CCGPoint3D pLookfrom, CCGPoint3D pLookat, CCGVec3 vVup, CCGdouble dFov, CCGdouble dAspect, CCGdouble dAperture, CCGdouble dFocusDist);

		//! \brief 获取光线
		//! \param  s 水平偏移量
		//! \param  t 垂直偏移量
		//! \return 返回光线
		CCGRay GetRay(CCGdouble s, CCGdouble t);
		
	private:
		//! \brief 相机源点
		CCGPoint3D m_pViewOrigin;

		//! \brief 屏幕左下角点
		CCGPoint3D m_pLeftCorner;

		//! \brief 屏幕水平偏移分量
		CCGVec3 m_vHorizontial;

		//! \brief 屏幕垂直偏移分量
		CCGVec3 m_vVertical;

		//! \brief 相机坐标系
		CCGVec3 m_u, m_v, m_w;

		//! \brief 光圈半径
		CCGdouble m_dLenRadius;
	};

	CCGPoint3D GetRandPointInUnitCircle();
}

#endif