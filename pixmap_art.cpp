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
	change_bird.save("art/changed-bird.ppm");

	ppm_image image2;
	image2.load("art/ppm/cloud-ascii.ppm");
	cout << "loaded image with width and height: " << image2.width() << " " << image2.height() << endl;

	/*
	//ppm_pixel old_color = { 96,147,203 };
	ppm_pixel new_color = { 0,0,0 };
	ppm_image change = image2.change_non_gray_white_black(new_color);
	change.save("art/changed-cloud.ppm");
	*/
	
	ppm_image tiled = image2.horizontal_tiles(3);
	ppm_image tiled_resize = tiled.resize(image.width(), image.height());
	tiled_resize.save("art/tiled-bckgrnd.ppm");

	//ppm_image  invert_background = tiled_resize.invert_color();

	//ppm_image swirl = light_resize.swirl_colors();
	//ppm_image tiled = swirl.horizontal_tiles(3);
	//tiled.save("art/swirl-tiled.ppm");

	ppm_image combine = change_bird.replace_nonwhite(tiled_resize);
	combine.save("art/birds-and-tiled-clouds.ppm");
	//ppm_image blend = image.alpha_blend(tiled_resize, 0.4f);
	//blend.save("art/cloud-birds-blend-0.6.ppm");

	//ppm_image invert = image.invert_color();
	//invert.save("art/inverted.ppm");

	/*
	ppm_image image2;
	image2.load("art/ppm/cloud-ascii.ppm");
	cout << "loaded image with width and height: " << image2.width() << " " << image2.height() << endl;

	ppm_image light_resize = image.resize(image2.width(), image2.height());

	ppm_image swirl = light_resize.swirl_colors();
	ppm_image tiled = swirl.horizontal_tiles(3);
	tiled.save("art/swirl-tiled.ppm");

	ppm_image blend = image2.alpha_blend(tiled, 0.6f);
	blend.save("art/eyelights-tiled-swirl-blend-0.6.ppm");

	/*
	ppm_image image2;
	image2.load("art/ppm/lights-ascii.ppm");
	cout << "loaded image with width and height: " << image2.width() << " " << image2.height() << endl;


	//ppm_image eye_sub = image.subimage(100, 250, 200, 300);
	//eye_sub.save("art/eye-sub.ppm");

	ppm_image swirl = image.swirl_colors();
	swirl.save("art/swirl.ppm");

	ppm_image image2;
	image2.load("art/ppm/eye-ascii.ppm");
	cout << "loaded image with width and height: " << image2.width() << " " << image2.height() << endl;

	ppm_image swirl2 = image2.swirl_colors();

	ppm_image light_resize = swirl.resize(image2.width(), image2.height());
	ppm_image blend = light_resize.alpha_blend(swirl2, 0.3f);
	blend.save("art/eyelights-blend-0.3(1).ppm");
	*/
}

