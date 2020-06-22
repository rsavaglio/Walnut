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
IncludeDir ["Glad"] = "Walnut/vendor/Glad/include"
IncludeDir ["ImGui"] = "Walnut/vendor/imgui"


-- Include other premake files
include "Walnut/vendor/GLFW" 
include "Walnut/vendor/Glad"
include "Walnut/vendor/imgui"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"WN_PLATFORM_WINDOWS",
			"WN_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "WN_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	
	filter "configurations:Release"
		defines "WN_RELEASE"
		buildoptions "/MD"
		optimize "On"

	
	filter "configurations:Dist"
		defines "WN_DIST"
		buildoptions "/MD"
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
		buildoptions "/MDd"
		symbols "On"

	
	filter "configurations:Release"
		defines "WN_RELEASE"
		buildoptions "/MD"
		optimize "On"

	
	filter "configurations:Dist"
		defines "WN_DIST"
		buildoptions "/MD"
		optimize "On"