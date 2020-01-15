/*
 Project 4 - Part 1 / 9
 video: Chapter 2 Part 7
 Returning Values tasks 

 Create a branch named Part1
 
 1) write 3 UDTs named FloatType, DoubleType, IntType.
 
 2) give each UDT the following member functions:
        add( lhs, rhs );
        subtract( lhs, rhs );
        multiply( lhs, rhs );
        divide( lhs, rhs );
 
 3) make them return the correct primitive type. e.g. if you're implementing the FloatType::add function, your implementation would start like this:
        float FloatType::add( float lhs, float rhs )
 
 4) declare a few instances of each class in main() and call the member functions with the appropriate arguments.
        FloatType ft;
        auto result = ft.add(3.2f, 23.f );
 
 5) print out those results using std::cout:
        std::cout "result of ft.add(): " << result << std::endl;
 
 6) After you finish defining each type/function, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */
#include <iostream>

struct FloatType
{
    float add( float lhs, float rhs );
    float subtract( float lhs, float rhs );
    float multiply( float lhs, float rhs );
    float divide( float lhs, float rhs );
};

float FloatType::add( float lhs, float rhs )
{
    return  lhs + rhs;
}

float FloatType::subtract( float lhs, float rhs )
{
    return lhs - rhs;
}

float FloatType::multiply( float lhs, float rhs )
{
    return lhs * rhs;
}

float FloatType::divide( float lhs, float rhs )
{
    if (rhs == 0.0f)
    {
        std::cout<<"error divide by zero"<<std::endl;
        return 0.0f;
    }
    return lhs/rhs;
}

struct DoubleType 
{
    double add( double lhs, double rhs );
    double subtract( double lhs, double rhs );
    double multiply( double lhs, double rhs );
    double divide( double lhs, double rhs );
};

double DoubleType::add(double lhs, double rhs)
{
    return lhs + rhs;
}

double DoubleType::subtract(double lhs, double rhs)
{
    return lhs - rhs;
}

double DoubleType::divide(double lhs, double rhs)
{
    if (rhs == 0.0)
    {
        std::cout << "error divide by zero"<<std::endl;
        return 0.0;
    }
    return lhs/rhs;
}

double DoubleType::multiply(double lhs, double rhs)
{
    return lhs * rhs;
}


struct IntType
{
    int add( int lhs, int rhs );
    int subtract( int lhs, int rhs );
    int multiply( int lhs, int rhs );
    int divide( int lhs, int rhs );
};

int IntType::add(int lhs, int rhs)
{
    return lhs+rhs;
}

int IntType::subtract(int lhs, int rhs)
{
    return lhs-rhs;
}

int IntType::multiply(int lhs, int rhs)
{
    return lhs*rhs;
}

int IntType::divide(int lhs, int rhs)
{
    if (rhs == 0)
    {
        std::cout<<"error divide by zero"<<std::endl;
        return 0;
    }
    return lhs/rhs;
}

int main()
{
    FloatType f;
    IntType i;
    DoubleType d;
    auto addF = f.add(2.5f, 6.5f);
    auto subF = f.subtract(2.5f, 6.5f);
    auto divI = i.divide(8, 2);
    auto multiD = d.multiply(4.4567, 3.7899765);
    auto subD = d.subtract(45.6784, 20.7895);

    std::cout<< "result of f.add(): "<<addF<<std::endl;
    std::cout<< "result of f.subtract(): "<<subF<<std::endl;
    std::cout<< "result of i.divide(): "<<divI<<std::endl;
    std::cout<< "result of d.multiply(): "<<multiD<<std::endl;
    std::cout<< "result of d.subtract(): "<<subD<<std::endl;

    std::cout << "good to go!" << std::endl;
}
