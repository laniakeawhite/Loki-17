#include "FunctorTest.h"
#include "Functor.h"
#include <string>
#include <iostream>
// The using directive is acceptable for a small C++ program
using namespace std;
// Define a test functor
struct TestFunctor
{
    void operator()(int i, double d)
    {
        cout << "TestFunctor::operator()(" << i
             << ", " << d << ") called.\n";
    }
};

string TestFunction(double, double)
{
    cout << "TestFunction string type is call" << endl;
    static const char buffer[] = "Hello, world!";
    // It's safe to return a pointer to a static buffer
    return string("hello,world");
}

const char *Fun(int i, int j)
{
    cout << "Fun(" << i << ", " << j << ") called\n";
    return "0";
}

class Parrot
{
public:
    void Eat()
    {
        cout << "Tsk, knick, tsk...\n";
    }
    void Speak()
    {
        cout << "Oh Captain, my Captain!\n";
    }

    int test_0()
    {
        return 100;
    }

    int test_1(int param)
    {
        return 100 + param;
    }

    int test_2(int p1, int p2)
    {
        return p1 * p2;
    }
};
//------------------------------------------------------------------------------------------
void FunctorTest::Test()
{
    TestCallOperator();
    TestCallFunction();
    TestCallMemberFunc();
    TestBind();
}

void FunctorTest::TestCallOperator()
{
    TestFunctor f;
    Loki::Functor<void, TYPELIST_2(int, double)> cmd(f);
    cmd(4, 4.5);
}
void FunctorTest::TestCallFunction()
{
    Loki::Functor<string, TYPELIST_2(int, int)> cmd1(TestFunction);
    // Should print "world!"
    // cout << cmd1(10, 10).substr(7);
    string ret = cmd1(10, 101);
    cout << "ret size  = " << ret.size() << endl;
    cout << ret.data() << endl;
}

void FunctorTest::TestCallMemberFunc()
{
    Parrot geronimo;
    // Define two Functors
    Loki::Functor<void> cmd1(&geronimo, &Parrot::Eat);
    Loki::Functor<void> cmd2(&geronimo, &Parrot::Speak);
    Loki::Functor<int> cmd3(&geronimo, &Parrot::test_0);
    Loki::Functor<int, TYPELIST_1(int)> cmd4(&geronimo, &Parrot::test_1);
    // Loki::Functor<int,int>   cmd4(&geronimo, &Parrot::test_1);//bad
    Loki::Functor<int, TYPELIST_2(int, int)> cmd5(&geronimo, &Parrot::test_2);
    // Invoke each of them
    cmd1();
    cmd2();
    cout << cmd3() << endl;
    cout << cmd4(200) << endl;
    cout << cmd5(23, 10) << endl;
}

void FunctorTest::TestBind()
{
    Loki::Functor<const char *, TYPELIST_2(char, int)> f1(Fun);
    Loki::Functor<std::string, TYPELIST_1(double)> f2(
        Loki::BindFirst(f1, 10));
    // Prints: Fun(10, 15) called
    f2(15);
}