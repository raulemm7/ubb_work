#include <iostream>
#include "TestExtins.h"
#include "TestScurt.h"
using namespace std;

int main() {
    // timpul de executie al testelor e foarte mare
    // datorita numarului mare de date introduse
	testAll();
    testAllExtins();

    cout<<"End";
}
