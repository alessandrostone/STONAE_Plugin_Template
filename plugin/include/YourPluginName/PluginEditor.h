#pragma once

#include "CustomMouseTracker.h"
#include "GUIConstants.h"
#include "PluginProcessor.h"
#include "TabbedComponent.h"
#include "melatonin_inspector/melatonin_inspector.h"
#include <array>
#include <functional>
#include <juce_gui_basics/juce_gui_basics.h>
#include <visage/app.h>

// ██████╗ ██╗     ██╗   ██╗ ██████╗ ██╗███╗   ██╗
// ██╔══██╗██║     ██║   ██║██╔════╝ ██║████╗  ██║
// ██████╔╝██║     ██║   ██║██║  ███╗██║██╔██╗ ██║
// ██╔═══╝ ██║     ██║   ██║██║   ██║██║██║╚██╗██║
// ██║     ███████╗╚██████╔╝╚██████╔╝██║██║ ╚████║
// ╚═╝     ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝  ╚═══╝

// ███████╗██████╗ ██╗████████╗ ██████╗ ██████╗
// ██╔════╝██╔══██╗██║╚══██╔══╝██╔═══██╗██╔══██╗
// █████╗  ██║  ██║██║   ██║   ██║   ██║██████╔╝
// ██╔══╝  ██║  ██║██║   ██║   ██║   ██║██╔══██╗
// ███████╗██████╔╝██║   ██║   ╚██████╔╝██║  ██║
// ╚══════╝╚═════╝ ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝

namespace audio_plugin {

struct AttachedSlider {
  using Slider = juce::Slider;
  using Attachment = juce::SliderParameterAttachment;
  using Component = juce::Component;

  AttachedSlider(AudioPluginAudioProcessor &processor, param::PID pID)
      : slider(), attachment(*processor.params[static_cast<size_t>(pID)],
                             slider, nullptr) {
    slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
  }

  Slider     slider;
  Attachment attachment;
};
class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  using AttachedSliderArray = std::array<AttachedSlider, param::NumParams>;
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
  // This constructor will be called when the editor is created.
  // It is called by the AudioProcessorEditor constructor.
  // The editor is created when the plugin is loaded, and it is destroyed
  // when the plugin is unloaded.
  void AddVisageApp();
  ~AudioPluginAudioProcessorEditor() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  AudioPluginAudioProcessor &processorRef;

  // melatonin::Inspector inspector{*this};

  std::unique_ptr<visage::ApplicationWindow> app_;

  TabbedComponent tabs{juce::TabbedButtonBar::TabsAtTop};

  juce::Slider     slider;
  juce::ComboBox   menu;
  juce::TextButton button;

  CustomMouseTracker mouseTracker;

  juce::ComponentBoundsConstrainer constrainer;
  void                             setResizeBehaviour();

  AttachedSliderArray sliders;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
} // namespace audio_plugin
