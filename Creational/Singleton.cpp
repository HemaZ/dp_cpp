#include <iostream>
#include <mutex>
#include <thread>

/**
 * @brief Singelton class with thread safe/not-safe implementation.
 *
 */
class Singleton {
private:
  Singleton() {}
  ~Singleton() {}
  static Singleton *pInstance;
  static std::mutex creationMutex;
  static std::mutex workMutex;
  int workData = 0;

public:
  static Singleton *CreateInstance();
  static Singleton *CreateInstanceNotThreadSafe();
  void DoWorkThreadSafe();
  void DoWorkNotThreadSafe();

  Singleton(Singleton &) = delete;
  void operator=(const Singleton &) = delete;
};

Singleton *Singleton::pInstance{nullptr};
std::mutex Singleton::creationMutex;
std::mutex Singleton::workMutex;

Singleton *Singleton::CreateInstance() {
  std::lock_guard<std::mutex> lock(creationMutex);
  if (pInstance == nullptr) {
    pInstance = new Singleton;
  }
  return pInstance;
}

Singleton *Singleton::CreateInstanceNotThreadSafe() {
  if (pInstance == nullptr) {
    pInstance = new Singleton;
  }
  return pInstance;
}

void Singleton::DoWorkThreadSafe() {
  std::lock_guard<std::mutex> lock(workMutex);
  std::cout << "Doing work " << workData++ << std::endl;
}

void Singleton::DoWorkNotThreadSafe() {

  std::cout << "Doing work " << workData++ << std::endl;
}

void Thread1() {
  Singleton *singelton = Singleton::CreateInstance();
  for (size_t i = 0; i < 10; i++) {
    singelton->DoWorkThreadSafe();
  }
}

void Thread2() {
  Singleton *singelton = Singleton::CreateInstanceNotThreadSafe();
  for (size_t i = 0; i < 10; i++) {
    singelton->DoWorkNotThreadSafe();
  }
}

int main(int argc, char const *argv[]) {
  std::cout << "Doing Work Thread Safe." << std::endl;
  std::thread t1(Thread1);
  std::thread t2(Thread1);
  t1.join();
  t2.join();

  std::cout << "Doing Work Not Thread Safe." << std::endl;
  std::thread t3(Thread2);
  std::thread t4(Thread2);
  t3.join();
  t4.join();

  return 0;
}
