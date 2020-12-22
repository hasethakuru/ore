workspace "Ore"
	architecture "x64"
	startproject "sandbox"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
includeDir = {}
includeDir["GLFW"] = "Ore/modules/GLFW/include"
includeDir["Glad"] = "Ore/modules/Glad/include"
includeDir["ImGui"] = "Ore/modules/imgui"
includeDir["glm"] = "Ore/modules/glm"

include "Ore/modules/GLFW"
include "Ore/modules/Glad"
include "Ore/modules/imgui"

project "Ore"
	location "Ore"

	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "opch.h"
	pchsource "Ore/src/opch.cpp"

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/modules/glm/glm/**.hpp",
		"%{prj.name}/modules/glm/glm/**.inl"
	}

	includedirs {
		"%{prj.name}/modules/spdlog/include",
		"%{prj.name}/src",
		"%{includeDir.GLFW}",
		"%{includeDir.Glad}",
		"%{includeDir.ImGui}",
		"%{includeDir.glm}"
	}

	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"ORE_PLATFORM_WINDOWS",
			"ORE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	
	filter "configurations:Debug"
		defines "ORE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ORE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ORE_DIST"
		runtime "Release"
		optimize "on"

project "sandbox"
	location "sandbox"
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")	
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Ore/modules/spdlog/include",
		"Ore/src",
		"%{includeDir.glm}",
		"Ore/modules"
	}

	links 
	{
		"Ore"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"ORE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ORE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ORE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ORE_DIST"
		runtime "Release"
		optimize "on"