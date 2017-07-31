-- premake for flatgltf_unittests

---

if generate_thirdparty_projects and generate_thirdparty_projects == true then

---

project "flatgltf_2_0_loader"
	kind "ConsoleApp"
	language "C++"
	flags {}

	includedirs {
		flatgltf_includedirs,
		flatbuffers_includedirs,
		glm_includedirs,
		khutils_includedirs,
		bandit_includedirs,
	}

	defines {
	}

	files {
		path.join(flatgltf_root, "test", "flatgltf_2_0_loader.cpp"),
	}

	links {
		"flatgltf_2_0",
		"flatbuffers",
	}

build_cppfwd("flatgltf_2_0_loader")

end -- _OPTIONS["with-thirdparty"] ~= nil

---

