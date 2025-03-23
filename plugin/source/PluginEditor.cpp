#include "YourPluginName/PluginEditor.h"
#include "YourPluginName/PluginProcessor.h"
#include <visage/app.h>
#include <visage_app/application_window.h>
#include <visage_ui/popup_menu.h>

using namespace visage::dimension;

namespace audio_plugin {

AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p),
      sliders{AttachedSlider(p, param::PID::GainWet),
              AttachedSlider(p, param::PID::Frequency)} {

  juce::ignoreUnused(processorRef);

  // addTabsComponent();

  for (int i = 0; i < tabs.getNumTabs(); ++i) {
    auto *tabButton = tabs.getTabbedButtonBar().getTabButton(i);
    tabButton->setWantsKeyboardFocus(true);
  }

  for (auto i = 0u; i < sliders.size();
       ++i) { // Here 'u' suffix indicates the integer literal is of type
              // 'unsigned int', same as size_type but without signedness
    auto &sliderr = sliders[i];

    addAndMakeVisible(sliderr.slider);
  }

  setSize(400, 300); // default size

  // addAndMakeVisible(mouseTracker);

  // AddVisageApp();

  // open the inspector window
  // inspector.setVisible(true);

  // enable the inspector
  // inspector.toggle(true);
  setResizeBehaviour();
}

void AudioPluginAudioProcessorEditor::addTabsComponent() {
  slider.setSliderStyle(
      juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
  slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
  slider.setWantsKeyboardFocus(true);
  tabs.addTab("Slider", juce::Colours::coral, &slider, false);

  menu.addItemList(juce::StringArray{"Item 1", "Item 2", "Item 3"}, 1);
  menu.setSelectedItemIndex(0);
  menu.setDescription("Test Menu");
  tabs.addTab("Menu", juce::Colours::blue, &menu, false);

  button.setButtonText("Demo");
  button.setClickingTogglesState(true);

  tabs.addTab("Button", juce::Colours::red, &button, false);

  addAndMakeVisible(tabs);
}

void AudioPluginAudioProcessorEditor::setResizeBehaviour() {
  using namespace GUIConstants;
  constrainer.setSizeLimits(
      int((float)defaultWidth * 0.5f), int((float)defaultHeight * 0.5f),
      int((float)defaultWidth * 5.0f), int((float)defaultHeight * 5.0f));
  setConstrainer(&constrainer);
  setResizable(true, true);
}

void AudioPluginAudioProcessorEditor::AddVisageApp() {
  app_ = std::make_unique<visage::ApplicationWindow>();
  app_->setWindowDimensions(80_vmin, 60_vmin);

  app_->onDraw() = [this](visage::Canvas &canvas) {
    canvas.setColor(0xff000066);
    canvas.fill(0, 0, app_->width(), app_->height());

    float circle_radius = app_->height() * 0.1f;
    float x = app_->width() * 0.5f - circle_radius;
    float y = app_->height() * 0.5f - circle_radius;
    canvas.setColor(0xff00ffff);
    canvas.circle(x, y, 2.0f * circle_radius);
  };

  app_->onResize() = [this] {
    DBG("window resized: " << app_->width() << "x" << app_->height());
  };

  app_->onShow() = [] { DBG("window shown"); };
  app_->onHide() = [] { DBG("window hidden"); };

  app_->show();
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {
  DBG("editor destroyed");
  // app_->close();
  // app_.reset();
  // inspector.setVisible(false);
  // inspector.toggle(false);
}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("STONAE Audio Plugin Template", getLocalBounds(),
                   juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized() {
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
  auto bounds = getLocalBounds();
  tabs.setBounds(bounds);
  mouseTracker.setBounds(getLocalBounds()); // Fill entire editor

  auto w = static_cast<float>(getWidth());
  auto h = static_cast<float>(getHeight());

  auto x = 0.f;
  auto y = 0.f;
  auto sliderWidth = w / static_cast<float>(sliders.size());
  for (int i = 0; i < static_cast<int>(sliders.size()); ++i) {
    sliders[i].slider.setBounds(
        juce::Rectangle<float>(x, y, sliderWidth, h).toNearestInt());
    x += sliderWidth;
  }
}

} // namespace audio_plugin
