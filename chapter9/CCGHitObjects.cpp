#include "CCGHitObjects.h"


namespace CCG
{
	CCGSphere::CCGSphere(const CCGPoint3D &pCenter, CCGdouble dRadius, shared_ptr<CCGMaterial> pMaterial) : 
		m_pCenter(pCenter), 
		m_dRadius(dRadius),
		m_pMaterial(pMaterial)
	{
	}

	CCGbool CCGSphere::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		CCGVec3 vOc = rIn.GetOrigin() - m_pCenter;
		CCGdouble dA = Dot(rIn.GetDirection(), rIn.GetDirection());
		CCGdouble dB = Dot(rIn.GetDirection(), vOc);
		CCGdouble dC = Dot(vOc, vOc) - m_dRadius*m_dRadius;
		CCGdouble dDiscrmination = dB*dB - dA*dC;
		if (dDiscrmination > 0) {
			CCGdouble temp = (-dB - sqrt(dDiscrmination)) / dA;
			if (tMin < temp && temp < tMax) {
				sRecord.t = temp;
				sRecord.pIntersect = rIn.PointAtParam(sRecord.t);
				sRecord.vNormal = (sRecord.pIntersect - m_pCenter) / m_dRadius;
				sRecord.pMaterial = m_pMaterial;
				return TRUE;
			}

			temp = (-dB + sqrt(dDiscrmination)) / dA;
			if (tMin < temp && temp < tMax) {
				sRecord.t = temp;
				sRecord.pIntersect = rIn.PointAtParam(sRecord.t);
				sRecord.vNormal = (sRecord.pIntersect - m_pCenter) / m_dRadius;
				sRecord.pMaterial = m_pMaterial;
				return TRUE;
			}
		}
		return FALSE;
	}

	CCGHitList::CCGHitList(CCGHitObject **pList, CCGint nSize)
	{
		m_pList = pList;
		m_nListSize = nSize;
	}

	CCGbool CCGHitList::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		CCGHitRecord sTempRec;
		CCGbool bIsHit = FALSE;
		CCGdouble dCloseSoFar = tMax;
		for (CCGint i = 0; i < m_nListSize; ++i) {
			if (m_pList[i]->Hit(rIn, tMin, dCloseSoFar, sTempRec)) {
				sRecord = sTempRec;
				dCloseSoFar = sTempRec.t;
				bIsHit = TRUE;
			}
		}
		return bIsHit;
	}
}
