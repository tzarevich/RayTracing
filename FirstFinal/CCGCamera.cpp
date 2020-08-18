#include "CCGCamera.h"
#include "CCGRay.h"

namespace CCG
{

	CCGCamera::CCGCamera()
	{
	}

	CCGCamera::CCGCamera(CCGPoint3D &pLookfrom, CCGPoint3D &pLookat, CCGVec3 &vVup, CCGdouble dVof, CCGdouble dAspect, CCGdouble dAperture, CCGdouble dFocusDis)
	{
		m_dLensRadius = dAperture / 2.0;
		CCGdouble dTheta = DegreesToRadians(dVof);
		CCGdouble dHalfHeight = tan(dTheta / 2);
		CCGdouble dHalfWidth = dAspect * dHalfHeight;

		m_ViewOrigin = pLookfrom;
		m_w = UnitVector(pLookfrom - pLookat);
		m_u = UnitVector(Cross(vVup, m_w));
		m_v = Cross(m_w, m_u);

		m_LeftCorner = m_ViewOrigin - m_u*dFocusDis*dHalfWidth - m_v*dFocusDis*dHalfHeight - dFocusDis*m_w;
		m_Horizontial = 2.0*dHalfWidth*dFocusDis*m_u;
		m_Vertical = 2.0*dHalfHeight*dFocusDis*m_v;
	}

	CCGCamera::~CCGCamera()
	{
	}

	CCGRay CCGCamera::GetRay(CCGdouble s, CCGdouble t)
	{
		CCGPoint3D p = m_dLensRadius * GetRandomPointInUnitCircle();
		CCGVec3 vOffset = m_u*p.x() + m_v*p.y();
		return CCGRay(m_ViewOrigin + vOffset, m_LeftCorner + s*m_Horizontial + t*m_Vertical - m_ViewOrigin - vOffset);
	}

	CCGPoint3D GetRandomPointInUnitCircle()
	{
		CCGPoint3D p;
		do
		{
			p = 2.0 * CCGPoint3D(RandomZeroToOne(), RandomZeroToOne(), 0) - CCGPoint3D(1, 1, 0);
		} while (Dot(p, p) >= 1.0);
		return p;
	}
}
