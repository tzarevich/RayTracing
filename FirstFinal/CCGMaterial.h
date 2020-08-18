#ifndef CCGMATERIAL_H
#define CCGMATERIAL_H
#pragma once

#include "CCGdefs.h"
#include "CCGVec3.h"

namespace CCG
{
	struct CCGHitRecord;
	class CCGRay;
	//! \brief ���ϻ���
	class CCGMaterial
	{
	public:
		//! \brief ���캯��
		CCGMaterial();

		//! \brief ��������
		virtual ~CCGMaterial();

		//! \brief ɢ�䴿�麯��
		//! \param rIn �������
		//! \param sRec ײ����Ϣ
		//! \param vAut ˥��ϵ��
		//! \param rScattered �������
		//! \return �����Ƿ���
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRec, CCGVec3 &vAut, CCGRay &rScattered) const = 0;
	};

	//! \brief �ʲ������Բ�����
	class CCGLambertian : public CCGMaterial
	{
	public:
		//! \brief ���캯��
		CCGLambertian();

		//! \brief ���캯��
		CCGLambertian(const CCGVec3 &vAut);

		//! \brief ��������
		~CCGLambertian();

		//! \brief �ʲ�������ɢ�亯�����������
		//! \param rIn �������
		//! \param sRec ײ����Ϣ
		//! \param vAut ˥��ϵ��
		//! \param rScattered �������
		//! \return �����Ƿ���
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRec, CCGVec3 &vAut, CCGRay &rScattered) const override;

	private:
		//! \brief ˥��ϵ��
		CCGVec3 m_Attenuation;
	};

	//! \brief ����������
	class CCGMental : public CCGMaterial
	{
	public:
		//! \brief ���캯��
		CCGMental();

		//! \brief ���캯��
		CCGMental(const CCGVec3 &vAut, CCGdouble dFuzz);

		//! \brief ��������
		~CCGMental();

		//! \brief ����ɢ�亯�����й̶���ʽ
		//! \param rIn �������
		//! \param sRec ײ����Ϣ
		//! \param vAut ˥��ϵ��
		//! \param rScattered �������
		//! \return �����Ƿ���
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRec, CCGVec3 &vAut, CCGRay &rScattered) const override;

	private:
		//! \brief ˥��ϵ��
		CCGVec3 m_vAttenuation;

		//! \brief ģ��ϵ�������Ըı䷴�䷽��
		CCGdouble m_dFuzz;
	};

	//! \brief ����ʲ�����
	class CCGDielectric : public CCGMaterial
	{
	public:
		//! \brief ���캯��
		CCGDielectric();

		//! \brief ���캯��
		CCGDielectric(CCGdouble dRefIdx);

		//! \brief ��������
		~CCGDielectric();

		//! \brief ����ʲ���ɢ�亯����������ʾ������仹������
		//! \param rIn �������
		//! \param sRec ײ����Ϣ
		//! \param vAut ˥��ϵ��
		//! \param rScattered �������
		//! \return �����Ƿ�����
		virtual CCGbool Scatter(const CCGRay &rIn, CCGHitRecord &sRec, CCGVec3 &vAut, CCGRay &rScattered) const override;

	private:
		//! \brief �����
		CCGdouble m_dRefIdx;
	};

	CCGVec3 GetRandomPointInUnitSphere();

	CCGVec3 Reflect(const CCGVec3 &vIn, const CCGVec3 &vNormal);

	CCGbool Refract(const CCGVec3 &vIn, const CCGVec3 &vNormal, CCGdouble dRef, CCGVec3 &vRefracted);

	CCGdouble Schlick(CCGdouble dCos, CCGdouble dRefIdx);
}

#endif

