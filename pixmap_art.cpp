#include <iostream>
#include "ppm_image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
	ppm_image image;
	image.load("art/ppm/birds-ascii.ppm");
	cout << "loaded image with width and height: " << image.width() << " " << image.height() << endl;

	ppm_pixel old_color = { 0,0,0 };
	ppm_pixel new_color = { 96,147,203 };
	ppm_image change_bird = image.change_color(old_color, new_color);
	change_bird.save("../changed-bird.ppm");

	ppm_image image2;
	image2.load("art/ppm/cloud-ascii.ppm");
	cout << "loaded image with width and height: " << image2.width() << " " << image2.height() << endl;

	ppm_image tiled = image2.horizontal_tiles(3);
	ppm_image tiled_resize = tiled.resize(image.width(), (image.height()/2));
	ppm_image background = tiled_resize.combine_rows(tiled_resize);
	background.save("../tiled-bckgrnd.ppm");

	ppm_image combine = change_bird.replace_nonwhite(background);
	combine.save("../art1-birds-and-tiled-clouds.ppm");

	ppm_image image3;
	image3.load("art/ppm/eye-ascii.ppm");
	cout << "loaded image with width and height: " << image3.width() << " " << image3.height() << endl;

	ppm_image image4;
	image4.load("art/ppm/lights-ascii.ppm");
	cout << "loaded image with width and height: " << image4.width() << " " << image4.height() << endl;
	ppm_image resized = image4.resize(image3.width(), image3.height());
	ppm_image swirl = resized.swirl_colors();
	swirl.save("../swirl.ppm");

	ppm_image invert = image3.invert_color();
	invert.save("../inverted.ppm");

	ppm_image blend = invert.alpha_blend(swirl, 0.6f);
	blend.save("../art2-eyelights-invert-swirl-blend-0.6.ppm");
}

