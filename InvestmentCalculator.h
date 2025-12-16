#ifndef AIRGEADBANKING_INVESTMENTCALCULATOR_H_
#define AIRGEADBANKING_INVESTMENTCALCULATOR_H_

#include <iostream>
#include <iomanip>
#include <string>

class InvestmentCalculator {
public:
    // Constructor
    InvestmentCalculator();

    // Accessors (Getters)
    double GetInitialInvestment() const;
    double GetMonthlyDeposit() const;
    double GetAnnualInterestRate() const;
    int GetNumberOfYears() const;

    // Mutators (Setters)
    void SetInitialInvestment(double t_amount);
    void SetMonthlyDeposit(double t_amount);
    void SetAnnualInterestRate(double t_rate);
    void SetNumberOfYears(int t_years);

    // Main functional methods
    void GatherUserInput();
    void CalculateAndPrintReport(double t_monthlyDepositAmount);
    bool PromptToContinue();

private:
    double m_initialInvestment;
    double m_monthlyDeposit;
    double m_annualInterestRate;
    int m_numberOfYears;

    // Helper functions
    double GetValidatedInput(const std::string& t_prompt, bool t_allowZero);
    void PrintReportHeader(const std::string& t_title);
};

#endif // AIRGEADBANKING_INVESTMENTCALCULATOR_H_
