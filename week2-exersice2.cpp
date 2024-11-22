#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class Methane {
 public:
  Methane() : hydrogen_count_(0), carbon_count_(0) {}

  void Hydrogen(std::function<void()> releaseHydrogen) {
    std::unique_lock<std::mutex> lock(mtx_);
    // 等待条件：碳线程到达并且当前氢线程数小于 4
    cv_.wait(lock, [this]() { return carbon_count_ > 0 && hydrogen_count_ < 4; });

    // 释放一个氢原子
    releaseHydrogen();
    ++hydrogen_count_;

    // 如果满足甲烷分子条件（4H + 1C），重置计数器并唤醒其他线程
    if (hydrogen_count_ == 4 && carbon_count_ == 1) {
      Reset();
    } else {
      cv_.notify_all();  // 唤醒其他等待的氢线程或碳线程
    }
  }

  void Carbon(std::function<void()> releaseCarbon) {
    std::unique_lock<std::mutex> lock(mtx_);
    // 等待条件：当前只能有 1 个碳线程
    cv_.wait(lock, [this]() { return carbon_count_ == 0; });

    // 释放一个碳原子
    releaseCarbon();
    ++carbon_count_;

    // 如果满足甲烷分子条件（4H + 1C），重置计数器并唤醒其他线程
    if (hydrogen_count_ == 4 && carbon_count_ == 1) {
      Reset();
    } else {
      cv_.notify_all();  // 唤醒等待的氢线程
    }
  }

 private:
  void Reset() {
    hydrogen_count_ = 0;
    carbon_count_ = 0;
    cv_.notify_all();  // 唤醒所有等待的线程
  }

  int hydrogen_count_;  // 当前到达的氢线程数
  int carbon_count_;    // 当前到达的碳线程数
  std::mutex mtx_;
  std::condition_variable cv_;
};

int main() {
  Methane methane;

  // 输入线程顺序
  std::string input = "HHHHHHCCCHHHH";
  std::vector<std::thread> threads;

  // 定义氢原子的行为
  auto releaseHydrogen = []() { std::cout << "H"; };

  // 定义碳原子的行为
  auto releaseCarbon = []() { std::cout << "C"; };

  // 创建线程
  for (char atom : input) {
    if (atom == 'H') {
      threads.emplace_back(&Methane::Hydrogen, &methane, releaseHydrogen);
    } else if (atom == 'C') {
      threads.emplace_back(&Methane::Carbon, &methane, releaseCarbon);
    }
  }

  // 等待所有线程完成
  for (auto& thread : threads) {
    thread.join();
  }

  return 0;
}
