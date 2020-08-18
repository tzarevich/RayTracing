#ifndef HITABLE_H
#define HITABLE_H
#pragma once
#include "CGRay.h"

namespace CCG
{
	class CCGRay;
	//! \brief ��¼ײ���в�������Ϣ�ṹ��
	struct CCGHitRecord
	{
		//! \brief ���߷����еĲ���t��ֵ
		CCGdouble t;

		//! \brief ����������Ľ�������
		CCGVec3 p;

		//! \brief �����������γɵķ���
		CCGVec3 normal;
	};
	//! \brief��ײ���������
	class CCGHitable
	{
	public:
		//! \brief ײ���������жϹ����������Ƿ��ཻ
		//! \param rΪ����
		//! \param tMin��tMaxΪ����ֵt�������ޣ����������Χ��Ϊû��ײ��
		//! \param rec��¼ײ���в�����һЩ�������罻�㣬���ߣ�����tֵ
		//! \return ײ������true��δײ������false
		virtual CCGbool Hit(const CCGRay &r, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &rec) const = 0;
	};

	//! \brief ��ײ������֮������
	class CCGSphere : public CCGHitable
	{
	public:
		//! \brief ���캯��
		CCGSphere();

		//! \brief ��ֵ���캯��
		CCGSphere(CCGVec3 cen, CCGdouble r);

		//! \brief ��������
		~CCGSphere();

		//! \brief ʵ�������Լ���ײ���麯��
		//! \param rΪ����
		//! \param tMin��tMaxΪ����ֵt�������ޣ����������Χ��Ϊû��ײ��
		//! \param rec��¼ײ���в�����һЩ�������罻�㣬���ߣ�����tֵ
		//! \return ײ������true��δײ������false
		virtual CCGbool Hit(const CCGRay &r, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &rec) const;

	private:
		//! \brief �������������
		CCGVec3 center;

		//! \brief ����뾶
		CCGdouble radius;
	};

	//! \brief ��ײ���������࣬���������ײ������
	class CCGHitableList : public CCGHitable
	{
	public:
		//! \brief ���캯��
		CCGHitableList();

		//! \brief ��ֵ���캯��
		CCGHitableList(CCGHitable **l, CCGint n);

		//! \brief ײ�������������ṩһ��ͳһ�Ľӿڣ����ֲ�ͬ�Ŀ�ײ������ִ���Լ��ķ���
		//! \param rΪ����
		//! \param tMin��tMaxΪ����ֵt�������ޣ����������Χ��Ϊû��ײ��
		//! \param rec��¼ײ���в�����һЩ�������罻�㣬���ߣ�����tֵ
		//! \return ײ������true��δײ������false
		virtual CCGbool Hit(const CCGRay &r, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &rec) const;

		//! \brief ��������
		~CCGHitableList();

	private:
		//! \brief �����ɶ����ײ������ָ���ָ��
		CCGHitable **m_pList;

		//! \brief ���а�������ĸ���
		CCGint m_nListSize;
	};
}

#endif

