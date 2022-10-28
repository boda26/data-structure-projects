
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG png;
  png.readFromFile("tests/pacman.png");
  FloodFilledImage image(png);
  DFS dfs(png, Point(100,50), 0.2);
  BFS bfs(png, Point(100,50), 0.2);
  MyColorPicker myColor;
  RainbowColorPicker rainbow(0.5);
  image.addFloodFill(bfs, rainbow);
  image.addFloodFill(dfs, myColor);
  Animation animation = image.animate(1000);
  PNG secondFrame = animation.getFrame(1);
	PNG lastFrame = animation.getFrame(animation.frameCount() - 1);
  lastFrame.writeToFile("myFloodFill.png");
	animation.write("myFloodFill.gif");
}
