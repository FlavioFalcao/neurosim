/*
 * NeuroSim Library Main Source
 * Colby Horn
 */

#include <iostream>

#include "neurosim.hpp"

using namespace neuro;
using namespace std;

int main(int argc, char** argv) {
	Network net = Network();
	cin >> net;
	cout << "==================================================" << endl;
	cout << "=== Neural Net ===================================" << endl;
	cout << "==================================================" << endl;
	net.evalTraverse();
	cout << net;
	return 0;
}

