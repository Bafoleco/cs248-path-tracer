//
// Created by Bay Foley-Cox on 3/5/22.
//

#include "Camera.h"
#include <utility>

/*
 * Transforms screenspace x,y to direction in world
 */
Vec3 Camera::getPixelDir(double x, double y) {
    double normX = (x - (double) num_cols / 2) / num_cols;
    double normY = (y - (double) num_rows / 2) / num_rows;
    return (dir * near_clip + normX * xAxis * width + normY * yAxis * height).normalized();
}

int Camera::getNumCols() const {
    return num_cols;
}

int Camera::getNumRows() const {
    return num_rows;
}

Camera::Camera(Vec3 pos, const Vec3 &dir, double hfov, double nearClip, int numCols, int numRows)
        : pos(std::move(pos)), dir(dir.normalized()), near_clip(nearClip),
          num_cols(numCols), num_rows(numRows) {


    double aspectRatio = (double) numCols / numRows;
    double vfov = 2 * atan(tan(hfov / 2) * (1/aspectRatio));

    width = tan(hfov / 2) * near_clip;
    height = tan(vfov / 2) * near_clip;

    vertical = Vec3(0, 0, 1);
    xAxis = dir.cross(vertical);
    yAxis = dir.cross(xAxis);
}

Vec3 &Camera::getPos() {
    return pos;
}
