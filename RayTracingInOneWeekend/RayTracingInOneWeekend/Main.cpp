#include <iostream>
#include <fstream>
#include <chrono>

#include "Ray.h"

using namespace std;

glm::vec3 GetRayColor(const Ray& r)
{
	glm::vec3 unitVector =  glm::normalize(r.GetDirection());
	auto a = 0.5f * (unitVector.y + 1.0f);
	return (1.0f - a) * glm::vec3(1.0, 1.0, 1.0) + a * glm::vec3(0.5, 0.7, 1.0);
}
void WriteColor(fstream& f, glm::vec3 color)
{
	int ir															= static_cast<int>(255.0f * color.r);
	int ig															= static_cast<int>(255.0f * color.g);
	int ib															= static_cast<int>(255.0f * color.b);
	f << ir << " " << ig << " " << ib << endl;
	//f << color.r << " " << color.g << " " << color.b << endl;
}
int main()
{
	auto startTime													= chrono::high_resolution_clock::now();

	#pragma region Image
	float mAspectRatio												= 16.0f / 9;
	int imgWidth													= 400;
	int imgHeight													= static_cast<int>(imgWidth / mAspectRatio);
	if (imgHeight < 1)
		imgWidth = 1;
	#pragma endregion
	#pragma region Camera
	auto focalLength												= 1.0f;
	auto viewportHeight												= 2.0f;
	auto viewportWeight												= viewportHeight * imgWidth / imgHeight;
	auto cameraCenter												= glm::vec3(0, 0, 0);

	// Viewport UV
	// (0, 0) ============= (1, 0)
	//   ||                   ||
	//   ||                   ||
	//   ||                   ||
	// (0, 1) ============= (1, 1)
	auto viewportU													= glm::vec3(viewportWeight, 0, 0);
	auto viewportY													= glm::vec3(0, -viewportHeight, 0);		// Because y get larger, it decrease

	// Get Delta
	auto pixelDeltaU												= viewportU / static_cast<float>(imgWidth);
	auto pixelDeltaY												= viewportY / static_cast<float>(imgHeight);

	// Positive of coordinate z is right
	// Positive of coordinate y is up
	// Negative of coordinate z is viewing direction 
	auto viewportUpperLeft											= cameraCenter - glm::vec3(0, 0, focalLength) - viewportU / 2.0f - viewportY / 2.0f;
	auto pixel00Loc													= viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaY);	// This is because we will try to raycast for camera center to the topleft of pixel which has a offset from image coordinate space to camera space
	#pragma endregion
	#pragma region Render
	fstream file;
	file.open("result.ppm", ios::out | ios::trunc);
	file << "P3" << endl << imgWidth << " " << imgHeight << endl << "255" << endl;
	for (int y = 0; y < imgHeight; y++)
	{
		cout << "Scanlines remaining: " << (imgHeight - y) << endl;
		for (int x = 0; x < imgWidth; x++)
		{
			auto pixel = pixel00Loc + pixelDeltaU * static_cast<float>(x) + pixelDeltaY * static_cast<float>(y);
			Ray ray(cameraCenter, pixel - cameraCenter);
			WriteColor(file, GetRayColor(ray));
		}
	}
	cout << "Done" << endl;
	file.close();
	#pragma endregion
	auto endTime													= chrono::high_resolution_clock::now();
	cout << "Duration: " << chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count() << " ms" << endl;
	system("PAUSE");
	return 0;
}