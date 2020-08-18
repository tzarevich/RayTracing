#include "CCGDefs.h"
#include "CGCamera.h"
#include "CGRay.h"
#include "hitable.h"
#include "Vec3.h"
#include <cstdlib>
#include <ctime>
#include <random>

using namespace CCG;

void DifMar();

int main() {
	DifMar();
	return 0;
}

void DifMar() {
	srand((unsigned)time(NULL));
	CCGint nx = 200;
	CCGint ny = 100;
	CCGint ns = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	CCGHitable *list[2];
	list[0] = new CCGSphere(CCGVec3(0, 0, -1), 0.5);
	list[1] = new CCGSphere(CCGVec3(0, -100.5, -1), 100);
	CCGHitable *world = new CCGHitableList(list, 2);
	CCGCamera camera;

	for (CCGint j = ny - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
		for (CCGint i = 0; i < nx; ++i) {
			CCGVec3 col(0, 0, 0);
			for (CCGint s = 0; s < ns; ++s) {
				CCGdouble u = static_cast<CCGdouble>(i + GetRand()) / static_cast<CCGdouble>(nx);
				CCGdouble v = static_cast<CCGdouble>(j + GetRand()) / static_cast<CCGdouble>(ny);

				CCGRay r = camera.GetRay(u, v);
				col += Color(r, world);
			}
			col /= static_cast<CCGdouble>(ns);
			//这里进行gamma校正，取gamma2
			col = CCGVec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
			CCGint ir = static_cast<CCGint>(255.99 * col[0]);
			CCGint ig = static_cast<CCGint>(255.99 * col[1]);
			CCGint ib = static_cast<CCGint>(255.99 * col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	std::cerr << "\nDone\n";
}