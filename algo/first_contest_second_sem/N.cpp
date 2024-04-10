#include <iostream>
#include <map>
#include <string>
#include <set>

const int kMAXID = 1e5;
const int kTIME = 600;

class Track {
 public:
  int score_ = 0;
  int track_id_ = 0;

  Track(int score, int track_id) : score_(score), track_id_(track_id){};
};

class Compare {
 public:
  bool operator()(const Track& a, const Track& b) const {
    return a.score_ > b.score_ || (a.score_ == b.score_ && a.track_id_ < b.track_id_);
  }
};

class PriorityQueue {
 public:
  PriorityQueue() {
    for (int i = 1; i < kMAXID; ++i) {
      score_[i] = 0;
      tree_.emplace(0, i);
    }
  }
  void GetMax() {
    auto it = tree_.begin();
    Track tr = *it;
    std::cout << it->track_id_ << ' ' << it->score_ << '\n';
    score_[it->track_id_] = -1;
    tree_.erase(Track{it->score_, it->track_id_});
    tr.score_ = -1;
    tree_.insert(tr);
  }
  void ChangeKey(int track_id, int score) {
    int track_score = score_[track_id];
    if (score == 0) {
      std::cout << track_score << '\n';
      return;
    }
    score_[track_id] += score;
    tree_.erase(Track{track_score, track_id});
    tree_.insert(Track{track_score + score, track_id});
    std::cout << track_score + score << '\n';
  }

 private:
  std::set<Track, Compare> tree_;
  std::map<int, int> score_;
};

class People {
 public:
  void Vote(std::string& ip, int track_id, int score, size_t time, PriorityQueue& queue) {
    auto it = map_.find(ip);
    if (it == map_.end()) {
      map_[ip] = time;
      queue.ChangeKey(track_id, score);
      return;
    }
    if (static_cast<int>(time) - static_cast<int>(it->second) < kTIME) {
      queue.ChangeKey(track_id, 0);
      return;
    }
    map_[ip] = time;
    queue.ChangeKey(track_id, score);
  }

 private:
  std::map<std::string, size_t> map_;
};

int main() {
  std::string action;
  std::string ip;
  int time = 0;
  int track_id = 0;
  int score = 0;
  People people;
  PriorityQueue queue;
  while (true) {
    std::cin >> action;
    if (action == "VOTE") {
      std::cin >> ip >> track_id >> score >> time;
      people.Vote(ip, track_id, score, time, queue);
    } else if (action == "GET") {
      queue.GetMax();
    } else if (action == "EXIT") {
      std::cout << "OK" << '\n';
      break;
    }
  }
  return 0;
}