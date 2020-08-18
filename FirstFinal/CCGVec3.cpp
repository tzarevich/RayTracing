#include "CCGVec3.h"


namespace CCG{
	CCGVec3::CCGVec3()
	{
	}

	CCGVec3::CCGVec3(CCGdouble e0, CCGdouble e1, CCGdouble e2)
	{
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}

	CCGVec3::CCGVec3(const CCGVec3 &v)
	{
		e[0] = v.e[0];
		e[1] = v.e[1];
		e[2] = v.e[2];
	}

	CCGdouble CCGVec3::x() const
	{
		return e[0];
	}

	CCGdouble CCGVec3::y() const
	{
		return e[1];
	}

	CCGdouble CCGVec3::z() const
	{
		return e[2];
	}

	CCGdouble CCGVec3::r() const
	{
		return e[0];
	}

	CCGdouble CCGVec3::g() const
	{
		return e[1];
	}

	CCGdouble CCGVec3::b() const
	{
		return e[2];
	}

	const CCGVec3& CCGVec3::operator+() const
	{
		return *this;
	}

	CCGVec3 CCGVec3::operator-() const
	{
		return CCGVec3(-e[0], -e[1], -e[2]);
	}

	/*CCGdouble CCGVec3::operator[](int i) const
	{
		return e[i];
	}

	CCGdouble& CCGVec3::operator[](int i)
	{
		return e[i];
	}*/

	CCGVec3& CCGVec3::operator+=(const CCGVec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	CCGVec3& CCGVec3::operator-=(const CCGVec3& v)
	{
		e[0] -= v.e[0];
		e[1] -= v.e[1];
		e[2] -= v.e[2];
		return *this;
	}

	CCGVec3& CCGVec3::operator*=(const CCGVec3& v)
	{
		e[0] *= v.e[0];
		e[1] *= v.e[1];
		e[2] *= v.e[2];
		return *this;
	}

	CCGVec3& CCGVec3::operator/=(const CCGVec3& v)
	{
		e[0] /= v.e[0];
		e[1] /= v.e[1];
		e[2] /= v.e[2];
		return *this;
	}

	CCGVec3& CCGVec3::operator*=(const CCGdouble t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	CCGVec3& CCGVec3::operator/=(const CCGdouble t)
	{
		CCGdouble k = 1.0 / t;
		e[0] *= k;
		e[1] *= k;
		e[2] *= k;
		return *this;
	}

	CCGdouble CCGVec3::GetLength() const
	{
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}

	CCGdouble CCGVec3::GetSuqaredLength() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	void CCGVec3::ToUnitVector()
	{
		CCGdouble k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
		e[0] *= k;
		e[1] *= k;
		e[2] *= k;
	}

	CCGVec3::~CCGVec3()
	{
	}

	std::istream& operator>>(std::istream& is, CCGVec3 &t)
	{
		is >> t.e[0] >> t.e[1] >> t.e[2];
		return is;
	}

	std::ostream& operator<<(std::ostream& os, CCGVec3 &t)
	{
		os << t.e[0] << " " << t.e[1] << " " << t.e[2];
		return os;
	}

	CCGVec3 operator+(const CCGVec3 &v1, const CCGVec3 &v2)
	{
		return CCGVec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
	}

	CCGVec3 operator-(const CCGVec3 &v1, const CCGVec3 &v2)
	{
		return CCGVec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
	}

	CCGVec3 operator*(const CCGVec3 &v1, const CCGVec3 &v2)
	{
		return CCGVec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
	}

	CCGVec3 operator/(const CCGVec3 &v1, const CCGVec3 &v2)
	{
		return CCGVec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
	}

	CCGVec3 operator*(CCGdouble t, const CCGVec3 &v)
	{
		return CCGVec3(t * v.e[0], t * v.e[1], t * v.e[2]);
	}

	CCGVec3 operator*(const CCGVec3 &v, CCGdouble t)
	{
		return CCGVec3(t * v.e[0], t * v.e[1], t * v.e[2]);
	}

	CCGVec3 operator/(const CCGVec3 &v, CCGdouble t)
	{
		return CCGVec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
	}

	CCGdouble Dot(const CCGVec3 &v1, const CCGVec3 &v2)
	{
		return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
	}

	CCGVec3 Cross(const CCGVec3 &v1, const CCGVec3 &v2)
	{
		return CCGVec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
			(v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2]),
			(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
	}

	CCGVec3 UnitVector(CCGVec3 v)
	{
		return v / v.GetLength();
	}

	CCGVec3  CCGVec3::GetRandVector()
	{
		CCGdouble x = RandomZeroToOne();
		CCGdouble y = RandomZeroToOne();
		CCGdouble z = RandomZeroToOne();
		return CCGVec3(x, y, z);
	}
}