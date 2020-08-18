#ifndef HITABLE_H
#define HITABLE_H
#pragma once
#include "CGRay.h"

namespace CCG
{
	class CCGRay;
	//! \brief 记录撞击中产生的信息结构体
	struct CCGHitRecord
	{
		//! \brief 光线方程中的参数t的值
		CCGdouble t;

		//! \brief 光线与物体的交点坐标
		CCGVec3 p;

		//! \brief 交点与球心形成的法线
		CCGVec3 normal;
	};
	//! \brief可撞击物理基类
	class CCGHitable
	{
	public:
		//! \brief 撞击函数，判断光线与物体是否相交
		//! \param r为光线
		//! \param tMin、tMax为参数值t的上下限，超过这个范围视为没有撞击
		//! \param rec记录撞击中产生的一些参数，如交点，法线，参数t值
		//! \return 撞击返回true，未撞击返回false
		virtual CCGbool Hit(const CCGRay &r, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &rec) const = 0;
	};

	//! \brief 可撞击物体之球体类
	class CCGSphere : public CCGHitable
	{
	public:
		//! \brief 构造函数
		CCGSphere();

		//! \brief 赋值构造函数
		CCGSphere(CCGVec3 cen, CCGdouble r);

		//! \brief 析构函数
		~CCGSphere();

		//! \brief 实现球体自己的撞击虚函数
		//! \param r为光线
		//! \param tMin、tMax为参数值t的上下限，超过这个范围视为没有撞击
		//! \param rec记录撞击中产生的一些参数，如交点，法线，参数t值
		//! \return 撞击返回true，未撞击返回false
		virtual CCGbool Hit(const CCGRay &r, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &rec) const;

	private:
		//! \brief 球体的球心坐标
		CCGVec3 center;

		//! \brief 球体半径
		CCGdouble radius;
	};

	//! \brief 可撞击物体组类，包含多个可撞击物体
	class CCGHitableList : public CCGHitable
	{
	public:
		//! \brief 构造函数
		CCGHitableList();

		//! \brief 赋值构造函数
		CCGHitableList(CCGHitable **l, CCGint n);

		//! \brief 撞击函数，这里提供一个统一的接口，各种不同的可撞击物体执行自己的方法
		//! \param r为光线
		//! \param tMin、tMax为参数值t的上下限，超过这个范围视为没有撞击
		//! \param rec记录撞击中产生的一些参数，如交点，法线，参数t值
		//! \return 撞击返回true，未撞击返回false
		virtual CCGbool Hit(const CCGRay &r, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &rec) const;

		//! \brief 析构函数
		~CCGHitableList();

	private:
		//! \brief 包含由多个可撞击物体指针的指针
		CCGHitable **m_pList;

		//! \brief 类中包含物体的个数
		CCGint m_nListSize;
	};
}

#endif

