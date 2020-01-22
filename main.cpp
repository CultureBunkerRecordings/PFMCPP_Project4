/*
Project 4: Part 4 / 9
 Chapter 4 Part 7
 Function/Constructor Overloading

 Create a branch named Part4

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add pow() functions, and a powInternal() function to each of your UDTs
     a) your pow() functions should call powInternal()
     b) add a pow() whose argument type is the primitive your UDT owns.  the argument should be passed by copy.
     c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
         the argument should be passed as const ref
         i.e. if you had UDTs named IntType, FloatType, DoubleType
             in your IntType class, you'd have:
                 pow(const IntType&),
                 pow(const FloatType&),
                 pow(const DoubleType&),
                 and pow(int)
     d) be sure to remember the rules about what member functions can be called on const objects.
             (const objects can only call their const member functions)
 
 2) your powInternal() function should do something like this in its body:    *val = std::pow( *val, arg );
         where 'arg' is the passed-in type, converted to whatever type your object is holding.
             if your UDT owns an int, then arg would be an int.
             if your UDT owns a float, then arg would be a float.
         std::pow's documentation is found here: https://en.cppreference.com/w/cpp/numeric/math/pow so be sure to include
             the proper header file listed there.
 
 3) modify the Point class below to have Constructors that accept your UDTs.
     a) make the Constructor's UDT arguments initialize the Point class's two member variables.
     b) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     c) add a toString() function to the Point class that prints out the x and y members via std::cout.
 
 4) clear out your old main()
     a) use your new pow() function in main for all of your types and print out the results.
     b) use the Point class in main and multiply some Point instances with your UDTs
     c) use the Point::toString() function to print out the results.
 
 
 5) make sure it compiles without errors.
 
 You will need to use Forward Declaration and out-of-class definitions to complete this.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */

struct Point
{
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
private:
    float x{0}, y{0};
};

int main()
{
    
}


//#TODO: remove -Wno-deprecated flag after learning rule of 3-5-0 in part7/8/9
#include <iostream>

struct FloatType
{
    FloatType(float);
    ~FloatType();
    operator float() { return *floatTypeHeap; }
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
    operator double() { return *doubleTypeHeap; }
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
    operator int() { return *intTypeHeap; } 
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

    float fResult = f.multiply(i).divide(4.6f);

    double dResult = d.multiply(4.4567).divide(f);

    int iResult = i.add(10).subtract(d); 

    std::cout << "multiplying f by i and dividing by 4.6 results in: " << fResult << std::endl;

    std::cout << "Multipying d by 4.4567 and dividing it by f results in: "<< dResult << std::endl;

    std::cout << "Adding 10 to i and subtracting d results in: "<< iResult << std::endl;

    std::cout << "good to go!" << std::endl;
}
