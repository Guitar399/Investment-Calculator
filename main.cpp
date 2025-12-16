#include <iostream>
#include "InvestmentCalculator.h"

int main() {
    InvestmentCalculator calculator;
    bool continueProgram = true;

    while (continueProgram) {
        std::cout << "\n\n============== AIRGEAD BANKING ==============\n";
        std::cout << "         Investment Growth Calculator         \n";
        std::cout << "==============================================\n\n";

        // Get user input
        calculator.GatherUserInput();

        // Display charts
        calculator.CalculateAndPrintReport(0.0);                     // Without monthly deposits
        calculator.CalculateAndPrintReport(calculator.GetMonthlyDeposit()); // With monthly deposits

        // Ask user if they want to continue
        continueProgram = calculator.PromptToContinue();
    }

    std::cout << "\nThank you for using the Airgead Banking Investment Calculator.\n";
    std::cout << "Goodbye!\n";

    return 0;
}
