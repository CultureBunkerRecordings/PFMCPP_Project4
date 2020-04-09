
#include <iostream>
/*
Project 4: Part 7 / 9
Video: Chapter 5 Part 4

Create a branch named Part7

Do not delete your previous main. you will be adding to it.

Templates and Containers

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 

#1) if you're not using std::unique_ptr to own your heap-allocated type as a member variable, 
    replace your manual memory management techniques with a private std::unique_ptr member variable.

#2) replace your Heap-Allocated Numeric Type-owning class with a templated class called Numeric.
        replace all of your previous instances of your separate classes with this templated class.

#3) add a 'using <some name> = <your class template parameter>;' 
        treat this type declaration via 'using' as a static member variable
        use this Type alias as the argument everywhere you previously used the template argument.
        this will make it very easy to change the type if needed.
            i.e. if you have 'std::unique_ptr<NumericType> value;' before
                you'd replace NumericType in that variable declaration with '<some name>'
        
#4) you'll need to pair it with decltype() to help the compiler figure out the type of the object 
    your class owns when you make your lambda and free function that takes your unique_ptr.  
    i.e. like this for determining the template parameter of the unique_ptr function argument to your class's apply() function
        std::unique_ptr< decltype( <instance of class> )::<some name> >
    
#5) template your free function for the apply() that takes a function pointer so it can be used with your Wrapper class's apply() function

#6) add an explicit template specialization for 'double' of your wrapper class
        this template specialization will have one apply() function instead of 2. 

#7) this apply() function will be templated, and expect a Callable object, not std::function<>. 
        the function should allow for chaining.  
        the callable object should return void, like the function pointer-based apply() function in the primary class template

#8) instantiate your explicit template specialization

#9) call the apply function twice, once with a lambda and once with the free function
        the free function is templated, so you might need to call it including the template arguments.
        
#10) in addition to using the lambda argument to modify the owned object:  (your previous task's lambdas did this same thing) 
        make the lambda use your explicit template instance (maybe via a std::cout), 

#11) now that your class is templated, you'll need to adjust your logic in your division function to handle if your input is a zero or not, based on your templated type.  
        - look up how to use std::is_same<>::value on cppreference to determine the type of your template parameter.
        
        - look up how to use std::numeric_limits<>::epsilon() to determine if you're dividing by a floating point 0
        
        - read about Knuth's algorithm here: https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/

        - in plain-english, you'll need to implement logic like this:
        if your template type is an int
                if your parameter's type is also an int
                        if your parameter is 0
                                don't do the division
                else if it's less than epsilon
                        dont do the divison
        else if it's less than epsilon
                warn about doing the division

        - to make these checks work during compilation, your if() statements will need to be 'constexpr':  if constexpr (expression)

compile/link/run to make sure you don't have any errors

Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.

If you need to view an example, see: https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part7Example.cpp
*/





//#TODO: remove -Wno-deprecated flag after learning rule of 3-5-0 in part7/8/9
#include <iostream>
#include <cmath>
#include <functional>
#include <memory>

//forward declare

// struct FloatType;
// struct DoubleType;
//struct IntType;

//IntType definition /////////////////////////////////////////////
template<typename T>
struct Numeric
{
    using MyType = T;
    Numeric(MyType value): numericHeap(std::make_unique<MyType>(value)){}
    ~Numeric() = default;
    
    operator MyType() const 
    {
        return *numericHeap;
    }

    Numeric& operator+=(const MyType other)
    {
        *numericHeap += other;
        return *this;
    }

    Numeric& operator-=(const MyType other)
    {
        *numericHeap -= other;
        return *this;
    }

    Numeric& operator/=(const MyType other)
    {
        if (other == 0.0f)
            {
                std::cout << "error divide by zero" << std::endl; 
            } 
        else 
            { 
                *numericHeap /= other;
            }
        return *this;
    }

    Numeric& operator*=(const MyType other)
    {
        *numericHeap *= other;
        return *this;
    }
    template<typename X>
    Numeric& apply(X numericFunc)
    {
        numericFunc(numericHeap);
        return *this;
    }

    
    Numeric& apply(void(*numericFunc)(std::unique_ptr<MyType>&))
    {
        numericFunc(numericHeap);
        return *this;
    }

    Numeric& pow(MyType power)
    {
        *numericHeap = powInternal(power);
        return *this;
    }

    Numeric& pow(const Numeric& doubleRef)
    {
        *numericHeap = (powInternal(static_cast<MyType>(doubleRef)));
        return *this;
    }

private:
    MyType powInternal(MyType power)
    {
        return static_cast<MyType>(std::pow(*numericHeap, power));
    }
    
    std::unique_ptr<MyType> numericHeap = nullptr;
}; 

template<>
struct Numeric<double>
{
    using MyType = double;
    Numeric(MyType value): numericHeap(std::make_unique<MyType>(value)){}
    ~Numeric() = default;
    
    operator MyType() const 
    {
        return *numericHeap;
    }

    Numeric& operator+=(const MyType other)
    {
        *numericHeap += other;
        return *this;
    }

    Numeric& operator-=(const MyType other)
    {
        *numericHeap -= other;
        return *this;
    }

    Numeric& operator/=(const MyType other)
    {
        if (other == 0.0)
            {
                std::cout << "error divide by zero" << std::endl; 
            } 
        else 
            { 
                *numericHeap /= other;
            }
        return *this;
    }

    Numeric& operator*=(const MyType other)
    {
        *numericHeap *= other;
        return *this;
    }
    template<typename X>
    Numeric& apply(X numericFunc)
    {
        numericFunc(numericHeap);
        return *this;
    }

    Numeric& pow(MyType power)
    {
        *numericHeap = powInternal(power);
        return *this;
    }

    Numeric& pow(const Numeric& doubleRef)
    {
        *numericHeap = (powInternal(static_cast<MyType>(doubleRef)));
        return *this;
    }

private:
    MyType powInternal(MyType power)
    {
        return static_cast<MyType>(std::pow(*numericHeap, power));
    }
    
    std::unique_ptr<MyType> numericHeap = nullptr;
}; 

//Point definition ///////////////////////////////////////////

struct Point
{
    Point(float xy) : Point(xy, xy) { }  //This calls the constructor below.
    Point(float _x, float _y) : x(_x), y(_y) { }
    Point& multiply(float m);
    Point& multiply(Numeric<float>& m);
    void toString();
private:
    float x{0}, y{0};
};

//Point Implementation ///////////////////////////////////////////

Point& Point::multiply(float m)
{
    x *= m;
    y *= m;
    return *this;
}


Point& Point::multiply(Numeric<float>& m)
{
    return multiply(static_cast<float>(m));
}

void Point::toString()
{
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
}

//Free funcs ///////////////////////////////////////////
template <typename T>
void plusTen(std::unique_ptr<T>& heap)
{
    *heap += 10;
}

//MAIN ///////////////////////////////////////////

int main()
{
    Numeric<float> f(2.0f);
    Numeric<double> d(2.0);
    Numeric<int> i(2);

    std::cout << "i = " << i << std::endl;
    std::cout << "f = " << f << std::endl;
    std::cout << "d = " << d << std::endl;

    Point p(f);

    f.pow(i) /= 4.6f;

    d.pow(static_cast<double>(f)) *= 4.4567;

    i.pow(static_cast<int>(d)) += 10; 

    i /= 0;

    p.multiply(i).toString();

    p.multiply(f).toString();

    std::cout << "f by the power of  i and dividing by 4.6.. f: " << f << std::endl;

    std::cout << "d to the power of f times 4.4567.. d:  "<< d << std::endl;

    std::cout << "i to the power of d plus 10.. i: " << i << std::endl;

    i.apply(plusTen);

    std::cout << "Plus 10 to i using a function pointer = " << i << std::endl;

    using IntType = decltype(i);
    using FloatType = decltype(f);
    using DoubleType = decltype(d);

    i.apply([&i](std::unique_ptr<IntType::MyType>& IntHeap) -> IntType& 
    { 
        *IntHeap += 10;
        return i; 
    });

    std::cout << "Plus 10 to i using a lambda = " << i << std::endl;

    f.apply(plusTen);

    std::cout << "Plus 10 to f using a function pointer = " << f << std::endl;

    f.apply([&f](std::unique_ptr<FloatType::MyType>& FloatHeap) -> FloatType& 
    {
        *FloatHeap += 10;
        return f; 
    });

    std::cout << "Plus 10 to f using a lambda = " << f << std::endl;

    d.apply([&d](std::unique_ptr<DoubleType::MyType>& doubleHeap) -> DoubleType& 
    {
        *doubleHeap += 10.0; 
        return d; 
    });

    std::cout << "Plus 10 to d using a lambda = " << d << std::endl;

    std::cout << "good to go!" << std::endl;
}
