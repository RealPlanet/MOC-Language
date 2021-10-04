#include "..\Compiler\compiler.h"
#include <iostream>

CompilerStatus Compiler::start(const TokenList& tok)
{
	tokens = &tok;
	bytebuffer = new ByteBuffer(1);
	label_table = new Labels::LabelTable();

	std::size_t token_size = tokens->size();

	// Convert tokens into bytecode
	for (token_index = 0; token_index < token_size; token_index++) {
		Token tok = tokens->get(token_index);
		int result = tok.writable->write_bytecode(*this, bytebuffer);
		if (result != 0)
			return CompilerStatus::ERROR;
	}

	//Label redefinition pass
	for (int i = 0; i < missingLabels.size(); i++) {
		Labels::LabelInfo info = missingLabels[i];
		if (label_table->has_label(info.label_name)) {
			bytebuffer->write_byte32(label_table->at(info.label_name), true, info.bb_index);
			continue;
		}

		std::cout << "Bad LABEL use, undefined reference for label name ( " << info.label_name << " )." << std::endl;
		return CompilerStatus::ERROR;
	}

	return CompilerStatus::SUCCESS;
}
