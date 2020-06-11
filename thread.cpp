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
        spended_time = 1000000000*(t_end.tv_sec - t_start.tv_sec)+(t_end.tv_nsec - t_start.tv_nsec);
        cout << "Spended " << spended_time << " nanoseconds" << endl;
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

int main()
{
    CTimer timer;
    //timespec ts, te;
    //long int tt;
    //clock_gettime(CLOCK_REALTIME, &ts);
    //cout << ts.tv_nsec << endl;
    timer.Start();


	thread th1(func, 1, 100000000);
	thread th2(func, 10000000, 200000000);

	func(30, 30000000);

	th1.join();
	th2.join();
	timer.End();
	timer.Count();
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
	
    
}
