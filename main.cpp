/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */

struct A{};

struct HeapA
{
    HeapA();
    ~HeapA();
    A* a;
    int* intType;
};

HeapA::HeapA()
{
    intType = new int;
    a = new A();
}

HeapA::~HeapA()
{
    delete intType; 
    delete a;
}

 /*
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers  
         IntType should own a heap-allocated int, for example.
 
 2) give it a constructor that takes the appropriate primitive
    this argument will initialize the owned primitive's value.
         i.e. if you're owning an int on the heap, your ctor argument will initialize that heap-allocated int's value.
 
 3) modify those add/subtract/divide/multiply member functions from chapter 2 on it
         a) make them modify the owned numeric type
         b) set them up so they can be chained together.
             i.e.
             DoubleType dt(3.5);
             dt.add(3.0).multiply(-2.5).divide(7.2); //an example of chaining
 
 4) write some add/subtract/divide/multiply member functions for each type that take your 3 UDTs
         for example, IntType::divide(const DoubleType& dt);
 
 5) print out the results with some creative couts 
    i.e.
         FloatType ft(0.1f);
         IntType it(3);
         std::cout << "adding 3 and subtracting 'it' from 'ft' results in the following value: " << *ft.add(2.f).subtract( it ).value << std::endl;  //note the dereference of the `value` member of `ft`
 
 6) Don't let your heap-allocated owned type leak!
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */



#include <iostream>

struct FloatType
{
    FloatType(float);
    ~FloatType();
    FloatType add(float rhs );
    FloatType subtract(float rhs );
    FloatType multiply(float rhs );
    FloatType divide(float rhs );

    float* floatTypeHeap;
};

FloatType::FloatType(float floatValue)
{
    floatTypeHeap = new float;
    *floatTypeHeap = floatValue;
}

FloatType::~FloatType()
{
    delete floatTypeHeap;
}

FloatType FloatType::add(float rhs )
{
      *floatTypeHeap += rhs;
      return *this; 
}

FloatType FloatType::subtract(float rhs )
{
    *floatTypeHeap -= rhs;
    return *this;
}

FloatType FloatType::multiply(float rhs )
{
    *floatTypeHeap *= rhs;
    return *this;
}

FloatType FloatType::divide(float rhs )
{
    *floatTypeHeap /=rhs;
    return *this;
}

struct DoubleType 
{
    DoubleType(double);
    ~DoubleType();
    DoubleType add(double rhs );
    DoubleType subtract(double rhs );
    DoubleType multiply(double rhs );
    DoubleType divide(double rhs );
    double* doubleTypeHeap;
};

DoubleType::DoubleType(double doubleValue)
{
    doubleTypeHeap = new double;
    *doubleTypeHeap = doubleValue;
}

DoubleType::~DoubleType()
{
    delete doubleTypeHeap;
}

DoubleType DoubleType::add(double rhs)
{
    *doubleTypeHeap += rhs;
    return *this;
}

DoubleType DoubleType::subtract(double rhs)
{
    *doubleTypeHeap -= rhs;
    return *this;
}

DoubleType DoubleType::divide(double rhs)
{
    *doubleTypeHeap /= rhs;
    return *this;
}

DoubleType DoubleType::multiply(double rhs)
{
    *doubleTypeHeap *= rhs;
    return *this;
}


struct IntType
{
    IntType(int);
    ~IntType();
    IntType add(int rhs );
    IntType subtract(int rhs );
    IntType multiply(int rhs );
    IntType divide(int rhs );
    int* intTypeHeap;
};

IntType::IntType(int intValue)
{
    intTypeHeap = new int;
    *intTypeHeap = intValue;
}

IntType::~IntType()
{
    delete intTypeHeap;
}

IntType IntType::add(int rhs)
{
    *intTypeHeap += rhs;
    return *this;
}

IntType IntType::subtract(int rhs)
{
    *intTypeHeap -= rhs;
    return *this;
}

IntType IntType::multiply(int rhs)
{
    *intTypeHeap *= rhs;
    return *this;
}

IntType IntType::divide(int rhs)
{
    if (rhs == 0)
    {
        std::cout << "error divide by zero" << std::endl;
        *intTypeHeap = 0;
    }
    *intTypeHeap /= rhs;
    return *this;
}

int main()
{
    FloatType f(2.0f);
    IntType i(2);
    DoubleType d(2.0);

    auto fResult1 = f.add(2.0f).subtract(1.0f);

    auto fResult2 = f.subtract(1.5f).multiply(4);

    auto iResult1 = i.multiply(6).divide(8);

    auto dResult1 = d.multiply(4.4567).subtract(6.8526893);

    auto dResult2 = d.add(45.6784).divide(3.49).multiply(9.329);

    std::cout << "good to go!" << std::endl;
}
