
#include <iostream>
/*
Project 4: Part 5 / 9
 video: Chapter 5 Part 2
 Operator Overloading.

 Create a branch named Part5

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) replace the add/subtract/multiply/etc functions with overloaded math operators 
        e.g. add() would become operator+=() because it modifies the internal heap-allocated object.
 
 2) Your overloaded operators should only take primitives, passed by value.
 
 3) don't delete your conversion functions.
         if you removed them in Chapter 4 Part 7, put them back in.
         uncomment them if you commented them in Chapter 4 Part 7
 
 4) your main() function should be the same as Chapter 4 Part 7
     
 5) if your Chapter4 Part7 task didn't use any [+ - * or /], 
         add some in and fix the build errors that might result via the techniques you have learned in the previous weeks (hint: casting)
         i.e.
 */

 /*
 6) compile/link/run to make sure you don't have any errors
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */


//#TODO: remove -Wno-deprecated flag after learning rule of 3-5-0 in part7/8/9
#include <iostream>
#include <cmath>

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
    Point& multiplyInternal(float m);
    float x{0}, y{0};
};


//IntType definition /////////////////////////////////////////////

struct IntType
{
    IntType(int);
    ~IntType();
    operator int() const { return *intTypeHeap; }
    
    IntType& operator+=( const int other);
    IntType& operator-=(const int other);
    IntType& operator/=( const int other);
    IntType& operator*=(const int other);

    IntType& operator=(const IntType& other);

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

    FloatType& operator+=( const float other);
    FloatType& operator-=(const float other);
    FloatType& operator/=( const float other);
    FloatType& operator*=(const float other);

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

    DoubleType& operator+=( const double other);
    DoubleType& operator-=(const double other);
    DoubleType& operator/=( const double other);
    DoubleType& operator*=(const double other);

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
    return multiplyInternal(m);
}

Point& Point::multiplyInternal(float m)
{
    x *= m;
    y *= m;
    return *this;
}

Point& Point::multiply(IntType& m)
{
    return multiplyInternal(m);
}

Point& Point::multiply(FloatType& m)
{
    return multiplyInternal(m);
}

Point& Point::multiply(DoubleType& m)
{
    return multiplyInternal(static_cast<float>(m));
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
        *intTypeHeap = 0; 
    } 
    else 
    { 
        *intTypeHeap /= other;
    }
    return *this;
}

IntType& IntType::operator=(const IntType& other)
{
    *intTypeHeap = *other.intTypeHeap;
    return *this;
}

IntType& IntType::operator*=(const int other) 
{
    *intTypeHeap *= other;
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
    *intTypeHeap = powInternal(doubleRef);
    return *this;
}

int IntType::powInternal(int power)
{
    return std::pow(*intTypeHeap, power);
}

IntType& IntType::pow(const FloatType& floatRef)
{
    *intTypeHeap = static_cast<int>(powInternal(floatRef));
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
    *floatTypeHeap = static_cast<float>(powInternal(doubleRef)); 
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
    *doubleTypeHeap = static_cast <double> (powInternal(floatRef));
    return *this;
}

DoubleType& DoubleType::pow(const DoubleType& doubleRef)
{
    *doubleTypeHeap = powInternal(doubleRef);
    return *this;
}

double DoubleType::powInternal(double power)
{
    return std::pow(*doubleTypeHeap, power); 
}

//MAIN ///////////////////////////////////////////

int main()
{
    FloatType floatNum(4.3f);
    IntType intNum(2);
    IntType intNum2(6);

    /* 
    if you previously had a line like this demonstrating chaining:
        
        intNum.add(3).add(4.5f).divide(floatNum); 

    it should become:
    */

    intNum += 3;
    intNum += 4.5f;
    intNum /= floatNum;
    std::cout << "intNum: " << intNum << std::endl;

    intNum = 2 + (intNum2 - 4) + floatNum / 2.3;
     std::cout << "intNum: " << intNum << std::endl;
        
    return 0;
}
