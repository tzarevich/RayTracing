#include "CGCamera.h"

namespace CCG
{

	CCGCamera::CCGCamera()
	{
		//ֱ�ӽ��������ж������Ļ��С���ڹ��캯���г�ʼ��

		m_vLeftCorner = CCGVec3(-2.0, -1.0, -1.0);
		m_vHorizontial = CCGVec3(4.0, 0.0, 0.0);
		m_vVertical = CCGVec3(0.0, 2.0, 0.0);
		m_vOrigin = CCGVec3(0.0, 0.0, 0.0);
	}

	CCGRay CCGCamera::GetRay(CCGdouble u, CCGdouble v)
	{
		return CCGRay(m_vOrigin, m_vLeftCorner + u*m_vHorizontial + v*m_vVertical - m_vOrigin);
	}

	CCGCamera::~CCGCamera()
	{
	}

}