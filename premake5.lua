workspace "Walnut"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir ["glm"] = "Walnut/vendor/glm"


-- Include other premake files
include "Walnut/vendor/GLFW" 
include "Walnut/vendor/Glad"
include "Walnut/vendor/imgui"

project "Walnut"
	location "Walnut"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "wnpch.h"
	pchsource "Walnut/src/wnpch.cpp"


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
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

		defines
		{
			"WN_PLATFORM_WINDOWS",
			"WN_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "WN_DEBUG"
		runtime "Debug"
		symbols "on"

	
	filter "configurations:Release"
		defines "WN_RELEASE"
		runtime "Release"
		optimize "on"

	
	filter "configurations:Dist"
		defines "WN_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Walnut/src",
		"Walnut/vendor",
		"%{IncludeDir.glm}"
	}

	filter "system:windows"
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
		runtime "Debug"
		symbols "on"

	
	filter "configurations:Release"
		defines "WN_RELEASE"
		runtime "Release"
		optimize "on"

	
	filter "configurations:Dist"
		defines "WN_DIST"
		runtime "Release"
		optimize "on"
