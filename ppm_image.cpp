#include "ppm_image.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace agl;
using namespace std;

ppm_image::ppm_image() 
{
    columns = 0;
    rows = 0;
}

ppm_image::ppm_image(int w, int h) 
{
}

ppm_image::ppm_image(const ppm_image& orig)
{
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{
   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }

   // todo: your code here

   return *this;   
}

ppm_image::~ppm_image()
{
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
  
    image_array = new ppm_pixel[(rows*columns)];
    for (int i = 0; i < (rows * columns); i++)
    {
        file >> image_array[i].r >> image_array[i].g >> image_array[i].b;
    }
    file.close();
    
    for (int i = 0; i < (rows * columns); i++)
    {
        cout << "load " << image_array[i].r << "," << image_array[i].g << "," << image_array[i].b << endl;
    }
    
    return true;
}

bool ppm_image::save(const std::string& filename) const
{
   ofstream file;
   file.open(filename);

   cout << "columns: " << columns << ", rows: " << rows << endl;

   for (int i = 0; i < (rows * columns); i++)
   {
       cout << "write " << image_array[i].r << "," << image_array[i].g << "," << image_array[i].b << endl;
   }


   for (int i = 0; i < (rows * columns); i++)
   {
       file << image_array[i].r << " " << image_array[i].g << " " << image_array[i].b << endl;
   }
   file.close();

   return true;
   //return false;
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
