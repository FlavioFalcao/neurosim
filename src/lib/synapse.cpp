/*
 * NeuroSim Library Synapse Source
 * Colby Horn
 */

#include "neurosim.hpp"

using namespace std;

namespace neuro {

Synapse::Synapse(Neuron& source, float weight, Neuron& target): 
		source(source), weight(weight), target(target) {}
		
Neuron& Synapse::getSource() const { return source; }
float Synapse::getWeight() const { return weight; }
void Synapse::setWeight(float weight) { this->weight = weight; }
Neuron& Synapse::getTarget() const { return target; }

ostream& operator<<(ostream& stream, const Synapse& synapse) {
	return stream << "Synapse source=" << synapse.source.getId() << 
			" weight=" << synapse.weight << 
			" target=" << synapse.target.getId();
}

}

