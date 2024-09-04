SolutionName = 'SysInfo'
rootpath = '%{wks.location}/../'
buildpath = function(p) return rootpath..'Bin/'..p..'/' end
objpath = rootpath..'Build/obj/%{cfg.platform}/%{cfg.buildcfg}'
copy = function(p) return '{COPY} %{cfg.buildtarget.abspath} "'..rootpath..p..'/"' end

workspace ( SolutionName )
    configurations { "Debug", "Release" }
	platforms { 'x86', 'x64' }
	cppdialect 'C++latest'
	characterset 'MBCS'
	pic 'On'
	symbols 'On'
	flags 'MultiProcessorCompile'
	location 'Build'

    includedirs {
        'hpp'
    }

    filter {}
        defines { 'SYSINFO_BUILD' }

	filter 'platforms:x86'
		architecture 'x86'
	filter 'platforms:x64'
		architecture 'x86_64'

    filter 'configurations:Debug'
		defines { '_DEBUG' }
		targetsuffix '_d'
		runtime 'Debug'
		optimize 'Debug'
        symbols "On"

	filter 'configurations:Release'
		defines { 'NDEBUG' }
        targetsuffix ''
		runtime 'Release'
		optimize 'Speed'
        symbols "Off"

    filter 'system:windows'
		toolset 'v143'
		preferredtoolarchitecture 'x86_64'
		staticruntime 'On'
		defines {
			'_WIN32',
			'WIN32_LEAN_AND_MEAN',
			'NOMINMAX',
		}
		buildoptions { '/Zc:__cplusplus' }

    project ( SolutionName )
        kind 'SharedLib'
        language "C++"
        targetname ( SolutionName )
        targetdir(buildpath('.'))
        debugdir(buildpath('.'))
        --objdir(objpath)
        
        pchheader "pch.hpp"
        pchsource "pch.cpp"

        vpaths {
            ['Headers/*'] = { 'hpp/SysInfo/**.hpp', 'src/**.hpp' },
            ['Sources/*'] = 'src/**.cpp',
            ['Resources/*'] = { '**.manifest', 'premake5.lua' },
        }
    
        files {
            'premake5.lua',
            'src/**.hpp',
            'src/**.cpp',
            'hpp/**.hpp',
            '**.manifest',
        }

        filter {}