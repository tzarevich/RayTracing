#ifndef CCGMATERIAL_H
#define CCGMATERIAL_H
#pragma once

#include "CCGdefs.h"
#include "CCGVec3.h"

namespace CCG
{
	struct CCGHitRecord;
	class CCGRay;
	//! \brief 材料基类
	class CCGMaterial
	{
	public:
		//! \brief 构造函数
		CCGMaterial();

		//! \brief 析构函数
		virtual ~CCGMaterial();

		//! \brief 散射纯虚函数
		//! \param rIn 入射光线
		//! \param sRec 撞击信息
		//! \param vAut 衰减系数
		//! \param rScattered 反射光线
		//! \return 返回是否反射
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRec, CCGVec3 &vAut, CCGRay &rScattered) const = 0;
	};

	//! \brief 朗伯特特性材料类
	class CCGLambertian : public CCGMaterial
	{
	public:
		//! \brief 构造函数
		CCGLambertian();

		//! \brief 构造函数
		CCGLambertian(const CCGVec3 &vAut);

		//! \brief 析构函数
		~CCGLambertian();

		//! \brief 朗伯特理想散射函数，随机反射
		//! \param rIn 入射光线
		//! \param sRec 撞击信息
		//! \param vAut 衰减系数
		//! \param rScattered 反射光线
		//! \return 返回是否反射
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRec, CCGVec3 &vAut, CCGRay &rScattered) const override;

	private:
		//! \brief 衰减系数
		CCGVec3 m_Attenuation;
	};

	//! \brief 金属材料类
	class CCGMental : public CCGMaterial
	{
	public:
		//! \brief 构造函数
		CCGMental();

		//! \brief 构造函数
		CCGMental(const CCGVec3 &vAut, CCGdouble dFuzz);

		//! \brief 析构函数
		~CCGMental();

		//! \brief 金属散射函数，有固定公式
		//! \param rIn 入射光线
		//! \param sRec 撞击信息
		//! \param vAut 衰减系数
		//! \param rScattered 反射光线
		//! \return 返回是否反射
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRec, CCGVec3 &vAut, CCGRay &rScattered) const override;

	private:
		//! \brief 衰减系数
		CCGVec3 m_vAttenuation;

		//! \brief 模糊系数，用以改变反射方向
		CCGdouble m_dFuzz;
	};

	//! \brief 电解质材料类
	class CCGDielectric : public CCGMaterial
	{
	public:
		//! \brief 构造函数
		CCGDielectric();

		//! \brief 构造函数
		CCGDielectric(CCGdouble dRefIdx);

		//! \brief 析构函数
		~CCGDielectric();

		//! \brief 电解质材料散射函数，随机概率决定反射还是折射
		//! \param rIn 入射光线
		//! \param sRec 撞击信息
		//! \param vAut 衰减系数
		//! \param rScattered 反射光线
		//! \return 返回是否折射
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRec, CCGVec3 &vAut, CCGRay &rScattered) const override;

	private:
		//! \brief 折射比
		CCGdouble m_dRefIdx;
	};

	CCGVec3 GetRandomPointInUnitSphere();

	CCGVec3 Reflect(const CCGVec3 &vIn, const CCGVec3 &vNormal);

	CCGbool Refract(const CCGVec3 &vIn, const CCGVec3 &vNormal, CCGdouble dRef, CCGVec3 &vRefracted);

	CCGdouble Schlick(CCGdouble dCos, CCGdouble dRefIdx);
}

#endif

