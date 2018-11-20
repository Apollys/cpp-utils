#include <chrono>

class Timer {
  using high_res_clock = std::chrono::high_resolution_clock;

  private:
  high_res_clock::time_point start_time_point_;
  high_res_clock::time_point end_time_point_;
  double prev_duration_;
  bool running_;

  double computeDuration(high_res_clock::time_point start, high_res_clock::time_point end) {
    using DurationType = std::chrono::duration<double>;
    DurationType dur = std::chrono::duration_cast<DurationType>(end - start);
    return dur.count();
  }

  public:
  Timer() : prev_duration_(0), running_(true) {
    start_time_point_ = high_res_clock::now();
    end_time_point_ = high_res_clock::now();
  }

  // Resets and starts timer
  void reset() {
    start_time_point_ = high_res_clock::now();
    prev_duration_ = 0;
    running_ = true;
  }

  void pause() {
    end_time_point_ = high_res_clock::now();
    prev_duration_ += computeDuration(start_time_point_, end_time_point_);
    running_ = false;
  }

  // Restarts timer without resetting the total duration
  void resume() {
    start_time_point_ = high_res_clock::now();
    running_ = true;
  }

  double getSeconds() {
    if (running_) {
      return prev_duration_ + computeDuration(start_time_point_, high_res_clock::now());
    }
    return prev_duration_;
  }

};
