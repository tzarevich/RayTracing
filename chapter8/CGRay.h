#ifndef CGRAY_H
#define CGRAY_H
#pragma once

#include "Vec3.h"
#include "hitable.h"

namespace CCG
{
	class CCGHitable;
	//! \brief ������
	class CCGRay
	{
	public:
		//! \brief ���캯��
		CCGRay();

		//! \brief ��ֵ���캯��
		CCGRay(const CCGVec3 &a, const CCGVec3 &b);

		//! \brief ��������
		~CCGRay();

		//! \brief ��ȡ������ʼ��λ��
		CCGVec3 Origin() const;

		//! \brief ��ȡ���߷�������
		CCGVec3 Direction() const;

		//! \brief ��ȡ������ĳһ��λ��
		//! \param tΪ���ߺ����Ĳ���
		//! \return ���ع����϶�Ӧ����t�ĵ��λ��
		CCGVec3 PointAtParam(CCGdouble t) const;

	private:
		//! \brief �������λ��
		CCGVec3 A;

		//! \brief ���߷�������
		CCGVec3 B;
	};

	//! \brief ���ݹ��߼����Ӧ����ɫ
	//! \param rΪ����
	//! \return ������ɫRGBֵ
	//CCGVec3 Color(const CCGRay &r);

	//! \brief �жϹ����Ƿ��������ཻ
	//! \param centerΪ��������
	//! \param radiusΪ����뾶
	//! \param rΪ����
	//! \return ����true��ʾ�ཻ������false��ʾ���ཻ
	//CCGbool HitSphere(const CCGVec3 &center, CCGdouble radius, const CCGRay &r);

	//! \brief �����������Ľ���
	//! \param centerΪ��������
	//! \param radiusΪ����뾶
	//! \param rΪ����
	//! \return ���ؽ����Ӧ�Ĳ���ֵt
	CCGdouble HitSphere(const CCGVec3 &center, CCGdouble radius, const CCGRay &r);

	//! \brief ���ݱ���Ҫ������Ƿ��ཻ�ж���䣬���ཻ������ֵ��Ϊ��ɫ
	//CCGVec3 Color(const CCGRay &r);

	//! \brief ���ݱ��������ӵĿ�ײ�������࣬����Color����
	//! \param rΪ����
	//! \param worldΪ��ײ�����壬���ݴ����������;���������
	//! \return ���ط�����������ͶӰ����ɫ��
	//CCGVec3 Color(const CCGRay &r, CCGHitable *world);

	//! \brief ���ɵ�λ�����ڵ������
	CCGVec3 RandomInUnitSphere();

	//! \brief ���ݱ��������ӵķ������ʣ�����Color����
	//! \param rΪ����
	//! \param worldΪײ�������б�
	//! \return ���ؽ��㴦����ɫ��
	//CCGVec3 Color(const CCGRay &r, CCGHitable *world);

	//! \brief ���ݱ��������ӵĲ������ʣ�����Color����
	//! \param RayΪ����
	//! \param pHWorldΪײ�������б�
	//! \param nDepthΪ�ݹ���ȣ�������������
	//! \return �������շ��佻�����ɫ��
	CCGVec3 Color(const CCGRay &Ray, CCGHitable *pHWorld, CCGint nDepth);

	//! \brief ����0-1֮��������
	CCGdouble GetRand();
}
#endif