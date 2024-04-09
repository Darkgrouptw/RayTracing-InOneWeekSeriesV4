#include <iostream>
#include <fstream>

#include "Ray.h"

using namespace std;


void main()
{
	#pragma region Image
	double mAspectRatio = 16.0 / 9;
	int imgWidth = 400;
	int imgHeight = static_cast<int>(imgWidth / mAspectRatio);
	if (imgHeight < 1) imgWidth = 1;
	#pragma endregion
	#pragma region Camera
	auto focalLength = 1.0;
	auto viewportHeight = 2.0;
	auto viewportWeight = viewportHeight * imgWidth / imgHeight;
	auto cameraCenter = vec3(0, 0, 0);
	#pragma endregion

	fstream file;
	file.open("result.ppm", ios::out | ios::trunc);
	file << "P3" << endl << imgWidth << " " << imgHeight << endl << "255" << endl;
	for (int y = 0; y < imgHeight; y++)
	{
		clog << "Scanlines remaining: " << (imgHeight - y) << endl << flush;
		for (int x = 0; x < imgWidth; x++)
		{
			auto r = double(x) / (imgWidth - 1);
			auto g = double(y) / (imgHeight - 1);
			auto b = 0;

			int ir = static_cast<int>(255.0 * r);
			int ig = static_cast<int>(255.0 * g);
			int ib = static_cast<int>(255.0 * b);

			file << ir << " " << ig << " " << ib << endl;
		}
	}
	clog << "Done" << endl;
	file.close();
}