#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<fstream>
#include<utility>
#include<cmath>
#include<cctype>
#include<sstream>
using namespace std;

const double PI = 3.141592;

class MyPoint {
public:
    double x, y;
    MyPoint() = default;
    MyPoint(int a, int b) : x(a), y(b) {}
    MyPoint(double a, double b) : x(a), y(b) {}
};

class LineSegment {
private:
    MyPoint s, t;
public:
    LineSegment() = default;
    LineSegment(MyPoint a, MyPoint b) : s(a), t(b) {}
    LineSegment(double x1, double y1, double x2, double y2) :
        s(x1, y1), t(x2, y2) {}

    double cross_product(MyPoint p1, MyPoint p2, MyPoint p3) {
        return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    }

    bool on_line(MyPoint p) {
        return p.x >= min(s.x, t.x)
            && p.x <= max(s.x, t.x)
            && p.y >= min(s.y, t.y)
            && p.y <= max(s.y, t.y);
    }

    bool intersect(LineSegment other) {
        double d1 = cross_product(other.s, other.t, s);
        double d2 = cross_product(other.s, other.t, t);
        double d3 = cross_product(s, t, other.s);
        double d4 = cross_product(s, t, other.t);
        if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
            return true;
        if (d1 == 0 && on_line(other.s))
            return true;
        if (d2 == 0 && on_line(other.t))
            return true;
        if (d3 == 0 && on_line(s))
            return true;
        if (d4 == 0 && on_line(t))
            return true;
        return false;
    }

};

static vector<string> split_line(string& str) {
    vector<string> tokens;
    stringstream sstream(str);
    string t;
    while (getline(sstream, t, ' '))
        tokens.push_back(t);
    return tokens;
}

class MyRectangle {
private:
    MyPoint min, max;
    string str_rect;
public:
    MyRectangle() = default;
    MyRectangle(MyPoint a, MyPoint b) : min(a), max(b) {}
    MyRectangle(double x1, double y1, double x2, double y2) : min(x1, y1), max(x2, y2) {}
    MyRectangle(string str) {
        str_rect = str;
        vector<string> tokens = split_line(str);
        min = MyPoint(stod(tokens[1]), stod(tokens[3]));
        max = MyPoint(stod(tokens[2]), stod(tokens[4]));
    }

    double get_min_x() const { return min.x; }
    double get_min_y() const { return min.y; }
    double get_max_x() const { return max.x; }
    double get_max_y() const { return max.y; }
    string get_str_r() { return str_rect; }
    int area() const {
        return (max.x - min.x) * (max.y - min.y);
    }

    bool intersect(LineSegment seg) {
        LineSegment left(min, MyPoint(min.x, max.y));
        LineSegment right(MyPoint(max.x, min.y), max);
        LineSegment upper(MyPoint(min.x, max.y), max);
        LineSegment lower(min, MyPoint(max.x, min.y));
        return seg.intersect(upper) || seg.intersect(lower)
            || seg.intersect(left) || seg.intersect(right);
    }
};

class MyCircle {
private:
    MyPoint origin;
    double radius;
    string str_cir;
    vector<LineSegment> r_lines;
public:
    MyCircle() = default;
    MyCircle(double x, double y, double r) : origin(x, y), radius(r) {
        LineSegment r_x_min(MyPoint(origin.x - radius, origin.y), origin);
        LineSegment r_x_max(origin, MyPoint(origin.x + radius, origin.y));
        LineSegment r_y_min(MyPoint(origin.x, origin.y - radius), origin);
        LineSegment r_y_max(origin, MyPoint(origin.x, origin.y + radius));
        r_lines.push_back(r_x_min);
        r_lines.push_back(r_x_max);
        r_lines.push_back(r_y_min);
        r_lines.push_back(r_y_max);
    }
    MyCircle(string str) {
        str_cir = str;
        vector<string> tokens = split_line(str);
        origin = MyPoint(stod(tokens[1]), stod(tokens[2]));
        radius = stod(tokens[3]);
        LineSegment r_x_min(MyPoint(origin.x - radius, origin.y), origin);
        LineSegment r_x_max(origin, MyPoint(origin.x + radius, origin.y));
        LineSegment r_y_min(MyPoint(origin.x, origin.y - radius), origin);
        LineSegment r_y_max(origin, MyPoint(origin.x, origin.y + radius));
        r_lines.push_back(r_x_min);
        r_lines.push_back(r_x_max);
        r_lines.push_back(r_y_min);
        r_lines.push_back(r_y_max);
    }

    void set_circle(MyCircle c) { *this = c; }

    double get_origin_x() const { return origin.x; }
    double get_origin_y() const { return origin.y; }
    double get_radius() const { return radius; }
    string get_str_c() { return str_cir; }
    double area() const {
        return PI * radius * radius;
    }

    bool intersect_rect(MyRectangle r) {
        for (int i = 0; i < 360; i++) {
            LineSegment rl(MyPoint(origin.x, origin.y),
                MyPoint(origin.x + (cos((double)i * PI / 180.0) * radius),
                    origin.y + (sin((double)i * PI / 180.0) * radius)));
            if (r.intersect(rl))
                return true;
        }
        return false;
    }

    bool intersect_circle(MyCircle c) {
        for (int i = 0; i < 4; i++) {
            if (r_lines[i].intersect(c.r_lines[0]) || r_lines[i].intersect(c.r_lines[1])
                || r_lines[i].intersect(c.r_lines[2]) || r_lines[i].intersect(c.r_lines[3]))
                return true;
        }
        return false;
    }
};

MyCircle* new_circle = nullptr;
vector<MyRectangle*> raw_rects;
vector<MyCircle*> raw_circles;

void input_raw_shapes(istream& infile) {
    string str;
    string type;
    int n;
    getline(infile, str);
    n = stoi(str);
    while (getline(infile, str)) {
        type = str.substr(0, 1);
        if (type == "R") {
            raw_rects.push_back(new MyRectangle(str));
        }
        else if (type == "C") {
            raw_circles.push_back(new MyCircle(str));
        }
        else {
            delete new_circle;
            new_circle = new MyCircle("C " + str);
        }
    }
}

void output_intersect_shapes() {
    vector<pair<string, double>> shapes;
    for (int i = 0; i < raw_rects.size(); i++) {
        if (new_circle->intersect_rect(*raw_rects[i])) {
            auto p = make_pair(raw_rects[i]->get_str_r(), raw_rects[i]->area());
            shapes.push_back(p);
        }
    }
    for (int i = 0; i < raw_circles.size(); i++) {
        if (new_circle->intersect_circle(*raw_circles[i])) {
            auto p = make_pair(raw_circles[i]->get_str_c(), raw_circles[i]->area());
            shapes.push_back(p);
        }
    }
    for (int i = shapes.size() - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (shapes[j].second > shapes[j + 1].second)
                swap(shapes[j], shapes[j + 1]);
        }
    }
    for (auto& s : shapes)
        cout << s.first << endl;
}

int main() {
    ifstream infile("input1.txt");
    input_raw_shapes(infile);
    infile.close();
    output_intersect_shapes();

    return 0;
}
