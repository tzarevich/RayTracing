#include "CCGaabb.h"
#include "CCGRay.h"
#include <algorithm>
using namespace std;

namespace CCG
{
	CCGaabb::CCGaabb()
	{
	}

	CCGaabb::CCGaabb(const CCGVec3 &a, const CCGVec3 &b)
	{
		m_min = a;
		m_max = b;
	}

	CCGaabb::~CCGaabb()
	{
	}

	CCGVec3 CCGaabb::GetMin() const
	{
		return m_min;
	}

	CCGVec3 CCGaabb::GetMax() const
	{
		return m_max;
	}

	CCGbool CCGaabb::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax) const
	{
		for (int i = 0; i < 3; ++i) {
			CCGdouble dInvD = 1.0 / rIn.GetDirection()[i];
			CCGdouble dParamT0 = (m_min[i] - rIn.GetOrigin()[i]) * dInvD;
			CCGdouble dParamT1 = (m_max[i] - rIn.GetOrigin()[i]) * dInvD;

			if (dInvD < 0.0) {
				std::swap(dParamT0, dParamT1);
			}
			tMin = dParamT0 > tMin ? dParamT0 : tMin;
			tMax = dParamT1 < tMax ? dParamT1 : tMax;
			if (tMax <= tMin) {
				return FALSE;
			}
		}
		return TRUE;
	}

	CCGaabb SurroundingBox(CCGaabb box0, CCGaabb box1)
	{
		CCGVec3 small( min(box0.GetMin().x(), box1.GetMin().x()), 
			min(box0.GetMin().y(), box1.GetMin().y()), 
			min(box0.GetMin().z(), box1.GetMin().z()) );

		CCGVec3 big(max(box0.GetMax().x(), box1.GetMax().x()),
			max(box0.GetMax().y(), box1.GetMax().y()),
			max(box0.GetMax().z(), box1.GetMax().z()));
		return CCGaabb(small, big);
	}
}
