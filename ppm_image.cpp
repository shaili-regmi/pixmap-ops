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

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            old_row = floor((((double)i) / (h - (1))) * (rows - (1)));
            old_column = floor((((double)j) / (w - (1))) * (columns - (1)));
            ppm_pixel pixel_color = image_array[old_row][old_column];
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
   ppm_image result;
   return result;
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
   ppm_image result;
   return result;
}

ppm_image ppm_image::grayscale() const
{
    ppm_image result(columns, rows);
   
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            ppm_pixel old_color = image_array[i][j];
            double weighted_avg = (0.3*old_color.r) + (0.59*old_color.g) + (0.11*old_color.b);
            ppm_pixel new_color = { weighted_avg, weighted_avg, weighted_avg };
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
   return columns;
}

int ppm_image::width() const
{
   return rows;
}

void ppm_image::clear()
{
    delete[] image_array;
    /*
    for (int i = 0; i < rows; i++)
    {
        delete[] image_array[i];
    }
    delete[] image_array;*/
    image_array = NULL;
    
}
