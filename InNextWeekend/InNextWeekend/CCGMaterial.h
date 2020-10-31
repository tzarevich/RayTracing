#ifndef CCGMATERIAL_H
#define CCGMATERIAL_H
#pragma once

#include "CCGDefs.h"
#include "CCGHitObjects.h"
#include "CCGTexture.h"

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

		//! \brief ���⺯��
		//! \returan ���غ�ɫ����
		virtual CCGVec3	Emitted(CCGdouble u, CCGdouble v, const CCGVec3 &p) const;
	};

	//! \brief �ʲ������뷴�䣬����һ�־����������ԵĲ�����
	class CCGLambertina : public CCGMaterial
	{
	public:
		//! \brief ���캯��
		CCGLambertina(shared_ptr<CCGTexture> pAttenuation);

		//! \brief �ʲ�������ɢ�亯��
		//! \param rIn �������
		//! \param sRecord ��¼ײ����Ϣ
		//! \param vAttenuation ˥��ϵ��
		//! \param rScattered �������
		//! \return �ʲ������뷴�䣬һ���ᷴ�䣬����һֱ��true
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const override;
		
	private:
		//! \brief RGB˥��ϵ��
		shared_ptr<CCGTexture> m_pAttenuation;
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

	//! \brief ����������
	class CCGDfsLight : public CCGMaterial
	{
	public:
		//! \brief ���캯��
		CCGDfsLight();

		//! \brief ���캯��
		CCGDfsLight(shared_ptr<CCGTexture> pTex);

		//! \brief ��������
		~CCGDfsLight();

		//! \brief �������ɢ�亯��
		//! \param rIn �������
		//! \param sRecord ��¼ײ����Ϣ
		//! \param vAttenuation ˥��ϵ��
		//! \param rScattered �������
		//! \return ����false��������
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const override;

		//! \brief ���⺯��
		//! \returan ���ط�����ɫֵ
		virtual CCGVec3	Emitted(CCGdouble u, CCGdouble v, const CCGVec3 &p) const;

	public:
		//! \brief ����ֵ������������ɫ
		shared_ptr<CCGTexture> m_pEmit;
	};

	//! \brief smokeЧӦר�ò���
	class CCGIsotropic : public CCGMaterial
	{
	public:
		//! \brief ���캯��
		CCGIsotropic();

		//! \brief ���캯��
		CCGIsotropic(shared_ptr<CCGTexture> pTex);

		//! \brief ��������
		~CCGIsotropic();

		//! \brief smoke����ɢ�亯��
		//! \param rIn �������
		//! \param sRecord ��¼ײ����Ϣ
		//! \param vAttenuation ˥��ϵ��
		//! \param rScattered �������
		//! \return ����true
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const override;

	public:
		//! \brief ����
		shared_ptr<CCGTexture> m_pTex;
	};

	//! \brief ��������

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