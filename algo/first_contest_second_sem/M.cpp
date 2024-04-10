#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
  int64_t x;
  int64_t y;
  bool marked = false;
  int64_t NonSclalar(const Point& second, const Point& third) const {
    return (second.x - x) * (third.y - y) - (second.y - y) * (third.x - x);
  }
  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(const Point& other) const {
    return !(*this == other);
  }
};

std::istream& operator>>(std::istream& in, Point& p) {
  in >> p.x;
  in >> p.y;
  return in;
}

bool OnSegment(const Point& p1, const Point& p2, const Point& p3) {
  return (std::min(p1.x, p2.x) <= p3.x && p3.x <= std::max(p1.x, p2.x)) &&
         (std::min(p1.y, p2.y) <= p3.y && p3.y <= std::max(p1.y, p2.y));
}

struct Polygon {
  int size;
  std::vector<Point> points;
  Polygon(std::vector<Point>&& p) : size(static_cast<int>(p.size())), points(std::move(p)){};  // NOLINT

  void ConvexHull(std::vector<Point>& convex_hull) {
    size_t first = 0;
    for (size_t i = 0; i < points.size(); ++i) {
      if (!points[i].marked) {
        first = i;
        break;
      }
    }
    for (size_t i = 0; i < points.size(); ++i) {
      if (!points[i].marked &&
          ((points[i].x < points[first].x) || ((points[i].x == points[first].x) && (points[i].y < points[first].y)))) {
        first = i;
      }
    }
    convex_hull.push_back(points[first]);
    --size;

    Point base = points[first];
    Point curr = base;
    size_t curr_index = first;
    do {
      Point next = curr;
      for (size_t i = 0; i < points.size(); ++i) {
        if (points[i].marked) {
          continue;
        }
        int64_t sign = curr.NonSclalar(next, points[i]);
        if (sign < 0 || (sign == 0 && OnSegment(curr, points[i], next))) {
          next = points[i];
          curr_index = i;
        }
      }
      for (size_t i = 0; i < points.size(); ++i) {
        int64_t sign = curr.NonSclalar(next, points[i]);
        if (sign == 0 && points[i] != curr && points[i] != next && OnSegment(curr, next, points[i])) {
          if (!points[i].marked) {
            --size;
          }
          points[i].marked = true;
        }
      }
      points[curr_index].marked = true;
      --size;
      curr = next;
      convex_hull.push_back(next);
    } while (curr != base);
    ++size;
    points[first].marked = true;
    convex_hull.pop_back();
  }
};

bool PointInsideConvex(const std::vector<Point>& cont, const Point& p) {
  if (cont[1].NonSclalar(p, cont[0]) < 0) {
    return false;
  }
  auto it = std::lower_bound(cont.begin() + 2, cont.end(), p,
                             [&cont](const Point& lhs, const Point& rhs) { return cont[0].NonSclalar(lhs, rhs) > 0; });
  if (it == cont.end()) {
    return false;
  }
  return (*(it - 1)).NonSclalar(*it, p) >= 0;
}

int main() {
  size_t size1 = 0;
  std::cin >> size1;
  std::vector<Point> socobjects(size1);
  for (size_t i = 0; i < size1; ++i) {
    std::cin >> socobjects[i];
  }
  size_t size2 = 0;
  std::cin >> size2;
  std::vector<std::pair<Point, size_t>> scienceobjects(size2);
  for (size_t i = 0; i < size2; ++i) {
    std::cin >> scienceobjects[i].first;
  }
  Polygon poly(std::move(socobjects));
  size_t counter = 0;
  std::vector<Point> convex;
  while (true) {
    poly.ConvexHull(convex);
    for (size_t i = 0; i < size2; ++i) {
      if (PointInsideConvex(convex, scienceobjects[i].first)) {
        scienceobjects[i].second = counter;
      }
    }
    convex.clear();
    counter++;
    if (poly.size <= 2) {
      break;
    }
  }
  for (size_t i = 0; i < size2; ++i) {
    std::cout << scienceobjects[i].second << '\n';
  }
  return 0;
}