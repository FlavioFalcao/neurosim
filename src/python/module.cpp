/*
 * NeuroSim Library Python Module Export Source
 * Colby Horn
 */

#include <boost/python.hpp>

#include "neurosim.hpp"

using namespace boost::python;

using namespace neuro;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(network_add_overloads, network::add, 1, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(network_add_input_overloads, network::add_input, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(network_add_internal_overloads, network::add_internal, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(network_add_output_overloads, network::add_output, 1, 2)
network::const_reference (network::*network_getitem)(network::size_type) const = 
		&network::operator[];
const network::iterable& (network::*network_inputs)() const = &network::inputs;
const network::iterable& (network::*network_outputs)() const = &network::outputs;

float (neuron::*neuron_get_activation)() const = &neuron::activation;
void (neuron::*neuron_set_activation)(float) = &neuron::activation;
const neuron::iterable& (neuron::*neuron_inputs)() const = &neuron::inputs;
const neuron::iterable& (neuron::*neuron_outputs)() const = &neuron::outputs;

synapse::const_reference (synapse::*synapse_destination)() const = &synapse::destination;
synapse::const_reference (synapse::*synapse_source)() const = &synapse::source;
float (synapse::*synapse_get_weight)() const = &synapse::weight;
void (synapse::*synapse_set_weight)(float) = &synapse::weight;
synapse::const_reference (synapse::*synapse_getitem)(synapse::size_type) const = 
		&synapse::operator[];

BOOST_PYTHON_MODULE(neurosim) {
	{
	scope outer = class_<network>("Network")
		.def("__getitem__", network_getitem, return_value_policy<reference_existing_object>(),
				"Retrieves a neuron from the network by id.")
		.def("__iter__", iterator<network>(),
				"Provides iteration through all of the network's neurons,\n"
				"in an unspecified order.")
		.def("__len__", &network::size, "Returns the number of neurons in this network.")
		.def("add", &network::add, 
				network_add_overloads(args("id", "type", "activation", "bias"), 
				"Adds to this network a new neuron of the given type with\n"
				"the given id, activation, and bias. Throws a runtime error\n"
				"if a neuron with the given id already exists in the network."))
		.def("add_input", &network::add_input, 
				network_add_input_overloads(args("id", "activation"), 
				"Adds to this network a new input neuron with the given\n"
				"id and activation. Throws a runtime error if a neuron\n"
				"with the given id already exists in the network."))
		.def("add_internal", &network::add_internal, 
				network_add_internal_overloads(args("id", "bias"), 
				"Adds to this network a new output neuron with the given\n"
				"id and bias. Throws a runtime error if a neuron\n"
				"with the given id already exists in the network."))
		.def("add_output", &network::add_output, 
				network_add_output_overloads(args("id", "bias"), 
				"Adds to this network a new internal neuron with the given\n"
				"id and bias. Throws a runtime error if a neuron\n"
				"with the given id already exists in the network."))
		.def("clear", &network::clear, "Removes all of this network's neurons.")
		.def("contains", &network::contains,
				"Reports if a neuron with the given id is contained in\n"
				"the network.")
		.def("erase", &network::erase, "Removes a neuron from the network by id.")
		.def("eval_non_rec", &network::eval_non_rec,
				"Evaluates a non-recurrent network by fully propagating\n"
				"neural activation from the network's input neurons to\n"
				"its output neurons. Behavior is undefined for recurrent\n"
				"networks and will likely result in an unbounded loop.")
		.add_property("inputs", make_function(network_inputs, 
				return_value_policy<reference_existing_object>()),
				"An iterable collection of the network's input neurons.")
		.add_property("outputs", make_function(network_outputs, 
				return_value_policy<reference_existing_object>()),
				"An iterable collection of the network's output neurons.")
		.def("read_file", &network::read_file,
				"Reads a text-serialized network from the given filename\n"
				"into this network object, erasing its previous state.\n"
				"The function Network.write_file(...) can be used to produce\n"
				"such a text-serialized network file.\n")
		.def("write_file", &network::write_file,
				"Writes this network to the given filename, producing\n"
				"a text-serialized network file that the function\n"
				"Network.read_file(...) can read.")
	;
	
	class_<network::iterable>("Iterable", no_init)
		.def("__iter__", iterator<network::iterable>(),
				"Provides iteration through this collection of neurons.")
		.def("__len__", &network::iterable::size,
				"Returns the number of neurons in this collection.")
	;
	}
	
	{
	scope outer = class_<neuron>("Neuron", init<int, neuron::connection_type, float, float>())
		.def("__iter__", iterator<neuron>(),
				"Provides iteration through all of the neuron's input\n"
				"synapses. Use properties Neuron.inputs or Neuron.outputs\n"
				"to explicitly iterate through input or output synapses,\n"
				"respectively. (Property Neuron.inputs provides identical\n"
				"iteration functionality to this function.)")
		.def("__len__", &neuron::size,
				"Returns the number of input synapses. Use properties\n"
				"Neuron.inputs or Neuron.outputs to explicitly get\n"
				"the number of input or output synapses, respectively.\n"
				"(Property Neuron.inputs provides identical size\n"
				"functionality to this function.)")
		.def("__str__", &neuron::to_string,
				"Constructs a string description of this neuron, including\n"
				"its id, type, activation, and bias.")
		.add_property("activation", neuron_get_activation, neuron_set_activation,
				"Gets or sets this neuron's activation. Attempting to set\n"
				"the activation of a non-input neuron will result in\n"
				"a runtime error being thrown.")
		.add_property("bias", &neuron::bias,
				"Gets this neuron's bias.")
		.def("connect", &neuron::connect,
				"Connects this neuron to another neuron. If neurons are\n"
				"already connected, or this neuron is an output neuron,\n"
				"throws a runtime error")
		.def("disconnect", &neuron::disconnect, 
				"Disconnects this neuron from another neuron. If neurons are\n"
				"already disconnected, or this neuron is an output neuron,\n"
				"throws a runtime error")
		.def("eval", &neuron::eval,
				"Evaluates and updates the activation of this neuron\n"
				"according to the current activation of its inputs.")
		.add_property("id", &neuron::id, "Gets the id of this neuron.")
		.add_property("inputs", make_function(neuron_inputs, 
				return_value_policy<reference_existing_object>()),
				"An iterable collection of this neuron's input synapses.")
		.add_property("outputs", make_function(neuron_outputs, 
				return_value_policy<reference_existing_object>()),
				"An iterable collection of this neuron's output synapses.")
		.add_property("type", &neuron::type, "Gets the type of this neuron.")
	;
	
	enum_<neuron::connection_type>("Type")
		.value("Internal", neuron::INTERNAL)
		.value("Input", neuron::INPUT)
		.value("Output", neuron::OUTPUT)
	;
	
	class_<neuron::iterable>("Iterable", no_init)
		.def("__iter__", iterator<neuron::iterable>(),
				"Provides iteration through this collection of synapses.")
		.def("__len__", &neuron::iterable::size,
				"Returns the number of synapses in this collection.")
	;
	}
	
	class_<synapse>("Synapse", init<neuron&, float, neuron&>())
		.def("__getitem__", synapse_getitem, return_value_policy<reference_existing_object>(),
				"Retrieves the synapse source or destination by indexes\n"
				"0 or 1, respectively.")
		.def("__len__", &synapse::size,
				"Returns the length of the stored data (always 2).")
		.def("__str__", &synapse::to_string,
				"Constructs a string description of this synapse, including\n"
				"source and destination neuron ids along with synapse weight.")
		.add_property("destination", make_function(synapse_destination, 
				return_value_policy<reference_existing_object>()),
				"Gets the destination neuron of this synapse.")
		.add_property("source", make_function(synapse_source, 
				return_value_policy<reference_existing_object>()),
				"Gets the source neuron of this synapse.")
		.add_property("weight", synapse_get_weight, synapse_set_weight, 
				"Gets or sets the weight of this synapse.")
	;
}
