#include "CGRay.h"
#include "hitable.h"

namespace CCG
{
	class CCGHitable;
	class CCGSphere;
	class CCGHitableList;
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
	}

	CCGbool HitSphere(const CCGVec3 &center, CCGdouble radius, const CCGRay &r)
	{
		//���ݹ�ʽ��t*t*dot(B, B) + 2*t*dot(B, A-C) + dot(A-C, A-C) - R*R = 0

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
	}*/

	//���ݱ��������������������

	CCGdouble HitSphere(const CCGVec3 &center, CCGdouble radius, const CCGRay &r)
	{
		//���ݹ�ʽ��t*t*dot(B, B) + 2*t*dot(B, A-C) + dot(A-C, A-C) - R*R = 0

		CCGVec3 pc = r.Origin() - center;
		CCGdouble a = Dot(r.Direction(), r.Direction());
		CCGdouble b = 2 * Dot(r.Direction(), pc);
		CCGdouble c = Dot(pc, pc) - radius * radius;
		CCGdouble discrimination = b*b - 4 * a*c;
		if (discrimination < 0) {
			return -1.0;
		}
		else {
			return (-b - sqrt(discrimination)) / (2.0 * a);
		}
	}

	//CCGVec3 Color(const CCGRay &r)
	//{
	//	CCGdouble t = HitSphere(CCGVec3(0.0, 0.0, -1.0), 0.5, r);
	//	if (t > 0) {
	//		//���㵥λ���ߣ�������ֵ��ΧΪ(-1, 1)
	//		CCGVec3 N = unit_vector(r.PointAtParam(t) - CCGVec3(0, 0, -1));
	//		//ת��Ϊ(0, 1)������
	//		return 0.5*CCGVec3(N.x() + 1, N.y() + 1, N.z() + 1);
	//	}
	//	CCGVec3 unitDirection = unit_vector(r.Direction());
	//	t = 0.5 * (unitDirection.y() + 1.0);
	//	return (1.0 - t)*CCGVec3(1.0, 1.0, 1.0) + t*CCGVec3(0.5, 0.7, 1.0);
	//}

	//! \brief ��ӵ��µĿ�ײ�������࣬����Color����
	//! \param rΪ����
	//! \param worldΪ��ײ�����壬���ݴ����������;���������
	//! \return ���ط�����������ͶӰ����ɫ��

	CCGdouble GetRand() {
		return static_cast<CCGdouble>((rand() % RAND)) / static_cast<CCGdouble>(RAND);
	}
	
	CCGVec3 Color(const CCGRay &r, CCGHitable *world)
	{
		CCGHitRecord rec;
		if (world->Hit(r, 0.0, CCGDB_MAX, rec)) {
			return 0.5*CCGVec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
		}
		else {
			CCGVec3 vUintDir = unit_vector(r.Direction());
			CCGdouble t = 0.5*(vUintDir.y() + 1);
			return (1 - t)*CCGVec3(1.0, 1.0, 1.0) + t*CCGVec3(0.5, 0.7, 1.0);
		}
	}
}
