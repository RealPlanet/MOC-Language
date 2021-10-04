#include "LabelTable.h"
#include "..\..\Util.h"
#include <fstream>
#include <sstream>
#include <functional>

void Labels::LabelTable::add_label(std::string name, std::uint32_t bb_index){
	//If this is a new label simply add it at the end of table
	// Ignore all following redefinitions
	if (parsed_labels.find(name) == parsed_labels.end()){
		parsed_labels[name] = bb_index;
	}	
}
bool Labels::LabelTable::has_label(const std::string& name) const{
	return !(parsed_labels.find(name) == parsed_labels.end());
}