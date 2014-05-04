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
		.def("__getitem__", network_getitem, return_value_policy<reference_existing_object>())
		.def("__iter__", iterator<network>())
		.def("__len__", &network::size)
		.def("add", &network::add, 
				network_add_overloads(args("id", "type", "activation", "bias"), ""))
		.def("add_input", &network::add_input, 
				network_add_input_overloads(args("id", "activation"), ""))
		.def("add_internal", &network::add_internal, 
				network_add_internal_overloads(args("id", "bias"), ""))
		.def("add_output", &network::add_output, 
				network_add_output_overloads(args("id", "bias"), ""))
		.def("clear", &network::clear)
		.def("contains", &network::contains)
		.def("erase", &network::erase)
		.def("eval_non_rec", &network::eval_non_rec)
		.add_property("inputs", make_function(network_inputs, 
				return_value_policy<reference_existing_object>()))
		.add_property("outputs", make_function(network_outputs, 
				return_value_policy<reference_existing_object>()))
		.def("read_file", &network::read_file)
		.def("write_file", &network::write_file)
	;
	
	class_<network::iterable>("Iterable", no_init)
		.def("__iter__", iterator<network::iterable>())
		.def("__len__", &network::iterable::size)
	;
	}
	
	{
	scope outer = class_<neuron>("Neuron", init<int, neuron::connection_type, float, float>())
		.def("__iter__", iterator<neuron>())
		.def("__len__", &neuron::size)
		.def("__str__", &neuron::to_string)
		.add_property("activation", neuron_get_activation, neuron_set_activation)
		.add_property("bias", &neuron::bias)
		.def("connect", &neuron::connect)
		.def("disconnect", &neuron::disconnect)
		.def("eval", &neuron::eval)
		.add_property("id", &neuron::id)
		.add_property("inputs", make_function(neuron_inputs, 
				return_value_policy<reference_existing_object>()))
		.add_property("outputs", make_function(neuron_outputs, 
				return_value_policy<reference_existing_object>()))
		.add_property("type", &neuron::type)
	;
	
	enum_<neuron::connection_type>("Type")
		.value("Internal", neuron::INTERNAL)
		.value("Input", neuron::INPUT)
		.value("Output", neuron::OUTPUT)
	;
	
	class_<neuron::iterable>("Iterable", no_init)
		.def("__iter__", iterator<neuron::iterable>())
		.def("__len__", &neuron::iterable::size)
	;
	}
	
	class_<synapse>("Synapse", init<neuron&, float, neuron&>())
		.def("__getitem__", synapse_getitem, return_value_policy<reference_existing_object>())
		.def("__len__", &synapse::size)
		.def("__str__", &synapse::to_string)
		.add_property("destination", make_function(synapse_destination, 
				return_value_policy<reference_existing_object>()))
		.add_property("source", make_function(synapse_source, 
				return_value_policy<reference_existing_object>()))
		.add_property("weight", synapse_get_weight, synapse_set_weight)
	;
}
