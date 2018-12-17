
function(add_platform_module)
	cmake_parse_arguments(ARG "" "" "SOURCES;INCLUDES;LIBRARIES" ${ARGN})

	get_property(tmp GLOBAL PROPERTY NEO_PLATFORM_INCS_PROP)
	set(tmp "${tmp};${ARG_INCLUDES}")
	set_property(GLOBAL PROPERTY NEO_PLATFORM_INCS_PROP "${tmp}")
	
	get_property(tmp GLOBAL PROPERTY NEO_PLATFORM_SRCS_PROP)
	set(tmp "${tmp};${ARG_SOURCES}")
	set_property(GLOBAL PROPERTY NEO_PLATFORM_SRCS_PROP "${tmp}")
	
	get_property(tmp GLOBAL PROPERTY NEO_PLATFORM_LIBS_PROP)
	set(tmp "${tmp};${ARG_LIBRARIES}")
	set_property(GLOBAL PROPERTY NEO_PLATFORM_LIBS_PROP "${tmp}")
endfunction()


function(get_link_libraries OUTPUT_LIST TARGET)
	get_target_property(IMPORTED ${TARGET} IMPORTED)
	list(APPEND VISITED_TARGETS ${TARGET})
	if (IMPORTED)
		get_target_property(LIBS ${TARGET} INTERFACE_LINK_LIBRARIES)
	else()
		get_target_property(LIBS ${TARGET} LINK_LIBRARIES)
	endif()
	set(LIB_FILES "")
	foreach(LIB ${LIBS})
		if (TARGET ${LIB})
			list(FIND VISITED_TARGETS ${LIB} VISITED)
			if (${VISITED} EQUAL -1)
				get_link_libraries(LINK_LIB_FILES ${LIB})
				list(APPEND LIB_FILES ${LIB} ${LINK_LIB_FILES})
			endif()
		endif()
	endforeach()
	set(VISITED_TARGETS ${VISITED_TARGETS} PARENT_SCOPE)
	set(${OUTPUT_LIST} ${LIB_FILES} PARENT_SCOPE)
endfunction()

macro(fix_install_includes tgt)
	set(NEW_INCLUDES "")
	get_target_property(INCS ${tgt} INCLUDE_DIRECTORIES)
	foreach(INC ${INCS})
		set(NEW_INCLUDES ${NEW_INCLUDES} $<BUILD_INTERFACE:${INC}>)
	endforeach()
	
	set_target_properties(${tgt} PROPERTIES INCLUDE_DIRECTORIES "${NEW_INCLUDES}")
	set_target_properties(${tgt} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${NEW_INCLUDES}")
endmacro()
