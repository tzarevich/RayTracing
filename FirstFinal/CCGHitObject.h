#ifndef CCGHITOBJECT_H
#define CCGHITOBJECT_H
#pragma once

#include "CCGdefs.h"
#include "CCGVec3.h"
#include <vector>

namespace CCG
{
	class CCGRay;
	class CCGMaterial;

	//! \brief 撞击信息结构体
	struct CCGHitRecord
	{
		//! \brief 光线方程的参数t
		CCGdouble t;

		//! \brief 交点
		CCGPoint3D p;

		//! \brief 交点处的法线
		CCGVec3 normal;

		//! \brief 物体材料
		shared_ptr<CCGMaterial> mat;
	};

	//! \brief 物体基类
	class CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGHitObject();

		//! \brief 析构函数
		virtual ~CCGHitObject();

		//! \brief 撞击纯虚函数，判断是否相交并记录相交信息
		//! \param rIn 照射光线
		//! \param tMin 交点对应光线参数t的值的下限
		//! \param tMax 交点对应光线参数t的值的上限
		//! \param sRec 记录撞击信息结构体
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRec) const = 0;
	};

	//! \brief 球体类
	class CCGSphere : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGSphere();

		//! \brief 构造函数
		CCGSphere(const CCGPoint3D &pCen, CCGdouble dRad, shared_ptr<CCGMaterial> spMat);

		//! \brief 析构函数
		~CCGSphere();

		//! \brief 球体撞击函数，判断光线与球体是否相交并记录相交信息如交点及法线等
		//! \param rIn 照射光线
		//! \param tMin 交点对应光线参数t的值的下限
		//! \param tMax 交点对应光线参数t的值的上限
		//! \param sRec 记录撞击信息结构体
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRec) const override;

	private:
		//! \brief 球体球心
		CCGPoint3D m_Center;

		//! \brief 球体半径
		CCGdouble m_dRadius;

		//! \brief 球体材料
		shared_ptr<CCGMaterial> m_spMaterial;
	};

	//! \brief 可撞击物体组，包含多个可撞击物体
	class CCGHitArray : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGHitArray();

		//! \brief 构造函数
		CCGHitArray(shared_ptr<CCGHitObject> spHitObj);

		//! \brief 析构函数
		~CCGHitArray();

		//! \brief 添加物体
		void AddObject(shared_ptr<CCGHitObject> spHitObj);

		//! \brief 清空所有物体
		void ClearArray();

		//! \brief 物体组撞击函数，判断光线与包含的所有物体中的任一物体是否相交
		//! \param rIn 照射光线
		//! \param tMin 交点对应光线参数t的值的下限
		//! \param tMax 交点对应光线参数t的值的上限
		//! \param sRec 记录撞击信息结构体
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRec) const override;

	private:
		std::vector<shared_ptr<CCGHitObject>> m_vecHits;
	};
}
#endif
