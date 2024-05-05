#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

struct Vertex {
  int64_t shortest_path = -1;
  int64_t color = 0;
  std::vector<int64_t> list_;
};

void BFS(std::vector<Vertex>& vertex, int64_t first, bool fl) {
  vertex[first].color = 1;
  vertex[first].shortest_path = 0;
  std::queue<int64_t> queue;
  queue.push(first);
  while (!queue.empty()) {
    int64_t u = queue.front();
    queue.pop();
    for (auto v : vertex[u].list_) {
      if (vertex[v].color == 0) {
        if (!fl && (v == static_cast<int64_t>(vertex.size() - 1) || v == static_cast<int64_t>(vertex.size() - 3))) {
          continue;
        }
        if (fl && (v == static_cast<int64_t>(vertex.size() - 2) || v == static_cast<int64_t>(vertex.size() - 4))) {
          continue;
        }
        vertex[v].color = 1;
        vertex[v].shortest_path = vertex[u].shortest_path + 1;
        queue.push(v);
      }
    }
    vertex[u].color = 2;
  }
}

struct Point {
  int64_t x = 0;
  int64_t y = 0;
  Point() = default;
  Point(int64_t a, int64_t b) : x(a), y(b) {
  }
  int64_t NonSclalar(const Point& second, const Point& third) const {
    return (second.x - x) * (third.y - y) - (second.y - y) * (third.x - x);
  }
  auto operator<=>(const Point& other) const noexcept = default;
};

void Swap(Point& p1, Point& p2) {
  std::swap(p1.x, p2.x);
  std::swap(p1.y, p2.y);
}

int64_t Distance(const Point& p1, const Point& p2) {
  return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

struct Vector {
  int64_t x = 0;
  int64_t y = 0;
  Vector(const Point& a, const Point& b) : x(b.x - a.x), y(b.y - a.y) {
  }
  __int128_t CrossProduct(const Vector& other) const {
    return other.y * x - other.x * y;
  }
  __int128_t DotProduct(const Vector& other) const {
    return x * other.x + y * other.y;
  }
};

std::istream& operator>>(std::istream& in, Point& p) {
  in >> p.x >> p.y;
  return in;
}

bool OnSegment(const Point& p1, const Point& p2, const Point& p3) {
  return (std::min(p1.x, p2.x) <= p3.x && p3.x <= std::max(p1.x, p2.x)) &&
         (std::min(p1.y, p2.y) <= p3.y && p3.y <= std::max(p1.y, p2.y));
}

struct Segment {
  Point a;
  Point b;
  Segment(const Point& p1, const Point& p2) : a(p1), b(p2) {
  }
  bool IsIntersect(const Segment& other) const {
    Vector v1(other.a, a);
    Vector v2(other.a, other.b);
    Vector v3(a, b);
    Vector v4(a, other.a);
    Vector v5(other.a, b);
    Vector v6(a, other.b);
    auto d1 = static_cast<int64_t>(v1.CrossProduct(v2));
    auto d2 = static_cast<int64_t>(v5.CrossProduct(v2));
    auto d3 = static_cast<int64_t>(v4.CrossProduct(v3));
    auto d4 = static_cast<int64_t>(v6.CrossProduct(v3));
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
      return true;
    }
    return ((d1 == 0 && OnSegment(other.a, other.b, a)) || (d2 == 0 && OnSegment(other.a, other.b, b)) ||
            (d3 == 0 && OnSegment(a, b, other.a)) || (d4 == 0 && OnSegment(a, b, other.b)));
  }
};

struct Circle {
  Point p;
  int64_t r = 0;
  Circle(const Point& pt, int64_t c) : p(pt), r(c) {
  }
  Circle() = default;
  bool CircleIntersect(const Circle& other) const {
    int64_t d = Distance(p, other.p);
    return (r + other.r) * (r + other.r) >= d;
  }
  bool SegmentIntersect(const Segment& seg) const {
    Vector vec1(seg.a, p);
    Vector vec2(seg.a, seg.b);
    Vector vec3(seg.b, p);
    Vector vec4(seg.b, seg.a);
    return vec1.CrossProduct(vec2) * vec1.CrossProduct(vec2) <= r * r * (vec2.x * vec2.x + vec2.y * vec2.y);
  }
};

std::istream& operator>>(std::istream& in, Circle& circ) {
  in >> circ.p >> circ.r;
  return in;
}

struct Polygon {
  std::vector<Point> points;
  void ConvexHull() {
    std::vector<Point> convex_hull;
    size_t first = 0;
    for (size_t i = 0; i < points.size(); ++i) {
      if ((points[i].x < points[first].x) || ((points[i].x == points[first].x) && (points[i].y < points[first].y))) {
        first = i;
      }
    }
    convex_hull.push_back(points[first]);

    Point base = points[first];
    Point curr = base;
    size_t curr_index = first;
    do {
      Point next = points[(curr_index + 1) % points.size()];
      for (size_t i = 0; i < points.size(); ++i) {
        int64_t sign = curr.NonSclalar(next, points[i]);
        if (sign < 0 || (sign == 0 && OnSegment(curr, points[i], next))) {
          next = points[i];
          curr_index = i;
        }
      }
      curr = next;
      convex_hull.push_back(next);
    } while (curr != base);
    convex_hull.pop_back();
    points = convex_hull;
  }
};

std::istream& operator>>(std::istream& in, Polygon& poly) {
  poly.points.resize(4);
  in >> poly.points[0] >> poly.points[1] >> poly.points[2] >> poly.points[3];
  return in;
}

// идейно - если ввести, что сторона треугольника - это вершина и существует путь между двумя вершинами
// которые являются сторонами треугольника, то всё плохо, другие вершины - центры окружностей

int main() {
  Polygon poly;
  std::cin >> poly;
  poly.ConvexHull();
  int64_t n = 0;
  std::cin >> n;
  std::vector<Circle> circles;
  circles.reserve(n);
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> circles[i];
  }
  std::vector<Vertex> graph(n + 4);
  for (int64_t i = 0; i < n; ++i) {
    for (int64_t j = i + 1; j < n; ++j) {
      if (circles[i].CircleIntersect(circles[j])) {
        graph[i].list_.push_back(j);
        graph[j].list_.push_back(i);
      }
    }
  }
  for (int64_t i = 0; i < n; ++i) {
    if (circles[i].SegmentIntersect(Segment(poly.points[0], poly.points[1]))) {
      graph[i].list_.push_back(n);
      graph[n].list_.push_back(i);
    }
    if (circles[i].SegmentIntersect(Segment(poly.points[1], poly.points[2]))) {
      graph[i].list_.push_back(n + 1);
      graph[n + 1].list_.push_back(i);
    }
    if (circles[i].SegmentIntersect(Segment(poly.points[2], poly.points[3]))) {
      graph[i].list_.push_back(n + 2);
      graph[n + 2].list_.push_back(i);
    }
    if (circles[i].SegmentIntersect(Segment(poly.points[3], poly.points[0]))) {
      graph[i].list_.push_back(n + 3);
      graph[n + 3].list_.push_back(i);
    }
  }
  BFS(graph, n, false);
  if (graph[n + 2].shortest_path != -1) {
    std::cout << "NO\n";
    return 0;
  }
  for (int64_t i = 0; i < n + 4; ++i) {
    graph[i].shortest_path = -1;
    graph[i].color = 0;
  }
  BFS(graph, n + 1, true);
  if (graph[n + 3].shortest_path != -1) {
    std::cout << "NO\n";
    return 0;
  }
  std::cout << "YES\n";
  return 0;
}