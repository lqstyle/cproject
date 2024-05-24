#include <iostream>
#include <thread>
#include<mutex>
#include<atomic>
#include<future>

static std::once_flag flag;

using atomic_int = std::atomic<int>;
using atomic_long = std::atomic<long>;

static std::atomic_flag flag1(false);
static std::atomic_int n1;

thread_local int n = 0;

void testthreadLocal();

void testCallOnce();

void testAtomicInner1(atomic_int &t);

void testAtomic();

void testThread();

void testThreadAsync();

void threadFunction(int x, const std::string &message) {
  std::cout << "Thread function: " << x << " " << message << std::endl;
}

template<class T>
T testAtomicInner(T t);

int main() {

  testthreadLocal();
  //testCallOnce();
  //testAtomic();
//  testThread();
//  testThreadAsync();

  return 0;
}

void testthreadLocal() {
  auto f = [&](int x) {
    n += x;
    std::cout << n << std::endl;
  };

  std::thread t1(f, 10);
  std::thread t2(f, 20);
  t1.join();
  t2.join();
}

void testAtomic() {

  atomic_int x22{0};

  std::thread tsss(testAtomicInner1, std::ref(x22));
  std::thread tsss1(testAtomicInner1, std::ref(x22));
  tsss.join();
  tsss1.join();
}

template<class T>
T testAtomicInner(T t) {
  for (int i = 0; i < 1000; i++) {
    t++;
  }
  std::cout << t << std::endl;
  return t;
}

void testAtomicInner1(atomic_int &t) {
  for (int i = 0; i < 10000; i++) {
    t++;
  }
  std::cout << t << std::endl;
}

void testCallOnce() {
  auto f = []() {
    std::call_once(flag,
                   []() {
                     std::cout << "only once " << std::this_thread::get_id << std::endl;
                   });
  };

  std::thread t1(f);
  std::thread t2(f);
  t1.join();
  t2.join();
}

void testThread() {

  auto f1 = [&]() {
    auto value = flag1.test_and_set();
    if (value) {
      std::cout << "flag has been set." << std::endl;
    } else {
      std::cout << "set flag by " << std::this_thread::get_id() << std::endl; // 输出线程id
    }
    n1 += 100;
    std::this_thread::sleep_for(std::chrono::milliseconds(n1.load() * 10));
    std::cout << n1 << std::endl;
  };

  std::thread t1(f1);
  std::thread t2(f1);
  t1.join();
  t2.join();
}

void testThreadAsync(){
  auto task = [](auto x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(x * 1));
    std::cout << "sleep for " << x << std::endl;
    return x;
  };

  auto f1 = std::async(task,10);
  auto f2 = std::async(task,20);
  auto f3 = std::async(task,30);
  auto f4 = std::async(task,40);
  f1.wait();
  if(!f1.valid()){
    std::cout << "f1 finish" << std::endl;
    std::cout << f1.get() << std::endl;
  }
  f2.wait();
  if(!f2.valid()){
    std::cout << "f2 finish" << std::endl;
    std::cout << f2.get() << std::endl;
  }
  f3.wait();
  if(!f3.valid()){
    std::cout << "f3 finish" << std::endl;
    std::cout << f3.get() << std::endl;
  }
  f4.wait();
  if(!f4.valid()){
    std::cout << "f4 finish" << std::endl;
    std::cout << f4.get() << std::endl;
  }
}