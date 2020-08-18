#ifndef CCGHITOBJECTS_H
#define CCGHITOBJECTS_H
#pragma once

#include "CCGDefs.h"
#include "CCGRay.h"
#include <vector>

namespace CCG
{
	class CCGRay;
	class CCGMaterial;
	class CCGLambertina;
	class CCGSphere;

	//! \brief ��¼�������䵽����������Ϣ
	struct CCGHitRecord
	{
		//! \brief ײ�����Ӧ�����ߵĲ���tֵ
		CCGdouble t;

		//! \brief ����������Ľ���
		CCGPoint3D pIntersect;

		//! \brief ���㴦�ķ���
		CCGVec3 vNormal;

		//! \brief ����Ĳ�������
		shared_ptr<CCGMaterial> pMaterial;
	};

	//! \brief ��ײ�����������
	class CCGHitObject
	{
	public:
		//! \brief ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const = 0;
	};

	//! \brief ��ײ������֮������
	class CCGSphere : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGSphere(const CCGPoint3D &pCenter, CCGdouble dRadius, shared_ptr<CCGMaterial> pMaterial);

		//! \brief ����ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

	private:
		//! \brief ������������
		CCGPoint3D m_pCenter;

		//! \brief ����뾶
		CCGdouble m_dRadius;

		//! \brief �������
		shared_ptr<CCGMaterial> m_pMaterial;
	};

	//! \brief ��ײ����������
	class CCGHitList : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		//CCGHitList(CCGHitObject **pList, CCGint nSize);
		CCGHitList();

		//! \brief ��ֵ���캯��
		CCGHitList(shared_ptr<CCGHitObject> object);

		//! \brief �������
		void ClearList();

		//! \brief ��������
		void AddObject(shared_ptr<CCGHitObject> object);

		//! \brief ������ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

	private:
		//! \brief ���������ײ�������ָ��
		//CCGHitObject **m_pList;

		//! \brief �������������
		//CCGint m_nListSize;

		//! \brief ���������ײ����������
		std::vector<shared_ptr<CCGHitObject>> m_Object;
	};

	//CCGHitObject *RandomScene();
	CCGHitList RandomScene();
}

#endif
