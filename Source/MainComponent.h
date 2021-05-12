#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void startBrowsing();
private:
    //==============================================================================
    // Your private member variables go here...
    jucey::BonjourService serviceToRegister {"_koss._udp", "My Service", "local"};
    std::unique_ptr<jucey::BonjourService> serviceToDiscover;
    jucey::BonjourService enumerateDomains;
    juce::TextButton restBrowsing{ "RESET" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
