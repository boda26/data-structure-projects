#include "Image.h"
#include "cs225/PNG.h"
#include <cmath>

    void Image::darken() {
        for (unsigned i = 0; i < this->width(); i++) {
            for (unsigned j = 0; i < this->height(); j++) {
                cs225::HSLAPixel & pixel = this->getPixel(i, j);
                if (pixel.l - 0.1 < 0) {
                    pixel.l = 0;
                } else {
                    pixel.l = pixel.l - 0.1;
                }
            }
        }
    }

    void Image::darken(double amount) {
        for (unsigned i = 0; i < this->width(); i++) {
            for (unsigned j = 0; j < this->height(); j++) {
                cs225::HSLAPixel & pixel = this->getPixel(i, j);
                if (pixel.l - amount < 0) {
                    pixel.l = 0;
                } else {
                    pixel.l = pixel.l - amount;
                }
            }
        }
    }

    void Image::desaturate() {
        for (unsigned int i = 0; i < this->width(); i++) {
            for (unsigned int j = 0; j < this->height(); j++) {
                cs225::HSLAPixel & pixel = this->getPixel(i, j);
                if (pixel.s - 0.1 < 0) {
                    pixel.s = 0;
                } else {
                    pixel.s = pixel.s - 0.1;
                }
            }
        }
    }

    void Image::desaturate(double amount) {
        for (unsigned int i = 0; i < this->width(); i++) {
            for (unsigned int j = 0; j < this->height(); j++) {
                cs225::HSLAPixel & pixel = this->getPixel(i, j);
                if (pixel.s - amount < 0) {
                    pixel.s = 0;
                } else {
                    pixel.s = pixel.s - amount;
                }
            }
        }
    }

    void Image::grayscale() {
        for (unsigned x = 0; x < this->width(); x++) {
            for (unsigned y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                pixel.s = 0;
            }
        }
    }

    void Image::illinify() {
        for (unsigned int x = 0; x < this->width(); x++) {
            for (unsigned int y = 0; y < this->height(); y++) {
                cs225::HSLAPixel & pixel = this->getPixel(x, y);
                double min1 = fmin(fabs(pixel.h - 11), fabs(360 - pixel.h + 11));
                double min2 = fmin(fabs(pixel.h - 216), fabs(360 - pixel.h + 216));
                if (min1 < min2) {
                    pixel.h = 11;
                } else {
                    pixel.h = 216;
                }
            }
         }
    }

    void Image::lighten() {
        for (unsigned int i = 0; i < this->width(); i++) {
            for (unsigned int j = 0; j < this->height(); j++) {
                cs225::HSLAPixel & pixel = this->getPixel(i, j);
                if (pixel.l + 0.1 > 1) {
                    pixel.l = 1;
                } else {
                    pixel.l = pixel.l + 0.1;
                }
            }
        }
    }

    void Image::lighten(double amount) {
        for (unsigned int i = 0; i < this->width(); i++) {
            for (unsigned int j = 0; j < this->height(); j++) {
                cs225::HSLAPixel & pixel = this->getPixel(i, j);
                if (pixel.l + amount > 1) {
                    pixel.l = 1;
                } else {
                    pixel.l = pixel.l + amount;
                }
            }
        }
    }

    void Image::rotateColor(double degrees) {
        for (unsigned int i = 0; i < this->width(); i++) {
            for (unsigned int j = 0; j < this->height(); j++) {
                cs225::HSLAPixel & pixel = this->getPixel(i, j);
                double sum = pixel.h + degrees;
                if (sum < 0) {
                    while (sum < 0) {
                        sum = sum + 360;
                    }
                    pixel.h = sum;
                } else {
                    while (sum > 359) {
                        sum = sum - 360;
                    }
                    pixel.h = sum;
                }
            }
        }
    }

    void Image::saturate() {
        for (unsigned i = 0; i < this->width(); i++) {
            for (unsigned j = 0; j < this->height(); j++) {
                cs225::HSLAPixel & pixel = this->getPixel(i, j);
                if (pixel.s + 0.1 > 1) {
                    pixel.s = 1;
                } else {
                    pixel.s = pixel.s + 0.1;
                }
            }
        }
    }

    void Image::saturate(double amount) {
        for (unsigned i = 0; i < this->width(); i++) {
            for (unsigned j = 0; j < this->height(); j++) {
                cs225::HSLAPixel & pixel = this->getPixel(i, j);
                if (pixel.s + amount > 1) {
                    pixel.s = 1;
                } else {
                    pixel.s = pixel.s + amount;
                }
            }
        }
    }
    
    void Image::scale(double factor) {
        Image new_image = Image();
        new_image.resize(factor * this->width(), factor * this->height());
        for (unsigned i = 0; i < this->width(); i++) {
            for (unsigned j = 0; j < this->height(); j++) {
                cs225::HSLAPixel & pixel = this->getPixel(i, j);
                cs225::HSLAPixel & new_pixel = new_image.getPixel(i * factor, j * factor);
                new_pixel = pixel;
            }
        }
        *this = new_image;
    }

    void Image::scale(unsigned w, unsigned h) {

        double factor = fmin(((double)w / this->width()), ((double)h / this->height()));
        double new_w = factor * (this->width());
        double new_h = factor * (this->height());
        Image new_image = Image();
        new_image.resize(new_w, new_h);
        for (unsigned i = 0; i < this->width(); i++) {
            for (unsigned j = 0; j < this->height(); j++) {
                cs225::HSLAPixel & pixel = this->getPixel(i, j);
                cs225::HSLAPixel & new_pixel = new_image.getPixel(i * factor, j * factor);
                new_pixel = pixel;
            }
        }
        *this = new_image;
    }


