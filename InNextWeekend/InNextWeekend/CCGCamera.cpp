#include "CCGCamera.h"

namespace CCG
{
	CCGCamera::CCGCamera()
	{
	}

	

	CCGCamera::CCGCamera(CCGPoint3D pLookfrom, CCGPoint3D pLookat, CCGVec3 vVup, CCGdouble dFov, 
		CCGdouble dAspect, CCGdouble dAperture, CCGdouble dFocusDist, CCGdouble dT0, CCGdouble dT1)
	{
		m_t0 = dT0;
		m_t1 = dT1;
		m_dLenRadius = dAperture / 2;
		CCGdouble dTheta = dFov*PI / 180.0;
		CCGdouble dHalfHeight = tan(dTheta / 2);
		CCGdouble dHalfWidth = dAspect * dHalfHeight;

		m_ViewOrigin = pLookfrom;
		m_w = unit_vector(pLookfrom - pLookat);
		m_u = unit_vector(Cross(vVup, m_w));
		m_v = Cross(m_w, m_u);

		m_LeftCorner = m_ViewOrigin - dHalfWidth*dFocusDist*m_u - dHalfHeight*dFocusDist*m_v - dFocusDist*m_w;
		m_Horizontial = 2 * dHalfWidth * dFocusDist * m_u;
		m_Vertical = 2 * dHalfHeight * dFocusDist * m_v;
	}

	CCGRay CCGCamera::GetRay(CCGdouble s, CCGdouble t)
	{
		CCGPoint3D pRd = m_dLenRadius * GetRandPointInUnitCircle();
		CCGVec3 vOffset = m_u * pRd.x() + m_v * pRd.y();
		CCGdouble dTime = m_t0 + Rand()*(m_t1 - m_t0);
		return CCGRay(m_ViewOrigin + vOffset, m_LeftCorner + s*m_Horizontial + t*m_Vertical - m_ViewOrigin - vOffset, dTime);
	}

	CCGPoint3D GetRandPointInUnitCircle()
	{
		CCGPoint3D p;
		do
		{
			p = 2.0*CCGPoint3D(Rand(), Rand(), 0) - CCGPoint3D(1, 1, 0);
		} while (Dot(p, p) >= 1.0);
		return p;
	}

}

