#ifndef CGMATERIAL_H
#define CGMATERIAL_H
#pragma once

#include "hitable.h"
#include "CGRay.h"

namespace CCG
{
	//! \brief 材料基类
	class CCGMaterial
	{
	public:
		//! \brief 反射函数，根据不同材料有不同的反射行为
		//! \param RayIn为入射光线
		//! \param sRec为撞击信息结构体
		//! \param vAttenuation为衰减系数
		//! \param RayScattered为反射光线
		//! \return 返回值根据不同情况而定
		virtual CCGbool Scatter(const CCGRay &RayIn, const CCGHitRecord &sRec, CCGVec3 &vAttenuation, CCGRay &RayScattered) const = 0;
	};

	//! \brief 朗伯特散射材料类
	class CCGLambertian : public CCGMaterial
	{
	public:
		//! \brief 构造函数
		CCGLambertian(const CCGVec3 &v);

		//! \brief 朗伯特反射函数
		//! \param RayIn为入射光线
		//! \param sRec为撞击信息结构体
		//! \param vAttenuation为衰减系数
		//! \param RayScattered为反射光线
		//! \return 总是返回true，表示一定会有反射
		virtual CCGbool Scatter(const CCGRay &RayIn, const CCGHitRecord &sRec, CCGVec3 &vAttenuation, CCGRay &RayScattered) const override;

	private:
		//! \brief 衰减系数
		CCGVec3 m_vAlbedo;
	};


	//! \brief 金属材料类
	class CCGMental : public CCGMaterial
	{
	public:
		//! \brief 构造函数
		//! \add 添加了模糊系数
		CCGMental(const CCGVec3 &v, CCGdouble f);

		//! \brief 金属材料反射函数
		//! \param RayIn为入射光线
		//! \param sRec为撞击信息结构体
		//! \param vAttenuation为衰减系数
		//! \param RayScattered为反射光线
		//! \return 根据反射光线与法线的夹角返回值，锐角返回true，表示有效反射，钝角返回false，表示无效反射
		virtual CCGbool Scatter(const CCGRay &RayIn, const CCGHitRecord &sRec, CCGVec3 &vAttenuation, CCGRay &RayScattered) const override;
	private:
		//! \brief 金属材料衰减系数
		CCGVec3 m_vAlbedo;

		//! \brief 添加模糊系数，使反射方向随机，而不是固定
		CCGdouble m_dFuzz;
	};

	//! \brief 求金属材料反射光线
	//! \param v为入射光线单位向量
	//! \param n为法线单位向量
	//! \return 返回反射光线
	CCGVec3 Reflect(const CCGVec3 &v, const CCGVec3 &n);
}
#endif