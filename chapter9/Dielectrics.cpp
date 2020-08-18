#include "CCGDefs.h"
#include "Vec3.h"
#include "CCGRay.h"
#include "CCGCamera.h"
#include "CCGMaterial.h"

#include <cstdlib>
#include <ctime>

using namespace CCG;

void Dielectirc();

int main() {
	Dielectirc();
	return 0;
}

void Dielectirc() {
	srand((unsigned)time(NULL));
	CCGint nx = 200;
	CCGint ny = 100;
	CCGint ns = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	CCGHitObject *list[5];
	shared_ptr<CCGMaterial> m1(new CCGLambertina(CCGVec3(0.1, 0.2, 0.5)));
	list[0] = new CCGSphere(CCGPoint3D(0, 0, -1), 0.5, m1);

	shared_ptr<CCGMaterial> m2(new CCGLambertina(CCGVec3(0.8, 0.8, 0.0)));
	list[1] = new CCGSphere(CCGPoint3D(0, -100.5, -1), 100, m2);

	shared_ptr<CCGMaterial> m3(new CCGMental(CCGVec3(0.8, 0.6, 0.2), 0));
	list[2] = new CCGSphere(CCGPoint3D(1, 0, -1), 0.5, m3);

	shared_ptr<CCGMaterial> m4(new CCGDielectric(1.5));
	list[3] = new CCGSphere(CCGPoint3D(-1, 0, -1), 0.5, m4);

	list[4] = new CCGSphere(CCGPoint3D(-1, 0, -1), -0.45, m4);
	CCGHitObject *pWorld = new CCGHitList(list, 5);
	CCGCamera cCamera;
	for (CCGint j = ny - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining : " << j << " " << std::flush;
		for (CCGint i = 0; i < nx; ++i) {
			CCGColor3D cColor(0, 0, 0);
			for (CCGint s = 0; s < ns; ++s) {
				CCGdouble u = static_cast<CCGdouble>(i + GetDBRand()) / static_cast<CCGdouble>(nx);
				CCGdouble v = static_cast<CCGdouble>(j + GetDBRand()) / static_cast<CCGdouble>(ny);

				CCGRay rRay = cCamera.GetRay(u, v);
				cColor += Color(rRay, pWorld, 0);
			}
			cColor /= static_cast<CCGdouble>(ns);
			cColor = CCGColor3D(sqrt(cColor[0]), sqrt(cColor[1]), sqrt(cColor[2]));
			CCGint ir = static_cast<CCGint>(255.99 * cColor[0]);
			CCGint ig = static_cast<CCGint>(255.99 * cColor[1]);
			CCGint ib = static_cast<CCGint>(255.99 * cColor[2]);
			
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	std::cerr << "\nDone.\n";
}