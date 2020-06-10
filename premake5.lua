workspace "Walnut"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{architechture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {} -- Struct, LUA Table
IncludeDir ["GLFW"] = "Walnut/vendor/GLFW/include"

include "Walnut/vendor/GLFW" -- this includes the premake file from the submodule, gets included like a header file

project "Walnut"
	location "Walnut"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "wnpch.h"
	pchsource "Walnut/src/wnpch.cpp"


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
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

		defines
		{
			"WN_PLATFORM_WINDOWS",
			"WN_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "WN_DEBUG"
		symbols "On"

	
	filter "configurations:Release"
		defines "WN_RELEASE"
		optimize "On"

	
	filter "configurations:Dist"
		defines "WN_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Walnut/vendor/spdlog/include",
		"Walnut/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"WN_PLATFORM_WINDOWS"
		}

	links
	{
		"Walnut"
	}

	filter "configurations:Debug"
		defines "WN_DEBUG"
		symbols "On"

	
	filter "configurations:Release"
		defines "WN_RELEASE"
		optimize "On"

	
	filter "configurations:Dist"
		defines "WN_DIST"
		optimize "On"