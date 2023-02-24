#include <iostream>
#include <string>
#include <cmath>

using namespace std;

enum{BINARY, OCTAL, HEXADECIMAL, DECIMAL};

int fastExponent(int base, int exponent, int accumulator);
bool is(string number, int choice);
string convert(string number, int conversionFactor);
string binary(string number, int converter);

int main()
{
    cout << "This program converts numbers between different number systems. " << endl;

    cout << "Enter the number system in which you desire to enter your input. " << endl << endl;
    cout << "(1) Binary (2) Decimal (3) Octal (4) Hexadecimal (5) Custom " << endl << endl;
    cout << "Enter your choice: "; int choice;
    for(cin >> choice; choice < 1 || choice > 5; cin >> choice)
        cout << "Sorry! The input you have entered is invalid. Please enter a choice between [1,5]. " << endl << endl << "************************************************************************************" << endl << endl << "(1) Binary (2) Octal (3) Hexadecimal (4) Decimal (5) Custom " << endl << endl << "Enter your choice: ";

    if(choice != 1) { // Removable Block after other number system conversions have been implemented.
        cout << "Sorry! Only Binary Number conversions is allowed for now." << endl;
        cout << "Please try running the program again with '1' as your 1st input." << endl << endl;
        return 1;
    }
	
    cout << endl;

    const char * system[5] = {"binary", "decimal", "octal", "hexadecimal", "custom"};
    string number;
    cout << "Enter your " << system[choice-1] << " number: ";
    for(cin >> number; !is(number, choice); cin >> number)
        cout << endl << "Sorry! The number you have entered is not " << system[choice-1] << ".\nAll digits must be between (0 ... " << (choice == 1 ? "1": (choice == 2 ? "7": "9) U (A ... F) U (a ... f" )) << "). Please try again. " << endl << "************************************************************************************" << endl << endl << "Enter your " << system[choice-1] << " number: ";

    //Identifying Leading Zeros
    int zero_lead = -1;
    while(number[++zero_lead] == '0'){}

    //Backspacing original string to eliminate leading zeros if there is any
    number = number.substr(zero_lead, number.length() - zero_lead);

    if(zero_lead > 0)
        cout << endl << "There " << (zero_lead == 1 ? "is ": "are ") << zero_lead << " leading zero" << (zero_lead == 1 ? "": "s") << " in your " << system[choice - 1] << " number that " << (zero_lead == 1 ? "has" : "have") << " been eliminated. " << endl;

    cout << (zero_lead == 0 ? "Y": "Thereby, y") << "ou have entered a " << system[choice - 1] << " number: " << number << endl << endl;

    cout << "Which system do you want to convert this number into? " << endl << endl;
    cout << "(1) Binary (2) Decimal (3) Octal (4) Hexadecimal (5) Custom " << endl << endl;
    cout << "Enter your selection: "; int selection = -1;
    for(cin >> selection; selection == -1; cin >> selection)
    {
        if(selection < 1 || selection > 5)
            cout << "Sorry! The input you have entered is invalid. Please enter a choice between [1,5]. " << endl << endl << "Enter your choice: ";
        else if(selection == choice)
            cout << "Sorry! You cannot convert to the same number system. " << endl << system[choice - 1] << " -> " << system[choice - 1] << endl << endl;
    }
    //string number = convert(number, choice, selection);
    cout << endl << "The " << system[choice - 1] << " number " << "'" << number << "' converted into " << system[selection - 1] << " format is: " << convert(number, choice * 10 + selection) << endl << endl;

    return 0;
}

string convert(string number, int conversionFactor)
{
    int sum = 0;
    int converter = conversionFactor % 10;
    char * num;

    if(converter == 4)
        num = new char[(int)ceil(number.length() / converter)];

    //cout << "|";
    switch(conversionFactor / 10)
    {
        //Conversion n-system -> binary where n = {8, 10, 16}
        case 1:
            for(int count = 0; count  < number.length(); count++)
            {
                //cout << number[count] << ((number.length() - count - 1) % converter ? "": "|");

                if(number[count] == 49)
                    sum += fastExponent(2, (converter == 2 ? number.length() - count - 1 : (number.length() - 1 - count) % converter), 1);

                if(converter - 2)
                {
                    if( (count+1) % converter == (converter - 1) || count == number.length() - 1)
                    {
                        if(converter == 4)
                        {
                            num[(int)(count / converter)] = (sum > 9 ? sum + 55: sum + 48);
                            sum = 0;
                        }
                        else
                            if( count != number.length() - 1 )
                                sum *= 10;
                    }
                }
            }
            //cout << endl;
            if(converter == 4)
                return num;

            return to_string(sum);

            break;

        //Decimal conversion
        case 2:
            //return decimal(number, conversionFactor / 10);
            break;

        //Octal conversion
        case 3:
            //return hexadecimal(number, conversionFactor / 10);
            break;

        //Hexadecimal conversion
        case 4:
            //return octal(number, conversionFactor / 10);
            break;

        default:
            cout << "Sorry! The conversion factor you have sent is an invalid argument. " << endl;
    }
}

//Checks if a string is binary, decimal, octal or hexadecimal based on choice of input
bool is(string num, int choice)
{
    if(choice == 3 || choice == 2)
        choice = fastExponent(2, 3, 1) + (choice % 2 ? -1: 1);

    for(int i = 0; i < num.length(); i++)
    {
        if(choice == 4)
        {
            if(num[i] < 48 || (num[i] > 57 && num[i] < 65) || (num[i] > 70 && num[i] < 97) || num[i] > 102)
                return false;
        }
        else if(num[i] > choice + 48 || num[i] < '0')
            return false;
    }

    return true;
}

//Fast Exponentiation
int fastExponent(int base, int exponent, int accumulator)
{
    if(exponent == 0)
        return accumulator;
    else if(exponent % 2 == 0)
        return fastExponent(base * base, exponent/2, accumulator);

    return fastExponent(base, exponent-1, base * accumulator);
}
