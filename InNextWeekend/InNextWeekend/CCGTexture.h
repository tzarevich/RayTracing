#ifndef CCGTEXTURE_H
#define CCGTEXTURE_H
#pragma once

#include "Vec3.h"
#include "CGPerlin.h"

namespace CCG
{
	//! \brief �������
	class CCGTexture
	{
	public:
		//! \brief ���캯��
		CCGTexture();

		//! \brief ��������
		virtual ~CCGTexture();

	public:
		//! \brief ��ȡ����ֵ�麯��
		virtual CCGVec3 GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const = 0;
	};

	//! \brief ��������
	class CCGConsTex : public CCGTexture
	{
	public:
		//! \brief ���캯��
		CCGConsTex();

		//! \brief ���캯��
		CCGConsTex(CCGVec3 c);
		
		//! \brief ��������
		~CCGConsTex();

		//! \brief ��ȡ����
		//! \return ��������ֵ
		//! \remark ����u��v��p�������ã�ʵ�ʻ�����m_color����
		virtual CCGVec3 GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const override;

	private:
		//! \brief ����ֵ
		CCGColor3D m_color;
	};

	//! \brief ��������
	class CCGCheckerTex : public CCGTexture
	{
	public:
		//! \brief ���캯��
		CCGCheckerTex();

		//! \brief ���캯��
		CCGCheckerTex(shared_ptr<CCGTexture> pTexO, shared_ptr<CCGTexture> pTexE);

		//! \brief ��������
		~CCGCheckerTex();

		//! \brief ��ȡ����
		//! \return ��������ֵ
		//! \remark ����u��v��p�������ã�ʵ��������ż������ֵ����
		virtual CCGVec3 GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const override;

	private:
		//! \brief ������
		shared_ptr<CCGTexture> m_pOdd;

		//! \brief ż����
		shared_ptr<CCGTexture> m_pEven;
	};

	//! \brief ��������
	class CCGNoiseTex : public CCGTexture
	{
	public:
		//! \brief ���캯��
		CCGNoiseTex();

		//! \brief ���캯��
		CCGNoiseTex(CCGdouble dScale);

		//! \brief ��������
		~CCGNoiseTex();

	public:
		//! \brief ��ȡ����
		//! \return ��������ֵ
		//! \remark ����u��v��p�������ã�ʵ�������������ֵ����
		virtual CCGVec3 GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const override;

	public:
		//! \brief ��������ֵ
		CCGPerlin m_noise;

		//! \brief ����ϵ��
		CCGdouble m_dScale;
	};

	//! \brief ͼƬ����
	class CCGImageTex : public CCGTexture
	{
	public:
		//! \brief ���캯��
		CCGImageTex();

		//! \brief ���캯��
		CCGImageTex(CCGuchar *pData, CCGint nWidth, CCGint nHeight);

		//! \brief ��������
		~CCGImageTex();

		//! \brief ��ȡ����
		//! \return ��������ֵ
		//! \remark ����u��v������
		virtual CCGVec3 GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const override;
	public:
		//! \brief ��ȡͼƬ��RGBֵ
		CCGuchar *m_pData;


		//! \brief ͼƬ�Ŀ��
		CCGint m_nWidth, m_nHeight;
	};
}

#endif

