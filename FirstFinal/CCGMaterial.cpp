#include "CCGMaterial.h"
#include "CCGHitObject.h"
#include "CCGRay.h"

namespace CCG
{

	CCGMaterial::CCGMaterial()
	{
	}


	CCGMaterial::~CCGMaterial()
	{
	}

	CCGLambertian::CCGLambertian()
	{
	}

	CCGLambertian::CCGLambertian(const CCGVec3 &vAut) : m_Attenuation(vAut)
	{
	}

	CCGLambertian::~CCGLambertian()
	{
	}

	CCGbool CCGLambertian::Scatter(const CCGRay &rIn, CCGHitRecord &sRec, CCGVec3 &vAut, CCGRay &rScattered) const
	{
		CCGPoint3D target = sRec.p + sRec.normal + GetRandomPointInUnitSphere();
		vAut = m_Attenuation;
		rScattered = CCGRay(sRec.p, target - sRec.p);
		return TRUE;
	}

	CCGMental::CCGMental()
	{
	}

	CCGMental::CCGMental(const CCGVec3 &vAut, CCGdouble dFuzz) : m_vAttenuation(vAut), m_dFuzz(dFuzz < 1.0 ? dFuzz : 1.0)
	{
	}

	CCGMental::~CCGMental()
	{
	}

	CCGbool CCGMental::Scatter(const CCGRay &rIn, CCGHitRecord &sRec, CCGVec3 &vAut, CCGRay &rScattered) const
	{
		CCGVec3 vReflected = Reflect(UnitVector(rIn.GetDirection()), sRec.normal);
		rScattered = CCGRay(sRec.p, vReflected + m_dFuzz*GetRandomPointInUnitSphere());
		vAut = m_vAttenuation;
		return (Dot(rScattered.GetDirection(), sRec.normal) > 0);
	}

	CCGDielectric::CCGDielectric()
	{
	}

	CCGDielectric::CCGDielectric(CCGdouble dRefIdx) : m_dRefIdx(dRefIdx)
	{
	}

	CCGDielectric::~CCGDielectric()
	{
	}

	CCGbool CCGDielectric::Scatter(const CCGRay &rIn, CCGHitRecord &sRec, CCGVec3 &vAut, CCGRay &rScattered) const
	{
		CCGVec3 vOutNormal;
		CCGdouble dRef;
		vAut = CCGVec3(1.0, 1.0, 1.0);
		CCGdouble dCos;
		CCGdouble dProb;
		CCGVec3 vReflected = Reflect(rIn.GetDirection(), sRec.normal);
		CCGVec3 vRefracted;

		if (Dot(rIn.GetDirection(), sRec.normal) > 0) {
			vOutNormal = -sRec.normal;
			dRef = m_dRefIdx;
			dCos = m_dRefIdx * Dot(rIn.GetDirection(), sRec.normal) / rIn.GetDirection().GetLength();
		}
		else {
			vOutNormal = sRec.normal;
			dRef = 1 / m_dRefIdx;
			dCos = -Dot(rIn.GetDirection(), sRec.normal) / rIn.GetDirection().GetLength();
		}

		if (Refract(rIn.GetDirection(), vOutNormal, dRef, vRefracted)) {
			dProb = Schlick(dCos, m_dRefIdx);
		}
		else {
			rScattered = CCGRay(sRec.p, vReflected);
			dProb = 1.0;
		}

		if (RandomZeroToOne() < dProb) {
			rScattered = CCGRay(sRec.p, vReflected);
		}
		else {
			rScattered = CCGRay(sRec.p, vRefracted);
		}
		return TRUE;
	}

	CCGPoint3D GetRandomPointInUnitSphere()
	{
		CCGPoint3D p;
		do
		{
			p = 2.0*CCGPoint3D(RandomZeroToOne(), RandomZeroToOne(), RandomZeroToOne()) - CCGPoint3D(1, 1, 1);
		} while (p.GetSuqaredLength() > 1.0);
		return p;
	}

	CCGVec3 Reflect(const CCGVec3 &vIn, const CCGVec3 &vNormal)
	{
		return vIn - 2 * Dot(vIn, vNormal)*vNormal;
	}

	CCGbool Refract(const CCGVec3 &vIn, const CCGVec3 &vNormal, CCGdouble dRef, CCGVec3 &vRefracted)
	{
		CCGVec3 uv = UnitVector(vIn);
		CCGdouble dt = Dot(uv, vNormal);
		CCGdouble dis = 1 - dRef*dRef*(1.0 - dt*dt);
		if (dis > 0) {
			vRefracted = dRef*(uv - vNormal*dt) - vNormal*sqrt(dis);
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

	CCGdouble Schlick(CCGdouble dCos, CCGdouble dRefIdx)
	{
		CCGdouble a = (1 - dRefIdx) / (1 + dRefIdx);
		a = a*a;
		return a + (1 - a)*pow((1 - dCos), 5);
	}
}
