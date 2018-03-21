/*
  ==============================================================================

    VolumeMeter.h
    Created: 14 Mar 2018 3:07:38am
    Author:  anthony

  ==============================================================================
*/

#ifndef _VOLUMEMETER_H_
#define _VOLUMEMETER_H_

#include "../JuceLibraryCode/JuceHeader.h"

class VolumeMeter : public Component
{
public:
	VolumeMeter(double minValue = 0.0f, double maxValue = 1.0f);
	~VolumeMeter();

	void setVolume(double value);

	void paint(Graphics& g) override;
	void resized() override;

private:
	Range<double> _range;
	double _currentValue;

	ColourGradient _colourGradient;
};

#endif //_VOLUMEMETER_H_
