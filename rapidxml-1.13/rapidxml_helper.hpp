#include "rapidxml.hpp"

using namespace rapidxml;

xml_node<>* getChildWithAttribute(const xml_node<>* parent, std::string childName, std::string attr, std::string value)
{
	xml_node<>* node = parent->first_node(childName.c_str());
	while (xml_attribute<>* attribute = node->first_attribute(attr.c_str())) {
		if (std::string(attribute->value()) != value)
		{
			node = node->next_sibling(childName.c_str());
		}
	}
	return node;
}