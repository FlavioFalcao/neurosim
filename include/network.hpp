/*
 * NeuroSim Library Network Header
 * Colby Horn
 */

#ifndef __Network__
#define __Network__

#include <istream>
#include <ostream>
#include <vector>
#include <map>

#include "neuron.hpp"

namespace neuro {

class Network {
friend std::ostream& operator<<(std::ostream&, Network&);
friend std::istream& operator>>(std::istream&, Network&);
public:
	typedef std::vector<Neuron*>::iterator iterator;
	void     add(int, NeuronType, float = 0.0);
	void     add(int, NeuronType, float, float);
	void     erase(int);
	void     clear();
	iterator begin();
	iterator end();
	iterator inputs_begin();
	iterator inputs_end();
	iterator outputs_begin();
	iterator outputs_end();
	Neuron*  operator[](int id);
	void     evalTraverse();
private:
	std::vector<Neuron*>   neurons, inputs, outputs;
	std::map<int, Neuron*> neuron_table;
};

}

#endif

