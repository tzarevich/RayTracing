#include "CCGRay.h"
#include "CCGMaterial.h"

namespace CCG
{
	CCGRay::CCGRay()
	{
	}

	CCGRay::CCGRay(const CCGPoint3D &pOrigin, const CCGVec3 &vDirection) : m_pOrigin(pOrigin), m_vDirection(vDirection)
	{
	}

	CCGPoint3D CCGRay::GetOrigin() const
	{
		return m_pOrigin;
	}

	CCGVec3 CCGRay::GetDirection() const
	{
		return m_vDirection;
	}

	CCGVec3 CCGRay::PointAtParam(CCGdouble t) const
	{
		return m_pOrigin + t*m_vDirection;
	}

	/*CCGbool HitSphere(const CCGRay &rIn, CCGPoint3D &pCenter, CCGdouble dRadius)
	{
		CCGVec3 pc = rIn.GetOrigin() - pCenter;
		CCGdouble dA = Dot(rIn.GetDirection(), rIn.GetDirection());
		CCGdouble dB = 2 * Dot(pc, rIn.GetDirection());
		CCGdouble dC = Dot(pc, pc) - dRadius*dRadius;
		CCGdouble dDiscrimination = dB*dB - 4 * dA*dC;
		return (dDiscrimination > 0);
	}*/

	CCGdouble HitSphere(const CCGRay &rIn, CCGPoint3D &pCenter, CCGdouble dRadius)
	{
		CCGVec3 pc = rIn.GetOrigin() - pCenter;
		CCGdouble dA = Dot(rIn.GetDirection(), rIn.GetDirection());
		CCGdouble dB = 2 * Dot(pc, rIn.GetDirection());
		CCGdouble dC = Dot(pc, pc) - dRadius*dRadius;
		CCGdouble dDiscrimination = dB*dB - 4 * dA*dC;
		if (dDiscrimination < 0) {
			return -1.0;
		}
		else {
			return (-dB - sqrt(dDiscrimination)) / (2 * dA);
		}
	}

	CCGdouble GetDBRand()
	{
		return (rand() % RAND) / (1.0*RAND);
	}

	CCGPoint3D GetRandPointInUnitSphere()
	{
		CCGPoint3D pRand;
		do
		{
			pRand = 2.0*CCGPoint3D(GetDBRand(), GetDBRand(), GetDBRand()) - CCGPoint3D(1, 1, 1);
		} while (pRand.suqared_length() > 1);
		return pRand;
	}

	/*CCGColor3D Color(const CCGRay &rIn, CCGHitObject *hList)
	{
		CCGHitRecord sRec;
		if (hList->Hit(rIn, 0.001, CCGDB_MAX, sRec)) {
			CCGPoint3D pTarget = sRec.pIntersect + sRec.vNormal + GetRandPointInUnitSphere();
			return 0.5*Color(CCGRay(sRec.pIntersect, pTarget - sRec.pIntersect), hList);
		}
		CCGVec3 vUnitDir = unit_vector(rIn.GetDirection());
		CCGdouble t = 0.5*(vUnitDir.y() + 1.0);
		return (1.0 - t)*CCGColor3D(1, 1, 1) + t*CCGColor3D(0.5, 0.7, 1.0);
	}*/

	CCGColor3D Color(const CCGRay &rIn, CCGHitObject *hList, CCGint nDepth)
	{
		CCGHitRecord sRec;
		if (hList->Hit(rIn, 0.001, CCGDB_MAX, sRec)) {
			CCGVec3 tempAttenuation;
			CCGRay tempScattered;
			if (nDepth < 50 && sRec.pMaterial->Scatter(rIn, sRec, tempAttenuation, tempScattered)) {
				return tempAttenuation*Color(tempScattered, hList, nDepth + 1);
			} 
			else {
				return CCGColor3D(0, 0, 0);
			}
		}
		CCGVec3 vUnitDir = unit_vector(rIn.GetDirection());
		CCGdouble t = 0.5*(vUnitDir.y() + 1.0);
		return (1.0 - t)*CCGColor3D(1, 1, 1) + t*CCGColor3D(0.5, 0.7, 1.0);
	}
}