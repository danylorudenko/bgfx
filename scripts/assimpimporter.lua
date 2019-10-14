group "tools/assimp"

project "assimpimporter"

	kind "StaticLib"
	
	includedirs {
		path.join(ASSIMP_DIR, "BINARIES/x64/include"),
		path.join(ASSIMP_DIR, "include")
	}
	
	libdirs {
		path.join(BGFX_DIR, "assimpimporter")
	}
	
	links {
		"assimp-vc141-mtd"
	}
	
	files {
		path.join(BGFX_DIR, "assimpimporter/*.cpp"),
		path.join(BGFX_DIR, "assimpimporter/*.h")
	}
	