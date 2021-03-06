//============================================================================
// Name        : PolynomialSolver_IntervalBisection_VS_SecantMethod
// Author      : oguzhan-baser
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>

using namespace std;
//calculateFunction is a method to calculate a function value f(x) whose polynomial coefficient information and input value x are given as arguments
double calculateFunction(int* coeffs, int numOfTerms, double x){
	double result = 0;//initializes a double value to store result of the function
	for(int z =0;z<numOfTerms;z++){//iterates on each term/coefficient of the polynomial expression, i.o.w. calculates current term and adds it into the result already calculated
		result += (*(coeffs+z))*pow(x,z);
	}
	return result;//returns to final overall result calculated
}
//intervalBisection is a method to perform interval bisection method for one times
//this method calculates the function/output value of the midpointand and corresponding midpoint take place of the initial point with the same sign
void intervalBisection(int* coeffs, int numOfTerms, double &smallerGuess , double &biggerGuess){
	double midPoint = smallerGuess + ((biggerGuess-smallerGuess)/2);//calculates the midpoint without overflow
	double Fmidpoint = calculateFunction(coeffs, numOfTerms, midPoint);//calculates the function value of the midpoint
	double FSmallerGuess = calculateFunction(coeffs,numOfTerms,smallerGuess);//calculates the function for smaller initial guess x
	if (Fmidpoint*FSmallerGuess > 0){//if they have same sign then
		smallerGuess = midPoint;//smallerGuess variable takes the value of the midPoint value
	}
	else{//if their sign is different
		biggerGuess = midPoint;//biggerGuess variable takes the value of the midPoint value
	}
}
//secant is a method to find the root of a nonlinear/polynomial functions. Details of the method discussed in readme file of the repo.
void secant(int* coeffs, int numOfTerms, double &formerValue, double &currentValue){
	//following line is simply the equation to get next value of x variable. The formula is discussed in "readme" part
	double nextValue = currentValue - (calculateFunction(coeffs, numOfTerms, currentValue)*((currentValue-formerValue)/(calculateFunction(coeffs, numOfTerms, currentValue) - calculateFunction(coeffs, numOfTerms, formerValue))));
	formerValue = currentValue;//updates the former value with the current one
	currentValue = nextValue;//updates the current value with the just calculated one

}

int main(int argc, char** argv) {
	int* coeffs;//a variable to store the coefficients of a polynomial which is a0 + a1*x+ a2*x^2 + a3*x^3 ... stores the coefficients as [a0,a1,a2,a3...]
	int numOfTerms = argc-4;//a variable to store the total number of terms in the polynomial expression
	coeffs = new int[numOfTerms];
	for(int m=0; m<numOfTerms;m++){//gives the appropriate values to this coefficient array starts from the a0 and goes to an
		*(coeffs+(numOfTerms-1-m)) = atoi(argv[m+1]); //assigns value, starts from the end
	}
	double initialGuess1 = atof(argv[argc-3]);//takes the smaller initial guess
	double initialGuess2 = atof(argv[argc-2]);//takes the bigger one
	double tolerance = atof(argv[argc-1]);//takes the tolerance value
	int numIterations;//a variable to store total number of iterations while reaching to the result with proper tolerance
	double smallerGuess;//a variable to store smaller value iterated by algorithms say x0
	double biggerGuess;// a variable to store bigger value iterated by the algorithms say x1
	cout<<"...................BISECTION STARTS....................."<<endl;
	numIterations=0;//assigns the number of iterations as 0 before an iteration starts
	smallerGuess = initialGuess1;//assigns initial smaller guess as first argument got from command line
	biggerGuess = initialGuess2;//assigns initial bigger  guess as second argument got from command line
	while(abs(biggerGuess-smallerGuess)>tolerance){//applies the algorithm as long as aimed tolerance is reached
		intervalBisection(coeffs, numOfTerms, smallerGuess, biggerGuess);//applies the bisection method for 1 time
		numIterations++;//increases iteration num by 1
		}
	cout<<"the result is: "<<(smallerGuess/2+biggerGuess/2)<<endl;
	cout<<"Num of iterations: "<<numIterations<<endl;
	cout<<"...................BISECTION ENDS......................"<<endl<<endl;

	cout<<"...................SECANT STARTS....................."<<endl;
		numIterations=0;//assigns the number of iterations as 0 before an iteration starts
		smallerGuess = initialGuess1;//assigns initial smaller guess as first argument got from command line
		biggerGuess = initialGuess2;//assigns initial bigger  guess as second argument got from command line
		while(abs(biggerGuess-smallerGuess)>tolerance){//applies the algorithm as long as aimed tolerance is reached
			secant(coeffs, numOfTerms, smallerGuess, biggerGuess);//applies the secant method for 1 time
			numIterations++;//increases iteration num by 1
			}
		cout<<"the result is: "<<(smallerGuess/2+biggerGuess/2)<<endl;
		cout<<"Num of iterations: "<<numIterations<<endl;
	cout<<"...................SECANT ENDS......................"<<endl<<endl;

	cout<<"...................HYBRID STARTS....................."<<endl;
		numIterations=2;//assigns the number of iterations as 0 before an iteration starts,, already for the interval bisection method
		smallerGuess = initialGuess1;//assigns initial smaller guess as first argument got from command line
		biggerGuess = initialGuess2;//assigns initial bigger  guess as second argument got from command line
		intervalBisection(coeffs, numOfTerms, smallerGuess, biggerGuess);//two times interval bisection as described in in the "readme"
		intervalBisection(coeffs, numOfTerms, smallerGuess, biggerGuess);

		while(abs(biggerGuess-smallerGuess)>tolerance){//applies the algorithm as long as aimed tolerance is reached
			secant(coeffs, numOfTerms, smallerGuess, biggerGuess);//applies the secant method for 1 time
			numIterations++;
			}
		cout<<"the result is: "<<(smallerGuess/2+biggerGuess/2)<<endl;
		cout<<"Num of iterations: "<<numIterations<<endl;
	cout<<"...................HYBRID ENDS......................"<<endl;
	delete[] coeffs;

	return 0;
}


