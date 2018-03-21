/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "Balance.h"

#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"


//==============================================================================
MainContentComponent::MainContentComponent() : mics(12),
											   volMeters(12),
											   micsMap(12)
{
    setSize (625, 440); //football FIFA court - 105x68 + 100px bounds

	mics[MicID::UPPER_LEFT_CORNER].setParameters(true, 3 * float_Pi / 4);
	mics[MicID::UPPER_LEFT_QUATER].setParameters(true, float_Pi);
	mics[MicID::UPPER_RIGHT_QUATER].setParameters(true, float_Pi);
	mics[MicID::UPPER_RIGHT_CORNER].setParameters(true, -3 * float_Pi / 4);
	mics[MicID::LEFT_GATE].setParameters(true, float_Pi / 2);
	mics[MicID::RIGHT_GATE].setParameters(true, -float_Pi / 2);
	mics[MicID::LOWER_LEFT_CORNER].setParameters(true, float_Pi / 4);
	mics[MicID::LOWER_LEFT_QUATER].setParameters(true, 0);
	mics[MicID::LOWER_RIGHT_QUATER].setParameters(true, 0);
	mics[MicID::LOWER_RIGHT_CORNER].setParameters(true, -float_Pi / 4);
	mics[MicID::UPPER_CENTRAL].setParameters(true, float_Pi);
	mics[MicID::LOWER_CENTRAL].setParameters(true, 0);

	addAndMakeVisible(court);

	for (auto i = 0; i != mics.size(); i++)
	{
		mics[i].setSize(MIC_WIDTH, MIC_HEIGHT);
		addAndMakeVisible(mics[i]);
		addAndMakeVisible(volMeters[i]);
	}

	this->scalePositions();

	auto height = mics[MicID::LOWER_RIGHT_CORNER].getY() - mics[MicID::UPPER_LEFT_CORNER].getY();
	auto width = mics[MicID::LOWER_RIGHT_CORNER].getX() - mics[MicID::UPPER_LEFT_CORNER].getX();
	auto topLeftX = mics[MicID::UPPER_LEFT_CORNER].getX();
	auto topLeftY = mics[MicID::UPPER_LEFT_CORNER].getY();
	auto rangeMax = jmax(width, height);

	for (int i = 0; i < mics.size(); i++)
		micsMap[i].setXY(jmap(static_cast<float>(mics[i].getX() - topLeftX), static_cast<float>(0), static_cast<float>(rangeMax),
																			 static_cast<float>(0), static_cast<float>(1)), 
						 jmap(static_cast<float>(mics[i].getY() - topLeftY), static_cast<float>(0), static_cast<float>(rangeMax),
						 													 static_cast<float>(0), static_cast<float>(1)));

	_micObserveAngle = mics[0].getObserveAngle();

	startTimerHz(30);
}

MainContentComponent::~MainContentComponent()
{

}

void MainContentComponent::timerCallback()
{
	auto point = court.getObjectCoords();
	auto params = Balancer::rebalance(micsMap, point.getX(), point.getY(), _micObserveAngle);

	// tbb::parallel_for(tbb::blocked_range<int>(0, mics.size() - 1),
	// [&](const tbb::blocked_range<int>& r)
	// {
	// 	for (auto i = r.begin(); i != r.end(); i++)
	// 	{
	// 		mics[i].rotate(params[i].first);
	// 		mics[i].setVolume(params[i].second);
	// 	}
	// });

	for (auto i = 0; i != mics.size(); i++)
	{
		mics[i].rotate(params[i].first);
		mics[i].setVolume(params[i].second);
	}

	repaint();
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	
	for (auto i = 0; i != mics.size(); i++)
	{
		volMeters[i].setVolume(mics[i].getVolume());

		switch(i)
		{
			//Left gate
			case MicID::LEFT_GATE:
				g.drawText("Angle: " + String(radiansToDegrees(mics[i].getCurrentAngle())),
						mics[i].getX() - 60, mics[i].getY() + mics[i].getHeight() + 1, TEXT_WIDTH, TEXT_HEIGHT,
						Justification::centredLeft, false);
				g.drawText("Vol: " + String(mics[i].getVolume()),
						mics[i].getX() - 60, mics[i].getY() + mics[i].getHeight() + 11, TEXT_WIDTH, TEXT_HEIGHT,
						Justification::centredLeft, false);
				break;
			//Right gate
			case MicID::RIGHT_GATE:
				g.drawText("Angle: " + String(radiansToDegrees(mics[i].getCurrentAngle())),
						mics[i].getX(), mics[i].getY() + mics[i].getHeight() + 1, TEXT_WIDTH, TEXT_HEIGHT,
						Justification::centredLeft, false);
				g.drawText("Vol: " + String(mics[i].getVolume()),
						mics[i].getX(), mics[i].getY() + mics[i].getHeight() + 11, TEXT_WIDTH, TEXT_HEIGHT,
						Justification::centredLeft, false);
				break;
			//Upper row
			case MicID::UPPER_LEFT_QUATER:
			case MicID::UPPER_CENTRAL:
			case MicID::UPPER_RIGHT_QUATER:
			case MicID::UPPER_LEFT_CORNER:
			case MicID::UPPER_RIGHT_CORNER:
				g.drawText("Angle: " + String(radiansToDegrees(mics[i].getCurrentAngle())),
						mics[i].getX(), mics[i].getY() - 22, TEXT_WIDTH, TEXT_HEIGHT,
						Justification::centredLeft, false);
				g.drawText("Vol: " + String(mics[i].getVolume()),
						mics[i].getX(), mics[i].getY() - 11, TEXT_WIDTH, TEXT_HEIGHT,
						Justification::centredLeft, false);
				break;
			//Lower row
			case MicID::LOWER_LEFT_QUATER:
			case MicID::LOWER_CENTRAL:
			case MicID::LOWER_RIGHT_QUATER:
			case MicID::LOWER_LEFT_CORNER:
			case MicID::LOWER_RIGHT_CORNER:
				g.drawText("Angle: " + String(radiansToDegrees(mics[i].getCurrentAngle())),
						mics[i].getX(), mics[i].getY() + mics[i].getHeight() + 1, TEXT_WIDTH, TEXT_HEIGHT,
						Justification::centredLeft, false);
				g.drawText("Vol: " + String(mics[i].getVolume()),
						mics[i].getX(), mics[i].getY() + mics[i].getHeight() + 11, TEXT_WIDTH, TEXT_HEIGHT,
						Justification::centredLeft, false);
				break;
			//Drugogo ne danow
			default:
				break;
		}
	}
}

void MainContentComponent::resized()
{
	this->scalePositions();
}

void MainContentComponent::scalePositions()
{
	auto lb = getLocalBounds();

	court.setBounds(lb.getWidth() / 10,
		lb.getHeight() / 6,
		lb.getWidth() * 4 / 5,
		court.getWidth() * 68 / 105);

	auto courtBounds = court.getBounds();

	mics[MicID::UPPER_LEFT_CORNER].setTopLeftPosition(
		courtBounds.getX() - MIC_WIDTH, courtBounds.getY() - MIC_HEIGHT);
	mics[MicID::UPPER_LEFT_QUATER].setTopLeftPosition(
	 	courtBounds.getX() + courtBounds.getWidth() / 4 - MIC_WIDTH / 2, courtBounds.getY() - MIC_HEIGHT);
	mics[MicID::UPPER_RIGHT_QUATER].setTopLeftPosition(
		courtBounds.getX() + 3 * courtBounds.getWidth() / 4 - MIC_WIDTH / 2, courtBounds.getY() - MIC_HEIGHT);
	mics[MicID::UPPER_RIGHT_CORNER].setTopLeftPosition(
		courtBounds.getX() + courtBounds.getWidth(), courtBounds.getY() - MIC_HEIGHT);

	mics[MicID::LEFT_GATE].setTopLeftPosition(
		courtBounds.getX() - MIC_WIDTH, courtBounds.getY() + courtBounds.getHeight() / 2 - MIC_HEIGHT / 2);
	mics[MicID::RIGHT_GATE].setTopLeftPosition(
		courtBounds.getX() + courtBounds.getWidth(), courtBounds.getY() + courtBounds.getHeight() / 2 - MIC_HEIGHT / 2);

	mics[MicID::LOWER_LEFT_CORNER].setTopLeftPosition(
		courtBounds.getX() - MIC_WIDTH, courtBounds.getY() + courtBounds.getHeight());
	mics[MicID::LOWER_LEFT_QUATER].setTopLeftPosition(
		courtBounds.getX() + courtBounds.getWidth() / 4 - MIC_WIDTH / 2, courtBounds.getY() + courtBounds.getHeight());
	mics[MicID::LOWER_RIGHT_QUATER].setTopLeftPosition(
		courtBounds.getX() + 3 * courtBounds.getWidth() / 4 - MIC_WIDTH / 2, courtBounds.getY() + courtBounds.getHeight());
	mics[MicID::LOWER_RIGHT_CORNER].setTopLeftPosition(
		courtBounds.getX() + courtBounds.getWidth(), courtBounds.getY() + courtBounds.getHeight());

	mics[MicID::UPPER_CENTRAL].setTopLeftPosition(
		courtBounds.getX() + courtBounds.getWidth() / 2 - MIC_WIDTH / 2, courtBounds.getY() - MIC_HEIGHT);
	mics[MicID::LOWER_CENTRAL].setTopLeftPosition(
		courtBounds.getX() + courtBounds.getWidth() / 2 - MIC_WIDTH / 2, courtBounds.getY() + courtBounds.getHeight());

	for (int i = 0; i < mics.size(); i++)
	{
		switch(i)
		{
			//Left meter
			case MicID::UPPER_LEFT_QUATER:
			case MicID::UPPER_CENTRAL:
			case MicID::UPPER_RIGHT_QUATER:
			case MicID::UPPER_LEFT_CORNER:
			case MicID::UPPER_RIGHT_CORNER:
			case MicID::LEFT_GATE:
				volMeters[i].setBounds(mics[i].getX() - 21, mics[i].getY(), METER_WIDTH, METER_HEIGHT);
				break;
			//Right meter
			case MicID::LOWER_LEFT_QUATER:
			case MicID::LOWER_CENTRAL:
			case MicID::LOWER_RIGHT_QUATER:
			case MicID::LOWER_LEFT_CORNER:
			case MicID::LOWER_RIGHT_CORNER:
			case MicID::RIGHT_GATE:
				volMeters[i].setBounds(mics[i].getX() + mics[i].getWidth() + 11, mics[i].getY(), METER_WIDTH, METER_HEIGHT);
				break;
			default:
				break;
		}
		mics[i].rotate();
	}
}
