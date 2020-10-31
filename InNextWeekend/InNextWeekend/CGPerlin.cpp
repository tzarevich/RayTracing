#include "CGPerlin.h"

namespace CCG
{
	CCGVec3 *CCGPerlin::m_pRand = PerlinGenerate();
	CCGint *CCGPerlin::m_pPermX = PerlinGerPerm();
	CCGint *CCGPerlin::m_pPermY = PerlinGerPerm();
	CCGint *CCGPerlin::m_pPermZ = PerlinGerPerm();

	CCGPerlin::CCGPerlin()
	{
	}


	CCGPerlin::~CCGPerlin()
	{
	}

	/*
	CCGdouble CCGPerlin::Noise(const CCGVec3 &p) const
	{
		CCGdouble u = p.x() - floor(p.x());
		CCGdouble v = p.y() - floor(p.y());
		CCGdouble w = p.z() - floor(p.z());
		CCGint i = static_cast<CCGint>(4 * p.x()) & 255;
		CCGint j = static_cast<CCGint>(4 * p.y()) & 255;
		CCGint k = static_cast<CCGint>(4 * p.z()) & 255;
		return m_pRand[m_pPermX[i] ^ m_pPermY[j] ^ m_pPermZ[k]];
	}
	*/

	//CCGdouble CCGPerlin::Noise(const CCGVec3 &p) const
	//{
	//	CCGdouble u = p.x() - floor(p.x());
	//	CCGdouble v = p.y() - floor(p.y());
	//	CCGdouble w = p.z() - floor(p.z());
	//	// hermite cubic
	//	u = u * u * (3-2*u);
	//	v = v * v * (3-2*v);
	//	w = w * w * (3-2*w);
	//	
	//	CCGint i = static_cast<CCGint>(floor(p.x()));
	//	CCGint j = static_cast<CCGint>(floor(p.y()));
	//	CCGint k = static_cast<CCGint>(floor(p.z()));
	//	CCGdouble c[2][2][2];
	//	for (CCGint x = 0; x < 2; ++x) {
	//		for (CCGint y = 0; y < 2; ++y) {
	//			for (CCGint z = 0; z < 2; ++z) {
	//				c[x][y][z] = m_pRand[m_pPermX[(i + x) & 255] ^ m_pPermY[(j + y) & 255] ^ m_pPermZ[(k + z) & 255]];
	//			}
	//		}
	//	}
	//	return TrilinearInterp(c, u, v, w);
	//}

	CCGdouble CCGPerlin::Noise(const CCGVec3 &p) const
	{
		CCGdouble u = p.x() - floor(p.x());
		CCGdouble v = p.y() - floor(p.y());
		CCGdouble w = p.z() - floor(p.z());
		CCGint i = static_cast<CCGint>(floor(p.x()));
		CCGint j = static_cast<CCGint>(floor(p.y()));
		CCGint k = static_cast<CCGint>(floor(p.z()));
		CCGVec3 c[2][2][2];
		for (CCGint x = 0; x < 2; ++x) {
			for (CCGint y = 0; y < 2; ++y) {
				for (CCGint z = 0; z < 2; ++z) {
					c[x][y][z] = m_pRand[m_pPermX[(i + x) & 255] ^ m_pPermY[(j + y) & 255] ^ m_pPermZ[(k + z) & 255]];
				}
			}
		}
		return PerlinInterp(c, u, v, w);
	}

	CCGdouble CCGPerlin::Turb(const CCGVec3 &p, CCGint nDepth) const
	{
		CCGdouble dAccum = 0.0;
		CCGVec3 vTem = p;
		CCGdouble dWeight = 1.0;
		for (CCGint i = 0; i < nDepth; ++i) {
			dAccum += dWeight*Noise(vTem);
			dWeight *= 0.5;
			vTem *= 2;
		}
		return fabs(dAccum);
	}

	void Permute(CCGint *pArray, CCGint nCnt)
	{
		for (CCGint i = nCnt - 1; i > 0; --i) {
			CCGint nTarget = static_cast<CCGint>(Rand()*(i + 1));
			CCGint nTem = pArray[i];
			pArray[i] = pArray[nTarget];
			pArray[nTarget] = nTem;
		}
		return;
	}

	/*CCGdouble *PerlinGenerate()
	{
		CCGdouble *pArray = new CCGdouble[256];
		for (CCGint i = 0; i < 256; ++i) {
			pArray[i] = Rand();
		}
		return pArray;
	}*/

	CCGVec3 *PerlinGenerate()
	{
		CCGVec3 *v = new CCGVec3[256];
		for (CCGint i = 0; i < 256; ++i) {
			v[i] = unit_vector(CCGVec3(-1 + 2 * Rand(), -1 + 2 * Rand(), -1 + 2 * Rand()));
		}
		return v;
	}

	CCGint *PerlinGerPerm()
	{
		CCGint *pArray = new CCGint[256];
		for (CCGint i = 0; i < 256; ++i) {
			pArray[i] = i;
		}
		Permute(pArray, 256);
		return pArray;
	}

	CCGdouble TrilinearInterp(CCGdouble c[2][2][2], CCGdouble u, CCGdouble v, CCGdouble w)
	{
		CCGdouble dAccum = 0.0;
		for (CCGint i = 0; i < 2; ++i) {
			for (CCGint j = 0; j < 2; ++j) {
				for (CCGint k = 0; k < 2; ++k) {
					dAccum += (i*u + (1 - i)*(1 - u)) *
						(j*v + (1 - j)*(1 - v)) *
						(k*w + (1 - k)*(1 - w)) * c[i][j][k];
				}
			}
		}
		return dAccum;
	}

	CCGdouble PerlinInterp(CCGVec3 c[2][2][2], CCGdouble u, CCGdouble v, CCGdouble w)
	{
		CCGdouble uu = u * u * (3 - 2 * u);
		CCGdouble vv = v * v * (3 - 2 * v);
		CCGdouble ww = w * w * (3 - 2 * w);
		CCGdouble dAccum = 0.0;
		for (CCGint i = 0; i < 2; ++i) {
			for (CCGint j = 0; j < 2; ++j) {
				for (CCGint k = 0; k < 2; ++k) {
					CCGVec3 weight(u - i, v - j, w - k);
					dAccum += (i*uu + (1 - i)*(1 - uu)) *
						(j*vv + (1 - j)*(1 - vv)) *
						(k*ww + (1 - k)*(1 - ww)) * Dot(c[i][j][k],  weight);
				}
			}
		}
		return dAccum;
	}
}