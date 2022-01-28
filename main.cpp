//Preprocessors
#include <iostream>
#include <iomanip>
#include <cmath>

//Relevant information
struct TaxInfo
{
    double principal    {};
    double years        {};
    double rate         {};
    double compound     {};

};

//Prototypes
void printIntro();
int getOption(std::string& optionInput);
void exeCommand(int& exeOption);

//Related functions
namespace Interest
{
    void calcSimpleInterest(double, double, double);
    void  calcCompoundInterest(double, double, double, double);

    template <typename T>
    void checkData(T&);
}

int main()
{
    std::string userInput {};

    //Reasonable sentinel to quit
    while(userInput != "e")
    {
        printIntro();
        int optionInput {getOption(userInput)};
        exeCommand(optionInput);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    return 0;
}

void printIntro()
{
    std::cout << "\nWelcome to my Interest Calculation program!\n"
                 "What would you like to do today?  \n"
                 "Pick an option from below:\n"
                 "1. Simple Interest\n"
                 "2. Compound Interest\n"
                 "3. Quit\n"
                 ">>";
}

int getOption(std::string& optionInput)
{
    int retOption{};

    bool getInput = true;
    while (getInput)
    {
        std::getline(std::cin, optionInput);

        if (optionInput.length() != 1)
        {
            std::cout << "Invalid amount of characters\n";
        }

        else
        {
            if (optionInput == "e" || optionInput == "3")
            {
                std::cout << "Thank you for using my program!\n";
                std::exit(EXIT_SUCCESS);
            }

            try
            {
                retOption = std::stoi(optionInput);

                if (retOption > 3 || retOption < 1)
                {
                    std::cout << "Invalid number!\n";
                }

                else
                {
                    std::cout << "Input Accepted\n";
                    getInput = false;
                }
            }

            catch (std::invalid_argument &)
            {
                std::cout << "Issue accepting input!\n";
            }

            catch (std::out_of_range &)
            {
                std::cout << "Number entered is out of range!\n";
            }

        }
    }

    return retOption;
}

template <typename T>
void Interest::checkData(T& input)
{
    bool loopInput = true;
    while(loopInput)
    {
        std::cin >> input;

        if(std::cin.fail())
        {
            std::cout << "Input unrecognized!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << ">> ";
        }
        else if(input < 0)
        {
            std::cout << "Input too low!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << ">> ";
        }

        else
            loopInput = false;
    }
}

void Interest::calcSimpleInterest(double principal, double rate, double years)
{
    using std::cout;

    cout << "Enter the Principal Amount: ";
    Interest::checkData(principal);

    cout << "Enter the Interest Rate: ";
    Interest::checkData(rate);

    cout << "Enter the time in years: ";
    Interest::checkData(years);

    rate = rate / 100;

    double grandTotal = principal * (1 + (rate * years));
    double interestAccrued = grandTotal - principal;

    cout << "Interest accrued: $" << std::fixed << std::setprecision(2) <<interestAccrued << '\n';
    cout << "Grand total: $" << std::fixed << std::setprecision(2) << grandTotal << '\n';
}

void Interest::calcCompoundInterest(double principal, double rate, double years, double compound)
{
    using std::cout;

    cout << "Enter the Principal Amount: ";
    Interest::checkData(principal);

    cout << "Enter the Interest Rate: ";
    Interest::checkData(rate);

    cout << "Enter the time in years: ";
    Interest::checkData(years);

    cout << "Enter the number of compounding years: ";
    Interest::checkData(compound);

    rate = rate / 100;
    double exp = compound * years;

    double grandTotal = principal * std::pow((1 + (rate/compound)), exp);
    double interestAccrued = grandTotal - principal;

    cout << "Interest accrued: $" << std::fixed << std::setprecision(2) <<interestAccrued << '\n';
    cout << "Grand total: $" << std::fixed << std::setprecision(2) << grandTotal << '\n';
}

void exeCommand(int& exeOption)
{
    TaxInfo taxObj;

    switch(exeOption)
    {
        case 1:
            Interest::calcSimpleInterest(taxObj.principal, taxObj.rate, taxObj.years);
            break;

        case 2:
            Interest::calcCompoundInterest(taxObj.principal, taxObj.rate, taxObj.years, taxObj.compound);
            break;
    }
}
