#include "hitable.h"

namespace CCG
{
	CCGSphere::CCGSphere()
	{

	}

	CCGSphere::CCGSphere(CCGVec3 cen, CCGdouble r, shared_ptr<CCGMaterial> m) : center(cen), radius(r), m_pMat(m)
	{
		
	}

	CCGbool CCGSphere::Hit(const CCGRay &r, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &rec) const
	{
		CCGVec3 pc = r.Origin() - center;
		CCGdouble a = Dot(r.Direction(), r.Direction());
		CCGdouble b = Dot(pc, r.Direction());
		CCGdouble c = Dot(pc, pc) - radius*radius;
		CCGdouble discrimination = b*b - a*c;
		if (discrimination > 0) {
			CCGdouble temp = (-b - sqrt(discrimination)) / a;
			if (tMin < temp && temp < tMax){
				rec.t = temp;
				rec.p = r.PointAtParam(rec.t);
				rec.normal = (rec.p - center) / radius;
				rec.matPtr = m_pMat;
				return TRUE;
			}
			temp = (-b + sqrt(discrimination)) / a;
			if (tMin < temp && temp < tMax){
				rec.t = temp;
				rec.p = r.PointAtParam(rec.t);
				rec.normal = (rec.p - center) / radius;
				rec.matPtr = m_pMat;
				return TRUE;
			}
		}
		return FALSE;
	}

	CCGSphere::~CCGSphere()
	{

	}

	CCGHitableList::CCGHitableList()
	{
	}

	CCGHitableList::CCGHitableList(CCGHitable **l, CCGint n)
	{
		m_pList = l;
		m_nListSize = n;
	}

	CCGbool CCGHitableList::Hit(const CCGRay &r, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &rec) const
	{
		CCGHitRecord sTempRec;
		CCGbool bIsHit = FALSE;
		CCGdouble dClosestSoFar = tMax;

		for (CCGint i = 0; i < m_nListSize; ++i) {
			if (m_pList[i]->Hit(r, tMin, dClosestSoFar, sTempRec)) {
				bIsHit = TRUE;
				dClosestSoFar = sTempRec.t;
				rec = sTempRec;
			}
		}
		return bIsHit;
	}

	CCGHitableList::~CCGHitableList()
	{
	}
}

