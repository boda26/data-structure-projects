#include "StickerSheet.h"
#include "Image.h"
#include <iostream>

StickerSheet::StickerSheet(const Image & picture, unsigned max) 
{   
    
    base = new Image(picture);
    num_max = max;
    num_count = 0;
    w = new unsigned[max];
    h = new unsigned[max];
    stickers = new Image * [max];
    for (unsigned i = 0; i < max; i++) {
        w[i] = 0;
        h[i] = 0;
    }
}

StickerSheet::~StickerSheet() {
    _clear();
}

StickerSheet::StickerSheet(StickerSheet const &other) {
    _copy(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    if (this != &other) {
        _clear();
        _copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    Image** save_stickers = new Image * [num_count];
    unsigned* save_w = new unsigned[num_count];
    unsigned* save_h = new unsigned[num_count];

    for (unsigned i = 0; i < num_count; i++) {
        save_stickers[i] = stickers[i];
        save_w[i] = w[i];
        save_h[i] = h[i];
    }

    delete[] stickers;
    delete[] w;
    delete[] h;
    stickers = new Image* [max];
    w = new unsigned[max];
    h = new unsigned[max];

    if (max < num_count) {
        for (unsigned int a = 0; a < max; a++) {
            stickers[a] = save_stickers[a];
            w[a] = save_w[a];
            h[a] = save_h[a];
        }
        for (unsigned int b = max; b < num_count; b++) {
            delete save_stickers[b];
            save_stickers[b] = NULL;
        }
        num_count = max;
    } else {
        for (unsigned c = 0; c < num_count; c++) {
            stickers[c] = save_stickers[c];
            w[c] = save_w[c];
            h[c] = save_h[c];
        }
    }
    num_max = max;
    delete[] save_stickers;
    delete[] save_w;
    delete[] save_h;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    for (int i = 0; i < (int)num_max; i++) {
        if (i == (int)num_count) {
            stickers[i] = new Image(sticker);
            w[i] = x;
            h[i] = y;
            num_count++;
            return i;
        }
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index < num_count) {
        w[index] = x;
        h[index] = y;
        return true;
    }
    return false;
}

void StickerSheet::removeSticker(unsigned index) {
    delete stickers[index];
    stickers[index] = NULL;
    num_count--;
    for (unsigned i = index; i < num_max - 1; i++) {
        stickers[i] = stickers[i + 1];
        w[i] = w[i + 1];
        h[i] = h[i + 1];
    }
    stickers[num_max - 1] = NULL;
    w[num_max - 1] = 0;
    h[num_max - 1] = 0;
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index < num_count) {
        return stickers[index];
    }
    return NULL;
}

Image StickerSheet::render() const {
    Image to_render = Image(*base);

    for (unsigned i = 0; i < num_count; i++) {
        unsigned sticker_width = stickers[i]->width();
        unsigned sticker_height = stickers[i]->height();
        
        if (w[i] + sticker_width > to_render.width()) {
            to_render.resize(w[i] + sticker_width, to_render.height());
        }
        if (h[i] + sticker_height > to_render.height()) {
            to_render.resize(to_render.width(), h[i] + sticker_height);
        }
    }

    for (unsigned a = 0; a < num_count; a++) {
        for (unsigned b = 0; b < stickers[a]->width(); b++) {
            for (unsigned c = 0; c < stickers[a]->height(); c++) {
                cs225::HSLAPixel & pixel1 = stickers[a]->getPixel(b, c);
                if (pixel1.a != 0) {
                    cs225::HSLAPixel & pixel2 = to_render.getPixel(b + w[a], c + h[a]);
                    pixel2 = pixel1;
                }
            }
        }
    }

    return to_render;
}

void StickerSheet::_copy(const StickerSheet & other) {
    base = new Image(*(other.base));
    num_max = other.num_max;
    num_count = other.num_count;
    w = new unsigned[other.num_max];
    h = new unsigned[other.num_max];
    stickers = new Image* [other.num_max];
    for (unsigned i = 0; i < num_count; i++) {
        stickers[i] = new Image();
        *(stickers[i]) = *(other.stickers[i]);
        w[i] = other.w[i];
        h[i] = other.h[i];
    }
}

void StickerSheet::_clear() {
    for (unsigned i = 0; i < num_count; i++) {
        delete stickers[i];
        stickers[i] = NULL;
    }
    delete[] stickers;
    delete base;
    delete[] w;
    delete[] h;
}
