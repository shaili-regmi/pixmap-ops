#include <iostream>
#include "ppm_image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
	ppm_image image;
	image.load("art/ppm/lights-ascii.ppm");

	cout << "loaded image with width and height: " << image.width() << " " << image.height() << endl;

	ppm_image swirl = image.swirl_colors();
	swirl.save("art/swirl.ppm");

	ppm_image image2;
	image2.load("art/ppm/eye-ascii.ppm");
	cout << "loaded image with width and height: " << image2.width() << " " << image2.height() << endl;

	ppm_image swirl2 = image2.swirl_colors();

	ppm_image light_resize = swirl.resize(image2.width(), image2.height());
	ppm_image blend = light_resize.alpha_blend(swirl2, 0.3f);
	blend.save("art/eyelights-blend-0.3(1).ppm");
}

