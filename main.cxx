#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <openvdb/openvdb.h>

using namespace std;
using namespace openvdb;

int main(int argc, char** argv)
{
    openvdb::initialize();
    ifstream file("/home/deschmi/Development/scenery/data/MouseTracks/best_tracks/140521_best_early_tracks.csv");
    std::string line;
    vector<Vec4f> points;
    int linecount = 0;
    while (getline(file, line)) {
        linecount++;
        if(linecount == 1) {
            continue;
        }
        stringstream ss(line);
        std::string cell;
        vector<float> lineEntries;
        Vec4f point;
        while (getline(ss, cell, ',')) {
            lineEntries.push_back(stof(cell));
        }
        point[0] = lineEntries[0];
        point[1] = lineEntries[3];
        point[2] = lineEntries[2];
        point[3] = lineEntries[1];
        points.push_back(point);
    }

    float voxelSize = 0.01;
    FloatGrid::Ptr grid = FloatGrid::create(0.0);
    FloatGrid::Accessor accessor = grid->getAccessor();
    for (auto point : points) {
        Vec3f offset(point[3], point[2], point[1]);
        float x = int(offset[2] / voxelSize);
        float y = int(offset[1] / voxelSize);
        float z = int(offset[0] / voxelSize);
        Coord voxelCoords(x, y, z);
        accessor.setValue(voxelCoords, 1.);
    }

    grid->setTransform(
    openvdb::math::Transform::createLinearTransform(/*voxel size=*/0.001));
    GridPtrVec grids;
    grids.push_back(grid);
    openvdb::io::File outfile("/home/deschmi/Development/scenery/data/MouseTracks/cell_tracking_no_time.vdb");
    outfile.write(grids);
    outfile.close();

    return 0;
}
