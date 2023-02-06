#include <iostream>

using namespace std;

class AB
{
	private:
		int a;
		int b;
	public:
		
		int globalA = 0;
		
		AB(int A, int B)
		{
			a = A;
			b = B;
			cout << "Working" << endl;
			cout << "a = " << a << endl;
			cout << "b = " << b << endl;
		}
		
		void setAB()
		{
			cout << "enter a and b" << endl;
			cin >> a;
			cin >> b;
		}
		
		void getAB()
		{
			cout << a << endl << b << endl;
		}
		
		int returnA(){
			return a;
		}
		
		~AB(){
			
		}
};

int main()
{
	int result;
	
	setlocale(LC_ALL, "Russian");
	
	AB obj1(2, 5);
	
	obj1.setAB();
	obj1.getAB();
	
	AB obj2(5, 10);
	
	result = obj1.returnA()*2;
	
	cout << "result " << result << endl;
	obj1.getAB();
	
	obj1.globalA = result;
	
	return 0;
}