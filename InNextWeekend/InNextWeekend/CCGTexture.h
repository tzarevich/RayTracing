#ifndef CCGTEXTURE_H
#define CCGTEXTURE_H
#pragma once

#include "Vec3.h"
#include "CGPerlin.h"

namespace CCG
{
	//! \brief 纹理基类
	class CCGTexture
	{
	public:
		//! \brief 构造函数
		CCGTexture();

		//! \brief 析构函数
		virtual ~CCGTexture();

	public:
		//! \brief 获取纹理值虚函数
		virtual CCGVec3 GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const = 0;
	};

	//! \brief 常量纹理
	class CCGConsTex : public CCGTexture
	{
	public:
		//! \brief 构造函数
		CCGConsTex();

		//! \brief 构造函数
		CCGConsTex(CCGVec3 c);
		
		//! \brief 析构函数
		~CCGConsTex();

		//! \brief 获取纹理
		//! \return 返回纹理值
		//! \remark 这里u，v，p不起作用，实际还是由m_color决定
		virtual CCGVec3 GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const override;

	private:
		//! \brief 纹理值
		CCGColor3D m_color;
	};

	//! \brief 测试纹理
	class CCGCheckerTex : public CCGTexture
	{
	public:
		//! \brief 构造函数
		CCGCheckerTex();

		//! \brief 构造函数
		CCGCheckerTex(shared_ptr<CCGTexture> pTexO, shared_ptr<CCGTexture> pTexE);

		//! \brief 析构函数
		~CCGCheckerTex();

		//! \brief 获取纹理
		//! \return 返回纹理值
		//! \remark 这里u，v，p不起作用，实际是由奇偶的纹理值决定
		virtual CCGVec3 GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const override;

	private:
		//! \brief 奇纹理
		shared_ptr<CCGTexture> m_pOdd;

		//! \brief 偶纹理
		shared_ptr<CCGTexture> m_pEven;
	};

	//! \brief 噪声纹理
	class CCGNoiseTex : public CCGTexture
	{
	public:
		//! \brief 构造函数
		CCGNoiseTex();

		//! \brief 构造函数
		CCGNoiseTex(CCGdouble dScale);

		//! \brief 析构函数
		~CCGNoiseTex();

	public:
		//! \brief 获取纹理
		//! \return 返回纹理值
		//! \remark 这里u，v，p不起作用，实际是由随机噪声值决定
		virtual CCGVec3 GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const override;

	public:
		//! \brief 噪声纹理值
		CCGPerlin m_noise;

		//! \brief 比例系数
		CCGdouble m_dScale;
	};

	//! \brief 图片纹理
	class CCGImageTex : public CCGTexture
	{
	public:
		//! \brief 构造函数
		CCGImageTex();

		//! \brief 构造函数
		CCGImageTex(CCGuchar *pData, CCGint nWidth, CCGint nHeight);

		//! \brief 析构函数
		~CCGImageTex();

		//! \brief 获取纹理
		//! \return 返回纹理值
		//! \remark 这里u，v起作用
		virtual CCGVec3 GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const override;
	public:
		//! \brief 读取图片的RGB值
		CCGuchar *m_pData;


		//! \brief 图片的宽高
		CCGint m_nWidth, m_nHeight;
	};
}

#endif

