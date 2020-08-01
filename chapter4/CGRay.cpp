#include "CGRay.h"

namespace CCG
{

	CCGRay::CCGRay()
	{
	}

	CCGRay::CCGRay(const CCGVec3 &a, const CCGVec3 &b)
	{
		A = a;
		B = b;
	}

	CCGVec3 CCGRay::Origin() const
	{
		return A;
	}

	CCGVec3 CCGRay::Direction() const
	{
		return B;
	}

	CCGVec3 CCGRay::PointAtParam(CCGdouble t) const
	{
		return A + t*B;
	}

	CCGRay::~CCGRay()
	{
	}

	/*CCGVec3 color(const CCGRay &r)
	{
		CCGVec3 unitDirection = unit_vector(r.Direction());
		CCGdouble t = 0.5 * (unitDirection.y() + 1.0);
		return (1.0 - t)*CCGVec3(1.0, 1.0, 1.0) + t*CCGVec3(0.5, 0.7, 1.0);
	}*/

	CCGbool HitSphere(const CCGVec3 &center, CCGdouble radius, const CCGRay &r)
	{
		//根据公式：t*t*dot(B, B) + 2*t*dot(B, A-C) + dot(A-C, A-C) - R*R = 0

		CCGVec3 pc = r.Origin() - center;
		CCGdouble a = Dot(r.Direction(), r.Direction());
		CCGdouble b = 2 * Dot(r.Direction(), pc);
		CCGdouble c = Dot(pc, pc) - radius * radius;
		CCGdouble discrimination = b*b - 4*a*c;
		return (discrimination > 0);
	}

	CCGVec3 Color(const CCGRay &r)
	{
		if (HitSphere(CCGVec3(0.0, 0.0, -1.0), 0.5, r)) {
			return CCGVec3(1.0, 0.0, 0.0);
		}
		CCGVec3 unitDirection = unit_vector(r.Direction());
		CCGdouble t = 0.5 * (unitDirection.y() + 1.0);
		return (1.0 - t)*CCGVec3(1.0, 1.0, 1.0) + t*CCGVec3(0.5, 0.7, 1.0);
	}
}
