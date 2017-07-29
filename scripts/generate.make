#####################################################################
# include this file in your master makefile
# rules to call from master.generate:

##---

FLATGLTF_2_0_FLATC_CPP_FLAGS=\
	--cpp --scoped-enums --gen-name-strings --gen-object-api --no-includes --gen-mutable \
	-I $(PROJECT_SCAFFOLDING)/thirdparty/flatgltf/schemas/2.0 \
	-o $(PROJECT_SCAFFOLDING)/thirdparty/flatgltf/include/flatgltf/2.0/

##---

gen_flatgltf_headers: \
	gen_flatgltf_2_0_headers \
	;

gen_flatgltf_2_0_headers:
	@$(PROJECT_SCAFFOLDING)/tools/bin/darwin/flatc \
		$(FLATGLTF_2_0_FLATC_CPP_FLAGS) \
		$(PROJECT_SCAFFOLDING)/thirdparty/flatgltf/schemas/2.0/glTF.fbs
	@clang-format -i $(PROJECT_SCAFFOLDING)/thirdparty/flatgltf/include/flatgltf/2.0/*_generated.h

gen_flatgltf_2_0_schema_headers:
	@$(BIN2CPPSTRING) \
		-f $(PROJECT_SCAFFOLDING)/thirdparty/flatgltf/schemas/2.0/glTF.fbs \
		-o $(PROJECT_SCAFFOLDING)/thirdparty/flatgltf/src/2.0/glTF.cxx \
		-n flatgltf_2_0_schema

##---

# just being verbose
prn_flatgltf_verbose:
	@echo "generating flatgltf"

# rule to invoke
gen_flatgltf_flatbuffers: \
	prn_flatgltf_verbose \
	gen_flatgltf_headers \
	gen_flatgltf_2_0_schema_headers \
	;
