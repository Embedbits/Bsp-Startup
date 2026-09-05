# Template version: 1.0.0
# Sets the version of CMakeLists.txt file.
# Never, under any circumstances, change this line. It is used by
# the module generation script to identify the template version.

#======================== Library configuration ===============================#
# Publicly included directories to provide headers include
set( Startup_PublicIncludeDirs
    
)


# Privately included directories to provide headers include
set( Startup_PrivateIncludeDirs
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# Source files list for current library generation
set( Startup_SourceFiles
    Startup.c
)


# List of public header files provided by the current library
set( Startup_PublicHeaders 
    Startup_Types.h
    Startup_Port.h 
)


# List of dependent libraries that are publicly used by the current library
set( Startup_PublicDependentLibs
    Ral_Lib 
)


# List of dependent libraries that are privately used by the current library
set( Startup_PrivateDependentLibs
    Nvic_Lib
    Rcc_Lib
    BspMain_Lib
)


#========================== Library generation ================================#
# Create library
add_library(Startup_Lib STATIC ${Startup_SourceFiles})


# Include necessary libraries to the target
target_link_libraries( Startup_Lib
    PUBLIC 
        ${Startup_PublicDependentLibs} 
    PRIVATE 
        ${Startup_PrivateDependentLibs}
)


# Set public headers directory path in build folder
set(PUBLIC_HEADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/PublicHeaders)

# Generates the public headers directory in build folder
file(MAKE_DIRECTORY ${PUBLIC_HEADERS_DIR})

# Process all public headers
foreach(PublicHeader IN LISTS Startup_PublicHeaders)
    
    # Copy (or configure) only the public header there
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${PublicHeader} 
        ${PUBLIC_HEADERS_DIR}/${PublicHeader}
        COPYONLY
    )
    
endforeach()


# Set include directories for the created target
target_include_directories( Startup_Lib
    PUBLIC
        $<BUILD_INTERFACE:${PUBLIC_HEADERS_DIR}>
        $<INSTALL_INTERFACE:include>
        Startup_PublicIncludeDirs
    PRIVATE
        ${Startup_IncludeDirs}
        Startup_PrivateIncludeDirs
)


# Print status message
message(STATUS "Startup_Lib library created")

#========================= Documentation configuration ========================#
if(DOXYGEN_AVAILABLE STREQUAL "ON")
    Doxygen_AddPath("${CMAKE_CURRENT_SOURCE_DIR}/")
endif()
