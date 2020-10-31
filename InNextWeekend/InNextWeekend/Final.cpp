#include "CCGDefs.h"
#include "CCGCamera.h"
#include "CCGHitObjects.h"
#include "Vec3.h"
#include "CCGMaterial.h"
#include "CCGRay.h"
#include "CCGaabb.h"
#include "CCGTexture.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace CCG;

CCGColor3D Color(const CCGRay &rIn, const CCGHitObject& hList, CCGint nDepth);
CCGHitList RandomScene();
CCGHitList TwoSphere();
CCGHitList TwoPerlinSphere();
CCGHitList Earth();
CCGHitList SimpleLight();
CCGHitList CornellBox();
CCGHitList TwoBlocks();
CCGHitList RotateBlocks();
CCGHitList CornellSmoke();
CCGHitList FinalImage();
void Finally();

int main() {
	Finally();
	return 0;
}

void Finally() {
	srand((unsigned)time(NULL));
	//CCGdouble dAspect = 16.0 / 9.0;
	CCGdouble dAspect = 1.0;
	//CCGint nx = 1200;
	CCGint nx = 800;
	CCGint ny = static_cast<int>(nx / dAspect);
	CCGint ns = 500;

	CCGint channels = 3;
	CCGuchar *data = new CCGuchar[nx*ny*channels];

	//CCGPoint3D pLookfrom(0, 0, 12);	//图片纹理视点
	//CCGPoint3D pLookfrom(13, 2, 3);
	//CCGPoint3D pLookat(0, 0, 0);

	//矩形SimpleLight
	CCGPoint3D pLookfrom(26, 3, 6);		
	CCGPoint3D pLookat(0, 2, 0);

	//CornellBox
	//CCGPoint3D pLookfrom(278, 278, -800);
	//CCGPoint3D pLookat(278, 278, 0);

	//FinalImage
	//CCGPoint3D pLookfrom(478, 278, -600);
	//CCGPoint3D pLookat(278, 278, 0);

	CCGdouble dFov = 20;
	CCGdouble dToFocus = (pLookfrom - pLookat).length();
	CCGdouble dApert = 0.0;
	//CCGdouble dFov = 20;
	CCGCamera camera(pLookfrom, pLookat, CCGVec3(0, 1, 0), dFov, dAspect, dApert, dToFocus, 0.0, 1.0);

	//auto world = RandomScene();
	//auto world = TwoSphere();
	//auto world = TwoPerlinSphere();
	//auto world = Earth();
	auto world = SimpleLight();
	//auto world = RotateBlocks();
	//auto world = CornellSmoke();
	//auto world = FinalImage();
	for (CCGint j = ny - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining : " << j << " " << std::flush;
		for (CCGint i = 0; i < nx; ++i) {
			CCGColor3D cColor(0, 0, 0);
			for (CCGint s = 0; s < ns; ++s) {
				CCGdouble u = static_cast<CCGdouble>(i + Rand()) / static_cast<CCGdouble>(nx);
				CCGdouble v = static_cast<CCGdouble>(j + Rand()) / static_cast<CCGdouble>(ny);

				CCGRay rRay = camera.GetRay(u, v);
				cColor += Color(rRay, world, 0);
			}

			cColor /= static_cast<CCGdouble>(ns);
			cColor = CCGColor3D(sqrt(cColor[0]), sqrt(cColor[1]), sqrt(cColor[2]));

			CCGint ir = static_cast<CCGint>(255.99 * cColor[0]);
			CCGint ig = static_cast<CCGint>(255.99 * cColor[1]);
			CCGint ib = static_cast<CCGint>(255.99 * cColor[2]);

			data[(ny - j - 1)*nx*channels + channels*i] = ir;
			data[(ny - j - 1)*nx*channels + channels*i + 1] = ig;
			data[(ny - j - 1)*nx*channels + channels*i + 2] = ib;

			//std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	stbi_write_png("F:\\VS2013\\MyCppSpace\\OpenGL\\RayTracing\\OutputImage\\ImagePng\\NextFinalImage_1.png", nx, ny, channels, data, 0);
	std::cerr << "\nDone.\n";
}

CCGHitList FinalImage()
{
	
	CCGHitList boxes1;
	auto matGround = make_shared<CCGLambertina>(make_shared<CCGConsTex>(CCGColor3D(0.48, 0.83, 0.53)));
	const CCGint nBoxPerSide = 20;
	for(CCGint i = 0; i < nBoxPerSide; ++i) {
		for (CCGint j = 0; j < nBoxPerSide; ++j) {
			CCGdouble w = 100.0;
			CCGdouble x0 = -1000.0 + i*w;
			CCGdouble z0 = -1000.0 + j*w;
			CCGdouble y0 = 0.0;
			CCGdouble x1 = x0 + w;
			CCGdouble y1 = RandBW(1, 101);
			CCGdouble z1 = z0 + w;
			boxes1.AddObject(make_shared<CCGBox>(CCGPoint3D(x0, y0, z0), CCGPoint3D(x1, y1, z1), matGround));
		}
	}

	CCGHitList world;

	world.AddObject(make_shared<CCGBVHNode>(boxes1, 0, 1));
	
	auto light = make_shared<CCGDfsLight>(make_shared<CCGConsTex>(CCGColor3D(7, 7, 7)));
	world.AddObject(make_shared<CCGXZRect>(123, 423, 147, 412, 554, light));
	
	
	auto cen1 = CCGPoint3D(400, 400, 200);
	auto cen2 = cen1 + CCGVec3(30, 0, 0);
	auto moveSphereMat = make_shared<CCGLambertina>(make_shared<CCGConsTex>(CCGColor3D(0.7, 0.3, 0.1)));
	world.AddObject(make_shared<CCGMovSphere>(cen1, cen2, 0, 1, 50, moveSphereMat));
	
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(260, 150, 45), 50, make_shared<CCGDielectric>(1.5)));
	
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, 150, 145), 50, make_shared<CCGMental>(CCGColor3D(0.8, 0.8, 0.9), 10.0)));

	auto boundary = make_shared<CCGSphere>(CCGPoint3D(360, 150, 145), 70, make_shared<CCGDielectric>(1.5));
	world.AddObject(boundary);

	world.AddObject(make_shared<CCGConsMedium>(boundary, 0.2, make_shared<CCGConsTex>(CCGColor3D(0.2, 0.4, 0.9))));

	boundary = make_shared<CCGSphere>(CCGPoint3D(0, 0, 0), 5000, make_shared<CCGDielectric>(1.5));
	world.AddObject(make_shared<CCGConsMedium>(boundary, 0.0001, make_shared<CCGConsTex>(CCGColor3D(1, 1, 1))));

	CCGint nx, ny, nn;
	CCGuchar *pData = stbi_load("F:\\VS2013\\MyCppSpace\\OpenGL\\RayTracing\\OutputImage\\ImagePng\\earthmap.jpg", &nx, &ny, &nn, 0);
	auto pImageTex = make_shared<CCGImageTex>(pData, nx, ny);
	auto emat = make_shared<CCGLambertina>(pImageTex);
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(400, 200, 400), 100, emat));
	
	auto noiseTex = make_shared<CCGNoiseTex>(0.1);
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(220, 280, 300), 80, make_shared<CCGLambertina>(noiseTex)));
	
	
	//CCGHitList world;
	//world.AddObject(make_shared<CCGSphere>(CCGPoint3D(260, 150, 45), 50, make_shared<CCGDielectric>(1.5)));
	//world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, 150, 145), 50, make_shared<CCGMental>(CCGColor3D(0.8, 0.8, 0.9), 10.0)));
	//CCGint nx, ny, nn;
	//CCGuchar *pData = stbi_load("F:\\VS2013\\MyCppSpace\\OpenGL\\RayTracing\\OutputImage\\ImagePng\\earthmap.jpg", &nx, &ny, &nn, 0);
	//auto pImageTex = make_shared<CCGImageTex>(pData, nx, ny);
	//auto emat = make_shared<CCGLambertina>(pImageTex);
	//world.AddObject(make_shared<CCGSphere>(CCGPoint3D(400, 200, 400), 100, emat));


	CCGHitList boxes2;
	auto white = make_shared<CCGLambertina>(make_shared<CCGConsTex>(CCGColor3D(0.73, 0.23, 0.66)));
	CCGint ns = 1000;
	for (CCGint j = 0; j < ns; ++j) {
		CCGPoint3D o = CCGPoint3D(RandBW(0, 165), RandBW(0, 165), RandBW(0, 165));
		boxes2.AddObject(make_shared<CCGSphere>(o, 10, white));
	}
	world.AddObject(make_shared<CCGTranslate>(
		make_shared<CCGRotateY>(
			make_shared<CCGBVHNode>(boxes2, 0.0, 1.0), 15), 
			CCGVec3(-100, 270, 395)
		)
	);
	
	return world;
}

CCGHitList CornellSmoke()
{
	CCGHitList world;
	auto pRedConsTex = make_shared<CCGConsTex>(CCGVec3(0.65, 0.05, 0.05));
	auto pRedMaterial = make_shared<CCGLambertina>(pRedConsTex);
	auto pWhiteConsTex = make_shared<CCGConsTex>(CCGVec3(0.73, 0.73, 0.73));
	auto pWhiteMaterial = make_shared<CCGLambertina>(pWhiteConsTex);
	auto pGreenConsTex = make_shared<CCGConsTex>(CCGVec3(0.12, 0.45, 0.15));
	auto pGreenMaterial = make_shared<CCGLambertina>(pGreenConsTex);
	auto pLightConsTex = make_shared<CCGConsTex>(CCGVec3(7, 7, 7));
	auto pLightMaterial = make_shared<CCGDfsLight>(pLightConsTex);
	world.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGYZRect>(0, 555, 0, 555, 555, pGreenMaterial)));
	world.AddObject(make_shared<CCGYZRect>(0, 555, 0, 555, 0, pRedMaterial));
	world.AddObject(make_shared<CCGXZRect>(113, 443, 127, 432, 554, pLightMaterial));
	world.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGXZRect>(0, 555, 0, 555, 555, pWhiteMaterial)));
	world.AddObject(make_shared<CCGXZRect>(0, 555, 0, 555, 0, pWhiteMaterial));
	world.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGXYRect>(0, 555, 0, 555, 555, pWhiteMaterial)));

	auto pBox1 = make_shared<CCGBox>(CCGVec3(0, 0, 0), CCGVec3(165, 165, 165), pWhiteMaterial);
	auto pRotate1 = make_shared<CCGRotateY>(pBox1, -18);
	auto pTrans1 = make_shared<CCGTranslate>(pRotate1, CCGVec3(130, 0, 65));
	world.AddObject(make_shared<CCGConsMedium>(pTrans1, 0.01, make_shared<CCGConsTex>(CCGVec3(1, 1, 1))));

	auto pBox2 = make_shared<CCGBox>(CCGVec3(0, 0, 0), CCGVec3(165, 330, 165), pWhiteMaterial);
	auto pRotate2 = make_shared<CCGRotateY>(pBox2, 15);
	auto pTrans2 = make_shared<CCGTranslate>(pRotate2, CCGVec3(265, 0, 295));
	world.AddObject(make_shared<CCGConsMedium>(pTrans2, 0.01, make_shared<CCGConsTex>(CCGVec3(0, 0, 0))));

	return world;
}

CCGHitList RotateBlocks()
{
	CCGHitList world;
	auto pRedConsTex = make_shared<CCGConsTex>(CCGVec3(0.65, 0.05, 0.05));
	auto pRedMaterial = make_shared<CCGLambertina>(pRedConsTex);
	auto pWhiteConsTex = make_shared<CCGConsTex>(CCGVec3(0.73, 0.73, 0.73));
	auto pWhiteMaterial = make_shared<CCGLambertina>(pWhiteConsTex);
	auto pGreenConsTex = make_shared<CCGConsTex>(CCGVec3(0.12, 0.45, 0.15));
	auto pGreenMaterial = make_shared<CCGLambertina>(pGreenConsTex);
	auto pLightConsTex = make_shared<CCGConsTex>(CCGVec3(15, 15, 15));
	auto pLightMaterial = make_shared<CCGDfsLight>(pLightConsTex);
	world.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGYZRect>(0, 555, 0, 555, 555, pGreenMaterial)));
	world.AddObject(make_shared<CCGYZRect>(0, 555, 0, 555, 0, pRedMaterial));
	world.AddObject(make_shared<CCGXZRect>(213, 343, 227, 332, 554, pLightMaterial));
	world.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGXZRect>(0, 555, 0, 555, 555, pWhiteMaterial)));
	world.AddObject(make_shared<CCGXZRect>(0, 555, 0, 555, 0, pWhiteMaterial));
	world.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGXYRect>(0, 555, 0, 555, 555, pWhiteMaterial)));
	auto pBox1 = make_shared<CCGBox>(CCGVec3(0, 0, 0), CCGVec3(165, 165, 165), pWhiteMaterial);
	auto pRotate1 = make_shared<CCGRotateY>(pBox1, -18);
	world.AddObject(make_shared<CCGTranslate>(pRotate1, CCGVec3(130, 0, 65)));
	auto pBox2 = make_shared<CCGBox>(CCGVec3(0, 0, 0), CCGVec3(165, 330, 165), pWhiteMaterial);
	auto pRotate2 = make_shared<CCGRotateY>(pBox2, 15);
	world.AddObject(make_shared<CCGTranslate>(pRotate2, CCGVec3(265, 0, 295)));
	return world;
}

CCGHitList TwoBlocks()
{
	CCGHitList world;
	auto pRedConsTex = make_shared<CCGConsTex>(CCGVec3(0.65, 0.05, 0.05));
	auto pRedMaterial = make_shared<CCGLambertina>(pRedConsTex);
	auto pWhiteConsTex = make_shared<CCGConsTex>(CCGVec3(0.73, 0.73, 0.73));
	auto pWhiteMaterial = make_shared<CCGLambertina>(pWhiteConsTex);
	auto pGreenConsTex = make_shared<CCGConsTex>(CCGVec3(0.12, 0.45, 0.15));
	auto pGreenMaterial = make_shared<CCGLambertina>(pGreenConsTex);
	auto pLightConsTex = make_shared<CCGConsTex>(CCGVec3(15, 15, 15));
	auto pLightMaterial = make_shared<CCGDfsLight>(pLightConsTex);
	world.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGYZRect>(0, 555, 0, 555, 555, pGreenMaterial)));
	world.AddObject(make_shared<CCGYZRect>(0, 555, 0, 555, 0, pRedMaterial));
	world.AddObject(make_shared<CCGXZRect>(213, 343, 227, 332, 554, pLightMaterial));
	world.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGXZRect>(0, 555, 0, 555, 555, pWhiteMaterial)));
	world.AddObject(make_shared<CCGXZRect>(0, 555, 0, 555, 0, pWhiteMaterial));
	world.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGXYRect>(0, 555, 0, 555, 555, pWhiteMaterial)));
	world.AddObject(make_shared<CCGBox>(CCGVec3(130, 0, 65), CCGVec3(295, 165, 230), pWhiteMaterial));
	world.AddObject(make_shared<CCGBox>(CCGVec3(265, 0, 295), CCGVec3(430, 330, 460), pWhiteMaterial));
	return world;
}

CCGHitList CornellBox()
{
	CCGHitList world;
	auto pRedConsTex = make_shared<CCGConsTex>(CCGVec3(0.65, 0.05, 0.05));
	auto pRedMaterial = make_shared<CCGLambertina>(pRedConsTex);
	auto pWhiteConsTex = make_shared<CCGConsTex>(CCGVec3(0.73, 0.73, 0.73));
	auto pWhiteMaterial = make_shared<CCGLambertina>(pWhiteConsTex);
	auto pGreenConsTex = make_shared<CCGConsTex>(CCGVec3(0.12, 0.45, 0.15));
	auto pGreenMaterial = make_shared<CCGLambertina>(pGreenConsTex);
	auto pLightConsTex = make_shared<CCGConsTex>(CCGVec3(15, 15, 15));
	auto pLightMaterial = make_shared<CCGDfsLight>(pLightConsTex);
	world.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGYZRect>(0, 555, 0, 555, 555, pGreenMaterial)));
	world.AddObject(make_shared<CCGYZRect>(0, 555, 0, 555, 0, pRedMaterial));
	world.AddObject(make_shared<CCGXZRect>(213, 343, 227, 332, 554, pLightMaterial));
	world.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGXZRect>(0, 555, 0, 555, 555, pWhiteMaterial)));
	world.AddObject(make_shared<CCGXZRect>(0, 555, 0, 555, 0, pWhiteMaterial));
	world.AddObject(make_shared<CCGFlipNormals>(make_shared<CCGXYRect>(0, 555, 0, 555, 555, pWhiteMaterial)));
	return world;
}

//CCGHitList CornellBox()
//{
//	CCGHitList world;
//	auto pRedConsTex = make_shared<CCGConsTex>(CCGVec3(0.65, 0.05, 0.05));
//	auto pRedMaterial = make_shared<CCGLambertina>(pRedConsTex);
//	auto pWhiteConsTex = make_shared<CCGConsTex>(CCGVec3(0.73, 0.73, 0.73));
//	auto pWhiteMaterial = make_shared<CCGLambertina>(pWhiteConsTex);
//	auto pGreenConsTex = make_shared<CCGConsTex>(CCGVec3(0.12, 0.45, 0.15));
//	auto pGreenMaterial = make_shared<CCGLambertina>(pGreenConsTex);
//	auto pLightConsTex = make_shared<CCGConsTex>(CCGVec3(15, 15, 15));
//	auto pLightMaterial = make_shared<CCGDfsLight>(pLightConsTex);
//	world.AddObject(make_shared<CCGYZRect>(0, 555, 0, 555, 555, pGreenMaterial));
//	world.AddObject(make_shared<CCGYZRect>(0, 555, 0, 555, 0, pRedMaterial));
//	world.AddObject(make_shared<CCGXZRect>(213, 343, 227, 332, 554, pLightMaterial));
//	world.AddObject(make_shared<CCGXZRect>(0, 555, 0, 555, 0, pWhiteMaterial));
//	world.AddObject(make_shared<CCGXYRect>(0, 555, 0, 555, 555, pWhiteMaterial));
//	return world;
//}

CCGHitList SimpleLight()
{
	CCGHitList world;
	auto pCheckerTex = make_shared<CCGNoiseTex>(4);
	auto lGroundMaterial = make_shared<CCGLambertina>(pCheckerTex);
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, -1000, 0), 1000, lGroundMaterial));
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, 2, 0), 2, lGroundMaterial));
	auto pConsTex = make_shared<CCGConsTex>(CCGVec3(4, 4, 4));
	auto pLightMat = make_shared<CCGDfsLight>(pConsTex);
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, 7, 0), 2, pLightMat));
	world.AddObject(make_shared<CCGXYRect>(3, 5, 1, 3, -2, pLightMat));
	return world;
}

CCGHitList Earth()
{
	CCGHitList world;
	CCGint nx, ny, nn;
	CCGuchar *pData = stbi_load("F:\\VS2013\\MyCppSpace\\OpenGL\\RayTracing\\OutputImage\\ImagePng\\earthmap.jpg", &nx, &ny, &nn, 0);
	auto pCheckerTex = make_shared<CCGImageTex>(pData, nx, ny);
	auto lGroundMaterial = make_shared<CCGLambertina>(pCheckerTex);
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, 0, 0), 2, lGroundMaterial));
	return world;
}

CCGHitList TwoPerlinSphere()
{
	CCGHitList world;
	auto pCheckerTex = make_shared<CCGNoiseTex>(4);
	auto lGroundMaterial = make_shared<CCGLambertina>(pCheckerTex);
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, -1000, 0), 1000, lGroundMaterial));
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, 2, 0), 2, lGroundMaterial));
	return world;
}

CCGHitList TwoSphere()
{
	CCGHitList world;
	auto pCheckerTex = make_shared<CCGCheckerTex>(make_shared<CCGConsTex>(CCGColor3D(0.2, 0.3, 0.1)), 
		make_shared<CCGConsTex>(CCGColor3D(0.9, 0.9, 0.9)));
	auto lGroundMaterial = make_shared<CCGLambertina>(pCheckerTex);
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, -10, 0), 10, lGroundMaterial));
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, 10, 0), 10, lGroundMaterial));
	return world;
}

CCGHitList RandomScene()
{
	CCGHitList world;
	auto pCheckerTex = make_shared<CCGCheckerTex>(make_shared<CCGConsTex>(CCGColor3D(0.2, 0.3, 0.1)), make_shared<CCGConsTex>(CCGColor3D(0.9, 0.9, 0.9)));
	auto lGroundMaterial = make_shared<CCGLambertina>(pCheckerTex);
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, -1000, 0), 1000, lGroundMaterial));
	for (CCGint a = -4; a < 4; ++a) {
		for (CCGint b = -4; b < 4; ++b) {
			CCGdouble dChooseMat = Rand();
			CCGPoint3D pCenter(a + 0.9*Rand(), 0.2, b + 0.9*Rand());
			if ((pCenter - CCGPoint3D(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<CCGMaterial> pSphereMat;

				if (dChooseMat < 0.8) {	//Lambertina
					CCGVec3 vAttenuation = CCGVec3::RandVec() * CCGVec3::RandVec();
					pSphereMat = make_shared<CCGLambertina>(make_shared<CCGConsTex>(vAttenuation));
					world.AddObject(make_shared<CCGMovSphere>(pCenter, pCenter +  CCGPoint3D(0, 0.5*Rand(), 0), 0.0, 1.0, 0.2, pSphereMat));
				}
				else if (dChooseMat < 0.95) { //mental
					CCGVec3 vAttenuation = CCGVec3(0.5*(1 + Rand()), 0.5*(1 + Rand()), 0.5*Rand());
					CCGdouble r = RandBW(0, 0.5);
					//auto fuzz = r > 0.5 ? r - 0.5 : r;
					pSphereMat = make_shared<CCGMental>(vAttenuation, r);
					world.AddObject(make_shared<CCGSphere>(pCenter, 0.2, pSphereMat));
				}
				else {	//dielectric
					pSphereMat = make_shared<CCGDielectric>(1.5);
					world.AddObject(make_shared<CCGSphere>(pCenter, 0.2, pSphereMat));
				}
			}
		}
	}

	auto m1 = make_shared<CCGDielectric>(1.5);
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, 1, 0), 1.0, m1));

	auto m2 = make_shared<CCGLambertina>(make_shared<CCGConsTex>(CCGVec3(0.4, 0.2, 0.1)));
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(-4, 1, 0), 1.0, m2));

	auto m3 = make_shared<CCGMental>(CCGVec3(0.7, 0.6, 0.5), 0);
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(4, 1, 0), 1.0, m3));
	return world;
}


//CCGColor3D Color(const CCGRay &rIn, const CCGHitObject& hList, CCGint nDepth)
//{
//	CCGHitRecord sRec;
//
//	if (nDepth >= 50) {
//		return CCGColor3D(0, 0, 0);
//	}
//	if (hList.Hit(rIn, 0.001, CCGDB_MAX, sRec)) {
//		CCGVec3 tempAttenuation;
//		CCGRay tempScattered;
//		if (sRec.pMaterial->Scatter(rIn, sRec, tempAttenuation, tempScattered)) {
//			return tempAttenuation*Color(tempScattered, hList, nDepth + 1);
//		}
//		return CCGColor3D(0, 0, 0);
//	}
//	CCGVec3 vUnitDir = unit_vector(rIn.GetDirection());
//	CCGdouble t = 0.5*(vUnitDir.y() + 1.0);
//	return (1.0 - t)*CCGColor3D(1, 1, 1) + t*CCGColor3D(0.5, 0.7, 1.0);
//}

//! \brief 加入矩形及发光函数后的color函数


CCGColor3D Color(const CCGRay &rIn, const CCGHitObject& hList, CCGint nDepth)
{
	CCGHitRecord sRec;
	if (hList.Hit(rIn, 0.001, CCGDB_MAX, sRec)) {
		CCGVec3 tempAttenuation;
		CCGRay tempScattered;
		CCGVec3 emitted = sRec.pMaterial->Emitted(sRec.u, sRec.v, sRec.pIntersect);
		if (nDepth < 50 && sRec.pMaterial->Scatter(rIn, sRec, tempAttenuation, tempScattered)) {
			return emitted + tempAttenuation*Color(tempScattered, hList, nDepth + 1);
		}
		else {
			return emitted;
		}
	}
	else {
		return CCGVec3(0, 0, 0);
	}
}
