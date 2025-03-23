#pragma once

#include <juce_gui_basics/juce_gui_basics.h> // Only include necessary JUCE modules

class CustomMouseTracker : public juce::Component {
public:
  CustomMouseTracker();
  ~CustomMouseTracker() override; // Add this!

  void paint(juce::Graphics &g) override;
  void resized() override;

  void mouseMove(const juce::MouseEvent &event) override;  // a
  void mouseDown(const juce::MouseEvent &event) override;  // b
  void mouseDrag(const juce::MouseEvent &event) override;  // c
  void mouseEnter(const juce::MouseEvent &event) override; // d
  void mouseExit(const juce::MouseEvent &event) override;  // e

private:
  int          mouseX = 0, mouseY = 0;
  juce::Colour currentColor = juce::Colours::black;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomMouseTracker)
};
