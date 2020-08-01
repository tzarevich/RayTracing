#include <iostream>
#include <fstream>

using namespace std;

void writeIntoPPM();

int main() {
	writeIntoPPM();
	return 0;
}

void writeIntoPPM() {
	ofstream ofile("F:\\VS2013\\MyCppSpace\\OpenGL\\RayTracing\\OutputImage\\first.ppm");
	if (ofile.is_open()){
		cout << " open \n";
		const int image_width = 256;
		const int image_height = 256;

		cout << "P3\n" << image_width << " " << image_height << "\n255\n";
		ofile << "P3\n" << image_height << " " << image_height << "\n255\n";

		for (int j = image_height - 1; j >= 0; --j){
			for (int i = 0; i < image_width; ++i){
				auto r = double(i) / (image_width - 1);
				auto g = double(j) / (image_height - 1);
				auto b = 0.25;

				int ir = static_cast<int>(255.999 * r);
				int ig = static_cast<int>(255.999 * g);
				int ib = static_cast<int>(255.999 * b);

				cout << ir << " " << ig << " " << ib << "\n";
				ofile << ir << " " << ig << " " << ib << "\n";
			}
		}

		ofile.close();

	}
	else {
		cout << "open file failed.\n";
	}
}