//
// Created by Bay Foley-Cox on 3/5/22.
//

#ifndef PATH_TRACER_CAMERA_H
#define PATH_TRACER_CAMERA_H

#include <Eigen/Core>
#include <Eigen/Geometry>
#include "../types.h"

class Camera {
public:
    Camera(Vec3 pos, const Vec3 &dir, double vfov, double hfov, double nearClip,
           int numCols, int numRows);

    int getNumCols() const;
    int getNumRows() const;

    Vec3 &getPos();

    Vec3 getPixelDir(double x, double y);
private:
    Vec3 pos;
    Vec3 dir;
    double near_clip;
    int num_cols = 1080;
    int num_rows = 720;
    Vec3 vertical;
    Vec3 xAxis;
    Vec3 yAxis;
    double width;
    double height;
};


#endif //PATH_TRACER_CAMERA_H
