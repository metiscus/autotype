solution "AutoType"
	configurations { "Debug", "Release" }
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }
 
	configuration "Release"
		defines { "NDEBUG" }
        flags { "Optimize" } 
		
	project "autotype"
		kind "ConsoleApp"
		language "C++"
		files { "**.cpp", "**.h" }
		includedirs{ "rapidxml" }