#ifndef CCGMATERIAL_H
#define CCGMATERIAL_H
#pragma once

#include "CCGDefs.h"
#include "CCGHitObjects.h"

namespace CCG
{
	//! \brief ���ϻ���
	class CCGMaterial
	{
	public:
		//! \brief ɢ�䴿�麯��
		//! \param rIn �������
		//! \param sRecord ��¼ײ����Ϣ
		//! \param vAttenuation ˥��ϵ��
		//! \param rScattered �������
		//! \return ���ݾ���ķ�����Ϸ���ֵ
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const = 0;
	};

	//! \brief �ʲ������뷴�䣬����һ�־����������ԵĲ�����
	class CCGLambertina : public CCGMaterial
	{
	public:
		//! \brief ���캯��
		CCGLambertina(const CCGVec3 &vAttenuation);

		//! \brief �ʲ�������ɢ�亯��
		//! \param rIn �������
		//! \param sRecord ��¼ײ����Ϣ
		//! \param vAttenuation ˥��ϵ��
		//! \param rScattered �������
		//! \return �ʲ������뷴�䣬һ���ᷴ�䣬����һֱ��true
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const override;
		
	private:
		//! \brief RGB˥��ϵ��
		CCGVec3 m_vAttenuation;
	};

	//! \brief ����������
	class CCGMental : public CCGMaterial
	{
	public:
		//! \brief ���캯��
		CCGMental(const CCGVec3 &vAttenuation, CCGdouble dFuzz);

		//! \brief ����ɢ�亯��
		//! \param rIn �������
		//! \param sRecord ��¼ײ����Ϣ
		//! \param vAttenuation ˥��ϵ��
		//! \param rScattered �������
		//! \return ���ݷ���ļнǷ��أ����true���۽�false
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const override;
	private:
		//! \brief RGB˥��ϵ��
		CCGVec3 m_vAttenuation;

		//! \brief ���ģ��ϵ����ʹ���䷽������������ǹ̶�
		CCGdouble m_dFuzz;
	};

	//! \brief ��Ե������
	class CCGDielectric : public CCGMaterial
	{
	public:
		//! \brief ���캯��
		CCGDielectric(CCGdouble dRefIdx);

		//! \brief ��Ե����ɢ�亯��
		//! \param rIn �������
		//! \param sRecord ��¼ײ����Ϣ
		//! \param vAttenuation ˥��ϵ��
		//! \param rScattered �������
		//! \return �����Ƿ��������
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const override;

	private:
		//! \brief ����ϵ����
		CCGdouble m_dRefIdx;
	};

	//! \brief ��������Ϸ�����
	//! \param vIn ������
	//! \param vNormal ����
	//! \return ���ط�����
	CCGVec3 Reflect(const CCGVec3 &vIn, const CCGVec3 &vNormal);

	//! \brief ���Ե����������
	//! \param vIn ������
	//! \param vNormal ����
	//! \param dNiOverNt ����ϵ��
	//! \param vRefrated ������
	//! \return �������䷵��true�����򷵻�false
	CCGbool Refract(const CCGVec3 &vIn, const CCGVec3 &vNormal, CCGdouble dNiOverNt, CCGVec3 &vRefrated);

	//! \brief ��ϵ��
	//! \param dCos ϵ��
	//! \param dRefIdx ����ϵ����
	//! \return 
	CCGdouble Schlick(CCGdouble dCos, CCGdouble dRefIdx);
}

#endif