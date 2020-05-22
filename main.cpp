#include <chrono>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;
using namespace chrono;

// Convert a duration to a count of milliseconds
template <class Rep, class Period>
int64_t msec(const std::chrono::duration<Rep, Period> &dur) {
  return (int64_t)duration_cast<milliseconds>(dur).count();
}

system_clock::time_point tp_since_epoch(int64_t miliseconds) {
  std::chrono::milliseconds dur(miliseconds);
  std::chrono::time_point<std::chrono::system_clock> dt(dur);
  return dt;
}

system_clock::time_point tp_epoch() {
  time_point<system_clock, duration<int>> tp_seconds(duration<int>(0));
  system_clock::time_point tp(tp_seconds);
  return tp;
}

steady_clock::time_point now() { return steady_clock::now(); }

string getTimestampStr(unsigned long now_ms) {
  time_t time = 1072915200 + now_ms / 1000;
  std::stringstream nowSs;
  nowSs << std::put_time(std::localtime(&time), "%a %b %d %Y %T") << '.'
        << std::setfill('0') << std::setw(3) << now_ms;
  return nowSs.str();
}

string getTimestamp_() {
  // get a precise timestamp as a string

  const auto now = std::chrono::system_clock::now();
  const auto nowAsTimeT = std::chrono::system_clock::to_time_t(now);
  const auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
                         now.time_since_epoch()) %
                     1000;
  std::stringstream nowSs;
  nowSs << std::put_time(std::localtime(&nowAsTimeT), "%a %b %d %Y %T") << '.'
        << std::setfill('0') << std::setw(3) << nowMs.count();
  return nowSs.str();
}

string getTimestamp_correct(int64_t miliseconds) {
  // get a precise timestamp as a string

  system_clock::time_point dt = tp_since_epoch(miliseconds);
  const auto nowAsTimeT = std::chrono::system_clock::to_time_t(dt);
  const auto nowMs = miliseconds %
                     1000;
  std::stringstream nowSs;
  nowSs << std::put_time(std::localtime(&nowAsTimeT), "%a %b %d %Y %T") << '.'
        << std::setfill('0') << std::setw(3) << nowMs;
  return nowSs.str();
}

int main() {

  int64_t milliseconds_since_epoch =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  cout << "Time in Milliseconds =" << milliseconds_since_epoch << std::endl;
  cout << "Time =" << getTimestamp_correct(milliseconds_since_epoch) << std::endl;


  return 0;
}

int main_t() {
  std::time_t t = std::time(0); // t is an integer type
  std::cout << t << " seconds since 01-Jan-1970\n";

  int64_t milliseconds_since_epoch =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  cout << "Time in Milliseconds =" << milliseconds_since_epoch << std::endl;
  const unsigned long nowMs =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();
  cout << nowMs << endl;
  auto end = tp_since_epoch(nowMs);
  // display time_point:
  std::time_t tt = system_clock::to_time_t(end);
  std::cout << "time_point tp is: " << ctime(&tt) << endl;
  cout << getTimestamp_() << endl;

  int64_t milliSecondsSinceEpoch = nowMs;
  const auto durationSinceEpoch =
      std::chrono::milliseconds(milliSecondsSinceEpoch);
  const time_point<system_clock> tp_after_duration(durationSinceEpoch);
  time_t time_after_duration = system_clock::to_time_t(tp_after_duration);

  std::tm *formattedTime = std::localtime(&time_after_duration);

  long long int milliseconds_remainder = milliSecondsSinceEpoch % 1000;
  cout << put_time(std::localtime(&time_after_duration), "%y-%m-%d-%H-%M-%S-")
       << milliseconds_remainder << endl;

  return 0;
}
