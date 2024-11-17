#include <iostream>
#include <fstream>
#include <chrono>

#include "Ray.h"

using namespace std;

double hitSphere(const glm::dvec3& pCenter, double pRadius, const Ray& pRay)
{
	// Circle Formula check if it's inside							=>  x^2 + y^2 + z^2 <= r^2
	// Point Ray 													=> pRayCenter + pRay.GetDirection() * t
	// Center 														=> pCenter
	//
	// check b^2 - 4ac >= 0
	glm::dvec3 rayToCenter 											= pCenter - pRay.GetOrigin();
	double a 														= glm::dot(pRay.GetDirection(), pRay.GetDirection());
	double b 														= -2.0 * glm::dot(pRay.GetDirection(), rayToCenter);
	double c 														= glm::dot(rayToCenter, rayToCenter) - pRadius * pRadius;
	double discriminant 											= b * b - 4 * a * c;					// 判斷式
	if (discriminant < 0)
		return -1;												
	return  (-b - sqrt(discriminant)) / (2 * a);
}

glm::dvec3 GetRayColor(const Ray& r)
{
	auto sphereCenter 												= glm::dvec3(0, 0, -1);
	auto t 															= hitSphere(sphereCenter, 0.5, r);
	if (t > 0) 
	{
		glm::dvec3 normal 											= glm::normalize(r.At(t) - sphereCenter);
		return 0.5 * (normal + glm::dvec3(1, 1, 1));
	}

	glm::dvec3 unitVector =  glm::normalize(r.GetDirection());
	auto a = 0.5f * (unitVector.y + 1.0f);
	return (1.0f - a) * glm::dvec3(1.0, 1.0, 1.0) + a * glm::dvec3(0.5, 0.7, 1.0);
}
void WriteColor(fstream& f, glm::dvec3 color)
{
	int ir															= static_cast<int>(255.0 * color.r);
	int ig															= static_cast<int>(255.0 * color.g);
	int ib															= static_cast<int>(255.0 * color.b);
	f << ir << " " << ig << " " << ib << endl;
	//f << color.r << " " << color.g << " " << color.b << endl;
}
int main()
{
	auto startTime													= chrono::high_resolution_clock::now();

	#pragma region Image
	double mAspectRatio												= 16.0 / 9;
	int imgWidth													= 400;
	int imgHeight													= static_cast<int>(imgWidth / mAspectRatio);
	if (imgHeight < 1)
		imgWidth = 1;
	#pragma endregion
	#pragma region Camera
	auto focalLength												= 1.0;
	auto viewportHeight												= 2.0;
	auto viewportWeight												= viewportHeight * imgWidth / imgHeight;
	auto cameraCenter												= glm::dvec3(0, 0, 0);

	// Viewport UV
	// (0, 0) ============= (1, 0)
	//   ||                   ||
	//   ||                   ||
	//   ||                   ||
	// (0, 1) ============= (1, 1)
	auto viewportU													= glm::dvec3(viewportWeight, 0, 0);
	auto viewportY													= glm::dvec3(0, -viewportHeight, 0);		// Because y get larger, it decrease

	// Get Delta
	auto pixelDeltaU												= viewportU / static_cast<double>(imgWidth);
	auto pixelDeltaY												= viewportY / static_cast<double>(imgHeight);

	// Positive of coordinate z is right
	// Positive of coordinate y is up
	// Negative of coordinate z is viewing direction 
	auto viewportUpperLeft											= cameraCenter - glm::dvec3(0, 0, focalLength) - viewportU / 2.0 - viewportY / 2.0;
	auto pixel00Loc													= viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaY);	// This is because we will try to raycast for camera center to the topleft of pixel which has a offset from image coordinate space to camera space
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
			auto pixel = pixel00Loc + pixelDeltaU * static_cast<double>(x) + pixelDeltaY * static_cast<double>(y);
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