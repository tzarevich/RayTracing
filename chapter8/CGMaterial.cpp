#include "CGMaterial.h"

namespace CCG
{
	CCGLambertian::CCGLambertian(const CCGVec3 &v) : m_vAlbedo(v)
	{
	}

	CCGbool CCGLambertian::Scatter(const CCGRay &RayIn, const CCGHitRecord &sRec, CCGVec3 &vAttenuation, CCGRay &RayScattered) const
	{
		CCGVec3 vTarget = sRec.p + sRec.normal + RandomInUnitSphere();
		RayScattered = CCGRay(sRec.p, vTarget - sRec.p);
		vAttenuation = m_vAlbedo;
		return TRUE;
	}

	CCGMental::CCGMental(const CCGVec3 &v, CCGdouble f) : m_vAlbedo(v)
	{
		if (f < 1) {
			m_dFuzz = f;
		}
		else {
			m_dFuzz = 1;
		}
	}

	CCGbool CCGMental::Scatter(const CCGRay &RayIn, const CCGHitRecord &sRec, CCGVec3 &vAttenuation, CCGRay &RayScattered) const
	{
		CCGVec3 vReflected = Reflect(unit_vector(RayIn.Direction()), sRec.normal);
		//RayScattered = CCGRay(sRec.p, vReflected);
		RayScattered = CCGRay(sRec.p, vReflected + m_dFuzz*RandomInUnitSphere());
		vAttenuation = m_vAlbedo;
		return (Dot(RayScattered.Direction(), sRec.normal) > 0);
	}

	CCGVec3 Reflect(const CCGVec3 &v, const CCGVec3 &n)
	{
		return v - 2*Dot(v, n)*n;
	}
}
