#ifndef CCGCAMERA_H
#define CCGCAMERA_H
#pragma once

#include "CGRay.h"

namespace CCG
{
	class CCGRay;

	//! \brief 相机类
	class CCGCamera
	{
	public:
		//! \brief 构造函数
		CCGCamera();

		//! \brief 通过相机不同的视点获取对应的光线
		//! \param u,v分别为水平和垂直偏移量
		//! \return 返回屏幕上视点与相机形成的光线
		CCGRay GetRay(CCGdouble u, CCGdouble v);

		//! \brief 析构函数
		~CCGCamera();

	private:
		//! \brief 相机中心点
		CCGVec3 m_vOrigin;

		//! \brief 屏幕左下角点
		CCGVec3 m_vLeftCorner;

		//! \brief 屏幕水平向量，用于将屏幕上的视点右移
		CCGVec3 m_vHorizontial;

		//! \brief 屏幕垂直向量，用于将屏幕上的视点上移
		CCGVec3 m_vVertical;
	};

}
#endif