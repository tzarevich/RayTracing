#ifndef CCGVec3_H_INCLUDED
#define CCGVec3_H_INCLUDED
#pragma once

#include <cmath>
#include <iostream>
#include <cstdlib>
#include "CCGDefs.h"

namespace CCG{
	//! \brief �ռ�ά���࣬Ҳ������ʾλ�ü�������
	class CCGVec3
	{
	public:
		//! \brief ���캯��
		CCGVec3();

		//! \brief ��ֵ���캯��
		CCGVec3(CCGdouble e0, CCGdouble e1, CCGdouble e2);

		//! \brief �������캯��
		CCGVec3(const CCGVec3& v);

		//! \brief ��������
		~CCGVec3();

		//! \brief ����x������
		CCGdouble x() const;

		//! \brief ����y������
		CCGdouble y() const;

		//! \brief ����z������
		CCGdouble z() const;

		//! \brief ���غ�ɫ����ֵ
		CCGdouble r() const;

		//! \brief ������ɫ����ֵ
		CCGdouble g() const;

		//! \brief ������ɫ����ֵ
		CCGdouble b() const;

		//! \brief ����+��Ŀ�����
		const CCGVec3& operator+() const;

		//! \brief ����-��Ŀ�����
		CCGVec3 operator-() const;

		//! \brief ����[]�����
		CCGdouble operator[](int i) const { return e[i]; }
		CCGdouble& operator[](int i) { return e[i]; }

		//! \brief ����+=˫Ŀ�����
		CCGVec3& operator+=(const CCGVec3& v);

		//! \brief ����-=˫Ŀ�����
		CCGVec3& operator-=(const CCGVec3& v);

		//! \brief ����*=˫Ŀ�����
		CCGVec3& operator*=(const CCGVec3& v);
		CCGVec3& operator*=(const CCGdouble t);

		//! \brief ����/=˫Ŀ�����
		CCGVec3& operator/=(const CCGVec3& v);
		CCGVec3& operator/=(const CCGdouble t);

		//! \brief ��ȡ��������
		CCGdouble length() const;

		//! \brief ��ȡ�������ȵ�ƽ��
		CCGdouble suqared_length() const;

		//! \brief ת��Ϊ��λ����
		void make_unit_vector();

	public:
		//! \brief ��ά�����x, y, z��Ӧ0, 1, 2
		CCGdouble e[3];
	};

	//! \brief ���������������
	std::istream& operator>>(std::istream &is, CCGVec3 &t);

	//! \brief ��������������
	std::ostream& operator<<(std::ostream &os, CCGVec3 &t);

	//! \brief ����+˫Ŀ������������������
	CCGVec3 operator+(const CCGVec3 &v1, const CCGVec3 &v2);

	//! \brief ����-˫Ŀ������������������
	CCGVec3 operator-(const CCGVec3 &v1, const CCGVec3 &v2);

	//! \brief ����*˫Ŀ������������������
	CCGVec3 operator*(const CCGVec3 &v1, const CCGVec3 &v2);

	//! \brief ����/˫Ŀ������������������
	CCGVec3 operator/(const CCGVec3 &v1, const CCGVec3 &v2);

	//! \brief ����*˫Ŀ�������һ��������һ�������
	CCGVec3 operator*(CCGdouble t, const CCGVec3 &v);
	CCGVec3 operator*(const CCGVec3 &v, CCGdouble t);

	//! \brief ����/˫Ŀ�������һ��������һ�������
	inline CCGVec3 operator/(const CCGVec3 &v, CCGdouble t);

	//! \brief ���������ڻ����
	CCGdouble Dot(const CCGVec3 &v1, const CCGVec3 &v2);

	//! \brief ��������������
	CCGVec3 Corss(const CCGVec3 &v1, const CCGVec3 &v2);

	//! \brief ������λ��
	CCGVec3 unit_vector(CCGVec3 v);
}

#endif