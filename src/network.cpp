/*
 * NeuroSim Library Core Network Source
 * Colby Horn
 */

#include <queue>
#include <stdexcept>

#include "neurosim.hpp"

using namespace std;
using namespace boost;

namespace neuro {

void Network::add(int id, NeuronType type, float arg) {
	if (type == INPUT)
		add(id, type, arg, 0.0);
	else
		add(id, type, 0.0, arg);
}

void Network::add(int id, NeuronType type, float activation, float bias) {
	if (!contains(id)) {
		Neuron* neuron = new Neuron(id, type, activation, bias);
		neuron_table[id] = neuron;
		neurons.push_back(neuron);
		if (neuron->getType() == INPUT)
			inputs.push_back(neuron);
		else if (neuron->getType() == OUTPUT)
			outputs.push_back(neuron);
	}
}

bool Network::contains(int id) {
	return neuron_table.find(id) != neuron_table.end();
}

Neuron& Network::operator[](int id) {
	if (contains(id))
		return *neuron_table[id];
	else
		throw out_of_range("method Network::operator[] received out of range id");
}

vector<Neuron*>::iterator findById(vector<Neuron*>& neurons, int id) {
	vector<Neuron*>::iterator neuron = neurons.begin();
	while ((*neuron)->getId() != id && neuron != neurons.end()) ++neuron;
	return neuron;
}

void Network::erase(int id) {
	if (neuron_table.find(id) != neuron_table.end()) {
		neuron_table.erase(id);
		vector<Neuron*>::iterator location = findById(neurons, id);
		Neuron* neuron = *location;
		neurons.erase(location);
		if (neuron->getType() == INPUT) {
			location = findById(inputs, id);
			inputs.erase(location);
		} else if (neuron->getType() == OUTPUT) {
			location = findById(outputs, id);
			outputs.erase(location);
		} 
		delete neuron;
	}
}

void Network::clear() {
	neurons.clear();
	inputs.clear();
	outputs.clear();
	neuron_table.clear();
}

Network::iterator deref(vector<Neuron*>::iterator itr) {
	return make_transform_iterator(itr, &dereference<Neuron>);
}

Network::iterator Network::begin() { return deref(neurons.begin()); }
Network::iterator Network::end() { return deref(neurons.end()); }
Network::iterator Network::inputs_begin() { return deref(inputs.begin()); }
Network::iterator Network::inputs_end() { return deref(inputs.end()); }
Network::iterator Network::outputs_begin() { return deref(outputs.begin()); }
Network::iterator Network::outputs_end() { return deref(outputs.end()); }

void Network::evalTraverse() {
	queue<Neuron*> frontier;
	for (iterator input = inputs_begin(); input != inputs_end(); ++input)
		frontier.push(&*input);
	while (!frontier.empty()) {
		Neuron* neuron = frontier.front();
		neuron->evalActivation();
		for (Neuron::iterator child = neuron->outputs_begin(); 
				child != neuron->outputs_end(); ++child)
			frontier.push(&child->getTarget());
		frontier.pop();
	}
}

}

