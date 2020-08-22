#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
 more example changes for this file...
*/
class MainComponent  : public juce::Component,
                       public juce::ChangeListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    enum transportState {
        stopped,
        starting,
        playing,
        stopping
    };
    void changeState(transportState newState){
        if(state != newState){
            state = newState;
            switch(state){
                case stopped:
                    stopButton.setEnabled(false);
                    playButton.setEnabled(true);
                    transportSource.setPosition(0.0);
                    break;
                case starting:
                    playButton.setEnabled(false);
                    transportSource.start();
                    break;
                case playing:
                    stopButton.setEnabled(true);
                    break;
                case stopping:
                    transportSource.stop();
                    break;
            }
        }
    }
    void changeListenerCallback(juce::ChangeBroadcaster* source) override
    {
        if(source == &transportSource){
            if(transportSource.isPlaying()){
                changeState(playing);
            } else {
                changeState(stopped);
            }
        }
    }
    transportState state;
private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;
    
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
