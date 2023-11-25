#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>
#include <functional>
#include <iterator>
#include <stdexcept>

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}

class Polygon {
public:
    Polygon(const std::vector<Point>& vertices) : vertices(vertices) {}

    double area() const {
        double area = 0.0;
        int n = vertices.size();
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            area += (vertices[i].x * vertices[j].y) - (vertices[j].x * vertices[i].y);
        }
        return std::abs(area / 2.0);
    }

  

private:
    std::vector<Point> vertices;
};

std::vector<Polygon> readPolygons(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open the file: " + filename);
    }

    std::vector<Polygon> polygons;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int n;
        iss >> n;
        std::vector<Point> points(n);
        for (Point& p : points) {
            iss >> p;
        }
        polygons.push_back(Polygon(points));
    }
    return polygons;
}

class CommandManager {
public:
    CommandManager(const std::vector<Polygon>& polygons) : polygons(polygons) {}

    void processCommands(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Could not open the file: " + filename);
        }

        std::string cmd;
        while (file >> cmd) {
            if (cmd == "AVG") {
                printAverageArea();
            } else if (cmd == "SUM") {
                printSumArea();
            } else if (cmd == "MAX") {
                printMaxArea();
            } else if (cmd == "MIN") {
                printMinArea();
            } // Further commands can be added
        }
    }

private:
    std::vector<Polygon> polygons;

    void printAverageArea() {
        double total = 0;
        for (const auto& poly : polygons) {
            total += poly.area();
        }
        std::cout << "Average Area: " << (total / polygons.size()) << std::endl;
    }

    void printSumArea() {
        double total = 0;
        for (const auto& poly : polygons) {
            total += poly.area();
        }
        std::cout << "Sum of Areas: " << total << std::endl;
    }

    void printMaxArea() {
        double maxArea = 0;
        for (const auto& poly : polygons) {
            maxArea = std::max(maxArea, poly.area());
        }
        std::cout << "Max Area: " << maxArea << std::endl;
    }

    void printMinArea() {
        double minArea = std::numeric_limits<double>::max();
        for (const auto& poly : polygons) {
            minArea = std::min(minArea, poly.area());
        }
        std::cout << "Min Area: " << minArea << std::endl;
    }
};

int main() {
    try {
        auto polygons = readPolygons("poly.txt");
        CommandManager manager(polygons);
        manager.processCommands("cmd.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
