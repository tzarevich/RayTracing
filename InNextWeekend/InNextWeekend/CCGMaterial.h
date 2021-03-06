#ifndef CCGMATERIAL_H
#define CCGMATERIAL_H
#pragma once

#include "CCGDefs.h"
#include "CCGHitObjects.h"
#include "CCGTexture.h"

namespace CCG
{
	//! \brief 材料基类
	class CCGMaterial
	{
	public:
		//! \brief 散射纯虚函数
		//! \param rIn 入射光线
		//! \param sRecord 记录撞击信息
		//! \param vAttenuation 衰减系数
		//! \param rScattered 反射光线
		//! \return 根据具体的反射材料返回值
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const = 0;

		//! \brief 发光函数
		//! \returan 返回黑色背景
		virtual CCGVec3	Emitted(CCGdouble u, CCGdouble v, const CCGVec3 &p) const;
	};

	//! \brief 朗伯特理想反射，定义一种具有这种特性的材料类
	class CCGLambertina : public CCGMaterial
	{
	public:
		//! \brief 构造函数
		CCGLambertina(shared_ptr<CCGTexture> pAttenuation);

		//! \brief 朗伯特理想散射函数
		//! \param rIn 入射光线
		//! \param sRecord 记录撞击信息
		//! \param vAttenuation 衰减系数
		//! \param rScattered 反射光线
		//! \return 朗伯特理想反射，一定会反射，所以一直返true
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const override;
		
	private:
		//! \brief RGB衰减系数
		shared_ptr<CCGTexture> m_pAttenuation;
	};

	//! \brief 金属材料类
	class CCGMental : public CCGMaterial
	{
	public:
		//! \brief 构造函数
		CCGMental(const CCGVec3 &vAttenuation, CCGdouble dFuzz);

		//! \brief 金属散射函数
		//! \param rIn 入射光线
		//! \param sRecord 记录撞击信息
		//! \param vAttenuation 衰减系数
		//! \param rScattered 反射光线
		//! \return 根据反射的夹角返回，锐角true，钝角false
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const override;
	private:
		//! \brief RGB衰减系数
		CCGVec3 m_vAttenuation;

		//! \brief 添加模糊系数，使反射方向随机，而不是固定
		CCGdouble m_dFuzz;
	};

	//! \brief 绝缘材料类
	class CCGDielectric : public CCGMaterial
	{
	public:
		//! \brief 构造函数
		CCGDielectric(CCGdouble dRefIdx);

		//! \brief 绝缘材料散射函数
		//! \param rIn 入射光线
		//! \param sRecord 记录撞击信息
		//! \param vAttenuation 衰减系数
		//! \param rScattered 反射光线
		//! \return 返回是否存在折射
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const override;

	private:
		//! \brief 折射系数比
		CCGdouble m_dRefIdx;
	};

	//! \brief 发光物体类
	class CCGDfsLight : public CCGMaterial
	{
	public:
		//! \brief 构造函数
		CCGDfsLight();

		//! \brief 构造函数
		CCGDfsLight(shared_ptr<CCGTexture> pTex);

		//! \brief 析构函数
		~CCGDfsLight();

		//! \brief 发光材料散射函数
		//! \param rIn 入射光线
		//! \param sRecord 记录撞击信息
		//! \param vAttenuation 衰减系数
		//! \param rScattered 反射光线
		//! \return 返回false，不反射
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const override;

		//! \brief 发光函数
		//! \returan 返回发光颜色值
		virtual CCGVec3	Emitted(CCGdouble u, CCGdouble v, const CCGVec3 &p) const;

	public:
		//! \brief 纹理值，决定最终颜色
		shared_ptr<CCGTexture> m_pEmit;
	};

	//! \brief smoke效应专用材料
	class CCGIsotropic : public CCGMaterial
	{
	public:
		//! \brief 构造函数
		CCGIsotropic();

		//! \brief 构造函数
		CCGIsotropic(shared_ptr<CCGTexture> pTex);

		//! \brief 析构函数
		~CCGIsotropic();

		//! \brief smoke材料散射函数
		//! \param rIn 入射光线
		//! \param sRecord 记录撞击信息
		//! \param vAttenuation 衰减系数
		//! \param rScattered 反射光线
		//! \return 返回true
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const override;

	public:
		//! \brief 纹理
		shared_ptr<CCGTexture> m_pTex;
	};

	//! \brief 公共函数

	//! \brief 求金属材料反射线
	//! \param vIn 入射线
	//! \param vNormal 法线
	//! \return 返回反射线
	CCGVec3 Reflect(const CCGVec3 &vIn, const CCGVec3 &vNormal);

	//! \brief 求绝缘材料折射线
	//! \param vIn 入射线
	//! \param vNormal 法线
	//! \param dNiOverNt 折射系数
	//! \param vRefrated 折射线
	//! \return 存在折射返回true，否则返回false
	CCGbool Refract(const CCGVec3 &vIn, const CCGVec3 &vNormal, CCGdouble dNiOverNt, CCGVec3 &vRefrated);

	//! \brief 求系数
	//! \param dCos 系数
	//! \param dRefIdx 折射系数比
	//! \return 
	CCGdouble Schlick(CCGdouble dCos, CCGdouble dRefIdx);
}

#endif