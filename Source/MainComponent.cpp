#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
//    const auto enumerateCallback = [](const jucey::BonjourService& service,
//                                        bool isAvailable,
//                                        bool isMoreComing,
//                                        const juce::Result& result)
//    {
//        if (result.wasOk())
//        {
//            std::cout << (isAvailable ? "Added service:" : "Removed service:") << std::endl;
//            std::cout << service.getType() << std::endl;
//            std::cout << service.getName() << std::endl;
//            std::cout << service.getDomain() << std::endl;
//        }
//    };
//    
//    enumerateDomains.enumerateDomains(enumerateCallback);
//    
//
//    juce::DatagramSocket udpSocket;
//    udpSocket.bindToPort(0);
//    const auto onServiceRegistered = [](const jucey::BonjourService& service,
//                                        const juce::Result& result)
//    {
//        if (result.wasOk())
//        {
//            std::cout << "Registered service:" << std::endl;
//            std::cout << service.getType() << std::endl;
//            std::cout << service.getName() << std::endl;
//            std::cout << service.getDomain() << std::endl;
//        }
//    };
//
//    serviceToRegister.registerAsync (onServiceRegistered, udpSocket);
    
    addAndMakeVisible(restBrowsing);
    restBrowsing.onClick = [this]()
    {
        serviceToDiscover->stopService();
        serviceToDiscover.reset();
        juce::Timer::callAfterDelay(1000, [this]()
        {
            startBrowsing();
        });
    };
    setSize (600, 400);
    startBrowsing();
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    restBrowsing.centreWithSize(200, 80);
}

void MainComponent::startBrowsing()
{
    serviceToDiscover = std::make_unique<jucey::BonjourService>("_vepro._tcp.");
    
    const auto onServiceDiscovered = [](const jucey::BonjourService& service,
                                        bool isAvailable,
                                        bool isMoreComing,
                                        const juce::Result& result)
    {
        if (result.wasOk())
        {
            std::cout << (isAvailable ? "Added service:" : "Removed service:") << std::endl;
            std::cout << service.getType() << std::endl;
            std::cout << service.getName() << std::endl;
            std::cout << service.getDomain() << std::endl;
        }
    };

    serviceToDiscover->discoverAsync (onServiceDiscovered, 0);
}
