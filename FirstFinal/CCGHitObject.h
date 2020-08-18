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

	//! \brief ײ����Ϣ�ṹ��
	struct CCGHitRecord
	{
		//! \brief ���߷��̵Ĳ���t
		CCGdouble t;

		//! \brief ����
		CCGPoint3D p;

		//! \brief ���㴦�ķ���
		CCGVec3 normal;

		//! \brief �������
		shared_ptr<CCGMaterial> mat;
	};

	//! \brief �������
	class CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGHitObject();

		//! \brief ��������
		virtual ~CCGHitObject();

		//! \brief ײ�����麯�����ж��Ƿ��ཻ����¼�ཻ��Ϣ
		//! \param rIn �������
		//! \param tMin �����Ӧ���߲���t��ֵ������
		//! \param tMax �����Ӧ���߲���t��ֵ������
		//! \param sRec ��¼ײ����Ϣ�ṹ��
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRec) const = 0;
	};

	//! \brief ������
	class CCGSphere : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGSphere();

		//! \brief ���캯��
		CCGSphere(const CCGPoint3D &pCen, CCGdouble dRad, shared_ptr<CCGMaterial> spMat);

		//! \brief ��������
		~CCGSphere();

		//! \brief ����ײ���������жϹ����������Ƿ��ཻ����¼�ཻ��Ϣ�罻�㼰���ߵ�
		//! \param rIn �������
		//! \param tMin �����Ӧ���߲���t��ֵ������
		//! \param tMax �����Ӧ���߲���t��ֵ������
		//! \param sRec ��¼ײ����Ϣ�ṹ��
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRec) const override;

	private:
		//! \brief ��������
		CCGPoint3D m_Center;

		//! \brief ����뾶
		CCGdouble m_dRadius;

		//! \brief �������
		shared_ptr<CCGMaterial> m_spMaterial;
	};

	//! \brief ��ײ�������飬���������ײ������
	class CCGHitArray : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGHitArray();

		//! \brief ���캯��
		CCGHitArray(shared_ptr<CCGHitObject> spHitObj);

		//! \brief ��������
		~CCGHitArray();

		//! \brief �������
		void AddObject(shared_ptr<CCGHitObject> spHitObj);

		//! \brief �����������
		void ClearArray();

		//! \brief ������ײ���������жϹ�������������������е���һ�����Ƿ��ཻ
		//! \param rIn �������
		//! \param tMin �����Ӧ���߲���t��ֵ������
		//! \param tMax �����Ӧ���߲���t��ֵ������
		//! \param sRec ��¼ײ����Ϣ�ṹ��
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRec) const override;

	private:
		std::vector<shared_ptr<CCGHitObject>> m_vecHits;
	};
}
#endif
