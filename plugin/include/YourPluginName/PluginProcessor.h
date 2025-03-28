#pragma once

#include "Params.h"
#include <array>

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>

// third-party includes
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE(
    "-Wunused-function") // GCC doesn't like Foley's static functions
JUCE_BEGIN_IGNORE_WARNINGS_MSVC(
    4458) // MSVC doesn't like Foley's hiding class members
#include <foleys_gui_magic/foleys_gui_magic.h>
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
JUCE_END_IGNORE_WARNINGS_MSVC

namespace audio_plugin {
class AudioPluginAudioProcessor : public foleys::MagicProcessor {
public:
  using RAPPtr = juce::RangedAudioParameter *;
  using RAPPtrArray = std::array<RAPPtr, param::NumParams>;
  AudioPluginAudioProcessor();
  ~AudioPluginAudioProcessor() override;

  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
  using AudioProcessor::processBlock;

  // juce::AudioProcessorEditor *createEditor() override;
  // bool                        hasEditor() const override;

  const juce::String getName() const override;

  bool   acceptsMidi() const override;
  bool   producesMidi() const override;
  bool   isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  int                getNumPrograms() override;
  int                getCurrentProgram() override;
  void               setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

  juce::AudioProcessorValueTreeState apvts;
  RAPPtrArray                        params;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessor)
};
} // namespace audio_plugin
