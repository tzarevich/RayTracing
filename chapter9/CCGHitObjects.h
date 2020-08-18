#ifndef CCGHITOBJECTS_H
#define CCGHITOBJECTS_H
#pragma once

#include "CCGRay.h"

namespace CCG
{
	class CCGRay;
	class CCGMaterial;
	class CCGLambertina;

	//! \brief 记录光线照射到物体所得信息
	struct CCGHitRecord
	{
		//! \brief 撞击点对应到光线的参数t值
		CCGdouble t;

		//! \brief 光线与物体的交点
		CCGPoint3D pIntersect;

		//! \brief 交点处的法线
		CCGVec3 vNormal;

		//! \brief 物体的材料属性
		shared_ptr<CCGMaterial> pMaterial;
	};

	//! \brief 可撞击物体抽象类
	class CCGHitObject
	{
	public:
		//! \brief 撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const = 0;
	};

	//! \brief 可撞击物体之球体类
	class CCGSphere : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGSphere(const CCGPoint3D &pCenter, CCGdouble dRadius, shared_ptr<CCGMaterial> pMaterial);

		//! \brief 球体撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

	private:
		//! \brief 球体中心坐标
		CCGPoint3D m_pCenter;

		//! \brief 球体半径
		CCGdouble m_dRadius;

		//! \brief 球体材料
		shared_ptr<CCGMaterial> m_pMaterial;
	};

	//! \brief 可撞击物体组类
	class CCGHitList : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGHitList(CCGHitObject **pList, CCGint nSize);

		//! \brief 物体组撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

	private:
		//! \brief 包含多个可撞击物体的指针
		CCGHitObject **m_pList;

		//! \brief 包含的物体个数
		CCGint m_nListSize;
	};

}

#endif

