#include <iostream>
#include <thread>
#include <chrono>

void thread_funcion(int delay)
{
    for (int var = 0; var < 10; ++var) {
        std::cout << "thread_id: "<< std::this_thread::get_id() << "   iteration_count: " << var << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void join_by_rotation(int delay_1, int delay_2, int delay_3){
    std::thread thread_1(thread_funcion, delay_1);
    thread_1.join();
    std::thread thread_2(thread_funcion, delay_2);
    thread_2.join();
    std::thread thread_3(thread_funcion, delay_3);
    thread_3.join();
}

void join_parallel(int delay_1, int delay_2, int delay_3){
    std::thread thread_1(thread_funcion, delay_1);
    std::thread thread_2(thread_funcion, delay_2);
    std::thread thread_3(thread_funcion, delay_3);
    thread_1.join();
    thread_2.join();
    thread_3.join();
}

void detach_parallel(int delay_1, int delay_2, int delay_3){
    std::thread thread_1(thread_funcion, delay_1);
    std::thread thread_2(thread_funcion, delay_2);
    std::thread thread_3(thread_funcion, delay_3);

    thread_3.detach(); // Вetach continues to perform its tasks until the program closes without slowing down the main thread

    thread_1.join(); // join не разрешает выйти из функции до своего завершения
    thread_2.detach(); // detach продолжает выполнения своих задач до закрытия программы при это не тормозя основой поток
}

int main(int argc, char *argv[])
{
    int time_out = 2000;
    int delay_1 = 25;
    int delay_2 = 50;
    int delay_3 = 100;
    std::cout << "Call the thread in order" << std::endl;
    join_by_rotation(delay_1, delay_2, delay_3);
    std::cout << "Done!" << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time_out));

    std::cout << "Call the thread in parallel" << std::endl;
    join_parallel(delay_1, delay_2, delay_3);
    std::cout << "Done!" << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time_out));

    std::cout << "Example of using detach" << std::endl;
    detach_parallel(delay_1, delay_2, delay_3);
    std::cout << "Done!" << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time_out));

    return 0;
}


