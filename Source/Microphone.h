/*
==============================================================================

			Microphone.h
			Created: 5 Nov 2017 3:26:14pm
			Author:  Anthony

==============================================================================
*/

#ifndef _MIC_COMPONENT_H
#define _MIC_COMPONENT_H

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
//
//	A class, which represents single microphone with it's functionality
//
//==============================================================================
class Microphone : public Component
{
public:
	Microphone(const float baseAngle, const bool rotatable) : _baseAngle(baseAngle),
															  _rotatable(rotatable)
	{
		micImage = ImageCache::getFromMemory(BinaryData::microphone_png, BinaryData::microphone_pngSize);
		_currentAngle = 0;
		_volume = 0;

		rotate(_currentAngle);
	}

	Microphone()
	{
		micImage = ImageCache::getFromMemory(BinaryData::microphone_png, BinaryData::microphone_pngSize);
		_currentAngle = 0;
		_volume = 0;
		_baseAngle = 0;
		_rotatable = true;

		rotate(_currentAngle);
	}

	~Microphone()
	{

	}

	void setRotatable(const bool rotatable) { _rotatable = rotatable; }
	void setBaseAngle(const float baseAngle) { _baseAngle = baseAngle; }
	void setVolume(const float vol) { _volume = vol; }
	void setParameters(const bool rotatable, const float baseAngle)
	{
		setRotatable(rotatable);
		setBaseAngle(baseAngle);

		rotate(_currentAngle);
	}

	float getVolume() const { return _volume; }
	float getBaseAngle() const { return _baseAngle; }
	float getCurrentAngle() const { return _currentAngle; }
	float getAngle() const { return _baseAngle + _currentAngle; }
	float getObserveAngle() const { return _rotatable ? 2 * float_Pi / 3 : float_Pi / 3; }

	void rotate(float angle)
	{
		auto lb = getLocalBounds();
		_currentAngle = angle < 0
							  ? jmax(-float_Pi / 6, angle)
							  : jmin(float_Pi / 6, angle);

		this->setTransform(AffineTransform::rotation(_currentAngle + _baseAngle,
													 getPosition().getX() + lb.getWidth() / 2,
													 getPosition().getY() + lb.getHeight() / 2));

	}

	void rotate()
	{
		rotate(_currentAngle);
	}

	void paint(Graphics& g) override
	{
		auto lb = getLocalBounds();
		g.drawImage(micImage, lb.toFloat(), RectanglePlacement::stretchToFit, true);
	}

	void resized() override {}
private:
	Image micImage;

	float _baseAngle;
	float _currentAngle;
	bool _rotatable;

	float _volume;//0..1

};

#endif
