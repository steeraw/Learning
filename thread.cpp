#include <iostream>
#include <thread>
#include <time.h>
#include <cmath>
#include <mutex>

#ifdef _WIN64
#include <Windows.h>
#endif

#define PI 3.14159265

using namespace std;

class CTimer
{
    //LARGE_INTEGER t_start, t_end;
#ifdef linux
    timespec t_start, t_end;
#elif _WIN64
    long long t_start_speed, t_end_speed, t_start_count, t_end_count;
#endif
    long long spent_time;
public:
    void Start()
    {
#ifdef linux
        clock_gettime(CLOCK_REALTIME, &t_start);
#elif _WIN64
        QueryPerformanceFrequency((LARGE_INTEGER*)& t_start_speed);
  QueryPerformanceCounter((LARGE_INTEGER*)&t_start_count);
  //QueryPerformanceFrequency((LARGE_INTEGER*)& t_start);
#endif
        cout << "Counting started" << endl;
    }
    void End()
    {
#ifdef linux
        clock_gettime(CLOCK_REALTIME, &t_end);
#elif _WIN64
        QueryPerformanceFrequency((LARGE_INTEGER*)& t_end_speed);
  QueryPerformanceCounter((LARGE_INTEGER*)& t_end_count);
  //QueryPerformanceFrequency((LARGE_INTEGER*)& t_end);
#endif
        cout << "Counting finished" << endl;
    }
    void Count()
    {
#ifdef linux
        spent_time = 1000 * (t_end.tv_sec - t_start.tv_sec) + (t_end.tv_nsec - t_start.tv_nsec) / 1000000;
#elif _WIN64
        spent_time = (1000 * t_end_count / t_end_speed) - (1000 * t_start_count / t_start_speed);
#endif
        //spent_time = t_end.tv_nsec - t_start.tv_nsec;
        cout << "Spent " << spent_time << " miliseconds" << endl;
    }

};
mutex mu;
void func(int a, int b)
{

	long double sum = 0;
	for (a; a <= b; a++)
	{
		sum += sin(a * PI / 180);
		
		//cout << "Thread ID: " << this_thread::get_id() << "  Current sum:\t" << sum << endl;
	}
	mu.lock();
	cout << "Thread ID: " << this_thread::get_id() << " Sum =\t" << sum << endl;
	mu.unlock();
}

void func_2_1()
{
    func(1,100000000);
    func(100000000,200000000);
    func(200000000,300000000);
    func(300000000,400000000);
}

void func_2_2()
{
    func(400000000,500000000);
    func(500000000,600000000);
    func(600000000,700000000);
    func(700000000,800000000);
}

void func_4_1()
{
    func(1,100000000);
    func(100000000,200000000);
}
void func_4_2()
{
    func(200000000,300000000);
    func(300000000,400000000);
}
void func_4_3()
{
    func(400000000,500000000);
    func(500000000,600000000);
}
void func_4_4()
{
    func(600000000,700000000);
    func(700000000,800000000);
}
int main()
{
    CTimer timer1,timer2,timer4,timer8;

    timer1.Start();
    func(1,100000000);
    func(100000000,200000000);
    func(200000000,300000000);
    func(300000000,400000000);
    func(400000000,500000000);
    func(500000000,600000000);
    func(600000000,700000000);
    func(700000000,800000000);
    timer1.End();
    timer2.Start();
    thread th_2_1(func_2_1);
    thread th_2_2(func_2_2);
    th_2_1.join();
    th_2_2.join();
    timer2.End();
    timer4.Start();
    thread th_4_1(func_4_1);
    thread th_4_2(func_4_2);
    thread th_4_3(func_4_3);
    thread th_4_4(func_4_4);
    th_4_1.join();
    th_4_2.join();
    th_4_3.join();
    th_4_4.join();
    timer4.End();
    timer8.Start();
    thread th_8_1(func, 1, 10000000);
    thread th_8_2(func, 10000000, 20000000);
    thread th_8_3(func, 20000000, 30000000);
    thread th_8_4(func, 30000000, 40000000);
    thread th_8_5(func, 40000000, 50000000);
    thread th_8_6(func, 50000000, 60000000);
    thread th_8_7(func, 60000000, 70000000);
    thread th_8_8(func, 70000000, 80000000);
    th_8_1.join();
    th_8_2.join();
    th_8_3.join();
    th_8_4.join();
    th_8_5.join();
    th_8_6.join();
    th_8_7.join();
    th_8_8.join();

    timer8.End();

	cout << "1 thread - ";
    timer1.Count();
    cout << endl;
    cout << "2 threads - ";
    timer2.Count();
    cout << endl;
    cout << "4 threads - ";
    timer4.Count();
    cout << endl;
    cout << "8 threads - ";
    timer8.Count();
    cout << endl;
}
