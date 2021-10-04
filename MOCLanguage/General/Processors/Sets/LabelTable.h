#include <unordered_map>
#ifndef MOC_LABELTABLE_H
#define MOC_LABELTABLE_H

namespace Labels {
	struct LabelInfo {
		std::size_t bb_index;
		std::string label_name;

		LabelInfo(std::string name, std::size_t index) : label_name{ name }, bb_index{ index }{}
	};

	class LabelTable
	{
	private:
		// Label name - Label BB Index
		std::unordered_map <std::string, uint32_t>	parsed_labels;
	public:
		LabelTable() {}
		void add_label(std::string name, uint32_t bb_index);
		//void write_labels_to_file(std::string path);
		//void read_labels_from_file(std::string path);

		inline int at(std::string key) { return parsed_labels.at(key); }
		bool has_label(const std::string& name) const;
		inline const std::unordered_map <std::string, uint32_t> getTable() { return parsed_labels; }
	};

	
}
#endif // !MOC_LABELTABLE_H


