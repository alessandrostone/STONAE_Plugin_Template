
# Mandatory line, sets the minimum version of CMake that should be used with this repository.
# I specified 3.22 because I trust it. However, currently I have 3.26 installed on my machine.
# To verify your version run
# $ cmake --version
cmake_minimum_required(VERSION 3.22)

# Sets a few variables, like PROJECT_NAME
project(StonaeAudioPluginTemplate LANGUAGES C CXX OBJC OBJCXX)

# Always use the newest C++ standard on green-field projects if possible.
# Currently, JUCE supports only C++ 20 cross-platform.
set(CMAKE_CXX_STANDARD 20)


cmake_policy(SET CMP0177 NEW)
# I like to download the dependencies to the same folder as the project.
# If you want to install them system wide, set CPM_SOURCE_CACHE with the path to the dependencies
# either as an environment variable or pass it to the cmake script with -DCPM_SOURCE_CACHE=<path>.
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set(PLUGIN_GUI_MAGIC_USE_EXTERNAL_JUCE ON)
# Downloads CPM if not already downloaded. CPM is an easy-to-use package manager nicely integrated with CMake.
include(cmake/cpm.cmake)

# This commands downloads AND configures JUCE. It sets up some variables, like JUCE_SOURCE_DIR.
CPMAddPackage(
    NAME JUCE
    GIT_TAG 8.0.6
    VERSION 8.0.6
    GITHUB_REPOSITORY juce-framework/JUCE
    SOURCE_DIR ${LIB_DIR}/juce
)

# Adds googletest.
CPMAddPackage(
    NAME GOOGLETEST
    GITHUB_REPOSITORY google/googletest
    GIT_TAG v1.15.2
    VERSION 1.15.2
    SOURCE_DIR ${LIB_DIR}/googletest
    OPTIONS
        "INSTALL_GTEST OFF"
        "gtest_force_shared_crt ON"
)

CPMAddPackage(
    NAME visage
    GITHUB_REPOSITORY VitalAudio/visage
    GIT_TAG main
    SOURCE_DIR ${LIB_DIR}/visage
)

CPMAddPackage(
    NAME chowdsp_utils
    GITHUB_REPOSITORY Chowdhury-DSP/chowdsp_utils
    GIT_TAG master
    SOURCE_DIR ${LIB_DIR}/chowdsp_utils
    OPTIONS
        "chowdsp_utils_BUILD_TESTS OFF"
)

CPMAddPackage(
    NAME melatonin_inspector
    GITHUB_REPOSITORY sudara/melatonin_inspector
    GIT_TAG main
    SOURCE_DIR ${LIB_DIR}/melatonin_inspector
    OPTIONS
        "BUILD_TESTS OFF"
)

CPMAddPackage (
        NAME foleys_gui_magic
        GITHUB_REPOSITORY ffAudio/foleys_gui_magic
        GIT_TAG origin/main
        # DOWNLOAD_ONLY YES
        OPTIONS 
        "FOLEYS_BUILD_EXAMPLE OFF"
        "FOLEYS_BUILD_TESTS OFF"
        "FOLEYS_USE_EXTERNAL_JUCE ON"
        "FOLEYS_USE_EXTERNAL_JUCE_MODULES ON"
        "FOLEYS_RUN_PLUGINVAL OFF"
            
    )





# This command allows running tests from the "build" folder (the one where CMake generates the project to).
enable_testing()

# Adds all the targets configured in the "plugin" folder.
add_subdirectory(plugin)

# Adds all the targets configured in the "test" folder.
add_subdirectory(test)
