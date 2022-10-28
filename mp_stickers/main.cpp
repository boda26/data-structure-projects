#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma = Image();
  alma.readFromFile("alma.png");
  Image s = Image();
  s.readFromFile("tests/i.png");
  s.scale(0.5);

  std::cout << alma.width() << std::endl;
  std::cout << alma.height() << std::endl;
  std::cout << s.width() << std::endl;
  std::cout << s.height() << std::endl;

  const Image & base = alma;
  Image & sticker = s;
  StickerSheet sheet = StickerSheet(base, 4);
  sheet.addSticker(sticker, 0, 0);
  sheet.addSticker(sticker, 787, 0);
  sheet.addSticker(sticker, 0, 437);
  sheet.addSticker(sticker, 787, 437);
  Image to_return = sheet.render();
  to_return.illinify();
  to_return.writeToFile("myImage.png");
  return 0;
}
