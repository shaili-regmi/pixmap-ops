#include "ppm_image.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <math.h>

#define FORMAT "P3" // Image file format
#define MAX_VALUE 255 // Maximum color value

using namespace agl;
using namespace std;

ppm_image::ppm_image() // default constructor
{
    columns = 0;
    rows = 0;
}

ppm_image::ppm_image(int w, int h) // constructor
{
    columns = w;
    rows = h;
    
    // Creating a 2D array (array of arrays) to store the image (deleted in destructor)
    image_array = new ppm_pixel * [rows];
    for (int i = 0; i < rows; i++)
    {
        image_array[i] = new ppm_pixel[columns];
    }
}

ppm_image::ppm_image(const ppm_image& orig) // copy constructor
{
    clear();
    columns = orig.columns;
    rows = orig.rows;
    
    image_array = new ppm_pixel * [rows];
    for (int i = 0; i < rows; i++)
    {
        image_array[i] = new ppm_pixel[columns];
        for (int j = 0; j < columns; j++)
        {
            image_array[i][j] = orig.image_array[i][j];
        }
    }
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{
   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }

   // todo: your code here
   clear();
   columns = orig.columns;
   rows = orig.rows;
   
   image_array = new ppm_pixel * [rows];
   for (int i = 0; i < rows; i++)
   {
       image_array[i] = new ppm_pixel[columns];
       for (int j = 0; j < columns; j++)
       {
           image_array[i][j] = orig.image_array[i][j];
       }
   }
   return *this;   
}

ppm_image::~ppm_image()
{
    clear();
}

bool ppm_image::load(const std::string& filename)
{
    ifstream file(filename);

    if (!file)
    {
        return false;
    }

    string format, max_color; // used below to skip the format and max color value lines in the file 

    file >> format >> columns >> rows >> max_color;
    
    // Creating a 2D array (array of arrays) to store the image (deleted in destructor)
    image_array = new ppm_pixel* [rows];
    for (int i = 0; i < rows; i++)
    {
        image_array[i] = new ppm_pixel[columns];
    }
    
    // Variables temporarily used to store the pixel colors read from the file
    int red;
    int green;
    int blue;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            file >> red >> green >> blue;
            image_array[i][j].r = (unsigned char)red;
            image_array[i][j].g = (unsigned char)green;
            image_array[i][j].b = (unsigned char)blue;
        }
    }
    file.close();
    return true;
}

bool ppm_image::save(const std::string& filename) const
{

    ofstream file(filename);
    if (!file)
    {
        return false;
    }

    file << FORMAT << endl;
    file << columns << " " << rows << endl;
    file << MAX_VALUE << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            file << (int)image_array[i][j].r << " " << (int)image_array[i][j].g << " " << (int)image_array[i][j].b << endl;
        }
    }

    file.close();
    return true;
}

 ppm_image ppm_image::resize(int w, int h) const
{
    ppm_image result(w, h);
    int old_row, old_column;
    ppm_pixel pixel_color;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            old_row = floor((((double)i) / (h - (1))) * (rows - (1)));
            old_column = floor((((double)j) / (w - (1))) * (columns - (1)));
            pixel_color = image_array[old_row][old_column];
            result.image_array[i][j] = pixel_color;
        }
    }
    return result;
}

ppm_image ppm_image::flip_horizontal() const
{
    ppm_image result(columns, rows);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            result.image_array[i][j] = image_array[(rows-1) - i][j];
            result.image_array[(rows-1) - i][j] = image_array[i][j];
        }
    }
    return result;
}

ppm_image ppm_image::subimage(int startx, int starty, int w, int h) const
{
    ppm_image result(w, h);

    // indices for subimage
    int i1 = 0;
    int j1 = 0; 
    for (int i = startx; i < (startx + h); i++)
    {
        for (int j = starty; j < (starty + w); j++)
        {
            result.image_array[i1][j1] = image_array[i][j];
            j1++;
        }
        j1 = 0;
        i1++;
    }
    return result;
}

void ppm_image::replace(const ppm_image& image, int startx, int starty)
{
    // Indices for given image
    int i1 = 0;
    int j1 = 0;

    // Boundaries in case clamping is needed
    int bound_x;
    int bound_y;
    bound_x = (startx + image.rows < rows) ? (startx + image.rows) : rows;
    bound_y = (starty + image.columns < columns) ? (starty + image.columns) : columns;

    for (int i = startx; i < bound_x; i++)
    {
        for (int j = starty; j < bound_y; j++)
        {
            image_array[i][j] = image.image_array[i1][j1];
            j1++;
        }
        j1 = 0;
        i1++;
    }
}

ppm_image ppm_image::alpha_blend(const ppm_image& other, float alpha) const
{
    // Apply the following calculation to the pixels in 
    // our image and the given image:
    //    this.pixels = this.pixels * (1-alpha) + other.pixel * alpha
    // Can assume that the two images are the same size
    ppm_image result(columns, rows);
    ppm_pixel this_color;
    ppm_pixel other_color;
    float r_new;
    float g_new;
    float b_new;
    ppm_pixel new_color;


    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            this_color = image_array[i][j];
            other_color = other.image_array[i][j];
            r_new = floor((((float)this_color.r) * (1 - alpha)) + (((float)other_color.r) * alpha));
            g_new = floor((((float)this_color.g) * (1 - alpha)) + (((float)other_color.g) * alpha));
            b_new = floor((((float)this_color.b) * (1 - alpha)) + (((float)other_color.b) * alpha));
            new_color = { ((unsigned char)r_new), ((unsigned char)g_new), ((unsigned char)b_new) };
            result.image_array[i][j] = new_color;
        }
    }
    return result;
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
    ppm_image result(columns, rows);
    ppm_pixel old_color;
    float r_correction;
    float g_correction;
    float b_correction;
    ppm_pixel new_color;

    // variables for intermediate calculations
    float base_r, base_b, base_g;
    float power = 1.0f / gamma;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            old_color = image_array[i][j];
            base_r = (((float)old_color.r) / ((float)MAX_VALUE));
            base_g = (((float)old_color.g) / ((float)MAX_VALUE));
            base_b = (((float)old_color.b) / ((float)MAX_VALUE));
            r_correction = floor((MAX_VALUE * pow(base_r, power)));
            g_correction = floor((MAX_VALUE * pow(base_g, power)));
            b_correction = floor((MAX_VALUE * pow(base_b, power)));
            new_color = { ((unsigned char)r_correction), ((unsigned char)g_correction), ((unsigned char)b_correction) };
            result.image_array[i][j] = new_color;
        }
    }
    return result;
}

ppm_image ppm_image::grayscale() const
{
    ppm_image result(columns, rows);
    ppm_pixel old_color;
    double weighted_avg;
    ppm_pixel new_color;
   
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            old_color = image_array[i][j];
            weighted_avg = floor((0.3*old_color.r) + (0.59*old_color.g) + (0.11*old_color.b));
            new_color = { ((unsigned char)weighted_avg), ((unsigned char)weighted_avg), ((unsigned char)weighted_avg) };
            result.image_array[i][j] = new_color;
        }
    }
    return result;
}

ppm_image ppm_image::swirl_colors() const
{
    ppm_image result(columns, rows);
    ppm_pixel old_color;
    ppm_pixel new_color;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            old_color = image_array[i][j];
            new_color = { old_color.g, old_color.b, old_color.r };
            result.image_array[i][j] = new_color;
        }
    }
    return result;
}

ppm_pixel ppm_image::get(int row, int col) const
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (i == row && j == col)
            {
                red = image_array[i][j].r;
                green = image_array[i][j].g;
                blue = image_array[i][j].b;

                return ppm_pixel {red, green, blue};
            }
        }
    }
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (i == row && j == col)
            {
                image_array[i][j] = c;
            }
        }
    }
}

int ppm_image::height() const
{
   return rows;
}

int ppm_image::width() const
{
   return columns;
}

void ppm_image::clear()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] image_array[i];
    }
    delete[] image_array;

    image_array = NULL;  
}
