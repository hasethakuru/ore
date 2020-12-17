workspace "Ore"
	architecture "x64"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
includeDir = {}
includeDir["GLFW"] = "Ore/modules/GLFW/include"

include "Ore/modules/GLFW"

project "Ore"
	location "Ore"

	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "opch.h"
	pchsource "Ore/src/opch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/modules/spdlog/include",
		"%{prj.name}/src",
		"%{includeDir.GLFW}"
	}

	links 
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"ORE_PLATFORM_WINDOWS",
			"ORE_BUILD_DLL"
		}

		postbuildcommands 
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox")
		}

	filter "configurations:Debug"
		defines "ORE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "ORE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "ORE_DIST"
		buildoptions "/MD"
		optimize "On"

project "sandbox"
	location "sandbox"
	kind "ConsoleApp"

	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Ore/modules/spdlog/include",
		"Ore/src"
	}

	links 
	{
		"Ore"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"ORE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ORE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "ORE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ORE_DIST"
		optimize "On"