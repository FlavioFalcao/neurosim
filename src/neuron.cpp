/*
 * NeuroSim Library Neuron Source
 * Colby Horn
 */

#include <ostream>
#include <stdexcept>

#include "neurosim.hpp"

using namespace std;

namespace neuro {

Neuron::Neuron(int id, NeuronType type, float activation, float bias): 
		id(id), type(type), activation(activation), bias(bias) {}

int Neuron::getId() const { return id; }
NeuronType Neuron::getType() const { return type; }
float Neuron::getActivation() const { return activation; }

void Neuron::setActivation(float activation) {
	if (type == INPUT)
		this->activation = activation;
	else
		throw runtime_error("method Neuron::setActivation may only be called if Neuron::type == INPUT");
}

float Neuron::evalActivation() {
	if (type != INPUT) {
		activation = getBias();
		for (iterator synapse = inputs_begin(); 
				synapse != inputs_end(); ++synapse) {
			activation += (*synapse)->getWeight() * 
					(*synapse)->getSource()->getActivation();
		}
	}
	return activation;
}

float Neuron::getBias() const { return bias; }

Neuron::iterator Neuron::inputs_begin() { return inputs.begin(); }
Neuron::iterator Neuron::inputs_end() {	return inputs.end(); }
Neuron::iterator Neuron::outputs_begin() { return outputs.begin(); }
Neuron::iterator Neuron::outputs_end() { return outputs.end(); }

Neuron::iterator findSynapseBySource(vector<Synapse*>& synapses, 
		Neuron* source) {
	Neuron::iterator syn = synapses.begin();
	while (syn != synapses.end() && (*syn)->getSource() != source) ++syn;
	return syn;
}

Neuron::iterator findSynapseByTarget(vector<Synapse*>& synapses, 
		Neuron* target) {
	Neuron::iterator syn = synapses.begin();
	while (syn != synapses.end() && (*syn)->getTarget() != target) ++syn;
	return syn;
}

void Neuron::connect(Neuron* target, float weight) {
	if (type != OUTPUT) {
		if (findSynapseByTarget(outputs, target) == outputs.end()) {
			Synapse* synapse = new Synapse(this, weight, target);
			this->outputs.push_back(synapse);
			target->inputs.push_back(synapse);
		}
	} else
		throw runtime_error("method Neuron::connect may only be called if Neuron::type != OUTPUT");
}

void Neuron::disconnect(Neuron* target) {
	Neuron::iterator outputs_itr = findSynapseByTarget(this->outputs, target),
			inputs_itr = findSynapseBySource(target->inputs, this);
	if (type != OUTPUT) {
		if (outputs_itr != outputs.end()) {
			Synapse* synapse = *outputs_itr;
			this->outputs.erase(outputs_itr);
			target->inputs.erase(inputs_itr);
			delete synapse;
		}
	} else
		throw runtime_error("method Neuron::disconnect may only be called if Neuron::type != OUTPUT");
}

ostream& operator<<(ostream& stream, const Neuron& neuron) {
	return stream << "Neuron id=" << neuron.id << 
			" type=" << getNeuronTypeText(neuron.type) <<
			" activation=" << neuron.activation << " bias=" << neuron.bias;
}

}
