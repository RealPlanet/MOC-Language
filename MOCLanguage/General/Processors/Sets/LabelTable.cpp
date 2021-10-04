#include "LabelTable.h"
#include <fstream>
#include <sstream>
#include <functional>
#include "..\..\Util.h"

void Labels::LabelTable::add_label(std::string name, std::uint32_t bb_index)
{
	//If this is a new label simply add it at the end of table
	if (parsed_labels.find(name) == parsed_labels.end()){
		parsed_labels[name] = bb_index;
	}	
}
/*
void Labels::LabelTable::write_labels_to_file(std::string path)
{
	std::ofstream output(path, std::ios::binary);
	for (auto val : getTable()) {
		output << val.first << " " << val.second << std::endl;
	}
	output.close();
}

void Labels::LabelTable::read_labels_from_file(std::string path)
{
	std::ifstream input(path, std::ios::binary);
	std::string source = "";
	source.assign((std::istreambuf_iterator<char>(input)),
		(std::istreambuf_iterator<char>()));
	pUtil::trim(source);

	std::istringstream file_stream(source);
	while (!file_stream.eof()) {
		std::string next_line;
		std::getline(file_stream, next_line);

		//Key-Value pair for each line
		std::istringstream line_stream(next_line);
		std::string key;
		std::string value;
		line_stream >> key;
		line_stream >> value;

		parsed_labels[key] = pUtil::get_number(value);
	}
	input.close();
}
*/
bool Labels::LabelTable::has_label(const std::string& name) const
{
	return !(parsed_labels.find(name) == parsed_labels.end());
}

