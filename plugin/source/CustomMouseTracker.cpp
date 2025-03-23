#include "YourPluginName/CustomMouseTracker.h"

CustomMouseTracker::~CustomMouseTracker() {} 

// Constructor
CustomMouseTracker::CustomMouseTracker()
{
    setSize(400, 300); // Default size
}

// Paint function (draws background and mouse coordinates)
void CustomMouseTracker::paint(juce::Graphics& g)
{
    g.fillAll(currentColor); // Fill background

    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Mouse X: " + juce::String(mouseX) + " Y: " + juce::String(mouseY),
               getLocalBounds(), juce::Justification::centred);
}

// Handle window resizing
void CustomMouseTracker::resized() {}

// Track mouse movement
void CustomMouseTracker::mouseMove(const juce::MouseEvent& event)
{
    mouseX = event.x;
    mouseY = event.y;
    repaint();
}

// Change color when clicked
void CustomMouseTracker::mouseDown(const juce::MouseEvent& event)
{
    currentColor = juce::Colours::green;
    repaint();
}

// Update position while dragging
void CustomMouseTracker::mouseDrag(const juce::MouseEvent& event)
{
    mouseX = event.x;
    mouseY = event.y;
    repaint();
}

// Change color when hovering
void CustomMouseTracker::mouseEnter(const juce::MouseEvent&)
{
    currentColor = juce::Colours::red;
    repaint();
}

// Reset color when exiting
void CustomMouseTracker::mouseExit(const juce::MouseEvent&)
{
    currentColor = juce::Colours::black;
    repaint();
}
