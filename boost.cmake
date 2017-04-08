set(REQUIRED_BOOST_COMPONENTS filesystem system regex system)

find_package(Boost REQUIRED COMPONENTS ${REQUIRED_BOOST_COMPONENTS})

if (WIN32)
	foreach(COMPONENT ${REQUIRED_BOOST_COMPONENTS})
		string(TOUPPER ${CMAKE_BUILD_TYPE} UPPERCASE_BUILD_TYPE)
		string(TOUPPER ${COMPONENT} COMPONENT_UPPERCASE)
		set(FILENAME ${Boost_${COMPONENT_UPPERCASE}_LIBRARY_${UPPERCASE_BUILD_TYPE}})
		# message("lib:" ${FILENAME})
		
		# get_filename_component(BASE_NAME ${FILENAME} NAME_WE)
		get_filename_component(DIRECTORY_NAME ${FILENAME} PATH)
		
		file(GLOB files ${DIRECTORY_NAME}/../bin/*${COMPONENT}*.dll)
			
		file(COPY ${files} DESTINATION ${CMAKE_BINARY_DIR})
		install(FILES ${files} DESTINATION bin)
	endforeach(COMPONENT)
endif (WIN32)
