find_package(Mikmod REQUIRED)

if (WIN32)
	get_filename_component(DIRECTORY_NAME ${MIKMOD_LIBRARY} PATH)
	#message("Mikmod:" ${DIRECTORY_NAME})
	
	file(GLOB files ${DIRECTORY_NAME}/*mikmod*.dll)
			
	#message("glob:" ${files})
			
	file(COPY ${files} DESTINATION ${CMAKE_BINARY_DIR})
	install(FILES ${files} DESTINATION bin)
endif (WIN32)
