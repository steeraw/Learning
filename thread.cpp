#include <iostream>
#include <thread>
#include <time.h>
#include <cmath>
#include <mutex>
#include <vector>

#ifdef _WIN64
#include <Windows.h>
#endif

#define PI 3.14159265

using namespace std;
#ifdef _WIN64
class CTimer
{
    //LARGE_INTEGER t_start, t_end;
    long long t_start_speed, t_end_speed, t_start_count, t_end_count;
    long long spent_time;
public:
    void Start()
    {

        QueryPerformanceFrequency((LARGE_INTEGER*)& t_start_speed);
  QueryPerformanceCounter((LARGE_INTEGER*)&t_start_count);
  //QueryPerformanceFrequency((LARGE_INTEGER*)& t_start);
        cout << "Counting started" << endl;
    }
    void End()
    {

        QueryPerformanceFrequency((LARGE_INTEGER*)& t_end_speed);
  QueryPerformanceCounter((LARGE_INTEGER*)& t_end_count);
  //QueryPerformanceFrequency((LARGE_INTEGER*)& t_end);

        cout << "Counting finished" << endl;
    }
    void Count()
    {

        spent_time = (1000 * t_end_count / t_end_speed) - (1000 * t_start_count / t_start_speed);

        //spent_time = t_end.tv_nsec - t_start.tv_nsec;
        cout << "Spent " << spent_time << " miliseconds" << endl;
    }

};
#endif
#ifdef linux
class CTimer
{
    //LARGE_INTEGER t_start, t_end;

    timespec t_start, t_end;

    long long spent_time;
public:
    void Start()
    {
        clock_gettime(CLOCK_REALTIME, &t_start);

        cout << "Counting started" << endl;
    }
    void End()
    {

        clock_gettime(CLOCK_REALTIME, &t_end);

        cout << "Counting finished" << endl;
    }
    void Count()
    {
        spent_time = 1000 * (t_end.tv_sec - t_start.tv_sec) + (t_end.tv_nsec - t_start.tv_nsec) / 1000000;

        //spent_time = t_end.tv_nsec - t_start.tv_nsec;
        cout << "Spent " << spent_time << " miliseconds" << endl;
    }


};
#endif
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

vector<int> vect;

bool prime_detect(int n)
{
    for (int i = 2; i < n; ++i) {
        if(n % i == 0)
        {
            return false;
        }
    }
    return true;
}

void prime_gen(int n)
{
    int num, i = 0;

    while (i < n)
    {

        num = rand() % 10000;

        if(prime_detect(num))
        {
            {
                lock_guard<mutex> guard(mu);
                //mu.lock();
                vect.push_back(num);
                cout << "Thread ID: " << this_thread::get_id() << " Num =\t" << num << endl;
                //mu.unlock();

                i++;
            }
        }

    }
}

int main()
{
    CTimer timer1,timer2,timer4,timer8;
    timer1.Start();
    prime_gen(100);
    prime_gen(100);
    prime_gen(100);
    prime_gen(100);
    prime_gen(100);
    prime_gen(100);
    prime_gen(100);
    prime_gen(100);
    cout << vect.size() << endl;
    timer1.End();
    timer8.Start();
    thread threads_4_1(prime_gen, 100);
    thread threads_4_2(prime_gen, 100);
    thread threads_4_3(prime_gen, 100);
    thread threads_4_4(prime_gen, 100);
    thread threads_4_5(prime_gen, 100);
    thread threads_4_6(prime_gen, 100);
    thread threads_4_7(prime_gen, 100);
    thread threads_4_8(prime_gen, 100);
    /*thread threads_4_9(prime_gen, 25);
    thread threads_4_10(prime_gen, 25);
    thread threads_4_11(prime_gen, 25);
    thread threads_4_12(prime_gen, 25);
    thread threads_4_13(prime_gen, 25);
    thread threads_4_14(prime_gen, 25);
    thread threads_4_15(prime_gen, 25);
    thread threads_4_16(prime_gen, 25);
    thread threads_4_17(prime_gen, 25);
    thread threads_4_18(prime_gen, 25);
    thread threads_4_19(prime_gen, 25);
    thread threads_4_20(prime_gen, 25);
    thread threads_4_21(prime_gen, 25);
    thread threads_4_22(prime_gen, 25);
    thread threads_4_23(prime_gen, 25);
    thread threads_4_24(prime_gen, 25);
    thread threads_4_25(prime_gen, 25);
    thread threads_4_26(prime_gen, 25);
    thread threads_4_27(prime_gen, 25);
    thread threads_4_28(prime_gen, 25);
    thread threads_4_29(prime_gen, 25);
    thread threads_4_30(prime_gen, 25);
    thread threads_4_31(prime_gen, 25);
    thread threads_4_32(prime_gen, 25);*/
    threads_4_1.join();
    threads_4_2.join();
    threads_4_3.join();
    threads_4_4.join();
    threads_4_5.join();
    threads_4_6.join();
    threads_4_7.join();
    threads_4_8.join();
    /*threads_4_9.join();
    threads_4_10.join();
    threads_4_11.join();
    threads_4_12.join();
    threads_4_13.join();
    threads_4_14.join();
    threads_4_15.join();
    threads_4_16.join();
    threads_4_17.join();
    threads_4_18.join();
    threads_4_19.join();
    threads_4_20.join();
    threads_4_21.join();
    threads_4_22.join();
    threads_4_23.join();
    threads_4_24.join();
    threads_4_25.join();
    threads_4_26.join();
    threads_4_27.join();
    threads_4_28.join();
    threads_4_29.join();
    threads_4_30.join();
    threads_4_31.join();
    threads_4_32.join();*/
    timer8.End();

    cout << vect.size() << endl;
    for (auto it = vect.begin(); it != vect.end(); ++it)
    {
        cout << *it << " ";
    }




    cout << endl;
    cout << "1 thread - ";
    timer1.Count();
    cout << endl;
    cout << "8 threads - ";
    timer8.Count();
    cout << endl;
    /*CTimer timer1,timer2,timer4,timer8;

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
    cout << endl;*/
}
