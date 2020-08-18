#ifndef CCGCAMERA_H
#define CCGCAMERA_H
#pragma once

#include "CGRay.h"

namespace CCG
{
	class CCGRay;

	//! \brief �����
	class CCGCamera
	{
	public:
		//! \brief ���캯��
		CCGCamera();

		//! \brief ͨ�������ͬ���ӵ��ȡ��Ӧ�Ĺ���
		//! \param u,v�ֱ�Ϊˮƽ�ʹ�ֱƫ����
		//! \return ������Ļ���ӵ�������γɵĹ���
		CCGRay GetRay(CCGdouble u, CCGdouble v);

		//! \brief ��������
		~CCGCamera();

	private:
		//! \brief ������ĵ�
		CCGVec3 m_vOrigin;

		//! \brief ��Ļ���½ǵ�
		CCGVec3 m_vLeftCorner;

		//! \brief ��Ļˮƽ���������ڽ���Ļ�ϵ��ӵ�����
		CCGVec3 m_vHorizontial;

		//! \brief ��Ļ��ֱ���������ڽ���Ļ�ϵ��ӵ�����
		CCGVec3 m_vVertical;
	};

}
#endif