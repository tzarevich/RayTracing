#include "CCGCamera.h"

namespace CCG
{

	CCGCamera::CCGCamera()
	{
		m_pViewOrigin = CCGPoint3D(0, 0, 0);
		m_pLeftCorner = CCGPoint3D(-2, -1, -1);
		m_vHorizontial = CCGVec3(4, 0, 0);
		m_vVertical = CCGVec3(0, 2, 0);
	}

	/*CCGCamera::CCGCamera(CCGPoint3D pLookfrom, CCGPoint3D pLookat, CCGVec3 vVup, CCGdouble dFov, CCGdouble dAspect)
	{
		CCGVec3 u, v, w;
		CCGdouble dTheta = dFov*PI / 180.0;
		CCGdouble dHalfHeight = tan(dTheta/2);
		CCGdouble dHalfWidth = dAspect * dHalfHeight;
		m_pViewOrigin = pLookfrom;
		w = unit_vector(pLookfrom - pLookat);
		u = unit_vector(Cross(vVup, w));
		v = Cross(w, u);
		m_pLeftCorner = m_pViewOrigin - dHalfWidth*u - dHalfHeight*v - w;
		m_vHorizontial = 2*dHalfWidth*u;
		m_vVertical = 2*dHalfHeight*v;
	}*/

	CCGPoint3D GetRandPointInUnitCircle()
	{
		CCGPoint3D pRand;
		do
		{
			pRand = 2.0*CCGPoint3D(GetDBRand(), GetDBRand(), 0) - CCGPoint3D(1, 1, 0);
		} while (Dot(pRand, pRand) >= 1.0);
		return pRand;
	}

	CCGCamera::CCGCamera(CCGPoint3D pLookfrom, CCGPoint3D pLookat, CCGVec3 vVup, CCGdouble dFov, CCGdouble dAspect, CCGdouble dAperture, CCGdouble dFocusDist)
	{
		m_dLenRadius = dAperture / 2;
		CCGdouble dTheta = dFov*PI / 180.0;
		CCGdouble dHalfHeight = tan(dTheta / 2);
		CCGdouble dHalfWidth = dAspect * dHalfHeight;
		m_pViewOrigin = pLookfrom;
		m_w = unit_vector(pLookfrom - pLookat);
		m_u = unit_vector(Cross(vVup, m_w));
		m_v = Cross(m_w, m_u);
		m_pLeftCorner = m_pViewOrigin - dHalfWidth*dFocusDist*m_u - dHalfHeight*dFocusDist*m_v - dFocusDist*m_w;
		m_vHorizontial = 2 * dHalfWidth * dFocusDist * m_u;
		m_vVertical = 2 * dHalfHeight * dFocusDist * m_v;
	}

	CCGRay CCGCamera::GetRay(CCGdouble s, CCGdouble t)
	{
		CCGPoint3D pRd = m_dLenRadius * GetRandPointInUnitCircle();
		CCGVec3 vOffset = m_u * pRd.x() + m_v * pRd.y();
		return CCGRay(m_pViewOrigin + vOffset, m_pLeftCorner + s*m_vHorizontial + t*m_vVertical - m_pViewOrigin - vOffset);
	}

	/*CCGRay CCGCamera::GetRay(CCGdouble s, CCGdouble t)
	{
		return CCGRay(m_pViewOrigin, m_pLeftCorner + s*m_vHorizontial + t*m_vVertical - m_pViewOrigin);
	}*/

}

