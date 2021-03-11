# pixmap-ops

Image manipulation demos based on the PPM image format.

TODO: Add a representative image for your project here

![art1](https://github.com/shaili-regmi/pixmap-ops/blob/main/art1-birds-and-tiled-clouds_png.png)
![art2](https://github.com/shaili-regmi/pixmap-ops/blob/main/art2-eyelights-invert-swirl-blend-0.6_png.png)

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake -G "Visual Studio 16 2019" ..
pixmap-ops/build $ start Pixmap-Ops.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
pixmap-ops/build $ ../bin/Debug/pixmap_test
pixmap-ops/build $ ../bin/Debug/pixmap_art
```

*macOS*

Open terminal to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake ..
pixmap-ops/build $ make
```

To run each program from build, you would type

```
pixmap-ops/build $ ../bin/pixmap_test
pixmap-ops/build $ ../bin/pixmap_art
```

## Image operators

TODO: Document the features of your PPM image class here. Include example images.

*Original images:*

![bird](https://github.com/shaili-regmi/pixmap-ops/blob/main/birds.png)
![cloud](https://github.com/shaili-regmi/pixmap-ops/blob/main/cloud.png)
![lights](https://github.com/shaili-regmi/pixmap-ops/blob/main/lights.jpg)
![eye](https://github.com/shaili-regmi/pixmap-ops/blob/main/eye.png)

*Extra functions implemented:*

ppm_image swirl_colors() const;
Returns a copy of this image with the colors rotated. 
The red channel becomes the green channel, the green becomes blue, and the blue becomes red.
Example: 
![light-swirled](https://github.com/shaili-regmi/pixmap-ops/blob/main/swirl_png.png)   

ppm_image invert_color() const;
Returns a copy of this image with the colors inverted
Example:
![inverted](https://github.com/shaili-regmi/pixmap-ops/blob/main/inverted_png.png)  

ppm_image horizontal_tiles(int number) const;    
Returns a horixontally tiled copy of the image with the same size and the given number of tiles.
Clamps the ends if needed.

ppm_image combine_rows(ppm_image image) const;
Returns a copy of this image stitched to another given image in the row-direction (height)
     
Example: horizontal_tiles and combine_rows are used to generate this image from the one original cloud.
![tiled and combined](https://github.com/shaili-regmi/pixmap-ops/blob/main/tiled-bckgrnd_png.png)
     
ppm_image replace_nonwhite(ppm_image background) const;
Returns a copy of this image with all non-white portions placed over given background picture
Assumes that the two images are the same size.
Example:
![replace_nonwhite](https://github.com/shaili-regmi/pixmap-ops/blob/main/replace_nonwhite_png.png)
    
ppm_image change_color(ppm_pixel color_old, ppm_pixel color_new) const;
Returns a copy of this image with all of the pixels with the given color_old replaced by the given color_new
Example:
![changed bird](https://github.com/shaili-regmi/pixmap-ops/blob/main/changed-bird_png.png)
  
## Results

TODO: Show artworks using your class

*Art1*

![art1](https://github.com/shaili-regmi/pixmap-ops/blob/main/art1-birds-and-tiled-clouds_png.png)
I made a tiled version of the cloud image using the horizontal_tiles function to make 3 clouds horizontally then used the
combine_rows function to combine this image with itself to create 3 more clouds below the first 3. 
I used that as the background for the birds by using the replace_nonwhite function by replacing all the
white areas of the bird image with the background. I didn't like the way the two colors looked together so 
I used the change_color function to change the color of the birds to one of the blue colors from the cloud image.

*Art2*

![art2](https://github.com/shaili-regmi/pixmap-ops/blob/main/art2-eyelights-invert-swirl-blend-0.6_png.png)
I wanted to blend the eye and the lights images together, but did not like the way the colors looked together. 
So, I inverted the color of the eye image and swirled the r,g,b channels of the lights image before blending.

