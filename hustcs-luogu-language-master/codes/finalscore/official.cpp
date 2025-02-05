#include <iostream>

int main() {
	int a, b, c;
	std::cin >> a >> b >> c;
	int finalscore = a / 10 * 2 + b / 10 * 3 + c / 10 * 5;
	std::cout << finalscore << std::endl;
	return 0;
}
