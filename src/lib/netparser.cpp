/*
 * NeuroSim Library Network Parsing Source
 * Colby Horn
 */
 
#include <stdexcept>
#include <string>

#include "neurosim.hpp"

using namespace std;

namespace neuro {

ostream& operator<<(ostream& stream, Network& net) {
	for (Network::iterator neuron = net.begin(); 
			neuron != net.end(); ++neuron) {
		if (neuron->getType() == INTERNAL)
			stream << "neuron";
		else if (neuron->getType() == INPUT)
			stream << "input";
		else if (neuron->getType() == OUTPUT)
			stream << "output";
		stream << " " << neuron->getId() << endl;
		if (neuron->getActivation() != 0.0)
			stream << "\tactivation " << neuron->getActivation() << endl;
		if (neuron->getBias() != 0.0)
			stream << "\tbias " << neuron->getBias() <<endl;
		for (Neuron::iterator synapse = neuron->begin();
				synapse != neuron->end(); ++synapse)
			stream << "synapse" << endl <<
					"\tsource " << synapse->getSource().getId() << endl <<
					"\ttarget " << synapse->getTarget().getId() << endl <<
					"\tweight " << synapse->getWeight() << endl;
	}
	return stream;
}

istream& operator>>(istream& stream, Network& net) {
	net.clear();
	string str_in;
	stream >> str_in;
	while (!stream.eof()) {
		if (str_in == "neuron" || str_in == "input" || str_in == "output") {
			NeuronType type;
			if (str_in == "neuron")
				type = INTERNAL;
			else if (str_in == "input")
				type = INPUT;
			else if (str_in == "output")
				type = OUTPUT;
			int id;
			stream >> id;
			float activation = 0.0, bias = 0.0;
			stream >> str_in;
			while (!stream.eof() && 
					(str_in == "activation" || str_in == "bias")) {
				if (str_in == "activation")
					stream >> activation;
				else if (str_in == "bias")
					stream >> bias;
				stream >> str_in;
			}
			if (net.contains(id))
				throw runtime_error("redefinition of id: " + to_string(id));
			else
				net.add(id, type, activation, bias);
		} else if (str_in == "synapse") {
			int target, source;
			float weight = 1.0;
			stream >> str_in;
			while (!stream.eof() && (str_in == "source" || 
					str_in == "target" || str_in == "weight")) {
				if (str_in == "source")
					stream >> source;
				else if (str_in == "target")
					stream >> target;
				else if (str_in == "weight")
					stream >> weight;
				stream >> str_in;
			}
			if (!net.contains(source))
				throw runtime_error("undefined connection source: " + 
						to_string(source));
			else if (!net.contains(target))
				throw runtime_error("undefined connection target: " + 
						to_string(target));
			else
				net[source].connect(net[target], weight);
		} else
			throw runtime_error("parse error on token: " + str_in); 
	}
	return stream;
}

}

