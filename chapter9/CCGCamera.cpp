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

	CCGRay CCGCamera::GetRay(CCGdouble u, CCGdouble v)
	{
		return CCGRay(m_pViewOrigin, m_pLeftCorner + u*m_vHorizontial + v*m_vVertical - m_pViewOrigin);
	}

}

