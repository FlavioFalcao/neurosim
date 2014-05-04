/*
 * NeuroSim Library Network Parsing Source
 * Colby Horn
 */

#include <sstream>
#include <stdexcept>
#include <string>

#include "network.hpp"

using namespace std;

namespace neuro {

ostream& operator<<(ostream& stream, network& net) {
	for (network::iterator n = net.begin(); n != net.end(); ++n) {
		if (n->type() == neuron::INTERNAL) {
			stream << "neuron";
		} else if (n->type() == neuron::INPUT) {
			stream << "input";
		} else if (n->type() == neuron::OUTPUT) {
			stream << "output";
		}
		stream << " " << n->id() << endl;
		if (n->activation() != 0.0) {
			stream << "\tactivation " << n->activation() << endl;
		}
		if (n->bias() != 0.0) {
			stream << "\tbias " << n->bias() << endl;
		}
		for (neuron::iterator s = n->begin(); s != n->end(); ++s) {
			stream << "synapse" << endl << "\tsource " << s->source().id() << endl << 
					"\tdestination " << s->destination().id() << endl << 
					"\tweight " << s->weight() << endl;
		}
	}
	return stream;
}

void parse_neuron(string& str_in, istream& stream, network& net) {
	neuron::connection_type type;
	if (str_in == "neuron") {
		type = neuron::INTERNAL;
	} else if (str_in == "input") {
		type = neuron::INPUT;
	} else if (str_in == "output") {
		type = neuron::OUTPUT;
	}
	int id;
	stream >> id;
	float activation = 0.0, bias = 0.0;
	stream >> str_in;
	while (!stream.eof() && (str_in == "activation" || str_in == "bias")) {
		if (str_in == "activation") {
			stream >> activation;
		} else if (str_in == "bias") {
			stream >> bias;
		}
		stream >> str_in;
	}
	if (net.contains(id)) {
		ostringstream stream;
		stream << "operator>>:: redefinition of <neuron id " << id << ", ...>";
		throw runtime_error(stream.str());
	}
	net.add(id, type, activation, bias);
}

void parse_synapse(string& str_in, istream& stream, network& net) {
	int source, destination;
	float weight = 1.0;
	stream >> str_in;
	while (!stream.eof() && 
			(str_in == "source" || str_in == "destination" || str_in == "weight")) {
		if (str_in == "source") {
			stream >> source;
		} else if (str_in == "destination") {
			stream >> destination;
		} else if (str_in == "weight") {
			stream >> weight;
		}
		stream >> str_in;
	}
	if (!net.contains(source)) {
		ostringstream stream;
		stream << "operator>>:: undefined source <neuron id " << source << ", ...>";
		throw runtime_error(stream.str());
	} else if (!net.contains(destination)) {
		ostringstream stream;
		stream << "operator>>:: undefined destination <neuron id " << destination << ", ...>";
		throw runtime_error(stream.str());
	}
	net[source].connect(net[destination], weight);
}

istream& operator>>(istream& stream, network& net) {
	net.clear();
	string str_in;
	stream >> str_in;
	while (!stream.eof()) {
		if (str_in == "neuron" || str_in == "input" || str_in == "output") {
			parse_neuron(str_in, stream, net);
		} else if (str_in == "synapse") {
			parse_synapse(str_in, stream, net);
		} else
			throw runtime_error("parse error on token: " + str_in); 
	}
	return stream;
}

}

