#include <iostream>
#include <cmath>
#include <random>

bool InCircle(double x, double y, double center_x, double center_y, double r) {
    return (x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) <= r * r;
}

double MonteCarlo(double x_start, double y_start, double width, double height, size_t points, auto is_inside) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist_x(0, 1);
    std::uniform_real_distribution<double> dist_y(0, 1);

    size_t hits = 0;
    for (size_t i = 0; i < points; ++i) {
        double x = x_start + dist_x(gen) * width;
        double y = y_start + dist_y(gen) * height;
        if (is_inside(x, y)) {
            ++hits;
        }
    }
    return static_cast<double>(hits) / points * width * height;
}

int main() {
    double cx1 = 1.0;
    double cy1 = 1.0;
    double r1 = 1.0;
    double cx2 = 1.5;
    double cy2 = 2.0;
    double r2 = std::sqrt(5) / 2.0;
    double cx3 = 2.0;
    double cy3 = 1.5;
    double r3 = std::sqrt(5) / 2.0;

    auto inside_region = [&](double x, double y) {
        return InCircle(x, y, cx1, cy1, r1) &&
               InCircle(x, y, cx2, cy2, r2) &&
               InCircle(x, y, cx3, cy3, r3);
    };

    double min_x = std::min({cx1 - r1, cx2 - r2, cx3 - r3});
    double min_y = std::min({cy1 - r1, cy2 - r2, cy3 - r3});
    double max_x = std::max({cx1 + r1, cx2 + r2, cx3 + r3});
    double max_y = std::max({cy1 + r1, cy2 + r2, cy3 + r3});

    double width = max_x - min_x;
    double height = max_y - min_y;

    for (size_t n = 100; n <= 100000; n += 500) {
        double area = MonteCarlo(min_x, min_y, width, height, n, inside_region);
        std::cout << "n: " << n << "\n"<< "area: " << area << std::endl;
    }
    return 0;
}