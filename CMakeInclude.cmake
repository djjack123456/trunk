# ------------------------------------------------------------------------------
# helpers
# ------------------------------------------------------------------------------

# define CMake designation of shared libraries (DLL or so) whatever the OS is
if( WIN32 )
	set( SHARED_LIB_TYPE RUNTIME ) # CMake considers Dlls as RUNTIME on Windows!
else()
	set( SHARED_LIB_TYPE LIBRARY )
endif()

if ( NOT USE_QT5 )

# Find mocable files (simply look for Q_OBJECT in all files!)
function( find_mocable_files __out_var_name )   # + input list
    set( local_list )
    foreach( one_file ${ARGN} )
        file( READ ${one_file} stream )
        if( stream MATCHES "Q_OBJECT" )
            list( APPEND local_list ${one_file} )
        endif()
    endforeach()
    set( ${__out_var_name} ${local_list} PARENT_SCOPE )
endfunction()

endif() #if ( NOT USE_QT5 )

# Export Qt Dlls to specified destinations
function( install_Qt_Dlls ) # 2 arguments: ARGV0 = release destination / ARGV1 = debug destination
if( WIN32 )
	if( ${ARGC} EQUAL 1 )
		
		if ( NOT USE_QT5 )
			set( QT_RELEASE_DLLS QtCore${QT_VERSION_MAJOR} QtGui${QT_VERSION_MAJOR} QtOpenGL${QT_VERSION_MAJOR} )
		else()
			set( QT_RELEASE_DLLS Qt5Core Qt5Gui Qt5OpenGL Qt5Widgets Qt5Concurrent Qt5PrintSupport icuin51 icuuc51 icudt51 )
			set( QT_BINARY_DIR ${QT5_ROOT_PATH}/bin )
		endif()
		#specific case for the MinGW version of Qts
		if( MINGW )
			list( APPEND QT_RELEASE_DLLS libgcc )
			list( APPEND QT_RELEASE_DLLS mingwm )
		endif()

		#release version
		foreach( element ${QT_RELEASE_DLLS} )
			file( GLOB dll_files ${QT_BINARY_DIR}/${element}*.dll )
			foreach( qtDLL ${dll_files} )
				if( NOT CMAKE_CONFIGURATION_TYPES )
					install( FILES ${qtDLL} DESTINATION ${ARGV0} )
				else()
					install( FILES ${qtDLL} CONFIGURATIONS Release DESTINATION ${ARGV0} )
				endif()
			endforeach()
		endforeach()
		
		# for mutli-config compiler only
		if( CMAKE_CONFIGURATION_TYPES )
		
			#release with debug info version
			foreach( element ${QT_RELEASE_DLLS} )
				file( GLOB dll_files ${QT_BINARY_DIR}/${element}*.dll )
				foreach( qtDLL ${dll_files} )
					install( FILES ${qtDLL} CONFIGURATIONS RelWithDebInfo DESTINATION ${ARGV0}_withDebInfo )
				endforeach()
			endforeach()

			#debug version
			if ( NOT USE_QT5 )
				set( QT_DEBUG_DLLS QtCored${QT_VERSION_MAJOR} QtGuid${QT_VERSION_MAJOR} QtOpenGLd${QT_VERSION_MAJOR} )
			else()
				set( QT_DEBUG_DLLS Qt5Cored Qt5Guid Qt5OpenGLd Qt5Widgetsd Qt5PrintSupportd icuin51 icuuc51 icudt51 )
				#set( QT_BINARY_DIR ${QT5_ROOT_PATH}/bin )
			endif()
			#specific case for the MinGW version of Qts
			if( MINGW )
				list( APPEND QT_DEBUG_DLLS libgcc )
				list( APPEND QT_DEBUG_DLLS mingwm )
			endif()
		
			foreach( element ${QT_DEBUG_DLLS} )
				file( GLOB dll_files ${QT_BINARY_DIR}/${element}*.dll )
				foreach( qtDLL ${dll_files} )
					install( FILES ${qtDLL} CONFIGURATIONS Debug DESTINATION ${ARGV0}_debug )
				endforeach()
			endforeach()

		endif()
	else()
		message( SEND_ERROR "function install_Qt_Dlls: invalid number of arguments! (need base destination)" )
	endif()
endif()
endfunction()

# Export Qt5 plugins to specified destinations
function( install_Qt5_plugins )

if( WIN32 )		# 1 argument: ARGV0 = base destination
	if( USE_QT5 )
		set( QT_PLUGINS_DIR ${QT5_ROOT_PATH}/plugins )
		set( platformPlugin qwindows )
		if( NOT CMAKE_CONFIGURATION_TYPES )
			install( FILES ${QT_PLUGINS_DIR}/platforms/${platformPlugin}.dll DESTINATION ${ARGV0}/platforms )
		else()
			install( FILES ${QT_PLUGINS_DIR}/platforms/${platformPlugin}.dll CONFIGURATIONS Release DESTINATION ${ARGV0}/platforms )
			install( FILES ${QT_PLUGINS_DIR}/platforms/${platformPlugin}.dll CONFIGURATIONS RelWithDebInfo DESTINATION ${ARGV0}_withDebInfo/platforms )
			install( FILES ${QT_PLUGINS_DIR}/platforms/${platformPlugin}d.dll CONFIGURATIONS Debug DESTINATION ${ARGV0}_debug/platforms )
		endif()
	endif()
endif()
endfunction()

# Export Qt imageformats DLLs to specified destinations
function( install_Qt_ImageFormats )
if( WIN32 )		# 1 argument: ARGV0 = base destination
	if( USE_QT5 )
		set( QT_PLUGINS_DIR ${QT5_ROOT_PATH}/plugins )
		set( QT_IMAGEFORMATS_PLUGINS qgif qico qjpeg )
	else()
		set( QT_VER_NUM "4")
	endif()
	foreach( imagePlugin ${QT_IMAGEFORMATS_PLUGINS} )
		if( NOT CMAKE_CONFIGURATION_TYPES )
			install( FILES ${QT_PLUGINS_DIR}/imageformats/${imagePlugin}${QT_VER_NUM}.dll DESTINATION ${ARGV0}/imageformats )
		else()
			install( FILES ${QT_PLUGINS_DIR}/imageformats/${imagePlugin}${QT_VER_NUM}.dll CONFIGURATIONS Release DESTINATION ${ARGV0}/imageformats )
			install( FILES ${QT_PLUGINS_DIR}/imageformats/${imagePlugin}${QT_VER_NUM}.dll CONFIGURATIONS RelWithDebInfo DESTINATION ${ARGV0}_withDebInfo/imageformats )
			install( FILES ${QT_PLUGINS_DIR}/imageformats/${imagePlugin}d${QT_VER_NUM}.dll CONFIGURATIONS Debug DESTINATION ${ARGV0}_debug/imageformats )
		endif()
	endforeach()
elseif( APPLE )	# 2 arguments: ARGV0 = bundle's plugin dir (destination) / ARGV1 = list of plugins to pass to fixup_bundle
	if ( USE_QT5 )
		message( SEND_ERROR "CMake's FindQt5 script doesn't help us anymore for this!!!" )
	endif()
	# install imageformat plugins
	foreach( imagePlugin ${QT_IMAGEFORMATS_PLUGINS} )
		set( PLUGIN_NAME lib${imagePlugin}${CMAKE_SHARED_LIBRARY_SUFFIX} )
		install( FILES ${QT_PLUGINS_DIR}/imageformats/${PLUGIN_NAME} DESTINATION ${ARGV0}/imageformats COMPONENT Runtime )
		list( APPEND QT_PLUGINS ${ARGV0}/imageformats/${PLUGIN_NAME} )
	endforeach()
	set( ${ARGV1} ${QT_PLUGINS} PARENT_SCOPE )
endif()
endfunction()

# Install shared libraries depending on the build configuration and OS
function( install_shared )	# 3 arguments:
							# ARGV0 = target
							# ARGV1 = release install destination
							# ARGV2 = 1 for debug install (if available)
							# ARGV3 = suffix (optional)
if( NOT CMAKE_CONFIGURATION_TYPES )
	install( TARGETS ${ARGV0} ${SHARED_LIB_TYPE} DESTINATION ${ARGV1}${ARGV3} )
else()
	install( TARGETS ${ARGV0} ${SHARED_LIB_TYPE} CONFIGURATIONS Release DESTINATION ${ARGV1}${ARGV3} )
	install( TARGETS ${ARGV0} ${SHARED_LIB_TYPE} CONFIGURATIONS RelWithDebInfo DESTINATION ${ARGV1}_withDebInfo${ARGV3} )
	if (${ARGV2} EQUAL 1)
		install( TARGETS ${ARGV0} ${SHARED_LIB_TYPE} CONFIGURATIONS Debug DESTINATION ${ARGV1}_debug${ARGV3} )
	endif()
endif()
endfunction()

# Extended 'install' command depending on the build configuration and OS
# 4 arguments:
#   - ARGV0 = signature
#   - ARGV1 = target (warning: one project or one file at a time)
#   - ARGV2 = base install destination (_debug or _withDebInfo will be automatically appended if multi-conf is supported)
#   - ARGV3 = install destination suffix (optional)
function( install_ext )
if( NOT CMAKE_CONFIGURATION_TYPES )
	install( ${ARGV0} ${ARGV1} DESTINATION ${ARGV2}${ARGV3} )
else()
	install( ${ARGV0} ${ARGV1} CONFIGURATIONS Release DESTINATION ${ARGV2}${ARGV3} )
	install( ${ARGV0} ${ARGV1} CONFIGURATIONS RelWithDebInfo DESTINATION ${ARGV2}_withDebInfo${ARGV3} )
	install( ${ARGV0} ${ARGV1} CONFIGURATIONS Debug DESTINATION ${ARGV2}_debug${ARGV3} )
endif()
endfunction()

# Default preprocessors
function( set_default_cc_preproc ) # 1 argument: ARGV0 = target
set( CC_DEFAULT_PREPROCESSORS NOMINMAX _CRT_SECURE_NO_WARNINGS ) #all configurations
set( CC_DEFAULT_PREPROCESSORS_RELEASE NDEBUG ) #release specific
set( CC_DEFAULT_PREPROCESSORS_DEBUG _DEBUG ) #debug specific

if (MSVC)
	#disable SECURE_SCL (see http://channel9.msdn.com/shows/Going+Deep/STL-Iterator-Debugging-and-Secure-SCL/)
	list( APPEND CC_DEFAULT_PREPROCESSORS_RELEASE _SECURE_SCL=0 )

	#use VLD for mem leak checking
	OPTION( OPTION_USE_VISUAL_LEAK_DETECTOR "Check to activate compilation (in debug) with Visual Leak Detector" OFF )
    if( ${OPTION_USE_VISUAL_LEAK_DETECTOR} )
		list( APPEND CC_DEFAULT_PREPROCESSORS_DEBUG USE_VLD )
    endif()
endif()

set_property( TARGET ${ARGV0} APPEND PROPERTY COMPILE_DEFINITIONS ${CC_DEFAULT_PREPROCESSORS} )
if( NOT CMAKE_CONFIGURATION_TYPES )
	set_property( TARGET ${ARGV0} APPEND PROPERTY COMPILE_DEFINITIONS ${CC_DEFAULT_PREPROCESSORS_RELEASE} )
else()
	set_property( TARGET ${ARGV0} APPEND PROPERTY COMPILE_DEFINITIONS_RELEASE ${CC_DEFAULT_PREPROCESSORS_RELEASE} )
	set_property( TARGET ${ARGV0} APPEND PROPERTY COMPILE_DEFINITIONS_DEBUG ${CC_DEFAULT_PREPROCESSORS_DEBUG} )
endif()
endfunction()

if( APPLE )
   function( get_support_libs )  # 1 argument - return var
      # get a list of support libs based on configuration
      #  we need this to install them properly when we are bundling the app
      list( APPEND SUPPORT_LIB_NAMES libCC_CORE_LIB )
      list( APPEND SUPPORT_LIB_NAMES libQCC_DB_LIB )

      if( ${OPTION_USE_XIOT} )
         list( APPEND SUPPORT_LIB_NAMES libxiot )
         list( APPEND SUPPORT_LIB_NAMES libxerces-c )
         list( APPEND SUPPORT_LIB_NAMES libopenFI )
      endif()
      
      if( ${OPTION_USE_LIBLAS} )
         list( APPEND SUPPORT_LIB_NAMES liblas )
         list( APPEND SUPPORT_LIB_NAMES liblaszip )
      endif()

      foreach( supportLib ${SUPPORT_LIB_NAMES} )
         set( LIB_NAME ${CMAKE_INSTALL_PREFIX}/lib/${supportLib}${CMAKE_SHARED_LIBRARY_SUFFIX} )
      
         # resolve any symbolic links
         get_filename_component( _resolvedFile ${LIB_NAME} REALPATH )
         list( APPEND SUPPORT_LIBS ${_resolvedFile} )
      endforeach()
   
      set( ${ARGV0} ${SUPPORT_LIBS} PARENT_SCOPE )
   endfunction()
endif()
