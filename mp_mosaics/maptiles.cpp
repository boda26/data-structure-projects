/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include "kdtree.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>(pixel.l, pixel.u, pixel.v);
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    map<Point<3>, TileImage*> map;
    vector<Point<3>> points;
    for (auto it = theTiles.begin(); it != theTiles.end(); ++it) {
        cs225::LUVAPixel pixel = (*it).getAverageColor();
        Point<3> pt = convertToXYZ(pixel);
        map[pt] = &*it;
        points.push_back(pt);
    }
    MosaicCanvas* output = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    KDTree<3> kd_tree(points);
    for (int a = 0; a < output->getRows(); a++) {
        for (int b = 0; b < output->getColumns(); b++) {
            Point<3> target = convertToXYZ(theSource.getRegionColor(a, b));
            Point<3> currBest = kd_tree.findNearestNeighbor(target);
            TileImage* replacement = map[currBest];
            output->setTile(a, b, replacement);
        }
    }
    return output;
}

