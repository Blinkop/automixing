/*
  ==============================================================================

    Court.h
    Created: 5 Nov 2017 1:46:11am
    Author:  Anthony

  ==============================================================================
*/

#ifndef _COURT_H
#define _COURT_H

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
	A court component, which represents FIFA bounded field with 105x68 basic bound
*/
class CourtComponent : public Component
{
public:
	CourtComponent() : _objectX(0), _objectY(0)
	{
		setLookAndFeel(&lookAndFeel);
		getLookAndFeel().setColour(ResizableWindow::backgroundColourId, juce::Colours::darkseagreen);
	}
	~CourtComponent()
	{
		setLookAndFeel(nullptr);
	}

	Point<float> getObjectCoords()
	{
		auto maxRange = jmax(getWidth(), getHeight());
		return Point<float>(jmap(static_cast<float>(_objectX), static_cast<float>(0), static_cast<float>(maxRange),
															   static_cast<float>(0), static_cast<float>(1)),
							jmap(static_cast<float>(_objectY), static_cast<float>(0), static_cast<float>(maxRange),
															   static_cast<float>(0), static_cast<float>(1)));
	}

	void paint(Graphics &g) override
	{
		g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
		g.setColour(juce::Colours::whitesmoke);
		g.drawRect(getLocalBounds(), 2.0f);
		g.fillEllipse(_objectX, _objectY, 5, 5);
	}

	void resized() override
	{

	}

	void mouseDown(const MouseEvent& event) override
	{
		_objectX = event.getMouseDownX();
		_objectY = event.getMouseDownY();
	}

private:
	LookAndFeel_V4 lookAndFeel;

	int _objectX;
	int _objectY;
};

#endif
