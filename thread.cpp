#include <iostream>
#include <thread>
#include <time.h>
#include <cmath>
#define PI 3.14159265

using namespace std;

class CTimer
{
    timespec t_start, t_end;
    long long spended_time;
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
        spended_time = t_end.tv_nsec - t_start.tv_nsec;
        spended_time = 1000*(t_end.tv_sec - t_start.tv_sec)+(t_end.tv_nsec - t_start.tv_nsec)/1000000;
        cout << "Spended " << spended_time << " miliseconds" << endl;
    }

};
void func(int a, int b)
{
	long double sum = 0;
	for (a; a <= b; a++)
	{
		sum += sin(a * PI / 180);
		
		//cout << "Thread ID: " << this_thread::get_id() << "  Current sum:\t" << sum << endl;
	}
	cout << "Thread ID: " << this_thread::get_id() << " Sum =\t" << sum << endl;	
}
void func_2_1()
{
    func(1,10000000);
    func(10000000,20000000);
    func(20000000,30000000);
    func(30000000,40000000);
}

void func_2_2()
{
    func(40000000,50000000);
    func(50000000,60000000);
    func(60000000,70000000);
    func(70000000,80000000);
}

void func_4_1()
{
    func(1,10000000);
    func(10000000,20000000);
}
void func_4_2()
{
    func(20000000,30000000);
    func(30000000,40000000);
}
void func_4_3()
{
    func(40000000,50000000);
    func(50000000,60000000);
}
void func_4_4()
{
    func(60000000,70000000);
    func(70000000,80000000);
}
int main()
{
    CTimer timer1,timer2,timer4,timer8;
    //timespec ts, te;
    //long int tt;
    //clock_gettime(CLOCK_REALTIME, &ts);
    //cout << ts.tv_nsec << endl;
    timer1.Start();
    func(1,10000000);
    func(10000000,20000000);
    func(20000000,30000000);
    func(30000000,40000000);
    func(40000000,50000000);
    func(50000000,60000000);
    func(60000000,70000000);
    func(70000000,80000000);
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



	/*thread th1(func, 1, 100000000);
	thread th2(func, 10000000, 200000000);

	func(30, 30000000);

	th1.join();
	th2.join();
	timer.End();
	timer.Count();*/
    //clock_gettime(CLOCK_REALTIME, &te);
    //cout << ts.tv_nsec << endl;
    //tt = te.tv_nsec - ts.tv_nsec;
    //cout << te.tv_nsec - ts.tv_nsec << endl;
    //tt=1000000000*(te.tv_sec - ts.tv_sec)+(te.tv_nsec - ts.tv_nsec);
    //cout << tt << endl;
	//th2.join();
	//func(0, 1000000);
	
	//func(1, 9);
	//func(3, 11);
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
