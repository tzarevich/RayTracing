#include "CCGHitObjects.h"
#include "CCGMaterial.h"
#include "Vec3.h"

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

	/*CCGHitList::CCGHitList(CCGHitObject **pList, CCGint nSize)
	{
		m_pList = pList;
		m_nListSize = nSize;
	}*/

	CCGHitList::CCGHitList()
	{

	}

	CCGHitList::CCGHitList(shared_ptr<CCGHitObject> object)
	{
		AddObject(object);
	}

	void CCGHitList::ClearList()
	{
		m_Object.clear();
	}

	void CCGHitList::AddObject(shared_ptr<CCGHitObject> object)
	{
		m_Object.push_back(object);
	}

	CCGbool CCGHitList::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		CCGHitRecord sTempRec;
		CCGbool bIsHit = FALSE;
		CCGdouble dCloseSoFar = tMax;
		for (const auto& obj : m_Object) {
			if (obj->Hit(rIn, tMin, dCloseSoFar, sTempRec)) {
				sRecord = sTempRec;
				dCloseSoFar = sTempRec.t;
				bIsHit = TRUE;
			}
		}
		return bIsHit;
	}

	CCGHitList RandomScene()
	{
		CCGHitList world;
		auto lGroundMaterial = make_shared<CCGLambertina>(CCGColor3D(0.5, 0.5, 0.5));
		world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, -1000, 0), 1000, lGroundMaterial));
		for (CCGint a = -4; a < 4; ++a) {
			for (CCGint b = -4; b < 4; ++b) {
				CCGdouble dChooseMat = GetDBRand();
				CCGPoint3D pCenter(a + 0.9*GetDBRand(), 0.2, b + 0.9*GetDBRand());
				if ((pCenter - CCGPoint3D(4, 0.2, 0)).length() > 0.9) {
					shared_ptr<CCGMaterial> pSphereMat;

					if (dChooseMat < 0.8) {	//Lambertina
						CCGVec3 vAttenuation = CCGVec3::RandVec() * CCGVec3::RandVec();
						pSphereMat =  make_shared<CCGLambertina>(vAttenuation);
						world.AddObject(make_shared<CCGSphere>(pCenter, 0.2, pSphereMat));
					}
					else if (dChooseMat < 0.95) { //mental
						CCGVec3 vAttenuation = CCGVec3(0.5*(1 + GetDBRand()), 0.5*(1 + GetDBRand()), 0.5*GetDBRand());
						CCGdouble r = GetDBRand();
						auto fuzz = r > 0.5 ? r - 0.5 : r;
						pSphereMat = make_shared<CCGMental>(vAttenuation, fuzz);
						world.AddObject(make_shared<CCGSphere>(pCenter, 0.2, pSphereMat));
					}
					else {	//dielectric
						pSphereMat = make_shared<CCGDielectric>(1.5);
						world.AddObject(make_shared<CCGSphere>(pCenter, 0.2, pSphereMat));
					}
				}
			}
		}

		auto m1 = make_shared<CCGDielectric>(1.5);
		world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, 1, 0), 1.0, m1));

		auto m2 = make_shared<CCGLambertina>(CCGVec3(0.4, 0.2, 0.1));
		world.AddObject(make_shared<CCGSphere>(CCGPoint3D(-4, 1, 0), 1.0, m2));

		auto m3 = make_shared<CCGMental>(CCGVec3(0.7, 0.6, 0.5), 0);
		world.AddObject(make_shared<CCGSphere>(CCGPoint3D(4, 1, 0), 1.0, m3));
		return world;
	}
}
