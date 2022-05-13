#ifndef MOC_LABEL_H
#define MOC_LABEL_H
#include "..\..\BaseClasses\Writable\BCWritable.h"
#include "..\..\Processors\Sets\LabelTable.h"
#include "..\..\Processors\Compiler\Compiler.h"

/*
* Stores a label definition or reference, handles writing the label reference OR marking the label as "to be updated" at the end of compile.
* Syntax:	L: for definition,
*			@R for reference
*/
class LabelName : public BCWritable {
public:
	std::string name;

	// If this is the definition or simply a reference used in an instruction
	bool isDefinition = false;

	LabelName(std::string n, bool isdef) : name{ n }, isDefinition{ isdef } {}
	virtual int write_bytecode(Compiler& compiler, ByteBuffer* bb) const override {
		if (isDefinition) {
			compiler.getLabels()->add_label(name, bb->buffer_index());
			return 0;
		}

		// If label doesn't exit save it for later
		if(!isDefinition && !compiler.getLabels()->has_label(name)){
			// Needs to save label name and bb index to overwrite the placeholder bits
			Labels::LabelInfo info(name, bb->buffer_index()); //FIXME :: +1
			bb->write_byte32(0x00);
			compiler.getUndefinedLabelReferences().push_back(info);
			return 0;
		}

		
		bb->write_byte32(compiler.getLabels()->at(name));
		return 0;
	}
};

#endif