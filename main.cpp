/*
 Project 4 - Part 3 / 9
 Video: Chapter 4 Part 3 
 Casting

 Create a branch named Part3
 
    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.

 1) remove your functions that accepted a User-Defined Type
 
 2) remove any getValue() functions if you added them
 
 3) move all of your add/subtract/multiply/divide implementations out of the class.
  
 4) add user-defined conversion functions that convert to the numeric type your object holds.
        i.e. if your type holds an int, you'll need an operator int() function.
 
 5) make your member variable private.
         this conversion function should be the ONLY WAY to access the held value.
 
 6) clean up any forward declaration that you might have.
 
 7) make sure it compiles & runs without errors.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */

//#TODO: remove -Wno-deprecated flag after learning rule of 3-5-0 in part7/8/9
#include <iostream>

struct FloatType
{
    FloatType(float);
    ~FloatType();
    operator float() const{return *floatTypeHeap;} FIXME this looks like crap
    FloatType& add(float rhs);
    FloatType& subtract(float rhs);
    FloatType& multiply(float rhs);
    FloatType& divide(float rhs);
    
    private:
    float* floatTypeHeap;
};

FloatType::FloatType(float floatValue)
{
    floatTypeHeap = new float(floatValue);
}

FloatType::~FloatType()
{
    delete floatTypeHeap;
}

FloatType& FloatType::add(float rhs)
{
    *floatTypeHeap += rhs;
    return *this; 
}

FloatType& FloatType::subtract(float rhs)
{
    *floatTypeHeap -= rhs;
    return *this;
}

FloatType& FloatType::multiply(float rhs)
{
    *floatTypeHeap *= rhs;
    return *this;
}

FloatType& FloatType::divide(float rhs)
{
    *floatTypeHeap /=rhs;
    return *this;
}

////////////////////////////////////////////////////////////////////////

struct DoubleType 
{
    DoubleType(double);
    ~DoubleType();
    operator double() const{return *doubleTypeHeap;} FIXME this looks like crap
    DoubleType& add(double rhs );
    DoubleType& subtract(double rhs );
    DoubleType& multiply(double rhs );
    DoubleType& divide(double rhs );
    
    private:
    double* doubleTypeHeap;
};

DoubleType::DoubleType(double doubleValue)
{
    doubleTypeHeap = new double(doubleValue);
}

DoubleType::~DoubleType()
{
    delete doubleTypeHeap;
}

DoubleType& DoubleType::add(double rhs)
{
    *doubleTypeHeap += rhs;
    return *this;
}

DoubleType& DoubleType::subtract(double rhs)
{
    *doubleTypeHeap -= rhs;
    return *this;
}

DoubleType& DoubleType::divide(double rhs)
{
    *doubleTypeHeap /= rhs;
    return *this;
}

DoubleType& DoubleType::multiply(double rhs)
{
    *doubleTypeHeap *= rhs;
    return *this;
}


/////////////////////////////////////////////////////////////////

struct IntType
{
    IntType(int);
    ~IntType();
    operator int() const{return *intTypeHeap;} FIXME this looks like crap
    IntType(const IntType& other); FIXME remove copy constructors
    IntType& add(int rhs );
    IntType& subtract(int rhs );
    IntType& multiply(int rhs );
    IntType& divide(int rhs );
    private:
    int* intTypeHeap = nullptr;
}; 

IntType::IntType(int intValue)
{
    intTypeHeap = new int(intValue);
}

IntType::~IntType()
{
    delete intTypeHeap;
}

IntType::IntType(const IntType& other)
{
    intTypeHeap = other.intTypeHeap;
}


IntType& IntType::add(int rhs)
{
    *intTypeHeap += rhs;
    return *this;
}

IntType& IntType::subtract(int rhs)
{
    *intTypeHeap -= rhs;
    return *this;
}


IntType& IntType::multiply(int rhs)
{
    *intTypeHeap *= rhs;
    return *this;
}

IntType& IntType::divide(int rhs)
{
    if (rhs == 0)
    {
        std::cout << "error divide by zero" << std::endl;
        *intTypeHeap = 0; 
    } 
    else 
    { 
        *intTypeHeap /= rhs;
    }

    return *this;
}

/////////////////////////////////////////////////////

int main()
{
    FloatType f(2.0f);
    DoubleType d(2.0);
    IntType i(2);

    auto fResult = f.multiply(i).divide(4.6f);

    auto dResult = d.multiply(4.4567).divide(f);

    auto iResult = i.add(10).subtract(d);

    std::cout << "multiplying f by i and dividing by 4.6 results in:" << fResult << std::endl;

    std::cout << "Multipying d by 4.4567 and dividing it by f results in: "<< dResult << std::endl;

    std::cout << "Adding 10 to i and subtracting d results in: "<< iResult << std::endl;

    std::cout << "good to go!" << std::endl;
}
