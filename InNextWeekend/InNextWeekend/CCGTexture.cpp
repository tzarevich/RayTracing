#include "CCGTexture.h"


namespace CCG
{

	CCGTexture::CCGTexture()
	{
	}


	CCGTexture::~CCGTexture()
	{
	}

	CCGConsTex::CCGConsTex()
	{
	}

	CCGConsTex::CCGConsTex(CCGVec3 c) : m_color(c)
	{
	}

	CCGConsTex::~CCGConsTex()
	{
	}

	CCGVec3 CCGConsTex::GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const
	{
		return m_color;
	}

	CCGCheckerTex::CCGCheckerTex()
	{
	}

	CCGCheckerTex::CCGCheckerTex(shared_ptr<CCGTexture> pTexE, shared_ptr<CCGTexture> pTexO) :
		m_pEven(pTexE), m_pOdd(pTexO)
	{
	}

	CCGCheckerTex::~CCGCheckerTex()
	{
	}

	CCGVec3 CCGCheckerTex::GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const
	{
		CCGdouble dSines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
		if (dSines < 0) {
			return m_pOdd->GetValue(u, v, p);
		}
		else {
			return m_pEven->GetValue(u, v, p);
		}
	}

	//! \brief ������������

	CCGNoiseTex::CCGNoiseTex()
	{
	}

	CCGNoiseTex::CCGNoiseTex(CCGdouble dScale) : m_dScale(dScale)
	{
	}

	CCGNoiseTex::~CCGNoiseTex()
	{
	}

	CCGVec3 CCGNoiseTex::GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const
	{
		//return CCGVec3(1, 1, 1)*m_noise.Noise(p);
		//�Ŵ�����
		//return CCGVec3(1, 1, 1)*m_noise.Noise(m_dScale * p);

		//������ź���turb����������ʽ

		//return CCGVec3(1, 1, 1)*m_noise.Turb(m_dScale * p);
		//return CCGVec3(1, 1, 1)*0.5*(1 + m_noise.Turb(m_dScale * p));
		
		//�������ŵı���
		return CCGVec3(1, 1, 1)*0.5*(1 + sin(m_dScale*p.z() + 10 * m_noise.Turb(p)));	
	}

	//ͼƬ������

	CCGImageTex::CCGImageTex()
	{
	}

	CCGImageTex::CCGImageTex(CCGuchar *pData, CCGint nWidth, CCGint nHeight) : 
		m_pData(pData), m_nWidth(nWidth), m_nHeight(nHeight)
	{
	}

	CCGImageTex::~CCGImageTex()
	{
		delete m_pData;
	}

	CCGVec3 CCGImageTex::GetValue(CCGdouble u, CCGdouble v, const CCGVec3 &p) const
	{
		CCGint i = CCGint((1 - u)*m_nWidth);
		CCGint j = CCGint((1 - v)*m_nHeight - 0.001);
		if (i < 0) i = 0;
		if (j < 0) j = 0;
		if (i > m_nWidth - 1) i = m_nWidth - 1;
		if (j > m_nHeight - 1) j = m_nHeight - 1;
		CCGdouble dRed = CCGint(m_pData[3 * i + 3 * m_nWidth*j]) / 255.0;
		CCGdouble dGreen = CCGint(m_pData[3 * i + 3 * m_nWidth*j + 1]) / 255.0;
		CCGdouble dBlue = CCGint(m_pData[3 * i + 3 * m_nWidth*j + 2]) / 255.0;
		return CCGVec3(dRed, dGreen, dBlue);
	}
}
