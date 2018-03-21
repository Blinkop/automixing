/*
  ==============================================================================

    VolumeMeter.cpp
    Created: 14 Mar 2018 3:07:38am
    Author:  anthony

  ==============================================================================
*/

#include "VolumeMeter.h"

VolumeMeter::VolumeMeter(double minValue, double maxValue)
{
	_range.setStart(minValue);
	_range.setEnd(maxValue);

	_currentValue = _range.getStart();
}

VolumeMeter::~VolumeMeter()
{

}

void VolumeMeter::setVolume(double value)
{
	_currentValue = jmin(jmax(value, _range.getStart()), _range.getEnd());
}

void VolumeMeter::paint(Graphics& g)
{
	auto lb = getLocalBounds();

	g.drawRect(lb.toFloat(), 1.0f);
	g.setGradientFill(ColourGradient(Colours::green, 0, lb.getHeight(), Colours::red, 0, 0, true));
	int height = jmap(
			_currentValue, _range.getStart(),
			_range.getEnd(),
			static_cast<double>(0),
			static_cast<double>(lb.getHeight())
	);
	g.fillRect(0, lb.getHeight() - height, lb.getWidth(), height);
}

void VolumeMeter::resized()
{

}
