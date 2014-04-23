/*
 * NeuroSim Library Synapse Header
 * Colby Horn
 */

#ifndef __Synapse__
#define __Synapse__

#include <ostream>

namespace neuro {

class Neuron;

class Synapse {
friend std::ostream& operator<<(std::ostream&, const Synapse&);
public:
	Synapse(Neuron*, float, Neuron*);
	Neuron* getSource() const;
	float	getWeight() const;
	void	setWeight(float);
	Neuron* getTarget() const;
private:
	Neuron* source;
	float	weight;
	Neuron* target;
};

}

#endif

