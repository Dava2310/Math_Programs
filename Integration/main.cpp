/*
    Developed by: Daniel Vetencourt, 22/02/23
    In this program, we will be using two methods: 

    Integration by Newton Cotes, and Integration by Simpson with 1/3

*/

#include <iostream>
#include <cmath>

using namespace std;

double evaluateFunction(double);
double cotesSimple();
double cotesMultiple();
double simpsonSimple();
double simpsonMultiple();

// Main function
int main() 
{

    int option = 0;
    double error, trueValue, result;
    bool pass = true;

    // Menu of options
    cout << "\t\tWelcome to the Integration Method Program." << endl;

    cout << "1- Integration By Newton Cotes - Simple" << endl;
    cout << "2- Integration By Newton Cotes - Multiple" << endl;
    cout << "3- Integration By Simpson 1/3 - Simple" << endl;
    cout << "4- Integration By Simpson 1/3 - Multiple" << endl;

    cout << "\nEnter the option between 1 - 4: ";
    cin >> option;

    cout << endl;

    // Depending of which option, it will join into the needed by the user
    switch (option)
    {
        case 1:
            result = cotesSimple();
            break;
        
        case 2:
            result = cotesMultiple();
            break;

        case 3:
            result = simpsonSimple();
            break;

        case 4:
            result = simpsonMultiple();
            break;

        default:
            cout << "You have inserted a different option " << endl;
            pass = false;
            break;
    }

    // In case the user gave a valid option
    if (pass) 
    {

        // Print the final result
        cout << "\t\t=================== FINAL RESULT ================= " << endl << endl;

        cout << "Result = " << result << endl << endl;

        if (result == 0)
        {
            cout << "It is likely that an error have ocurred on the procedure." << endl;
            return 0;
        }

        char answer = 'Y';

        // Calculation of the error
        cout << "Do you want to calculate the error (Y/N): ";
        cin >> answer;

        if (answer == 'Y' || answer == 'y') 
        {

            cout << "\nInsert the true value of the integral: ";
            cin >> trueValue;

            error = ((trueValue - result) / trueValue) * 100;

            cout << "\nError = ";
            printf("%.8f%\n", error);
        }
    }

    cout << "Bye!\n" << endl;
    return 0;
}

// In this function, we evaluate the function in a specific X point
double evaluateFunction(double x)
{
    double result;

    // Change this next line if you want to use a different function 
    result = 0.2 + (25 * x) - (200 * pow(x, 2)) + (675 * pow(x, 3)) - (900 * pow(x, 4)) + (400 * pow(x, 5));

    return result;
}

double cotesSimple()
{

    // Declaration of variables

    double a, b, F_a, F_b;
    double finalResult;

    // Step 1: Definition of A and B
    cout << "Step 1: Definition of a and b." << endl << endl;

    cout << "Insert the inferior limit (a): ";
    cin >> a;

    cout << "\n";

    cout << "Insert the superior limit (b): ";
    cin >> b;

    cout << "\n";

    // Step 2: Evaluate the function with a and b

    // Calculating F(a) and F(b)
    F_a = evaluateFunction(a);
    F_b = evaluateFunction(b);

    cout << "Step 2: Calculate F(a) and F(b)." << endl << endl;
    cout << "F(a) = " << F_a << endl;
    cout << "F(b) = " << F_b << endl;

    // Step 3: Calculating the Integral (aprox.)
    finalResult = (b - a) * ( (F_a + F_b) / (2) );

    return finalResult;
}

double cotesMultiple()
{
    // Declaration of variables

    double a, b, h;
    int n;
    double finalResult;

    // Step 1: Definition of A and B
    cout << "Step 1: Definition of a and b." << endl << endl;

    cout << "Insert the inferior limit (a): ";
    cin >> a;

    cout << "\n";

    cout << "Insert the superior limit (b): ";
    cin >> b;

    cout << "\n";

    // Step 2: Definition of n
    cout << "Step 2: Defintion of n." << endl << endl;
    cout << "Insert n (n have to be equal or more than 2): ";
    cin >> n;

    if (n < 2) 
    {
        return 0;
    }

    cout << "\n";

    // Step 3: Calculating h (the equal distance between each two points)
    
    h = (b - a) / n;
    
    cout << "Step 3: Calculation of H." << endl << endl;
    cout << "H = " << h << endl << endl;

    // Step 4: Calculating all the functions f(x_i)

    double functions[n + 1];
    double intermediumPoints = 0.0;

    cout << "Step 4: Calculating all functions f(xi)." << endl << endl;

    for (int i = 0; i <= n; i++) 
    {
        functions[i] = evaluateFunction(a + (h * i));

        cout << "F(" << (a + (h * i)) << ") = " << functions[i] << endl;

        // If i is different than 0 and different than n, it means it is an intermedium point
        if (i != 0 && i != n) 
        {
            intermediumPoints += functions[i];
        }
    }
    cout << endl;

    // Step 5: Calculating the Integral

    finalResult = (b - a) * ( ( functions[0] + (2 * intermediumPoints) + functions[n]) / (2 * n));

    return finalResult;
}

double simpsonSimple()
{
    // Declaration of variables

    double a, b, F_a, F_b, h, F_h;
    double finalResult;

    // Step 1: Definition of A and B
    cout << "Step 1: Definition of a and b." << endl << endl;

    cout << "Insert the inferior limit (a): ";
    cin >> a;

    cout << "\n";

    cout << "Insert the superior limit (b): ";
    cin >> b;

    cout << "\n";

    // Step 2: Calculating h (the equal distance between each two points)

    h = (b - a) / 2;

    cout << "Step 2: Calculating h." << endl << endl;

    cout << "H = " << h << endl << endl;

    // Step 3: Calculating F(a) ; F(b) ; F(h)
    F_a = evaluateFunction(a);
    F_b = evaluateFunction(b);
    F_h = evaluateFunction(h);

    cout << "Step 3: Calculate F(a) ; F(b) ; F(h)" << endl << endl;
    cout << "F(a) = " << F_a << endl;
    cout << "F(b) = " << F_b << endl;
    cout << "F(h) = " << F_h << endl;

    cout << "\n";

    // Step 4: Calculating the Integral (aprox.)
    finalResult = (b - a) * ( (F_a + (4 * F_h) + F_b) / 6);

    return finalResult;
}


double simpsonMultiple() 
{
    
    // Declaration of variables

    double a, b, h;
    int n;
    double finalResult;

    // Step 1: Definition of A and B
    cout << "Step 1: Definition of a and b." << endl << endl;

    cout << "Insert the inferior limit (a): ";
    cin >> a;

    cout << "\n";

    cout << "Insert the superior limit (b): ";
    cin >> b;

    cout << "\n";

    // Step 2: Definition of n
    cout << "Step 2: Defintion of n." << endl << endl;
    cout << "Insert n (n have to be more than 2): ";
    cin >> n;

    if (n <= 2) 
    {
        return 0;
    }

    cout << endl;

    // Step 3: Calculating h (the equal distance between each two points)

    h = (b - a) / n;

    cout << "Step 3: Calculating h." << endl << endl;

    cout << "H = " << h << endl << endl;

    // Step 4: Calculating all the functions f(x_i)

    double functions[n + 1];
    double pairs = 0.0, odds = 0.0;

    cout << "Step 4: Calculating all functions f(xi)." << endl << endl;

    for (int i = 0; i <= n; i++)
    {

        functions[i] = evaluateFunction(a + (h * i));

        cout << "F(" << (a + (h * i)) << ") = " << functions[i] << endl;

        // If it is not the first and last term
        if (i != 0 && i != n)
        {

            // If i is pair
            if (i % 2 == 0) 
            {
                pairs += functions[i];
            }
            // If i is odd
            else
            {
                odds += functions[i];
            }

        }
    }

    // Step 5: Calculating the integral

    finalResult = (b - a) * ( (functions[0] + (4 * odds) + (2 * pairs) + functions[n]) / (3 * n) );

    return finalResult;
}