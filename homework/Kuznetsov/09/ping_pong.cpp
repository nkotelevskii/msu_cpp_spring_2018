#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

const size_t ITERS = 1000000;
std::mutex m;
std::condition_variable conditionVariable;
int count = 0;


void ping(){
    std::unique_lock<std::mutex> lock(m);
    while(count <= ITERS) {

        while (count % 2 == 1)
            conditionVariable.wait(lock);

        std::cout << "ping" << std::endl;
        ++count;
        conditionVariable.notify_one();
    }
}
void pong(){
    std::unique_lock<std::mutex> lock(m);

    while(count <= ITERS) {

        while (count % 2 == 0)
            conditionVariable.wait(lock);

        std::cout << "pong" << std::endl;
        ++count;
        conditionVariable.notify_one();
    }
}

int main() {
    std::thread thread(ping);
    std::thread(pong).join();
    thread.join();

    /*���� ������ ����� ����� ��������
     * std::thread thread(ping);
     * pong();
     * thread.join();
     * �� �� ��� ����� ��� ����������� ������� ������� (�����)
     *
     * �� ������� ������ ���*/
    return 0;
}