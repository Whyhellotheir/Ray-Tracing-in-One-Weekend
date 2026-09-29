#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

int main(){
    //Image

    int imageWidth = 256;
    int imageHeight = 256;

    //render

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(int j = 0; j < imageHeight; j++){
        //progress indicator; clog for cli cout for std output which goes to the file
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for(int i = 0; i < imageWidth; i++){
            auto pixelColor = color(double(i)/(imageWidth - 1), double(j)/(imageHeight - 1), 0);
            write_color(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.               \n";
}