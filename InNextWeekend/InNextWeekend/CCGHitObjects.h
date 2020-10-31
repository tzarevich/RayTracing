#ifndef CCGHITOBJECTS_H
#define CCGHITOBJECTS_H
#pragma once

#include "CCGDefs.h"
#include "CCGRay.h"
#include "CCGaabb.h"
#include <vector>

namespace CCG
{
	class CCGRay;
	class CCGMaterial;
	class CCGLambertina;
	class CCGSphere;
	class CCGTexture;

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

		//! \brief Ϊ�����¼ӵ���������
		CCGdouble u, v;
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

		//! \brief �����Χ�к���
		//! \param t0,t1 ʱ��
		//! \param box ��Χ��
		//! \return �����Ƿ���ڰ�Χ��
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const = 0;
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

		//! \brief ���������Χ�к���
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

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

		//! \brief �������
		void AddObject(shared_ptr<CCGHitObject> object);

		//! \brief ������ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief �����������Χ�к���
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief ���������ײ����������
		std::vector<shared_ptr<CCGHitObject>> m_Object;
	};

	//! \brief �ƶ�����
	class CCGMovSphere : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGMovSphere();

		//! \brief ���캯��
		CCGMovSphere(CCGPoint3D c0, CCGPoint3D c1, CCGdouble dT0, CCGdouble dT1, CCGdouble dRadius, shared_ptr<CCGMaterial> mat);

		//! \brief �ƶ�����ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \brief tMin, tMax �����޶���Χ
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief �����Χ��
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

		//! \brief ��ȡ����
		CCGPoint3D GetCenter(CCGdouble t) const;

	private:
		//! \brief ������ʱ�����������˵�ʱ������
		CCGPoint3D m_cen0, m_cen1;

		//! \brief ʱ����
		CCGdouble m_t0, m_t1;

		//! \brief �뾶
		CCGdouble m_radius;

		//! \brief ����
		shared_ptr<CCGMaterial> m_material;
	};

	//! \brief BVH�࣬��Χ�����ṹ����Ϊ��������������
	class CCGBVHNode : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGBVHNode();

		//! \brief ���캯��
		//! \remark �ݹ齨��Χ����
		CCGBVHNode(std::vector<shared_ptr<CCGHitObject>> &objects, CCGint nStart, CCGint nEnd, CCGdouble dTime0, CCGdouble dTime1);

		//! \brief ���캯��
		CCGBVHNode(CCGHitList &list, CCGdouble dTime0, CCGdouble dTime1);

		//! \brief ��������
		~CCGBVHNode();

		//! \brief BVHײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param tMin, tMax �߽�ֵ
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief �����Χ��
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	private:
		//! \brief ������
		shared_ptr<CCGHitObject> m_pLeft;

		//! \brief ������
		shared_ptr<CCGHitObject> m_pRight;

		//! \brief ��Χ��
		CCGaabb m_box;
	};

	//! \brief xyƽ�����
	class CCGXYRect : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGXYRect();

		//! \brief ���캯��
		CCGXYRect(CCGdouble dXL, CCGdouble dXR, CCGdouble dYL, CCGdouble dYR, CCGdouble dPK, shared_ptr<CCGMaterial> pMat);

		//! \brief ��������
		~CCGXYRect();

		//! \brief XY����ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param tMin, tMax �߽�ֵ
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief �����Χ��
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief ����
		shared_ptr<CCGMaterial> m_pMat;

		//! \brief x�������Ҷ˵�
		CCGdouble m_dXL, m_dXR;

		//! \brief y�������Ҷ˵�
		CCGdouble m_dYL, m_dYR;

		//! \brief ����k
		CCGdouble m_dParamK;
	};

	//! \brief xzƽ�����
	class CCGXZRect : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGXZRect();

		//! \brief ���캯��
		CCGXZRect(CCGdouble dXL, CCGdouble dXR, CCGdouble dZL, CCGdouble dZR, CCGdouble dPK, shared_ptr<CCGMaterial> pMat);

		//! \brief ��������
		~CCGXZRect();

		//! \brief XZ����ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param tMin, tMax �߽�ֵ
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief �����Χ��
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief ����
		shared_ptr<CCGMaterial> m_pMat;

		//! \brief x�������Ҷ˵�
		CCGdouble m_dXL, m_dXR;

		//! \brief z�������Ҷ˵�
		CCGdouble m_dZL, m_dZR;

		//! \brief ����k
		CCGdouble m_dParamK;
	};

	//! \brief yzƽ�����
	class CCGYZRect : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGYZRect();

		//! \brief ���캯��
		CCGYZRect(CCGdouble dYL, CCGdouble dYR, CCGdouble dZL, CCGdouble dZR, CCGdouble dPK, shared_ptr<CCGMaterial> pMat);

		//! \brief ��������
		~CCGYZRect();

		//! \brief YZ����ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param tMin, tMax �߽�ֵ
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief �����Χ��
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief ��������
		shared_ptr<CCGMaterial> m_pMat;

		//! \brief y�������Ҷ˵�
		CCGdouble m_dYL, m_dYR;

		//! \brief z�������Ҷ˵�
		CCGdouble m_dZL, m_dZR;

		//! \brief ����k
		CCGdouble m_dParamK;
	};

	//! \brief ��ת������
	class CCGFlipNormals : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGFlipNormals();

		//! \brief ���캯��
		CCGFlipNormals(shared_ptr<CCGHitObject> pMat);

		//! \brief ��������
		~CCGFlipNormals();

		//! \brief ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param tMin, tMax �߽�ֵ
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief �����Χ��
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief ײ������
		shared_ptr<CCGHitObject> m_pMat;
	};

	//! \brief ������
	class CCGBox : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGBox();

		//! \brief ���캯��
		CCGBox(const CCGVec3 &p0, const CCGVec3 &p1, shared_ptr<CCGMaterial> pMat);

		//! \brief ��������
		~CCGBox();

		//! \brief ������ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param tMin, tMax �߽�ֵ
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief �����Χ��
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief ײ������
		CCGHitList m_pHit;

		//! \brief λ��
		CCGVec3 m_pMin, m_pMax;
	};

	//! \brief �ƶ�������
	class CCGTranslate : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGTranslate();

		//! \brief ���캯��
		CCGTranslate(shared_ptr<CCGHitObject> pHit, const CCGVec3 &dpt);

		//! \brief ��������
		~CCGTranslate();

		//! \brief Ҫ�ƶ��������ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param tMin, tMax �߽�ֵ
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief ����Ҫ�ƶ�������İ�Χ��
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief Ҫ�ƶ�������
		shared_ptr<CCGHitObject> m_pHit;

		//! \brief ƫ����
		CCGVec3 m_Offset;
	};

	//! \brief ��ת������
	class CCGRotateY : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGRotateY();

		//! \brief ���캯��
		CCGRotateY(shared_ptr<CCGHitObject> pHit, CCGdouble dAngle);

		//! \brief ��������
		~CCGRotateY();

		//! \brief Ҫ��ת�������ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param tMin, tMax �߽�ֵ
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief ����Ҫ��ת������İ�Χ��
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief Ҫ��ת������
		shared_ptr<CCGHitObject> m_pHit;

		//! \brief sinֵ
		CCGdouble m_dSin;

		//! \brief cosֵ
		CCGdouble m_dCos;

		//! \brief �Ƿ��а�Χ��
		CCGbool m_bHasBox;

		//! \brief ����
		CCGaabb m_Box;
	};

	//! \brief ����������
	class CCGConsMedium : public CCGHitObject
	{
	public:
		//! \brief ���캯��
		CCGConsMedium();

		//! \brief ���캯��
		CCGConsMedium(shared_ptr<CCGHitObject> pBoundary, CCGdouble dDensity, shared_ptr<CCGTexture> pTex);

		//! \brief ��������
		~CCGConsMedium();

		//! \brief �����ܶȵ������ײ���������ж��Ƿ��ཻ���������Ϣ��¼
		//! \param rIn �������
		//! \param tMin, tMax �߽�ֵ
		//! \param sRecord ���������Ϣ��¼
		//! \return �����Ƿ��ཻ
		virtual CCGbool Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const override;

		//! \brief ����Ҫ��ת������İ�Χ��
		virtual CCGbool BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const override;

	public:
		//! \brief ����������
		shared_ptr<CCGHitObject> m_pBoundary;

		//! \brief ����
		shared_ptr<CCGMaterial> m_pPhaseFunc;

		//! \brief �ܶ�
		CCGdouble m_dDensity;
	};

	//! \brief �Ƚϰ�Χ��
	CCGbool BoxCompare(const shared_ptr<CCGHitObject> a, const shared_ptr<CCGHitObject> b, CCGint nAxis);

	//! \brief �Ƚϰ�Χ�е�x����
	CCGbool BoxXCompare(const shared_ptr<CCGHitObject> a, const shared_ptr<CCGHitObject> b);

	//! \brief �Ƚϰ�Χ�е�y����
	CCGbool BoxYCompare(const shared_ptr<CCGHitObject> a, const shared_ptr<CCGHitObject> b);

	//! \brief �Ƚϰ�Χ�е�z����
	CCGbool BoxZCompare(const shared_ptr<CCGHitObject> a, const shared_ptr<CCGHitObject> b);

	//! \brief ��ȡ�������������
	//! \param p ��λ��������
	//! \param u,v ��������������ֵ
	//! \return ��
	void GetSphereUV(const CCGVec3 &p, CCGdouble &u, CCGdouble &v);
}

#endif

