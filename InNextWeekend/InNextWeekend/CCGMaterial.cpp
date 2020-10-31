#include "CCGMaterial.h"

namespace CCG
{

	//! \brief 材料基类

	CCGVec3 CCGMaterial::Emitted(CCGdouble u, CCGdouble v, const CCGVec3 &p) const
	{
		return CCGVec3(0, 0, 0);
	}
	
	//! \brief 朗伯特材料

	CCGLambertina::CCGLambertina(shared_ptr<CCGTexture> pAttenuation) : m_pAttenuation(pAttenuation)
	{
	}

	CCGbool CCGLambertina::Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const
	{
		CCGPoint3D pTarget = sRecord.pIntersect + sRecord.vNormal + GetRandPointInUnitSphere();
		rScattered = CCGRay(sRecord.pIntersect, pTarget - sRecord.pIntersect, rIn.GetTime());
		vAttenuation = m_pAttenuation->GetValue(sRecord.u, sRecord.v, sRecord.pIntersect);
		return TRUE;
	}

	//! \brief 金属材料

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

	//! \brief 绝缘材料

	CCGDielectric::CCGDielectric(CCGdouble dRefIdx) : m_dRefIdx(dRefIdx)
	{
	}

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

		if (Rand() < dReflectProb) {
			rScattered = CCGRay(sRecord.pIntersect, vReflected);
		}
		else {
			rScattered = CCGRay(sRecord.pIntersect, vRefracted);
		}
		return TRUE;
	}

	//! \brief 发光材料

	CCGDfsLight::CCGDfsLight()
	{
	}

	CCGDfsLight::CCGDfsLight(shared_ptr<CCGTexture> pTex) : m_pEmit(pTex)
	{
	}

	CCGDfsLight::~CCGDfsLight()
	{
	}

	CCGbool CCGDfsLight::Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const
	{
		return FALSE;
	}

	CCGVec3	CCGDfsLight::Emitted(CCGdouble u, CCGdouble v, const CCGVec3 &p) const
	{
		return m_pEmit->GetValue(u, v, p);
	}

	//! \brief smoke效应专用材料

	CCGIsotropic::CCGIsotropic()
	{
	}

	CCGIsotropic::CCGIsotropic(shared_ptr<CCGTexture> pTex) : m_pTex(pTex)
	{
	}

	CCGIsotropic::~CCGIsotropic()
	{
	}

	CCGbool CCGIsotropic::Scatter(const CCGRay &rIn, CCGHitRecord &sRecord, CCGVec3 &vAttenuation, CCGRay &rScattered) const
	{
		rScattered = CCGRay(sRecord.pIntersect, GetRandPointInUnitSphere());
		vAttenuation = m_pTex->GetValue(sRecord.u, sRecord.v, sRecord.pIntersect);
		return TRUE;
	}


	//! \brief 公用函数

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
		CCGdouble a = (1 - dRefIdx) / (1 + dRefIdx);
		a = a*a;
		return a + (1 - a)*pow((1 - dCos), 5);
	}
}