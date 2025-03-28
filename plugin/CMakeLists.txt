cmake_minimum_required(VERSION 3.22)

# Version is needed by JUCE.
project(AudioPlugin
    VERSION 0.1.0
    LANGUAGES CXX OBJCXX C
)
# juce_add_module(${PluginGuiMagic_SOURCE_DIR}/modules/foleys_gui_magic)
# Adding a directory with the library/application name as a subfolder of the
# include folder is a good practice. It helps avoid name clashes later on.
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/YourPluginName")

# Adds a plugin target (that's basically what the Projucer does).
juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME MyCompany # change this
    IS_SYNTH FALSE # may change this
    NEEDS_MIDI_INPUT FALSE # may change this
    NEEDS_MIDI_OUTPUT FALSE # may change this
    PLUGIN_MANUFACTURER_CODE MCMP # change this
    PLUGIN_CODE EXPL # change this
    FORMATS Standalone VST3 # may change this
    PRODUCT_NAME "YourPluginName" # change this
)

# Sets the source files of the plugin project.
target_sources(${PROJECT_NAME}
    PRIVATE
    source/PluginEditor.cpp
    source/PluginProcessor.cpp
    source/CustomMouseTracker.cpp
    ${INCLUDE_DIR}/PluginEditor.h
    ${INCLUDE_DIR}/PluginProcessor.h
    ${INCLUDE_DIR}/TabbedComponent.h
    ${INCLUDE_DIR}/CustomMouseTracker.h
    ${INCLUDE_DIR}/Params.h
)

# Sets the include directories of the plugin project.
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*
    # (Optional) If you need to propagate any include directories or definitions:
    PRIVATE 
    ${JUCE_DIR}/modules
)

# Links to all necessary dependencies. The present ones are recommended by JUCE.
# If you use one of the additional modules, like the DSP module, you need to specify it here.
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    foleys_gui_magic
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_basics
    juce::juce_core
    juce::juce_audio_basics
    juce::juce_audio_processors
    juce::juce_audio_plugin_client
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_extra
    juce::juce_opengl
    visage
    # chowdsp::chowdsp_dsp_utils
    # chowdsp::chowdsp_gui
    # chowdsp::chowdsp_plugin_base
    # chowdsp::chowdsp_plugin_state
    # chowdsp::chowdsp_parameters
    # chowdsp::chowdsp_plugin_utils
    # chowdsp::chowdsp_presets_v2
    # chowdsp::chowdsp_gui
    melatonin_inspector
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)

# These definitions are recommended by JUCE.
target_compile_definitions(${PROJECT_NAME}
    PUBLIC
    # switch the following off in the product to hide editor
    FOLEYS_SHOW_GUI_EDITOR_PALLETTE=1
    FOLEYS_SAVE_EDITED_GUI_IN_PLUGIN_STATE=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_MODAL_LOOPS_PERMITTED=1
)
install(TARGETS AudioPlugin_Standalone
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)
