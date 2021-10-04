#include <unordered_map>
#ifndef MOC_LABELTABLE_H
#define MOC_LABELTABLE_H
/*
* Stores all label definitions, generated during compilation. If by the end of compile some labels aren't defined (ie a label is used before it's defined)
* A for loop redefineds them.
*/
namespace Labels {

	// Structure used by the compiler to store missing references
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
		// Define a new label pointing to given index.
		void add_label(std::string name, uint32_t bb_index);
		// unordered_map method wrapper
		inline int at(std::string key) { return parsed_labels.at(key); }
		// Checks if label exists
		bool has_label(const std::string& name) const;
		// Getter for a const version of the label table
		inline const std::unordered_map <std::string, uint32_t> getTable() { return parsed_labels; }
	};
}
#endif // !MOC_LABELTABLE_H


