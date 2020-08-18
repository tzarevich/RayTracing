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
		CCGRay(const CCGPoint3D &pOrigin, const CCGVec3 &vDirection);

		//! \brief 获取光线起点位置
		CCGPoint3D GetOrigin() const;

		//! \brief 获取光线方向
		CCGVec3 GetDirection() const;

		//! \brief 获取光线上某一点的位置
		CCGPoint3D PointAtParam(CCGdouble t) const;

	private:
		//! \brief 光线起点位置
		CCGPoint3D m_pOrigin;

		//! \brief 光线方向向量
		CCGVec3 m_vDirection;
	};

	//! \brief 判断是否撞击，即光线是否照射到物体上
	//! \param rIn 照射光线
	//! \param pCenter 球体的球心
	//! \param dRadius 球体的半径
	//! \return 返回是否撞击，即光线是否照射到球体上，是返回true，否返回false
	//CCGbool HitSphere(const CCGRay &rIn, CCGPoint3D &pCenter, CCGdouble dRadius);

	//! \brief 判断是否撞击，即光线是否照射到物体上
	//! \param rIn 照射光线
	//! \param pCenter 球体的球心
	//! \param dRadius 球体的半径
	//! \return 返回撞击的交点的参数值t
	CCGdouble HitSphere(const CCGRay &rIn, CCGPoint3D &pCenter, CCGdouble dRadius);

	//! \brief 获取0-1之间的一个double型随机数
	CCGdouble GetDBRand();

	//! \brief 获取单位球体内的任意一点
	CCGPoint3D GetRandPointInUnitSphere();

	//! \brief 颜色函数，根据反射情况得到对应颜色表
	//! \param rIn 照射光线
	//! \param hList 物体组
	//! \return 返回撞击的交点的颜色值
	//CCGColor3D Color(const CCGRay &rIn, CCGHitObject *hList);

	//! \brief 颜色函数，根据反射情况得到对应颜色表
	//! \param rIn 照射光线
	//! \param hList 物体组
	//! \param nDepth 递归深度，即反射的最大次数
	//! \return 返回撞击的交点的颜色值
	CCGColor3D Color(const CCGRay &rIn, const CCGHitObject& hList, CCGint nDepth);
}

#endif
