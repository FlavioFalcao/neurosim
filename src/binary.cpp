/*
 * NeuroSim Library Main Source
 * Colby Horn
 */

#include <iostream>

#include "neurosim.hpp"

using namespace neuro;
using namespace std;

int main(int argc, char** argv) {
	network net;
	cout << "parsing neural network..." << endl;
	cin >> net;
	cout << "simulating a single non-recurrent evaluation iteration" << endl;
	net.eval_non_rec();
	cout << "printing neural network..." << endl;
	cout << net;
	return 0;
}

