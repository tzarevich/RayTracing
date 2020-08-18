#ifndef CGMATERIAL_H
#define CGMATERIAL_H
#pragma once

#include "hitable.h"
#include "CGRay.h"

namespace CCG
{
	//! \brief ���ϻ���
	class CCGMaterial
	{
	public:
		//! \brief ���亯�������ݲ�ͬ�����в�ͬ�ķ�����Ϊ
		//! \param RayInΪ�������
		//! \param sRecΪײ����Ϣ�ṹ��
		//! \param vAttenuationΪ˥��ϵ��
		//! \param RayScatteredΪ�������
		//! \return ����ֵ���ݲ�ͬ�������
		virtual CCGbool Scatter(const CCGRay &RayIn, const CCGHitRecord &sRec, CCGVec3 &vAttenuation, CCGRay &RayScattered) const = 0;
	};

	//! \brief �ʲ���ɢ�������
	class CCGLambertian : public CCGMaterial
	{
	public:
		//! \brief ���캯��
		CCGLambertian(const CCGVec3 &v);

		//! \brief �ʲ��ط��亯��
		//! \param RayInΪ�������
		//! \param sRecΪײ����Ϣ�ṹ��
		//! \param vAttenuationΪ˥��ϵ��
		//! \param RayScatteredΪ�������
		//! \return ���Ƿ���true����ʾһ�����з���
		virtual CCGbool Scatter(const CCGRay &RayIn, const CCGHitRecord &sRec, CCGVec3 &vAttenuation, CCGRay &RayScattered) const override;

	private:
		//! \brief ˥��ϵ��
		CCGVec3 m_vAlbedo;
	};


	//! \brief ����������
	class CCGMental : public CCGMaterial
	{
	public:
		//! \brief ���캯��
		//! \add �����ģ��ϵ��
		CCGMental(const CCGVec3 &v, CCGdouble f);

		//! \brief �������Ϸ��亯��
		//! \param RayInΪ�������
		//! \param sRecΪײ����Ϣ�ṹ��
		//! \param vAttenuationΪ˥��ϵ��
		//! \param RayScatteredΪ�������
		//! \return ���ݷ�������뷨�ߵļнǷ���ֵ����Ƿ���true����ʾ��Ч���䣬�۽Ƿ���false����ʾ��Ч����
		virtual CCGbool Scatter(const CCGRay &RayIn, const CCGHitRecord &sRec, CCGVec3 &vAttenuation, CCGRay &RayScattered) const override;
	private:
		//! \brief ��������˥��ϵ��
		CCGVec3 m_vAlbedo;

		//! \brief ���ģ��ϵ����ʹ���䷽������������ǹ̶�
		CCGdouble m_dFuzz;
	};

	//! \brief ��������Ϸ������
	//! \param vΪ������ߵ�λ����
	//! \param nΪ���ߵ�λ����
	//! \return ���ط������
	CCGVec3 Reflect(const CCGVec3 &v, const CCGVec3 &n);
}
#endif