/*
Project 4 - Part 6 / 9
Video: Chapter 5 Part 3
 
Create a branch named Part6
 
 Lambdas
 
    Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add two member functions named "apply()" to each of your Heap-Allocated Numeric Type wrappers.
         both apply() functions should work with chaining
 
 2) One of the apply() functions should takes a std::function<> object as the function argument.
    the std::function<> object should return *this;
 
 3) the other apply() function should take a function pointer. 
    the function pointer should return void.
 
 4) Make both of the member functions's Callable Function Parameter use your owned object as it's single parameter.
         e.g. if you manage your owned object via std::unique_ptr<T>, you'd use this for your std::function argument:
             std::function< OwnedT&(std::unique_ptr<T>&)>
             
         if you managed your owned object via a raw pointer, you'd use this for your std::function argument:
             std::function<OwnedT&(T&)>    
 
 5) call that Callable Function Parameter in the apply() member function.
         be sure to practice safe std::function usage (make sure it's not a nullptr function being called)
 
 6) Using one instance of each of your Heap-Allocated Numeric Type wrappers: Call your apply() member function twice in main()
         a) once with a lambda as the argument
         b) once with a free function as the argument.
         c) there will be a total of 6 calls to apply() in main(), 2x per HeapType, IntType, DoubleType instance.
         If this confuses you, rewatch the video where I pass a free function in to a function that wants a function pointer
 
 8) Make your lambda & free function update the value of your held object
 
 9) use std::cout statements to print out the results of calling apply()
 
build/run to make sure you don't have any errors

Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 
 If you need to see an example, look at https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part6Example.cpp
 */




//#TODO: remove -Wno-deprecated flag after learning rule of 3-5-0 in part7/8/9
#include <iostream>
#include <cmath>
#include <functional>

//forward declare

struct FloatType;
struct DoubleType;
struct IntType;

//Point definition ///////////////////////////////////////////

struct Point
{
    Point(float xy) : Point(xy, xy) { }  //This calls the constructor below.
    Point(float _x, float _y) : x(_x), y(_y) { }
    Point& multiply(float m);
    Point& multiply(IntType& m);
    Point& multiply(FloatType& m);
    Point& multiply(DoubleType& m);
    void toString();
private:
    float x{0}, y{0};
};


//IntType definition /////////////////////////////////////////////

struct IntType
{
    IntType(int);
    ~IntType();
    operator int() const { return *intTypeHeap; }
    
    IntType& operator+=(const int other);
    IntType& operator-=(const int other);
    IntType& operator/=(const int other);
    IntType& operator*=(const int other);

    IntType& apply(std::function<IntType&(int&)> intFunc);
    IntType& apply(void(*intFunc)(int&));

    IntType& pow(int power);
    IntType& pow(const IntType& intRef);
    IntType& pow(const FloatType& floatRef);
    IntType& pow(const DoubleType& doubleRef);
    
private:
    int powInternal(int power);
    int* intTypeHeap = nullptr;
}; 

//FloatType definition ///////////////////////////////////////////
struct FloatType
{
    FloatType(float);
    ~FloatType();
    operator float() const { return *floatTypeHeap; }

    FloatType& operator+=(const float other);
    FloatType& operator-=(const float other);
    FloatType& operator/=(const float other);
    FloatType& operator*=(const float other);

    FloatType& apply(std::function<FloatType&(float&)> floatFunc);
    FloatType& apply(void(*)(float&));

    FloatType& pow(float power);
    FloatType& pow(const IntType& intRef);
    FloatType& pow(const FloatType& floatRef);
    FloatType& pow(const DoubleType& doubleRef);  
    
private:
    float* floatTypeHeap = nullptr;
    float powInternal(float power);
    
};

//DoubleType definition /////////////////////////////////////////

struct DoubleType 
{
    DoubleType(double);
    ~DoubleType();
    operator double() const { return *doubleTypeHeap; }

    DoubleType& operator+=(const double other);
    DoubleType& operator-=(const double other);
    DoubleType& operator/=(const double other);
    DoubleType& operator*=(const double other);

    DoubleType& apply(std::function<DoubleType&(double&)>);
    DoubleType& apply(void(*)(double&));

    const DoubleType& pow(double power);
    DoubleType& pow(const IntType& intRef);
    DoubleType& pow(const FloatType& floatRef);
    DoubleType& pow(const DoubleType& doubleRef);
    
private:
    double powInternal(double power);
    double* doubleTypeHeap = nullptr;
};


//Point Implementation ///////////////////////////////////////////

Point& Point::multiply(float m)
{
    x *= m;
    y *= m;
    return *this;
}


Point& Point::multiply(IntType& m)
{
    return multiply(static_cast<float>(m));
}

Point& Point::multiply(FloatType& m)
{
    return multiply(static_cast<float>(m));
}

Point& Point::multiply(DoubleType& m)
{
    return multiply(static_cast<float>(m));
}

void Point::toString()
{
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
}

//IntType Implementation /////////////////////////////////////////


IntType::IntType(int intValue)
{
    intTypeHeap = new int(intValue);
}

IntType::~IntType()
{
    delete intTypeHeap;
}

IntType& IntType::operator+=( const int other) 
{
    *intTypeHeap += other;
    return *this;
}

IntType& IntType::operator-=(const int other)
{
    *intTypeHeap -= other;
    return *this;
}

IntType& IntType::operator/=( const int other) 
{
    if (other == 0)
    {
        std::cout << "error divide by zero" << std::endl; 
    } 
    else 
    { 
        *intTypeHeap /= other;
    }
    return *this;
}

IntType& IntType::operator*=(const int other) 
{
    *intTypeHeap *= other;
    return *this;
}

IntType& IntType::apply(std::function<IntType&(int&)> intFunc)
{
    if(intFunc)
    {
        return intFunc(*intTypeHeap);
    }
    return *this;
}

IntType& IntType::apply(void(*intFunc)(int&))
{
    if(intFunc)
    {
        intFunc(*intTypeHeap);
    }
    return *this;
}

IntType& IntType::pow(int power)
{
    *intTypeHeap = powInternal(power);
    return *this;
}

IntType& IntType::pow(const IntType& intRef)
{
    *intTypeHeap = powInternal(intRef);
    return *this;   
}

IntType& IntType::pow(const DoubleType& doubleRef)
{
    *intTypeHeap = powInternal(static_cast<int>(doubleRef));
    return *this;
}

int IntType::powInternal(int power)
{
    return static_cast<int>(std::pow(*intTypeHeap, power));
}

IntType& IntType::pow(const FloatType& floatRef)
{
    *intTypeHeap = (powInternal(static_cast<int>(floatRef)));
    return *this;
}

//FloatType Implementation //////////////////////////////////////


FloatType::FloatType(float floatValue)
{
    floatTypeHeap = new float(floatValue);
}

FloatType::~FloatType()
{
    delete floatTypeHeap;
}

FloatType& FloatType::operator+=( const float other) 
{
    *floatTypeHeap += other;
    return *this;
}

FloatType& FloatType::operator-=(const float other)
{
    *floatTypeHeap -= other;
    return *this;
}

FloatType& FloatType::operator/=( const float other) 
{
    *floatTypeHeap /= other;
    return *this;
}

FloatType& FloatType::operator*=(const float other) 
{
    *floatTypeHeap *= other;
    return *this;
}

FloatType& FloatType::apply(std::function<FloatType&(float&)> floatFunc)
{
    if(floatFunc)
    {
        return floatFunc(*floatTypeHeap);
    }
    return *this;
}

FloatType& FloatType::apply(void(*floatFunc)(float&))
{
    if(floatFunc)
    {
        floatFunc(*floatTypeHeap);
    }
    return *this;
}

FloatType& FloatType::pow(float power)
{
    powInternal(power);
    return *this;
}

FloatType& FloatType::pow(const IntType& intRef)
{ 
    powInternal(intRef);
    return *this; 
}

FloatType& FloatType::pow(const FloatType& floatRef)
{
    powInternal(floatRef);
    return *this; 
}

FloatType& FloatType::pow(const DoubleType& doubleRef)
{
    *floatTypeHeap = powInternal(static_cast<float>(doubleRef)); 
    return *this; 
}

float FloatType::powInternal(float power)
{
    return std::pow(*floatTypeHeap, power);
}

//DoubleType Implementation //////////////////////////////////////


DoubleType::DoubleType(double doubleValue)
{
    doubleTypeHeap = new double(doubleValue);
}

DoubleType::~DoubleType()
{
    delete doubleTypeHeap;
}

DoubleType& DoubleType::operator+=( const double other) 
{
    *doubleTypeHeap += other;
    return *this;
}

DoubleType& DoubleType::operator-=(const double other)
{
    *doubleTypeHeap -= other;
    return *this;
}

DoubleType& DoubleType::operator/=( const double other) 
{
    *doubleTypeHeap /= other;
    return *this;
}

DoubleType& DoubleType::operator*=(const double other) 
{
    *doubleTypeHeap *= other;
    return *this;
}

DoubleType& DoubleType::apply(std::function<DoubleType&(double&)> doubleFunc)
{
    if(doubleFunc)
    {
        return doubleFunc(*doubleTypeHeap);
    }
    return *this;
}

DoubleType& DoubleType::apply(void(*doubleFunc)(double&))
{
    if(doubleFunc)
    {
        doubleFunc(*doubleTypeHeap);
    }
    return *this;
}

const DoubleType& DoubleType::pow(double power)
{
    *doubleTypeHeap = powInternal(power);
    return *this;
}

DoubleType& DoubleType::pow(const IntType& intRef)
{
    *doubleTypeHeap = powInternal(intRef);
    return *this;
}

DoubleType& DoubleType::pow(const FloatType& floatRef)
{
    *doubleTypeHeap = powInternal(static_cast <double>(floatRef));
    return *this;
}

DoubleType& DoubleType::pow(const DoubleType& doubleRef)
{
    *doubleTypeHeap = powInternal(doubleRef);
    return *this;
}

double DoubleType::powInternal(double power)
{
    return static_cast<double>(std::pow(*doubleTypeHeap, power)); 
}

//Free funcs ///////////////////////////////////////////

void plusTen(int& intHeap)
{
    intHeap += 10;
}

void plusTen(float& floatHeap)
{
    floatHeap += 10.0f;
}

void plusTen(double& doubleHeap)
{
    doubleHeap += 10.0;
}

//MAIN ///////////////////////////////////////////

int main()
{
    FloatType f(2.0f);
    DoubleType d(2.0);
    IntType i(2);

    std::cout << "i = " << i << std::endl;
    std::cout << "f = " << f << std::endl;
    std::cout << "d = " << d << std::endl;

    Point p(f);

    f.pow(i) /= 4.6f;

    d.pow(f) *= 4.4567;

    i.pow(d) += 10; 

    i /= 0;

    p.multiply(i).toString();

    p.multiply(f).toString();

    std::cout << "f by the power of  i and dividing by 4.6.. f: " << f << std::endl;

    std::cout << "d times 4.4567 to the power of f.. d:  "<< d << std::endl;

    std::cout << "Adding 10 to i to the power of d.. i: " << i << std::endl;

    i.apply(plusTen);

    std::cout << "Plus 10 to i using a function pointer = " << i << std::endl;

    i.apply([&i](int& intHeap) -> IntType& 
    { 
        intHeap += 10;
        return i; 
    });

    std::cout << "Plus 10 to i using a lambda = " << i << std::endl;

    f.apply(plusTen);

    std::cout << "Plus 10 to f using a function pointer = " << f << std::endl;

    f.apply([&f](float& floatHeap) -> FloatType& 
    {
        floatHeap += 10;
        return f; 
    });

    std::cout << "Plus 10 to f using a lambda = " << f << std::endl;

    d.apply(plusTen);

    std::cout << "Plus 10 to d using a function pointer = " << d << std::endl;

    d.apply([&d](double& doubleHeap) -> DoubleType& 
    {
        doubleHeap += 10.0; 
        return d; 
    });

    std::cout << "Plus 10 to d using a lambda = " << d << std::endl;

    std::cout << "good to go!" << std::endl;
}
