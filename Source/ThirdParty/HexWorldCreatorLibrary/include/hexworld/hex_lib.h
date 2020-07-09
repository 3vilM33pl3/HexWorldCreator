#pragma once

struct Hexagon {
    int64_t X;
    int64_t Y;
    int64_t Z;

    Hexagon(int x_, int y_, int z_):X(x_), Y(y_), Z(z_) {};
};

struct AxialCoordinates {
    int32_t Q;
    int32_t R;

    AxialCoordinates(int32_t Q_, int32_t R_) {
        Q = Q_;
        R = R_;
    }
};

struct PixelPoint {
    int64_t X;
    int64_t Y;

    PixelPoint(int64_t X_, int64_t Y_)
    {
        X = X_;
        Y = Y_;
    }
};

// PixelPoint ConvertAxialToPixelCoords(const struct AxialCoordinates &ac, const int size) {
//     double x = size * (3.0 / 2.0 * ac.Q);
//     double y = size * (sqrt(3.0)/2.0 * ac.Q + sqrt(3.0) * ac.R);
//     return PixelPoint(x, y);
// }



