#ifndef CCGVec3_H_INCLUDED
#define CCGVec3_H_INCLUDED
#pragma once

#include <cmath>
#include <iostream>
#include <cstdlib>
#include "CCGDefs.h"

namespace CCG{
	//! \brief 空间维点类，也用作表示位置及向量等
	class CCGVec3
	{
	public:
		//! \brief 构造函数
		CCGVec3();

		//! \brief 赋值构造函数
		CCGVec3(CCGdouble e0, CCGdouble e1, CCGdouble e2);

		//! \brief 拷贝构造函数
		CCGVec3(const CCGVec3& v);

		//! \brief 析构函数
		~CCGVec3();

		//! \brief 返回x轴坐标
		CCGdouble x() const;

		//! \brief 返回y轴坐标
		CCGdouble y() const;

		//! \brief 返回z轴坐标
		CCGdouble z() const;

		//! \brief 返回红色像素值
		CCGdouble r() const;

		//! \brief 返回绿色像素值
		CCGdouble g() const;

		//! \brief 返回蓝色像素值
		CCGdouble b() const;

		//! \brief 重载+单目运算符
		const CCGVec3& operator+() const;

		//! \brief 重载-单目运算符
		CCGVec3 operator-() const;

		//! \brief 重载[]运算符
		CCGdouble operator[](int i) const { return e[i]; }
		CCGdouble& operator[](int i) { return e[i]; }

		//! \brief 重载+=双目运算符
		CCGVec3& operator+=(const CCGVec3& v);

		//! \brief 重载-=双目运算符
		CCGVec3& operator-=(const CCGVec3& v);

		//! \brief 重载*=双目运算符
		CCGVec3& operator*=(const CCGVec3& v);
		CCGVec3& operator*=(const CCGdouble t);

		//! \brief 重载/=双目运算符
		CCGVec3& operator/=(const CCGVec3& v);
		CCGVec3& operator/=(const CCGdouble t);

		//! \brief 获取向量长度
		CCGdouble length() const;

		//! \brief 获取向量长度的平方
		CCGdouble suqared_length() const;

		//! \brief 转换为单位向量
		void make_unit_vector();

	public:
		//! \brief 三维坐标点x, y, z对应0, 1, 2
		CCGdouble e[3];
	};

	//! \brief 重载输入流运算符
	std::istream& operator>>(std::istream &is, CCGVec3 &t);

	//! \brief 重载输出流运算符
	std::ostream& operator<<(std::ostream &os, CCGVec3 &t);

	//! \brief 重载+双目运算符，两个向量相加
	CCGVec3 operator+(const CCGVec3 &v1, const CCGVec3 &v2);

	//! \brief 重载-双目运算符，两个向量相减
	CCGVec3 operator-(const CCGVec3 &v1, const CCGVec3 &v2);

	//! \brief 重载*双目运算符，两个向量相乘
	CCGVec3 operator*(const CCGVec3 &v1, const CCGVec3 &v2);

	//! \brief 重载/双目运算符，两个向量相除
	CCGVec3 operator/(const CCGVec3 &v1, const CCGVec3 &v2);

	//! \brief 重载*双目运算符，一个向量和一个数相乘
	CCGVec3 operator*(CCGdouble t, const CCGVec3 &v);
	CCGVec3 operator*(const CCGVec3 &v, CCGdouble t);

	//! \brief 重载/双目运算符，一个向量和一个数相除
	inline CCGVec3 operator/(const CCGVec3 &v, CCGdouble t);

	//! \brief 两个向量内积点乘
	CCGdouble Dot(const CCGVec3 &v1, const CCGVec3 &v2);

	//! \brief 两个向量外积叉乘
	CCGVec3 Corss(const CCGVec3 &v1, const CCGVec3 &v2);

	//! \brief 向量单位化
	CCGVec3 unit_vector(CCGVec3 v);
}

#endif