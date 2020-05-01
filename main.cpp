
/*
Prject 4: Part 8 / 9
 video: Chapter 5 Part 6 Task 

Create a branch named Part8

 R-Values L-Values Move Semantics.

 This Task is going to demonstrate R-Values and writing Generic Code

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 
 
 Edit your Chapter 5 Part 4 Task and replace its instructions with these instructions
 
 Your job is to replace the owned type (the primitive specified by your template argument) from the 
     Templated Class you created in Ch5 p04 with a struct named Temporary that can behave ENTIRELY as a temporary object.
 
 That means you must use conversion functions to interact with what it owns.
 
 You need to figure out how to use conversion functions to be able to GET and SET the 'value' member variable.
    hint: conversion functions can return by value and also by ___...
  
 1) Here is a starting point for how to implement your Temporary struct.
 */
#include <cmath>
#include <iostream>
#include <functional>
#include <memory>
#include <typeinfo>

template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    /*
     revise these conversion functions to read/write to 'v' here
     hint: what qualifier do read-only functions usually have?
     */
    operator NumericType() const { return v;/* read-only function */ }
    operator NumericType&() { return v;/* read/write function */ }
private:
    static int counter;
    NumericType v;
};

/*
 2) add the definition of Temporary::counter here, which is a static variable and must be defined outside of the class.
    Remember the rules about how to define a Template member variable/function outside of the class.
*/
template<typename NumericType> int Temporary<NumericType>::counter = 0;
/*
 3) You'll need to template your overloaded math operator functions in your Templated Class from Ch5 p04
    use static_cast to convert whatever type is passed in to your template's NumericType before performing the +=, -=, etc.  here's an example implementation:
 */
// namespace example
// {
// template<typename NumericType>
// struct Numeric
// {
//     //snip
//     template<typename OtherType>
//     Numeric& operator-=(const OtherType& o) 
//     { 
//         *value -= static_cast<NumericType>(o); 
//         return *this; 
//     }
//     //snip
// };
// }

/*
 4) remove your specialized <double> template of your Numeric<T> class from the previous task (ch5 p04)
    replace the 2 apply() functions in your Numeric<T> with the single templated apply() function from the specialized <double> template.
 */

/*
 5) Template your pow() function the same way you templated the overloaded math operators
    Remove the call to powInternal() and just call std::pow() directly.
    you'll need to static_cast<> the pow() argument the same way you did in the overloaded math operators, when you pass it to std::pow()
 */
/*
 
 6) Finally, your conversion function in your templated class is going to be returning this Temporary, 
        so you should probably NOT return by copy if you want your templated class's owned object to be modified by any math operation.
    See the previous hint for implementing the conversion functions for the Temporary if you want to get the held value
*/


/*
 7)   replace main() with the main below

 If you did everything correctly, this is the output you should get:
 
I'm a Temporary<f> object, #0
I'm a Temporary<i> object, #0
I'm a Temporary<d> object, #0
f: -1.89
d: -3.024
i: -9
Point { x: -1.89, y: -9 }
d: 3.024
I'm a Temporary<d> object, #1
I'm a Temporary<d> object, #2
d: 1.49519e+08
Point { x: -2.82591e+08, y: -1.34567e+09 }
I'm a Temporary<f> object, #1
I'm a Temporary<i> object, #1
I'm a Temporary<i> object, #2
I'm a Temporary<i> object, #3
intNum: 5
I'm a Temporary<f> object, #2
f squared: 3.5721
I'm a Temporary<f> object, #3
f cubed: 45.5796
I'm a Temporary<d> object, #3
d squared: 2.2356e+16
I'm a Temporary<d> object, #4
d cubed: 1.11733e+49
I'm a Temporary<i> object, #4
i squared: 81
I'm a Temporary<i> object, #5
i cubed: 531441

Use a service like https://www.diffchecker.com/diff to compare your output. 

Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
*/

//#TODO: remove -Wno-deprecated flag after learning rule of 3-5-0 in part7/8/9


template<typename T>
struct Numeric
{
    using MyType = Temporary<T>;
    
    Numeric(MyType value): numericHeap(std::make_unique<MyType>(value)){}
    
    ~Numeric() = default;

    operator T() const  
    {
        return *numericHeap;
    }


    operator T&()  
    {
        return *numericHeap;
    }

    template<typename OtherType>
    Numeric& operator=(const OtherType& other)
    {
        *numericHeap = static_cast<T>(other);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator+=(const OtherType& other)
    {
        *numericHeap += static_cast<T>(other);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator-=(const OtherType& other)
    {
        *numericHeap -= static_cast<T>(other);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator/=(const OtherType& other)
    {
        // - in plain-english, you'll need to implement logic like this:
        // if your template type is an int
        //         if your parameter's type is also an int
        //                 if your parameter is 0
        //                         don't do the division
        //         else if it's less than epsilon
        //                 dont do the divison
        // else if it's less than epsilon
        //        warn about doing the division
        if constexpr(std::is_same<int, T>::value)
        {
            if constexpr(std::is_same<decltype(other), int>::value)
            {
                if (other == 0)
                {
                    return *this;
                }
            }
            else if (std::abs(other)<= std::numeric_limits<OtherType>::epsilon())
            {
                return *this;
            }
        }
        else if (std::abs(other)<= std::numeric_limits<OtherType>::epsilon())
        {
            std::cout<<"Warning division by zero";
        }
        *numericHeap /= static_cast<T>(other); 
        return *this;
    }

    template<typename OtherType>
    Numeric& operator*=(const OtherType& other)
    {
        *numericHeap *= static_cast<T>(other);
        return *this;
    }
    
    template<typename X>
    Numeric& apply(X numericFunc)
    {
        numericFunc(numericHeap);
        return *this;
    }
    template<typename OtherType>
    Numeric& pow(const OtherType& power)
    {
        *numericHeap = std::pow(*numericHeap, static_cast<T>(power));
        return *this;
    }

private:
    std::unique_ptr<MyType> numericHeap;
}; 


//Point definition ///////////////////////////////////////////

struct Point
{
    Point(float xy) : Point(xy, xy) { }  //This calls the constructor below.
    Point(float _x, float _y) : x(_x), y(_y) { }
    operator float() const { return x * y; }

    template <typename T>
    Point& multiply(const T& m);

    void toString();
private:
    float x{0}, y{0};
};

//Point Implementation ///////////////////////////////////////////
template <typename T>
Point& Point::multiply(const T& m)
{
    x *= static_cast<float>(m);
    y *= static_cast<float>(m);
    return *this;
}

void Point::toString()
{
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
}

//Free funcs ///////////////////////////////////////////
template <typename T>
void cube(std::unique_ptr<T>& heap)
{
    *heap = *heap * *heap * *heap;
}

//MAIN ///////////////////////////////////////////

int main()
{
    Numeric<float> f(0.1f);
    Numeric<int> i(3);
    Numeric<double> d(4.2);
    
    f += 2.f;
    f -= i;
    f *= d;
    f /= 2.f;
    std::cout << "f: " << f << std::endl;
    
    d += 2.f;
    d -= i;
    d *= f;
    d /= 2.f;
    std::cout << "d: " << d << std::endl;
    
    i += 2.f; i -= f; i *= d; i /= 2.f;
    std::cout << "i: "<< i << std::endl;
    
    Point p(f, i);
    p.toString();
    
    d *= -1;
    std::cout << "d: " << d << std::endl;
    
    p.multiply(d.pow(f).pow(i));
    std::cout << "d: " << d << std::endl;
    
    p.toString();
    
    Numeric<float> floatNum(4.3f);
    Numeric<int> intNum(2);
    Numeric<int> intNum2(6);
    intNum = 2 + (intNum2 - 4) + static_cast<double>(floatNum) / 2.3;
    std::cout << "intNum: " << intNum << std::endl;
    
    {
        using Type = decltype(f)::MyType;
        f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;
        
        f.apply( cube<Type> );
        std::cout << "f cubed: " << f << std::endl;
    }
    
    {
        using Type = decltype(d)::MyType;
        d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;
        
        d.apply( cube<Type> );
        std::cout << "d cubed: " << d << std::endl;
    }
    
    {
        using Type = decltype(i)::MyType;
        i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;
        
        i.apply( cube<Type> );
        std::cout << "i cubed: " << i << std::endl;
     }
}
