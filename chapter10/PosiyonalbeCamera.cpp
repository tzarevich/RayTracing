#include "CCGDefs.h"
#include "CCGCamera.h"
#include "CCGHitObjects.h"
#include "CCGMaterial.h"
#include "CCGRay.h"
#include "Vec3.h"
#include <ctime>
#include <cstdlib>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace CCG;

void PosCam();

int main() {
	PosCam();
	return 0;
}

void PosCam() {
	srand((unsigned)time(NULL));
	CCGdouble dAspect = 16.0 / 9.0;
	CCGint nx = 400;
	CCGint ny = static_cast<int>(nx / dAspect);
	CCGint ns = 50;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	CCGint channels = 3;
	CCGuchar *data = new CCGuchar[nx*ny*channels];

	/*CCGHitObject *list[5];
	list[0] = new CCGSphere(CCGPoint3D(0, 0, -1), 0.5, shared_ptr<CCGMaterial>(new CCGLambertina(CCGVec3(0.1, 0.2, 0.5))));
	list[1] = new CCGSphere(CCGPoint3D(0, -100.5, -1), 100, shared_ptr<CCGMaterial>(new CCGLambertina(CCGVec3(0.8, 0.8, 0))));
	list[2] = new CCGSphere(CCGPoint3D(1, 0, -1), 0.5, shared_ptr<CCGMaterial>(new CCGMental(CCGVec3(0.8, 0.6, 0.2), 0)));
	list[3] = new CCGSphere(CCGPoint3D(-1, 0, -1), 0.5, shared_ptr<CCGMaterial>(new CCGDielectric(1.5)));
	list[4] = new CCGSphere(CCGPoint3D(-1, 0, -1), -0.45, shared_ptr<CCGMaterial>(new CCGDielectric(1.5)));*/
	//CCGHitObject *world = RandomScene();
	//CCGCamera camera(CCGPoint3D(-2, 2, 1), CCGPoint3D(0, 0, -1), CCGVec3(0, 1, 0), 20, static_cast<CCGdouble>(nx) / static_cast<CCGdouble>(ny));

	CCGPoint3D pLookfrom(13, 2, 3);
	CCGPoint3D pLookat(0, 0, 0);
	//CCGdouble dToFocus = 10;
	//CCGdouble dApert = 0.1;
	CCGdouble dToFocus = (pLookfrom - pLookat).length();
	//CCGdouble dToFocus = 1.0;
	CCGdouble dApert = 0.0;
	CCGCamera camera(pLookfrom, pLookat, CCGVec3(0, 1, 0), 20, dAspect, dApert, dToFocus);
	
	auto world = RandomScene();
	for (CCGint j = ny - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining : " << j << " " << std::flush;
		for (CCGint i = 0; i < nx; ++i) {
			CCGColor3D cColor(0, 0, 0);
			for (CCGint s = 0; s < ns; ++s) {
				CCGdouble u = static_cast<CCGdouble>(i + GetDBRand()) / static_cast<CCGdouble>(nx);
				CCGdouble v = static_cast<CCGdouble>(j + GetDBRand()) / static_cast<CCGdouble>(ny);

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
	stbi_write_png("F:\\VS2013\\MyCppSpace\\OpenGL\\RayTracing\\OutputImage\\ImagePng\\StbWrite2.png", nx, ny, channels, data, 0);
	std::cerr << "\nDone.\n";
}