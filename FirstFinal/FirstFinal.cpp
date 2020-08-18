#include <iostream>
#include "CCGdefs.h"
#include "CCGVec3.h"
#include "CCGRay.h"
#include "CCGHitObject.h"
#include "CCGMaterial.h"
#include "CCGCamera.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace CCG;

CCGHitArray RandomScene();
CCGColor3D Color(const CCGRay &rIn, const CCGHitArray &world, CCGdouble nDepth);
void Final();

int main() {
	srand((unsigned)time(NULL));
	Final();
	return 0;
}

void Final(){
	CCGdouble dAsp = 16.0 / 9.0;
	CCGint nx = 400;
	CCGint ny = static_cast<CCGint>(nx / dAsp);
	CCGint ns = 10;
	CCGint channels = 3;
	CCGuchar *data = new CCGuchar[nx*ny*channels];
	CCGHitArray world = RandomScene();

	CCGPoint3D pLookfrom(13, 2, 3);
	CCGPoint3D pLookat(0, 0, 0);
	CCGVec3 vVup(0, 1, 0);
	CCGdouble dFocusDis = 10;
	CCGdouble dApt = 0;
	CCGCamera cam(pLookfrom, pLookat, vVup, 20, dAsp, dApt, dFocusDis);

	for (CCGint j = ny - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining : " << j << " " << std::flush;
		for (CCGint i = 0; i < nx; ++i) {
			CCGColor3D color(0, 0, 0);
			for (CCGint s = 0; s < ns; ++s) {
				CCGdouble u = static_cast<CCGdouble>(i + RandomZeroToOne()) / static_cast<CCGdouble>(nx);
				CCGdouble v = static_cast<CCGdouble>(j + RandomZeroToOne()) / static_cast<CCGdouble>(ny);

				CCGRay rRay = cam.GetRay(u, v);
				color += Color(rRay, world, 0);
			}

			color /= static_cast<CCGdouble>(ns);
			color = CCGColor3D(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));
			CCGint ir = static_cast<CCGint>(256 * color[0]);
			CCGint ig = static_cast<CCGint>(256 * color[1]);
			CCGint ib = static_cast<CCGint>(256 * color[2]);

			data[(ny - j - 1)*channels*nx + channels*i] = ir;
			data[(ny - j - 1)*channels*nx + channels*i + 1] = ig;
			data[(ny - j - 1)*channels*nx + channels*i + 2] = ib;
		}
	}
	stbi_write_png("F:\\VS2013\\MyCppSpace\\OpenGL\\RayTracing\\OutputImage\\ImagePng\\Final.png", nx, ny, channels, data, 0);
	std::cerr << "\nDone\n";
}

CCGColor3D Color(const CCGRay &rIn, const CCGHitArray &world, CCGdouble nDepth) {
	CCGHitRecord sTem;
	
	if (nDepth >= 50) {
		return CCGColor3D(0, 0, 0);
	}

	if (world.Hit(rIn, 0.001, DBL_MAX, sTem)) {
		CCGVec3 temAtu;
		CCGRay temSca;
		if (sTem.mat->Scatter(rIn, sTem, temAtu, temSca)){
			return temAtu*Color(temSca, world, nDepth + 1);
		}
		return CCGColor3D(0, 0, 0);
	}
	CCGVec3 uv = UnitVector(rIn.GetDirection());
	CCGdouble t = 0.5 * (uv.y() + 1.0);
	return (1.0 - t)*CCGColor3D(1, 1, 1) + t*CCGColor3D(0.5, 0.7, 1.0);
}

CCGHitArray RandomScene() {
	CCGHitArray world;
	auto groundMat = make_shared<CCGLambertian>(CCGVec3(0.5, 0.5, 0.5));
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(0, -1000, 0), 1000, groundMat));

	for (CCGint a = -3; a < 3; ++a) {
		for (CCGint b = -3; b < 3; ++b) {
			CCGdouble dChooseMat = RandomZeroToOne();
			CCGPoint3D pCenter(a + RandomZeroToOne()*0.9, 0.2, b + RandomZeroToOne()*0.9);
			if ((pCenter - CCGPoint3D(4, 0.2, 0)).GetLength() > 0.9) {
				shared_ptr<CCGMaterial> pSphereMat;

				if (dChooseMat < 0.8) {	//Lambertina
					CCGVec3 vAttenuation = CCGVec3::GetRandVector() * CCGVec3::GetRandVector();
					pSphereMat = make_shared<CCGLambertian>(vAttenuation);
					world.AddObject(make_shared<CCGSphere>(pCenter, 0.2, pSphereMat));
				}
				else if (dChooseMat < 0.95) { //mental
					CCGVec3 vAttenuation = CCGVec3(0.5*(1 + RandomZeroToOne()), 0.5*(1 + RandomZeroToOne()), 0.5*RandomZeroToOne());
					CCGdouble fuzz = RandomMinToMax(0, 0.5);
					pSphereMat = make_shared<CCGMental>(vAttenuation, fuzz);
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

	auto m2 = make_shared<CCGLambertian>(CCGVec3(0.4, 0.2, 0.1));
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(-4, 1, 0), 1.0, m2));

	auto m3 = make_shared<CCGMental>(CCGVec3(0.7, 0.6, 0.5), 0);
	world.AddObject(make_shared<CCGSphere>(CCGPoint3D(4, 1, 0), 1.0, m3));
	return world;
}