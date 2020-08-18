#include "CCGHitObject.h"
#include "CCGRay.h"

namespace CCG
{

	CCGHitObject::CCGHitObject()
	{
	}


	CCGHitObject::~CCGHitObject()
	{
	}

	CCGSphere::CCGSphere()
	{
	}

	CCGSphere::CCGSphere(const CCGPoint3D &pCen, CCGdouble dRad, shared_ptr<CCGMaterial> spMat) : 
		m_Center(pCen), m_dRadius(dRad), m_spMaterial(spMat)
	{
	}

	CCGSphere::~CCGSphere()
	{
	}

	CCGbool CCGSphere::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRec) const
	{
		//解一元二次方程求参数t
		CCGVec3 cp = rIn.GetOrigin() - m_Center;
		CCGdouble a = Dot(rIn.GetDirection(), rIn.GetDirection());
		CCGdouble b = Dot(rIn.GetDirection(), cp);
		CCGdouble c = Dot(cp, cp) - m_dRadius*m_dRadius;
		CCGdouble dDic = b*b - a*c;
		
		//存在两个实根，即光线与球体相割
		if (dDic > 0) {
			CCGdouble x1 = (-b - sqrt(dDic)) / a;
			if (tMin < x1 && x1 < tMax) {
				sRec.t = x1;
				sRec.p = rIn.GetPointAtParam(sRec.t);
				sRec.normal = (sRec.p - m_Center) / m_dRadius;
				sRec.mat = m_spMaterial;
				return TRUE;
			}
			CCGdouble x2 = (-b + sqrt(dDic)) / a;
			if (tMin < x2 && x2 < tMax) {
				sRec.t = x2;
				sRec.p = rIn.GetPointAtParam(sRec.t);
				sRec.normal = (sRec.p - m_Center) / m_dRadius;
				sRec.mat = m_spMaterial;
				return TRUE;
			}
		}
		return FALSE;
	}

	CCGHitArray::CCGHitArray()
	{
	}

	CCGHitArray::CCGHitArray(shared_ptr<CCGHitObject> spHitObj)
	{
		AddObject(spHitObj);
	}

	CCGHitArray::~CCGHitArray()
	{
	}

	void CCGHitArray::AddObject(shared_ptr<CCGHitObject> spHitObj)
	{
		m_vecHits.push_back(spHitObj);
	}

	void CCGHitArray::ClearArray()
	{
		m_vecHits.clear();
	}

	CCGbool CCGHitArray::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRec) const
	{
		CCGHitRecord sTem;
		CCGdouble dCloseSoFar = tMax;
		CCGbool bIsHit = FALSE;
		for (const auto &obj : m_vecHits) {
			if (obj->Hit(rIn, tMin, dCloseSoFar, sTem)){
				sRec = sTem;
				dCloseSoFar = sRec.t;
				bIsHit = TRUE;
			}
		}
		return bIsHit;
	}
}
