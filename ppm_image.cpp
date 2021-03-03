#include "ppm_image.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

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
}

ppm_image::ppm_image(const ppm_image& orig) // copy constructor
{
    columns = orig.columns;
    rows = orig.rows;
    image_array = orig.image_array;
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{
   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }

   // todo: your code here
   columns = orig.columns;
   rows = orig.rows;
   image_array = orig.image_array;

   return *this;   
}

ppm_image::~ppm_image()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] image_array[i];
    }
    delete[] image_array;
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
            //cout << "int red: " << red << ", int green: " << green << ", int blue: " << blue << endl;
            image_array[i][j].r = (unsigned char)red;
            image_array[i][j].g = (unsigned char)green;
            image_array[i][j].b = (unsigned char)blue;
        }
    }
    file.close();
    /*
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << image_array[i][j].r << " " << image_array[i][j].g << " " << image_array[i][j].b << endl;
        }
    }
    */
    return true;
}

bool ppm_image::save(const std::string& filename) const
{
    try
    {
        ofstream file(filename);
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
    } catch (...) 
    {
        return false;
    }
}

 ppm_image ppm_image::resize(int w, int h) const
{
    ppm_image result;
    return result;
}

ppm_image ppm_image::flip_horizontal() const
{
    ppm_image result;
    return result;
}

ppm_image ppm_image::subimage(int startx, int starty, int w, int h) const
{
    ppm_image result;
    return result;
}

void ppm_image::replace(const ppm_image& image, int startx, int starty)
{
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
   ppm_image result;
   return result;
}

ppm_pixel ppm_image::get(int row, int col) const
{
   return ppm_pixel{ 0,0,0 };
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
}

int ppm_image::height() const
{
   return columns;
}

int ppm_image::width() const
{
   return rows;
}
