#include "InvestmentCalculator.h"
#include <limits>
#include <cctype>

// ---------------- Constructor ----------------
InvestmentCalculator::InvestmentCalculator()
    : m_initialInvestment(0.0), m_monthlyDeposit(0.0), m_annualInterestRate(0.0), m_numberOfYears(0) {}

// ---------------- Getters ----------------
double InvestmentCalculator::GetInitialInvestment() const { return m_initialInvestment; }
double InvestmentCalculator::GetMonthlyDeposit() const { return m_monthlyDeposit; }
double InvestmentCalculator::GetAnnualInterestRate() const { return m_annualInterestRate; }
int InvestmentCalculator::GetNumberOfYears() const { return m_numberOfYears; }

// ---------------- Setters ----------------
void InvestmentCalculator::SetInitialInvestment(double t_amount) {
    if (t_amount < 0) throw std::invalid_argument("Initial investment cannot be negative.");
    m_initialInvestment = t_amount;
}

void InvestmentCalculator::SetMonthlyDeposit(double t_amount) {
    if (t_amount < 0) throw std::invalid_argument("Monthly deposit cannot be negative.");
    m_monthlyDeposit = t_amount;
}

void InvestmentCalculator::SetAnnualInterestRate(double t_rate) {
    if (t_rate < 0) throw std::invalid_argument("Interest rate cannot be negative.");
    m_annualInterestRate = t_rate;
}

void InvestmentCalculator::SetNumberOfYears(int t_years) {
    if (t_years <= 0) throw std::invalid_argument("Number of years must be greater than 0.");
    m_numberOfYears = t_years;
}

// ---------------- User Input ----------------
void InvestmentCalculator::GatherUserInput() {
    std::cout << "\n=============================\n";
    std::cout << "     Investment Input        \n";
    std::cout << "=============================\n";

    SetInitialInvestment(GetValidatedInput("Enter initial investment amount: $", false));
    SetMonthlyDeposit(GetValidatedInput("Enter monthly deposit amount: $", true));
    SetAnnualInterestRate(GetValidatedInput("Enter annual interest rate (%): ", false));
    SetNumberOfYears(static_cast<int>(GetValidatedInput("Enter number of years: ", false)));

    std::cout << "\n";
}

// ---------------- Input Validation ----------------
double InvestmentCalculator::GetValidatedInput(const std::string& t_prompt, bool t_allowZero) {
    double value;

    while (true) {
        std::cout << t_prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "❌ Invalid input. Please enter a numeric value.\n";
            continue;
        }

        if (value < 0) {
            std::cout << "❌ Value cannot be negative. Try again.\n";
            continue;
        }

        if (!t_allowZero && value == 0) {
            std::cout << "❌ Value must be greater than zero.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

// ---------------- Report Header ----------------
void InvestmentCalculator::PrintReportHeader(const std::string& t_title) {
    std::cout << "\n============================================================\n";
    std::cout << t_title << "\n";
    std::cout << "============================================================\n";
    std::cout << std::left
              << std::setw(10) << "Year"
              << std::setw(20) << "Year-End Balance"
              << std::setw(20) << "Year-End Earned Interest"
              << "\n";
    std::cout << "------------------------------------------------------------\n";
}

// ---------------- Report Calculation ----------------
void InvestmentCalculator::CalculateAndPrintReport(double t_monthlyDepositAmount) {
    double balance = m_initialInvestment;
    double rate = m_annualInterestRate / 100.0;

    std::string title = (t_monthlyDepositAmount > 0)
        ? "  Balance and Interest With Monthly Deposits  "
        : "  Balance and Interest Without Monthly Deposits  ";

    PrintReportHeader(title);

    for (int year = 1; year <= m_numberOfYears; ++year) {
        double interestEarned = 0.0;

        for (int month = 1; month <= 12; ++month) {
            double monthlyInterest = (balance + t_monthlyDepositAmount) * (rate / 12);
            interestEarned += monthlyInterest;
            balance += t_monthlyDepositAmount + monthlyInterest;
        }

        std::cout << std::left
                  << std::setw(10) << year
                  << "$" << std::setw(19) << std::fixed << std::setprecision(2) << balance
                  << "$" << std::setw(19) << interestEarned
                  << "\n";
    }

    std::cout << "------------------------------------------------------------\n";
}

// ---------------- Continue Prompt ----------------
bool InvestmentCalculator::PromptToContinue() {
    char choice;
    while (true) {
        std::cout << "\nWould you like to run another calculation? (Y/N): ";
        std::cin >> choice;
        choice = std::toupper(choice);

        if (choice == 'Y') return true;
        if (choice == 'N') return false;

        std::cout << "Invalid choice. Please enter Y or N.\n";
    }
}
