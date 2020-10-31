#ifndef CCGHITOBJECTS_H
#define CCGHITOBJECTS_H
#pragma once

#include "CCGDefs.h"
#include "CCGRay.h"
#include "CCGaabb.h"
#include <vector>

namespace CCG
{
	class CCGRay;
	class CCGMaterial;
	class CCGLambertina;
	class CCGSphere;
	class CCGTexture;

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

		//! \brief 为球体新加的纹理坐标
		CCGdouble u, v;
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

		//! \brief 计算包围盒函数
		//! \param t0,t1 时刻
		//! \param box 包围盒
		//! \return 返回是否存在包围盒
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const = 0;
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

		//! \brief 计算球体包围盒函数
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

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
		//CCGHitList(CCGHitObject **pList, CCGint nSize);
		CCGHitList();

		//! \brief 赋值构造函数
		CCGHitList(shared_ptr<CCGHitObject> object);

		//! \brief 清空数组
		void ClearList();

		//! \brief 添加物体
		void AddObject(shared_ptr<CCGHitObject> object);

		//! \brief 物体组撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief 计算多个物体包围盒函数
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief 包含多个可撞击物体数组
		std::vector<shared_ptr<CCGHitObject>> m_Object;
	};

	//! \brief 移动球体
	class CCGMovSphere : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGMovSphere();

		//! \brief 构造函数
		CCGMovSphere(CCGPoint3D c0, CCGPoint3D c1, CCGdouble dT0, CCGdouble dT1, CCGdouble dRadius, shared_ptr<CCGMaterial> mat);

		//! \brief 移动球体撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \brief tMin, tMax 交点限定范围
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief 计算包围盒
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

		//! \brief 获取球心
		CCGPoint3D GetCenter(CCGdouble t) const;

	private:
		//! \brief 球体在时间间隔的两个端点时的中心
		CCGPoint3D m_cen0, m_cen1;

		//! \brief 时间间隔
		CCGdouble m_t0, m_t1;

		//! \brief 半径
		CCGdouble m_radius;

		//! \brief 材料
		shared_ptr<CCGMaterial> m_material;
	};

	//! \brief BVH类，包围盒树结构，分为左子树和右子树
	class CCGBVHNode : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGBVHNode();

		//! \brief 构造函数
		//! \remark 递归建包围盒树
		CCGBVHNode(std::vector<shared_ptr<CCGHitObject>> &objects, CCGint nStart, CCGint nEnd, CCGdouble dTime0, CCGdouble dTime1);

		//! \brief 构造函数
		CCGBVHNode(CCGHitList &list, CCGdouble dTime0, CCGdouble dTime1);

		//! \brief 析构函数
		~CCGBVHNode();

		//! \brief BVH撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param tMin, tMax 边界值
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief 计算包围盒
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	private:
		//! \brief 左物体
		shared_ptr<CCGHitObject> m_pLeft;

		//! \brief 右物体
		shared_ptr<CCGHitObject> m_pRight;

		//! \brief 包围盒
		CCGaabb m_box;
	};

	//! \brief xy平面矩形
	class CCGXYRect : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGXYRect();

		//! \brief 构造函数
		CCGXYRect(CCGdouble dXL, CCGdouble dXR, CCGdouble dYL, CCGdouble dYR, CCGdouble dPK, shared_ptr<CCGMaterial> pMat);

		//! \brief 析构函数
		~CCGXYRect();

		//! \brief XY矩形撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param tMin, tMax 边界值
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief 计算包围盒
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief 材料
		shared_ptr<CCGMaterial> m_pMat;

		//! \brief x区间左右端点
		CCGdouble m_dXL, m_dXR;

		//! \brief y区间左右端点
		CCGdouble m_dYL, m_dYR;

		//! \brief 参数k
		CCGdouble m_dParamK;
	};

	//! \brief xz平面矩形
	class CCGXZRect : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGXZRect();

		//! \brief 构造函数
		CCGXZRect(CCGdouble dXL, CCGdouble dXR, CCGdouble dZL, CCGdouble dZR, CCGdouble dPK, shared_ptr<CCGMaterial> pMat);

		//! \brief 析构函数
		~CCGXZRect();

		//! \brief XZ矩形撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param tMin, tMax 边界值
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief 计算包围盒
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief 材料
		shared_ptr<CCGMaterial> m_pMat;

		//! \brief x区间左右端点
		CCGdouble m_dXL, m_dXR;

		//! \brief z区间左右端点
		CCGdouble m_dZL, m_dZR;

		//! \brief 参数k
		CCGdouble m_dParamK;
	};

	//! \brief yz平面矩形
	class CCGYZRect : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGYZRect();

		//! \brief 构造函数
		CCGYZRect(CCGdouble dYL, CCGdouble dYR, CCGdouble dZL, CCGdouble dZR, CCGdouble dPK, shared_ptr<CCGMaterial> pMat);

		//! \brief 析构函数
		~CCGYZRect();

		//! \brief YZ矩形撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param tMin, tMax 边界值
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief 计算包围盒
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief 材料属性
		shared_ptr<CCGMaterial> m_pMat;

		//! \brief y区间左右端点
		CCGdouble m_dYL, m_dYR;

		//! \brief z区间左右端点
		CCGdouble m_dZL, m_dZR;

		//! \brief 参数k
		CCGdouble m_dParamK;
	};

	//! \brief 反转法线类
	class CCGFlipNormals : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGFlipNormals();

		//! \brief 构造函数
		CCGFlipNormals(shared_ptr<CCGHitObject> pMat);

		//! \brief 析构函数
		~CCGFlipNormals();

		//! \brief 撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param tMin, tMax 边界值
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief 计算包围盒
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief 撞击物体
		shared_ptr<CCGHitObject> m_pMat;
	};

	//! \brief 盒体类
	class CCGBox : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGBox();

		//! \brief 构造函数
		CCGBox(const CCGVec3 &p0, const CCGVec3 &p1, shared_ptr<CCGMaterial> pMat);

		//! \brief 析构函数
		~CCGBox();

		//! \brief 立方体撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param tMin, tMax 边界值
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief 计算包围盒
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief 撞击物体
		CCGHitList m_pHit;

		//! \brief 位置
		CCGVec3 m_pMin, m_pMax;
	};

	//! \brief 移动物体类
	class CCGTranslate : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGTranslate();

		//! \brief 构造函数
		CCGTranslate(shared_ptr<CCGHitObject> pHit, const CCGVec3 &dpt);

		//! \brief 析构函数
		~CCGTranslate();

		//! \brief 要移动的物体的撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param tMin, tMax 边界值
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief 计算要移动的物体的包围盒
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief 要移动的物体
		shared_ptr<CCGHitObject> m_pHit;

		//! \brief 偏移量
		CCGVec3 m_Offset;
	};

	//! \brief 旋转物体类
	class CCGRotateY : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGRotateY();

		//! \brief 构造函数
		CCGRotateY(shared_ptr<CCGHitObject> pHit, CCGdouble dAngle);

		//! \brief 析构函数
		~CCGRotateY();

		//! \brief 要旋转的物体的撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param tMin, tMax 边界值
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief 计算要旋转的物体的包围盒
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief 要旋转的物体
		shared_ptr<CCGHitObject> m_pHit;

		//! \brief sin值
		CCGdouble m_dSin;

		//! \brief cos值
		CCGdouble m_dCos;

		//! \brief 是否有包围盒
		CCGbool m_bHasBox;

		//! \brief 盒体
		CCGaabb m_Box;
	};

	//! \brief 常量介质类
	class CCGConsMedium : public CCGHitObject
	{
	public:
		//! \brief 构造函数
		CCGConsMedium();

		//! \brief 构造函数
		CCGConsMedium(shared_ptr<CCGHitObject> pBoundary, CCGdouble dDensity, shared_ptr<CCGTexture> pTex);

		//! \brief 析构函数
		~CCGConsMedium();

		//! \brief 带有密度的物体的撞击函数，判断是否相交并将相关信息记录
		//! \param rIn 入射光线
		//! \param tMin, tMax 边界值
		//! \param sRecord 交点相关信息记录
		//! \return 返回是否相交
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief 计算要旋转的物体的包围盒
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief 包含的物体
		shared_ptr<CCGHitObject> m_pBoundary;

		//! \brief 材料
		shared_ptr<CCGMaterial> m_pPhaseFunc;

		//! \brief 密度
		CCGdouble m_dDensity;
	};

	//! \brief 比较包围盒
	CCGbool BoxCompare(const shared_ptr<CCGHitObject> a, const shared_ptr<CCGHitObject> b, CCGint nAxis);

	//! \brief 比较包围盒的x分量
	CCGbool BoxXCompare(const shared_ptr<CCGHitObject> a, const shared_ptr<CCGHitObject> b);

	//! \brief 比较包围盒的y分量
	CCGbool BoxYCompare(const shared_ptr<CCGHitObject> a, const shared_ptr<CCGHitObject> b);

	//! \brief 比较包围盒的z分量
	CCGbool BoxZCompare(const shared_ptr<CCGHitObject> a, const shared_ptr<CCGHitObject> b);

	//! \brief 获取球体的纹理坐标
	//! \param p 单位化法向量
	//! \param u,v 计算后的纹理坐标值
	//! \return 。
	void GetSphereUV(const CCGVec3 &p, CCGdouble &u, CCGdouble &v);
}

#endif

