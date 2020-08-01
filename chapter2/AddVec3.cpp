#include <iostream>
#include "Vec3.h"

void produceImage();

CCGint main() {
	produceImage();
	return 0;
}

void produceImage() {
	CCGint nx = 200;
	CCGint ny = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	for (CCGint j = ny - 1; j >= 0; --j) {
		for (CCGint i = 0; i < nx; ++i) {
			CCG::CCGVec3 col(CCGdouble(i) / CCGdouble(nx), CCGdouble(j) / CCGdouble(ny), 0.2);
			CCGint ir = static_cast<CCGint>(255.99 * col[0]);
			CCGint ig = static_cast<CCGint>(255.99 * col[1]);
			CCGint ib = static_cast<CCGint>(255.99 * col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}