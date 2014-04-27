/*
 * NeuroSim Library Python Module Export Source
 * Colby Horn
 */

#include <boost/python.hpp>

#include "neurosim.hpp"

using namespace boost::python;

using namespace neuro;

void (Network::*add2)(int, NeuronType) = &Network::add;
void (Network::*add3)(int, NeuronType, float) = &Network::add;
void (Network::*add4)(int, NeuronType, float, float) = &Network::add;

BOOST_PYTHON_MODULE(neurosim) {
	class_<Network>("Network")
		.def("add", add2)
		.def("add", add3)
		.def("add", add4)
		.def("contains", &Network::contains)
		.def("__getitem__", &Network::operator[],
				return_value_policy<reference_existing_object>())
		.def("erase", &Network::erase)
		.def("clear", &Network::clear)
		.def("__iter__", iterator<Network>())
		.def("evalTraverse", &Network::evalTraverse)
	;
	
	enum_<NeuronType>("NeuronType")
		.value("Internal", INTERNAL)
		.value("Input", INPUT)
		.value("Output", OUTPUT)
	;
	
	class_<Neuron>("Neuron", init<int, NeuronType, float, float>())
		.add_property("id", &Neuron::getId)
		.add_property("type", &Neuron::getType)
		.add_property("activation", 
				&Neuron::getActivation, &Neuron::setActivation)
		.def("evalActivation", &Neuron::evalActivation)
		.add_property("bias", &Neuron::getBias)
		.def("__iter__", iterator<Neuron>())
		.def("connect", &Neuron::connect)
		.def("disconnect", &Neuron::disconnect)
	;
	
	class_<Synapse>("Synapse", init<Neuron&, float, Neuron&>())
		.add_property("source", make_function(&Synapse::getSource, 
				return_value_policy<reference_existing_object>()))
		.add_property("weight", &Synapse::getWeight, &Synapse::setWeight)
		.add_property("target", make_function(&Synapse::getTarget, 
				return_value_policy<reference_existing_object>()))
	;
}
