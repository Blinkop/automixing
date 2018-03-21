/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Court.h"
#include "Microphone.h"
#include "VolumeMeter.h"

#include <vector>


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

enum MicID
{
    UPPER_LEFT_CORNER  = 0,
    UPPER_LEFT_QUATER  = 1,
    UPPER_RIGHT_QUATER = 2,
    UPPER_RIGHT_CORNER = 3,
    LEFT_GATE          = 4,
    RIGHT_GATE         = 5,
    LOWER_LEFT_CORNER  = 6,
    LOWER_LEFT_QUATER  = 7,
    LOWER_RIGHT_QUATER = 8,
    LOWER_RIGHT_CORNER = 9,
    UPPER_CENTRAL      = 10,
    LOWER_CENTRAL      = 11
};

class MainContentComponent   : public Component, public Timer
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

	void scalePositions();

    void paint (Graphics&) override;
    void resized() override;

    void timerCallback() override;

private:
    enum
    {
        MIC_HEIGHT = 40,
        MIC_WIDTH = 25,
        METER_HEIGHT = MIC_HEIGHT,
        METER_WIDTH = 10,
        TEXT_WIDTH = 100,
        TEXT_HEIGHT = 10
    };

    float _micObserveAngle;

    std::vector<Microphone> mics;
    std::vector<Point<float>> micsMap;
    std::vector<VolumeMeter> volMeters;

	CourtComponent court;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
