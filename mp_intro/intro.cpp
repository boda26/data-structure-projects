#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG png(1,1);
  png.readFromFile(inputFile);
  double h = png.height();
  double w = png.width();
  cs225::PNG newPNG(w, h);
  for (double i = 0; i < w; i++) {
    for (double j = 0; j < h; j++) {
      cs225::HSLAPixel pixel = png.getPixel(i, j);
      newPNG.getPixel(w - i - 1, h - j - 1) = pixel;
    }
  }
  newPNG.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned int i = 0; i < width; i++) {
    for (unsigned int j = 0; j < height; j++) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 100;
      if (pixel.h + i/5 <= 360) {
        pixel.h = pixel.h + i/5;
      } else {
        pixel.h = 360;
      }
      pixel.l = 0.5 + 0.0001 * i;
      pixel.s = 0.5 + 0.0001 * i;
      pixel.a = 1;
    }
  }
  return png;
}