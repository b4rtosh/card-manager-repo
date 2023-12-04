#include "luhn.h"
#include <iostream>

long Luhn::new_id{0};

bool Luhn::test(std::string number) {
    bool result{};
    for (int i = number.size() - 2; i >= 0; i -= 2) {
        number[i] = luhn_tab[((int)number[i]) - 48];
    }
    int a{};
    for (int i = 0; i < number.size(); ++i) {
        a += (int) number[i] - 48;
    }
    if (a % 10 == 0) result = true;
    return result;
}

std::vector<std::string> Luhn::brandNames
        {"Visa", "MasterCard", "American Express", "Diners Club", "Japan Credit Bureau"};
