#include "CCGDefs.h"
#include "CGRay.h"
#include "Vec3.h"
#include "hitable.h"

using namespace CCG;

void Normals();

int main() {
	Normals();
	return 0;
}


void Normals() {
	CCGint nx = 200;
	CCGint ny = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	CCGVec3 leftCorner(-2, -1, -1);
	CCGVec3 horizontial(4, 0, 0);
	CCGVec3 vertical(0, 2, 0);
	CCGVec3 origin(0, 0, 0);

	CCGHitable *list[2];
	list[0] = new CCGSphere(CCGVec3(0, 0, -1), 0.5);
	list[1] = new CCGSphere(CCGVec3(0, -100.5, -1), 100);
	CCGHitable *world = new CCGHitableList(list, 2);

	for (CCGint j = ny - 1; j >= 0; --j) {
		for (CCGint i = 0; i < nx; ++i) {
			CCGdouble u = static_cast<CCGdouble>(i) / static_cast<CCGdouble>(nx);
			CCGdouble v = static_cast<CCGdouble>(j) / static_cast<CCGdouble>(ny);

			CCGRay r(origin, leftCorner + u*horizontial + v*vertical);
			CCGVec3 p = r.PointAtParam(2.0);
			CCGVec3 col = Color(r, world);

			CCGint ir = static_cast<CCGint>(255.99 * col[0]);
			CCGint ig = static_cast<CCGint>(255.99 * col[1]);
			CCGint ib = static_cast<CCGint>(255.99 * col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}


/*
void Normals() {
	CCGint nx = 200;
	CCGint ny = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	CCGVec3 leftCorner(-2, -1, -1);
	CCGVec3 horizontial(4, 0, 0);
	CCGVec3 vertical(0, 2, 0);
	CCGVec3 origin(0, 0, 0);

	for (CCGint j = ny - 1; j >= 0; --j) {
		for (CCGint i = 0; i < nx; ++i) {
			CCGdouble u = static_cast<CCGdouble>(i) / static_cast<CCGdouble>(nx);
			CCGdouble v = static_cast<CCGdouble>(j) / static_cast<CCGdouble>(ny);
			
			CCGRay r(origin, leftCorner + u*horizontial + v*vertical);
			CCGVec3 col = Color(r);

			CCGint ir = static_cast<CCGint>(255.99 * col[0]);
			CCGint ig = static_cast<CCGint>(255.99 * col[1]);
			CCGint ib = static_cast<CCGint>(255.99 * col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
*/
