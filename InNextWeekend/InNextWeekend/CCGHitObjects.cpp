#include "CCGHitObjects.h"
#include "CCGMaterial.h"
#include "Vec3.h"
#include "CCGaabb.h"
#include "CCGTexture.h"
#include <algorithm>

namespace CCG
{
	//! \brief 球体

	CCGSphere::CCGSphere(const CCGPoint3D &pCenter, CCGdouble dRadius, shared_ptr<CCGMaterial> pMaterial) : 
		m_pCenter(pCenter), 
		m_dRadius(dRadius),
		m_pMaterial(pMaterial)
	{
	}

	CCGbool CCGSphere::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		CCGVec3 vOc = rIn.GetOrigin() - m_pCenter;
		CCGdouble dA = Dot(rIn.GetDirection(), rIn.GetDirection());
		CCGdouble dB = Dot(rIn.GetDirection(), vOc);
		CCGdouble dC = Dot(vOc, vOc) - m_dRadius*m_dRadius;
		CCGdouble dDiscrmination = dB*dB - dA*dC;
		if (dDiscrmination > 0) {
			CCGdouble temp = (-dB - sqrt(dDiscrmination)) / dA;
			if (tMin < temp && temp < tMax) {
				sRecord.t = temp;
				sRecord.pIntersect = rIn.PointAtParam(sRecord.t);
				sRecord.vNormal = (sRecord.pIntersect - m_pCenter) / m_dRadius;
				sRecord.pMaterial = m_pMaterial;
				GetSphereUV((sRecord.pIntersect - m_pCenter) / m_dRadius, sRecord.u, sRecord.v);
				return TRUE;
			}

			temp = (-dB + sqrt(dDiscrmination)) / dA;
			if (tMin < temp && temp < tMax) {
				sRecord.t = temp;
				sRecord.pIntersect = rIn.PointAtParam(sRecord.t);
				sRecord.vNormal = (sRecord.pIntersect - m_pCenter) / m_dRadius;
				sRecord.pMaterial = m_pMaterial;
				GetSphereUV((sRecord.pIntersect - m_pCenter) / m_dRadius, sRecord.u, sRecord.v);
				return TRUE;
			}
		}
		return FALSE;
	}

	CCGbool CCGSphere::BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const
	{
		box = CCGaabb(m_pCenter - CCGVec3(m_dRadius, m_dRadius, m_dRadius), m_pCenter + CCGVec3(m_dRadius, m_dRadius, m_dRadius));
		return TRUE;
	}

	//! \brief 撞击物体组

	CCGHitList::CCGHitList()
	{

	}

	CCGHitList::CCGHitList(shared_ptr<CCGHitObject> object)
	{
		AddObject(object);
	}

	void CCGHitList::ClearList()
	{
		m_Object.clear();
	}

	void CCGHitList::AddObject(shared_ptr<CCGHitObject> object)
	{
		m_Object.push_back(object);
	}

	CCGbool CCGHitList::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		CCGHitRecord sTempRec;
		CCGbool bIsHit = FALSE;
		CCGdouble dCloseSoFar = tMax;
		for (const auto& obj : m_Object) {
			if (obj->Hit(rIn, tMin, dCloseSoFar, sTempRec)) {
				sRecord = sTempRec;
				dCloseSoFar = sTempRec.t;
				bIsHit = TRUE;
			}
		}
		return bIsHit;
	}

	CCGbool CCGHitList::BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const
	{
		if (m_Object.empty()) {
			return FALSE;
		}

		CCGaabb tempBox;
		CCGbool bFirst = TRUE;
		
		for (const auto &obj : m_Object) {
			if (!obj->BoundingBox(t0, t1, tempBox)) return FALSE;
			box = bFirst ? tempBox : SurroundingBox(box, tempBox);
			bFirst = FALSE;
		}

		return TRUE;
	}

	//! \brief 移动球体

	CCGMovSphere::CCGMovSphere()
	{
	}

	CCGMovSphere::CCGMovSphere(CCGPoint3D c0, CCGPoint3D c1, CCGdouble dT0, CCGdouble dT1, CCGdouble dRadius, shared_ptr<CCGMaterial> mat) :
		m_cen0(c0), m_cen1(c1), m_t0(dT0), m_t1(dT1), m_radius(dRadius), m_material(mat)
	{
	}

	CCGbool CCGMovSphere::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		CCGVec3 vOc = rIn.GetOrigin() - GetCenter(rIn.GetTime());
		CCGdouble dA = Dot(rIn.GetDirection(), rIn.GetDirection());
		CCGdouble dB = Dot(rIn.GetDirection(), vOc);
		CCGdouble dC = Dot(vOc, vOc) - m_radius*m_radius;
		CCGdouble dDiscrmination = dB*dB - dA*dC;
		if (dDiscrmination > 0) {
			CCGdouble temp = (-dB - sqrt(dDiscrmination)) / dA;
			if (tMin < temp && temp < tMax) {
				sRecord.t = temp;
				sRecord.pIntersect = rIn.PointAtParam(sRecord.t);
				sRecord.vNormal = (sRecord.pIntersect - GetCenter(rIn.GetTime())) / m_radius;
				sRecord.pMaterial = m_material;
				return TRUE;
			}

			temp = (-dB + sqrt(dDiscrmination)) / dA;
			if (tMin < temp && temp < tMax) {
				sRecord.t = temp;
				sRecord.pIntersect = rIn.PointAtParam(sRecord.t);
				sRecord.vNormal = (sRecord.pIntersect - GetCenter(rIn.GetTime())) / m_radius;
				sRecord.pMaterial = m_material;
				return TRUE;
			}
		}
		return FALSE;
	}

	CCGbool CCGMovSphere::BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const
	{
		return TRUE;
	}

	CCGPoint3D CCGMovSphere::GetCenter(CCGdouble t) const
	{
		return m_cen0 + ((t - m_t0) / (m_t1 - m_t0))*(m_cen1 - m_cen0);
	}

	//! \brief 包围盒树

	CCGBVHNode::CCGBVHNode()
	{
	}

	CCGBVHNode::~CCGBVHNode()
	{
	}

	CCGBVHNode::CCGBVHNode(std::vector<shared_ptr<CCGHitObject>> &objects, CCGint nStart, CCGint nEnd, CCGdouble dTime0, CCGdouble dTime1)
	{
		CCGint nAxis = RandInt(0, 2);
		auto fCom = (nAxis == 0) ? BoxXCompare : ((nAxis == 1) ? BoxYCompare : BoxZCompare);
		CCGint nSpan = nEnd - nStart;

		if (nSpan == 1) {
			m_pLeft = m_pRight = objects[nStart];
		}
		else if (nSpan == 2) {
			if (fCom(objects[nStart], objects[nStart + 1])) {
				m_pLeft = objects[nStart];
				m_pRight = objects[nStart + 1];
			}
			else {
				m_pLeft = objects[nStart + 1];
				m_pRight = objects[nStart];
			}
		}
		else {
			std::sort(objects.begin() + nStart, objects.begin() + nEnd, fCom);

			auto mid = nStart + nSpan / 2;
			m_pLeft = make_shared<CCGBVHNode>(objects, nStart, mid, dTime0, dTime1);
			m_pRight = make_shared<CCGBVHNode>(objects, mid, nEnd, dTime0, dTime1);
		}

		CCGaabb boxLeft, boxRight;
		if (!m_pLeft->BoundingBox(dTime0, dTime1, boxLeft) || !m_pRight->BoundingBox(dTime0, dTime1, boxRight)) {
			std::cerr << "No bounding box in BVHNode constructor.\n";
		}

		m_box = SurroundingBox(boxLeft, boxRight);
	}

	CCGBVHNode::CCGBVHNode(CCGHitList &list, CCGdouble dTime0, CCGdouble dTime1) : 
		CCGBVHNode(list.m_Object, 0, (CCGint)list.m_Object.size(), dTime0, dTime1)
	{
	}

	CCGbool CCGBVHNode::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		if (!m_box.Hit(rIn, tMin, tMax)) {
			return FALSE;
		}

		CCGbool bIsHitLeft = m_pLeft->Hit(rIn, tMin, tMax, sRecord);
		CCGbool bIsHitRight = m_pRight->Hit(rIn, tMin, bIsHitLeft ? sRecord.t : tMax, sRecord);

		return bIsHitLeft || bIsHitRight;
		/*
		if (m_box.Hit(rIn, tMin, tMax)) {
			CCGHitRecord recLeft, recRight;
			CCGbool	bIsHitLeft = m_pLeft->Hit(rIn, tMin, tMax, recLeft);
			CCGbool	bIsHitRight = m_pRight->Hit(rIn, tMin, tMax, recRight);
			if (bIsHitLeft && bIsHitRight) {
				if (recLeft.t < recRight.t) {
					sRecord = recLeft;
				}
				else {
					sRecord = recRight;
				}
				return TRUE;
			}
			else if (bIsHitLeft) {
				sRecord = recLeft;
				return TRUE;
			}
			else if (bIsHitRight) {
				sRecord = recRight;
				return TRUE;
			}
			else {
				return FALSE;
			}
		}
		else {
			return FALSE;
		}
		*/
	}

	CCGbool CCGBVHNode::BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const
	{
		box = m_box;
		return TRUE;
	}


	//! \brief XY矩形

	CCGXYRect::CCGXYRect()
	{
	}

	CCGXYRect::CCGXYRect(CCGdouble dXL, CCGdouble dXR, CCGdouble dYL, CCGdouble dYR, CCGdouble dPK, shared_ptr<CCGMaterial> pMat) : 
		m_dXL(dXL), m_dXR(dXR), m_dYL(dYL), m_dYR(dYR), m_dParamK(dPK), m_pMat(pMat)
	{
	}

	CCGXYRect::~CCGXYRect()
	{
	}

	CCGbool CCGXYRect::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		CCGdouble t = (m_dParamK - rIn.GetOrigin().z()) / rIn.GetDirection().z();
		if (t < tMin || t > tMax) {
			return FALSE;
		}
		CCGdouble x = rIn.GetOrigin().x() + t*rIn.GetDirection().x();
		CCGdouble y = rIn.GetOrigin().y() + t*rIn.GetDirection().y();
		if (x < m_dXL || x > m_dXR || y < m_dYL || y > m_dYR) {
			return FALSE;
		}
		sRecord.u = (x - m_dXL) / (m_dXR - m_dXL);
		sRecord.v = (y - m_dYL) / (m_dYR - m_dYL);
		sRecord.t = t;
		sRecord.pMaterial = m_pMat;
		sRecord.pIntersect = rIn.PointAtParam(t);
		sRecord.vNormal = CCGVec3(0, 0, 1);
		return TRUE;
	}

	CCGbool CCGXYRect::BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const
	{
		box = CCGaabb(CCGVec3(m_dXL, m_dYL, m_dParamK - 0.0001), CCGVec3(m_dXR, m_dYR, m_dParamK + 0.0001));
		return TRUE;
	}

	//! \brief XZ矩形

	CCGXZRect::CCGXZRect()
	{
	}

	CCGXZRect::CCGXZRect(CCGdouble dXL, CCGdouble dXR, CCGdouble dZL, CCGdouble dZR, CCGdouble dPK, shared_ptr<CCGMaterial> pMat) :
		m_dXL(dXL), m_dXR(dXR), m_dZL(dZL), m_dZR(dZR), m_dParamK(dPK), m_pMat(pMat)
	{
	}

	CCGXZRect::~CCGXZRect()
	{
	}

	CCGbool CCGXZRect::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		CCGdouble t = (m_dParamK - rIn.GetOrigin().y()) / rIn.GetDirection().y();
		if (t < tMin || t > tMax) {
			return FALSE;
		}
		CCGdouble x = rIn.GetOrigin().x() + t*rIn.GetDirection().x();
		CCGdouble z = rIn.GetOrigin().z() + t*rIn.GetDirection().z();
		if (x < m_dXL || x > m_dXR || z < m_dZL || z > m_dZR) {
			return FALSE;
		}
		sRecord.u = (x - m_dXL) / (m_dXR - m_dXL);
		sRecord.v = (z - m_dZL) / (m_dZR - m_dZL);
		sRecord.t = t;
		sRecord.pMaterial = m_pMat;
		sRecord.pIntersect = rIn.PointAtParam(t);
		sRecord.vNormal = CCGVec3(0, 1, 0);
		return TRUE;
	}

	CCGbool CCGXZRect::BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const
	{
		box = CCGaabb(CCGVec3(m_dXL, m_dParamK - 0.0001, m_dZL), CCGVec3(m_dXR, m_dParamK + 0.0001, m_dZR));
		return TRUE;
	}


	//! \brief YZ矩形

	CCGYZRect::CCGYZRect()
	{
	}

	CCGYZRect::CCGYZRect(CCGdouble dYL, CCGdouble dYR, CCGdouble dZL, CCGdouble dZR, CCGdouble dPK, shared_ptr<CCGMaterial> pMat) :
		m_dYL(dYL), m_dYR(dYR), m_dZL(dZL), m_dZR(dZR), m_dParamK(dPK), m_pMat(pMat)
	{
	}

	CCGYZRect::~CCGYZRect()
	{
	}

	CCGbool CCGYZRect::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		CCGdouble t = (m_dParamK - rIn.GetOrigin().x()) / rIn.GetDirection().x();
		if (t < tMin || t > tMax) {
			return FALSE;
		}
		CCGdouble y = rIn.GetOrigin().y() + t*rIn.GetDirection().y();
		CCGdouble z = rIn.GetOrigin().z() + t*rIn.GetDirection().z();
		if (y < m_dYL || y > m_dYR || z < m_dZL || z > m_dZR) {
			return FALSE;
		}
		sRecord.u = (y - m_dYL) / (m_dYR - m_dYL);
		sRecord.v = (z - m_dZL) / (m_dZR - m_dZL);
		sRecord.t = t;
		sRecord.pMaterial = m_pMat;
		sRecord.pIntersect = rIn.PointAtParam(t);
		sRecord.vNormal = CCGVec3(1, 0, 0);
		return TRUE;
	}

	CCGbool CCGYZRect::BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const
	{
		box = CCGaabb(CCGVec3(m_dParamK - 0.0001, m_dYL, m_dZL), CCGVec3(m_dParamK + 0.0001, m_dYR, m_dZR));
		return TRUE;
	}

	//! \brief 反转法线类

	CCGFlipNormals::CCGFlipNormals()
	{
	}

	CCGFlipNormals::CCGFlipNormals(shared_ptr<CCGHitObject> pMat) : m_pMat(pMat)
	{
	}

	CCGFlipNormals::~CCGFlipNormals()
	{
	}

	CCGbool CCGFlipNormals::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		if (m_pMat->Hit(rIn, tMin, tMax, sRecord)) {
			sRecord.vNormal = -sRecord.vNormal;
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

	CCGbool CCGFlipNormals::BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const
	{
		return m_pMat->BoundingBox(t0, t1, box);
	}

	//! \brief 盒体类

	CCGBox::CCGBox()
	{
	}

	CCGBox::CCGBox(const CCGVec3 &p0, const CCGVec3 &p1, shared_ptr<CCGMaterial> pMat)
	{
		m_pMin = p0;
		m_pMax = p1;
		m_pHit.AddObject(make_shared<CCGXYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), pMat));
		m_pHit.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGXYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), pMat)));
		m_pHit.AddObject(make_shared<CCGXZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), pMat));
		m_pHit.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGXZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), pMat)));
		m_pHit.AddObject(make_shared<CCGYZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), pMat));
		m_pHit.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGYZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), pMat)));
	}

	CCGBox::~CCGBox()
	{
	}

	CCGbool CCGBox::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		return m_pHit.Hit(rIn, tMin, tMax, sRecord);
	}

	CCGbool CCGBox::BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const
	{
		box = CCGaabb(m_pMin, m_pMax);
		return TRUE;
	}

	//! \brief 移动物体类

	CCGTranslate::CCGTranslate()
	{
	}

	CCGTranslate::CCGTranslate(shared_ptr<CCGHitObject> pHit, const CCGVec3 &dpt) : m_pHit(pHit), m_Offset(dpt)
	{
	}

	CCGTranslate::~CCGTranslate()
	{
	}

	CCGbool CCGTranslate::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		CCGRay rayMoved(rIn.GetOrigin() - m_Offset, rIn.GetDirection(), rIn.GetTime());
		if (m_pHit->Hit(rayMoved, tMin, tMax, sRecord)) {
			sRecord.pIntersect += m_Offset;
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

	CCGbool CCGTranslate::BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const
	{
		if (m_pHit->BoundingBox(t0, t1, box)) {
			box = CCGaabb(box.GetMin() + m_Offset, box.GetMax() + m_Offset);
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

	//! \brief 旋转物体类
	
	CCGRotateY::CCGRotateY()
	{
	}

	CCGRotateY::CCGRotateY(shared_ptr<CCGHitObject> pHit, CCGdouble dAngle) : m_pHit(pHit)
	{
		CCGdouble dRadians = (PI / 180.0) * dAngle;
		m_dSin = sin(dRadians);
		m_dCos = cos(dRadians);
		m_bHasBox = m_pHit->BoundingBox(0, 1, m_Box);
		CCGVec3 vecMin(CCGDB_MAX, CCGDB_MAX, CCGDB_MAX);
		CCGVec3 vecMax(-CCGDB_MAX, -CCGDB_MAX, -CCGDB_MAX);
		for (CCGint i = 0; i < 2; ++i) {
			for (CCGint j = 0; j < 2; ++j) {
				for (CCGint k = 0; k < 2; ++k) {
					CCGdouble x = i*m_Box.GetMax().x() + (1 - i)*m_Box.GetMin().x();
					CCGdouble y = j*m_Box.GetMax().y() + (1 - j)*m_Box.GetMin().y();
					CCGdouble z = k*m_Box.GetMax().z() + (1 - k)*m_Box.GetMin().z();
					CCGdouble newx = m_dCos*x + m_dSin*z;
					CCGdouble newz = -m_dSin*x + m_dCos*z;
					CCGVec3 vecTester(newx, y, newz);
					for (CCGint c = 0; c < 3; ++c) {
						if (vecTester[c] > vecMax[c]) {
							vecMax[c] = vecTester[c];
						}
						if (vecTester[c] < vecMin[c]) {
							vecMin[c] = vecTester[c];
						}
					}
				}
			}
		}
		m_Box = CCGaabb(vecMin, vecMax);
	}

	CCGRotateY::~CCGRotateY()
	{
	}

	CCGbool CCGRotateY::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		CCGVec3 vecOrigin = rIn.GetOrigin();
		CCGVec3 vecDir = rIn.GetDirection();
		vecOrigin[0] = m_dCos*rIn.GetOrigin()[0] - m_dSin*rIn.GetOrigin()[2];
		vecOrigin[2] = m_dSin*rIn.GetOrigin()[0] + m_dCos*rIn.GetOrigin()[2];
		vecDir[0] = m_dCos*rIn.GetDirection()[0] - m_dSin*rIn.GetDirection()[2];
		vecDir[2] = m_dSin*rIn.GetDirection()[0] + m_dCos*rIn.GetDirection()[2];
		CCGRay rRotated(vecOrigin, vecDir, rIn.GetTime());
		if (m_pHit->Hit(rRotated, tMin, tMax, sRecord)) {
			CCGVec3 vecP = sRecord.pIntersect;
			CCGVec3 vecNormal = sRecord.vNormal;
			vecP[0] = m_dCos*sRecord.pIntersect[0] + m_dSin*sRecord.pIntersect[2];
			vecP[2] = -m_dSin*sRecord.pIntersect[0] + m_dCos*sRecord.pIntersect[2];
			vecNormal[0] = m_dCos*sRecord.vNormal[0] + m_dSin*sRecord.vNormal[2];
			vecNormal[2] = -m_dSin*sRecord.vNormal[0] + m_dCos*sRecord.vNormal[2];
			sRecord.pIntersect = vecP;
			sRecord.vNormal = vecNormal;
			return TRUE;
		}
		else {
			return FALSE;
		}
	}

	CCGbool CCGRotateY::BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const
	{
		box = m_Box;
		return m_bHasBox;
	}

	//! \brief 常量介质类
	
	CCGConsMedium::CCGConsMedium()
	{
	}

	CCGConsMedium::CCGConsMedium(shared_ptr<CCGHitObject> pBoundary, CCGdouble dDensity, shared_ptr<CCGTexture> pTex) : 
		m_pBoundary(pBoundary), m_dDensity(dDensity), m_pPhaseFunc(make_shared<CCGIsotropic>(pTex))
	{
	}

	CCGConsMedium::~CCGConsMedium()
	{
	}

	CCGbool CCGConsMedium::Hit(const CCGRay &rIn, CCGdouble tMin, CCGdouble tMax, CCGHitRecord &sRecord) const
	{
		CCGbool bRand = (Rand() < 0.00001);
		bRand = FALSE;
		CCGHitRecord sRec1, sRec2;
		if (m_pBoundary->Hit(rIn, -CCGDB_MAX, CCGDB_MAX, sRec1)) {
			if (m_pBoundary->Hit(rIn, sRec1.t + 0.0001, CCGDB_MAX, sRec2)) {
				if (bRand) {
					std::cerr << "\nt0 t1 " << sRec1.t << " " << sRec2.t << "\n";
				}
				if (sRec1.t < tMin) sRec1.t = tMin;
				if (sRec2.t > tMax) sRec2.t = tMax;
				if (sRec1.t >= sRec2.t) return FALSE;
				if (sRec1.t < 0) sRec1.t = 0;
				CCGdouble dDisInBound = (sRec2.t - sRec1.t)*rIn.GetDirection().length();
				CCGdouble dHitDis = -(1 / m_dDensity)*log(Rand());
				if (dHitDis < dDisInBound) {
					if (bRand) {
						std::cerr << "HitDistance = " << dHitDis << "\n"
							<< "sRecord.t = " << sRecord.t << "\n"
							<< "sRecord.pIntersect = " << sRecord.pIntersect << "\n";
					}
					sRecord.t = sRec1.t + dHitDis / rIn.GetDirection().length();
					sRecord.pIntersect = rIn.PointAtParam(sRecord.t);
					sRecord.vNormal = CCGVec3(1, 0, 0);
					sRecord.pMaterial = m_pPhaseFunc;
					return TRUE;
				}
			}
		}
		return FALSE;
	}

	CCGbool CCGConsMedium::BoundingBox(CCGdouble t0, CCGdouble t1, CCGaabb &box) const
	{
		return m_pBoundary->BoundingBox(t0, t1, box);
	}

	//! \brief 公共函数

	CCGbool BoxCompare(const shared_ptr<CCGHitObject> a, const shared_ptr<CCGHitObject> b, CCGint nAxis)
	{
		CCGaabb boxA, boxB;

		if (!a->BoundingBox(0, 0, boxA) || !b->BoundingBox(0, 0, boxB)) {
			std::cerr << "No bounding box in BVHNode constructor.\n";
		}
		
		return boxA.GetMin()[nAxis] < boxB.GetMin()[nAxis];
	}

	CCGbool BoxXCompare(const shared_ptr<CCGHitObject> a, const shared_ptr<CCGHitObject> b)
	{
		return BoxCompare(a, b, 0);
	}

	CCGbool BoxYCompare(const shared_ptr<CCGHitObject> a, const shared_ptr<CCGHitObject> b)
	{
		return BoxCompare(a, b, 1);
	}

	CCGbool BoxZCompare(const shared_ptr<CCGHitObject> a, const shared_ptr<CCGHitObject> b)
	{
		return BoxCompare(a, b, 2);
	}

	void GetSphereUV(const CCGVec3 &p, CCGdouble &u, CCGdouble &v)
	{
		CCGdouble dPhi = atan2(p.z(), p.x());
		CCGdouble dTheta = asin(p.y());
		u = 1 - (dPhi + PI) / (2 * PI);
		v = (dTheta + PI / 2) / PI;
	}
}
