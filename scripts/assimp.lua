group "tools/assimp"

project assimp

	kind StaticLib
	
	defines {
		"EXAMPLE=1"
	}
	
	includedirs {
		"myincludedir"
	}
	
	files {
		"mysource.cpp"
	}
	
	--examples of configuration
	configuration { "windows" }
		removefiles {
			path.join(GLSLANG, "glslang/OSDependent/Unix/**.cpp"),
			path.join(GLSLANG, "glslang/OSDependent/Unix/**.h"),
		}

	configuration { "not windows" }
		removefiles {
			path.join(GLSLANG, "glslang/OSDependent/Windows/**.cpp"),
			path.join(GLSLANG, "glslang/OSDependent/Windows/**.h"),
		}

	configuration { "vs*" }
		buildoptions {
			"/wd4005", -- warning C4005: '_CRT_SECURE_NO_WARNINGS': macro redefinition
			"/wd4065", -- warning C4065: switch statement contains 'default' but no 'case' labels
			"/wd4100", -- warning C4100: 'inclusionDepth' : unreferenced formal parameter
			"/wd4127", -- warning C4127: conditional expression is constant
			"/wd4189", -- warning C4189: 'isFloat': local variable is initialized but not referenced
			"/wd4244", -- warning C4244: '=': conversion from 'int' to 'char', possible loss of data
			"/wd4310", -- warning C4310: cast truncates constant value
			"/wd4389", -- warning C4389: '==': signed/unsigned mismatch
			"/wd4456", -- warning C4456: declaration of 'feature' hides previous local declaration
			"/wd4457", -- warning C4457: declaration of 'token' hides function parameter
			"/wd4458", -- warning C4458: declaration of 'language' hides class member
			"/wd4702", -- warning C4702: unreachable code
			"/wd4715", -- warning C4715: 'spv::Builder::makeFpConstant': not all control paths return a value
			"/wd4838", -- warning C4838: conversion from 'spv::GroupOperation' to 'unsigned int' requires a narrowing conversion
		}
		
-- example for linking
project "shaderc"
	kind "ConsoleApp"

	links {
		"assimp",
		"glsl-optimizer"
	}