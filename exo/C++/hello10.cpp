#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

constexpr int NB_TOUR = 10;

class multi_thread {
private:
    int compteur = 0;
    const int nb_tour;
    
public:
    std::mutex mutex;
    std::condition_variable cond;
    
    multi_thread() : nb_tour(NB_TOUR) {}
    
    friend void thread_hello_world(multi_thread& mt);
    friend void thread_done(multi_thread& mt);
};


void print_safe(const std::string& msg) {
    static std::mutex print_mutex;
    std::lock_guard<std::mutex> lock(print_mutex);
    std::cout << msg << std::endl;
}

void thread_hello_world(multi_thread& mt) {

    print_safe("Hello World!");

    std::unique_lock<std::mutex> lock(mt.mutex);
    mt.compteur++;

    if (mt.compteur == mt.nb_tour) {
        mt.cond.notify_one();
    }
}

void thread_done(multi_thread& mt) {
    std::unique_lock<std::mutex> lock(mt.mutex);
    
    mt.cond.wait(lock, [&mt] { return mt.compteur >= mt.nb_tour; });

    print_safe("Done!");
}

int main() {

    multi_thread mt;

    for (int i = 0; i < NB_TOUR; i++) {
        std::thread(thread_hello_world, std::ref(mt)).detach();
    }

    std::thread done(thread_done, std::ref(mt));
    done.join();

    return 0;
}
