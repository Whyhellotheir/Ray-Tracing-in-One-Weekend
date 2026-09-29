#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

bool hitSphere(const point3& center, double radius, const ray& r){
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc,oc) - radius * radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

color rayColor(const ray& r){
    if (hitSphere(point3(0,0,-1), 0.5, r)){
        return color(1,0,0);
    }
    

    vec3 unitDirection = unitVector(r.direction());
    auto a = 0.5*(unitDirection.y() + 1.0);
    return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
}

int main(){
    //Image

    auto aspectRatio = 16.0/9.0;
    int imageWidth = 400;

    //Calculate the image height, and ensure its at least 1;
    int imageHeight = int(imageWidth/aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    //Camera
    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);
    auto cameraCenter = point3(0,0,0);

    //Calc vectors across hor and down the vert viewport edges
    auto viewportU = vec3(viewportWidth, 0,0);
    auto viewportV = vec3(0, -viewportHeight, 0);

    //Calc the hor and vert delta vec from pix to pix
    auto pixelDeltaU = viewportU/imageWidth;
    auto pixelDeltaV = viewportV/imageHeight;

    //Calc the loc of upper left pix
    auto viewportUpperLeft = cameraCenter - vec3(0,0,focalLength) - viewportU/2 - viewportV/2;
    auto pixel00loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    //render

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(int j = 0; j < imageHeight; j++){
        //progress indicator; clog for cli cout for std output which goes to the file
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for(int i = 0; i < imageWidth; i++){
            auto pixelCenter = pixel00loc + (i * pixelDeltaU) + (j * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            ray r(cameraCenter, rayDirection);

            color pixelColor = rayColor(r);
            write_color(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.               \n";
}

//to get the picture 
//cmake --build build
//build\RayTracing.exe > fileName.ppm