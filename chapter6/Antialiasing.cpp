#include "CCGDefs.h"
#include "CGCamera.h"
#include "CGRay.h"
#include "hitable.h"
#include "Vec3.h"
#include <cstdlib>
#include <ctime>

using namespace CCG;

void Antialias();

int main() {
	Antialias();
	return 0;
}

void Antialias() {
	srand((unsigned)time(NULL));
	CCGint nx = 200;
	CCGint ny = 100;
	CCGint nz = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	CCGCamera camera;
	CCGHitable *list[2];
	list[0] = new CCGSphere(CCGVec3(0, 0, -1), 0.5);
	list[1] = new CCGSphere(CCGVec3(0, -100.5, -1), 100);
	CCGHitable *world = new CCGHitableList(list, 2);

	for (CCGint j = ny - 1; j >= 0; --j) {
		//std::cout << GetRand() << std::endl;
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (CCGint i = 0; i < nx; ++i) {
			CCGVec3 col(0, 0, 0);
			//这个函数随机取某一像素点周围的一百个样本点并求其颜色总和
			for (CCGint z = 0; z < nz; ++z) {
				CCGdouble u = (static_cast<CCGdouble>(i) + GetRand()) / static_cast<CCGdouble>(nx);
				CCGdouble v = (static_cast<CCGdouble>(j) + GetRand()) / static_cast<CCGdouble>(ny);

				CCGRay r = camera.GetRay(u, v);
				CCGVec3 p = r.PointAtParam(2.0);
				col += Color(r, world);
			}
			//然乎取平均值
			col /= static_cast<CCGdouble>(nz);
			CCGint ir = static_cast<CCGint>(255.99 * col[0]);
			CCGint ig = static_cast<CCGint>(255.99 * col[1]);
			CCGint ib = static_cast<CCGint>(255.99 * col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	std::cerr << "\nDone.\n";
}