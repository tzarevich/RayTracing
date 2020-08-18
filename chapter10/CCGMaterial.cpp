#include "CCGMaterial.h"

namespace CCG
{
	CCGLambertina::CCGLambertina(const CCGVec3 &vAttenuation) : m_vAttenuation(vAttenuation)
	{
	}

	CCGbool CCGLambertina::Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const
	{
		CCGPoint3D pTarget = sRecord.pIntersect + sRecord.vNormal + GetRandPointInUnitSphere();
		rScattered = CCGRay(sRecord.pIntersect, pTarget - sRecord.pIntersect);
		vAttenuation = m_vAttenuation;
		return TRUE;
	}

	CCGMental::CCGMental(const CCGVec3 &vAttenuation, CCGdouble dFuzz) : m_vAttenuation(vAttenuation)
	{
		if (dFuzz < 1.0) {
			m_dFuzz = dFuzz;
		}
		else {
			m_dFuzz = 1.0;
		}
	}

	CCGbool CCGMental::Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const
	{
		CCGVec3 vReflected = Reflect(unit_vector(rIn.GetDirection()), sRecord.vNormal);
		rScattered = CCGRay(sRecord.pIntersect, vReflected + m_dFuzz*GetRandPointInUnitSphere());
		vAttenuation = m_vAttenuation;
		return (Dot(rScattered.GetDirection(), sRecord.vNormal) > 0);
	}

	CCGDielectric::CCGDielectric(CCGdouble dRefIdx) : m_dRefIdx(dRefIdx)
	{
	}

	/*CCGbool CCGDielectric::Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const
	{
		CCGVec3 vOutNormal;
		CCGVec3 vReflected = Reflect(rIn.GetDirection(), sRecord.vNormal);
		CCGdouble dNiOverNt;
		vAttenuation = CCGVec3(1.0, 1.0, 1.0);
		CCGVec3 vRefracted;
		
		if (Dot(rIn.GetDirection(), sRecord.vNormal) > 0) {
			vOutNormal = -sRecord.vNormal;
			dNiOverNt = m_dRefIdx;
		}
		else {
			vOutNormal = sRecord.vNormal;
			dNiOverNt = 1 / m_dRefIdx;
		}

		if (Refract(rIn.GetDirection(), vOutNormal, dNiOverNt, vRefracted)) {
			rScattered = CCGRay(sRecord.pIntersect, vRefracted);
		}
		else {
			rScattered = CCGRay(sRecord.pIntersect, vReflected);
			return FALSE;
		}
		return TRUE;
	}*/

	//使用schlick公式后的散射函数

	CCGbool CCGDielectric::Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const
	{
		CCGVec3 vOutNormal;
		CCGVec3 vReflected = Reflect(rIn.GetDirection(), sRecord.vNormal);
		CCGdouble dNiOverNt;
		vAttenuation = CCGVec3(1.0, 1.0, 1.0);
		CCGVec3 vRefracted;
		CCGdouble dCos;
		CCGdouble dReflectProb;

		if (Dot(rIn.GetDirection(), sRecord.vNormal) > 0) {
			vOutNormal = -sRecord.vNormal;
			dNiOverNt = m_dRefIdx;
			dCos = m_dRefIdx * Dot(rIn.GetDirection(), sRecord.vNormal) / rIn.GetDirection().length();
		}
		else {
			vOutNormal = sRecord.vNormal;
			dNiOverNt = 1 / m_dRefIdx;
			dCos = -Dot(rIn.GetDirection(), sRecord.vNormal) / rIn.GetDirection().length();
		}

		if (Refract(rIn.GetDirection(), vOutNormal, dNiOverNt, vRefracted)) {
			dReflectProb = Schlick(dCos, m_dRefIdx);
		}
		else {
			rScattered = CCGRay(sRecord.pIntersect, vReflected);
			dReflectProb = 1.0;
		}

		if (GetDBRand() < dReflectProb) {
			rScattered = CCGRay(sRecord.pIntersect, vReflected);
		}
		else {
			rScattered = CCGRay(sRecord.pIntersect, vRefracted);
		}
		return TRUE;
	}

	CCGVec3 Reflect(const CCGVec3 &vIn, const CCGVec3 &vNormal)
	{
		return vIn - 2 * Dot(vIn, vNormal)*vNormal;
	}

	CCGbool Refract(const CCGVec3 &vIn, const CCGVec3 &vNormal, CCGdouble dNiOverNt, CCGVec3 &vRefrated)
	{
		CCGVec3 vUnitVec = unit_vector(vIn);
		CCGdouble dt = Dot(vUnitVec, vNormal);
		CCGdouble dDiscrminant = 1.0 - dNiOverNt*dNiOverNt*(1.0 - dt*dt);
		if (dDiscrminant > 0) {
			vRefrated = dNiOverNt*(vUnitVec - vNormal*dt) - vNormal*sqrt(dDiscrminant);
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

	CCGdouble Schlick(CCGdouble dCos, CCGdouble dRefIdx)
	{
		CCGdouble dR0 = (1 - dRefIdx) / (1 + dRefIdx);
		dR0 = dR0*dR0;
		return dR0 + (1 - dR0)*pow((1 - dCos), 5);
	}
}