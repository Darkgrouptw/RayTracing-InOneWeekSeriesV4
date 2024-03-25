#include <iostream>
#include <fstream>

using namespace std;

const int mIMGWidth = 256;
const int mIMGHeight = 256;

void main()
{
	fstream file;
	file.open("result.ppm", ios::out | ios::trunc);
	file << "P3" << endl << mIMGWidth << " " << mIMGHeight << endl << "255" << endl;
	for (int y = 0; y < mIMGHeight; y++)
	{
		clog << "Scanlines remaining: " << (mIMGHeight - y) << endl << flush;
		for (int x = 0; x < mIMGWidth; x++)
		{
			auto r = double(x) / (mIMGWidth - 1);
			auto g = double(y) / (mIMGHeight - 1);
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