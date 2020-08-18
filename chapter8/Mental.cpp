#include "CGMaterial.h"
#include "CGRay.h"
#include "hitable.h"
#include "CGCamera.h"
#include <ctime>

using namespace CCG;

void Mental();

int main() {
	Mental();
	return 0;
}

void Mental() {
	srand((unsigned)time(NULL));
	CCGint nx = 1000;
	CCGint ny = 600;
	CCGint ns = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	CCGHitable *list[4];
	shared_ptr<CCGMaterial> m(new CCGLambertian(CCGVec3(0.8, 0.3, 0.3)));
	list[0] = new CCGSphere(CCGVec3(0, 0, -1), 0.5, m);
	shared_ptr<CCGMaterial> m1(new CCGLambertian(CCGVec3(0.8, 0.8, 0.0)));
	list[1] = new CCGSphere(CCGVec3(0, -100.5, -1), 100, m1);
	shared_ptr<CCGMaterial> m2(new CCGMental(CCGVec3(0.8, 0.6, 0.2), 0.5));
	list[2] = new CCGSphere(CCGVec3(1, 0, -1), 0.5, m2);
	shared_ptr<CCGMaterial> m3(new CCGMental(CCGVec3(0.8, 0.8, 0.8), 1.5));
	list[3] = new CCGSphere(CCGVec3(-1, 0, -1), 0.5, m3);
	CCGHitable *pHWorld = new CCGHitableList(list, 4);
	CCGCamera camera;

	for (CCGint j = ny - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining : " << j << " " << std::flush;
		for (CCGint i = 0; i < nx; ++i) {
			CCGVec3 col(0, 0, 0);
			for (CCGint s = 0; s < ns; ++s) {
				CCGdouble u = static_cast<CCGdouble>(i + GetRand()) / static_cast<CCGdouble>(nx);
				CCGdouble v = static_cast<CCGdouble>(j + GetRand()) / static_cast<CCGdouble>(ny);

				CCGRay Ray = camera.GetRay(u, v);
				col += Color(Ray, pHWorld, 0);
			}
			col /= static_cast<CCGdouble>(ns);
			col = CCGVec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			CCGint ir = static_cast<CCGint>(255.99 * col[0]);
			CCGint ig = static_cast<CCGint>(255.99 * col[1]);
			CCGint ib = static_cast<CCGint>(255.99 * col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	std::cerr << "\nDone.\n";
}