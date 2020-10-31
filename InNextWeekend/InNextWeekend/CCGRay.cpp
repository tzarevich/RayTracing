#include "CCGRay.h"
#include "CCGMaterial.h"
#include "CCGDefs.h"

namespace CCG
{
	CCGRay::CCGRay()
	{
	}

	CCGRay::CCGRay(const CCGPoint3D &pOrigin, const CCGVec3 &vDirection, CCGdouble dTime) : 
		m_pOrigin(pOrigin), m_vDirection(vDirection), m_time(dTime)
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

	CCGdouble CCGRay::GetTime() const
	{
		return m_time;
	}

	CCGVec3 CCGRay::PointAtParam(CCGdouble t) const
	{
		return m_pOrigin + t*m_vDirection;
	}


	CCGPoint3D GetRandPointInUnitSphere()
	{
		CCGPoint3D p;
		do
		{
			p = 2.0*CCGPoint3D(Rand(), Rand(), Rand()) - CCGPoint3D(1, 1, 1);
		} while (p.suqared_length() > 1);
		return p;
	}
}