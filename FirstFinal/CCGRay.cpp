#include "CCGRay.h"

namespace CCG
{

	CCGRay::CCGRay()
	{
	}

	CCGRay::CCGRay(const CCGPoint3D &pO, const CCGVec3 &vDir) : 
		m_pOrigin(pO), m_vDirection(vDir)
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

	CCGPoint3D CCGRay::GetPointAtParam(CCGdouble t) const
	{
		return m_pOrigin + t*m_vDirection;
	}

	CCGRay::~CCGRay()
	{
	}

}