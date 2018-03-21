/*
  ==============================================================================

    Balance.h
    Created: 9 Mar 2018 7:19:37pm
    Author:  anthony

  ==============================================================================
*/

#ifndef _BALANCE_H_
#define _BALANCE_H_

#include "../JuceLibraryCode/JuceHeader.h"
#include "Microphone.h"
#include "MainComponent.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

#include <vector>
#include <memory>
#include <iostream>
class Balancer
{

enum
{
	ALPHA = 10
};

public:
	static float distanceToVol(float x, float delta)
	{
		if (x <= delta)
			return jmap(x, static_cast<float>(0), delta, 0.25f, 1.0f);
		else
			return jmin(1.0f, 1 / (std::exp(ALPHA * (x - delta))));
	}

	//x is 0..1 y is 0..1
	static std::vector<std::pair<float, float>> rebalance(
			std::vector<Point<float>>& mics,
			const float x,
			const float y,
			const float observeAngle)
	{
		std::vector<std::pair<float, float>> params(mics.size());
		constexpr float _delta = 1.0f / 3.0f;

		tbb::parallel_for(tbb::blocked_range<int>(0, mics.size()),
		[&](const tbb::blocked_range<int>& r)
		{
			for (auto i = r.begin(); i != r.end(); i++)
			{
				//setup vol and angle for all mics
				auto _centralX = mics[i].getX();
				auto _centralY = mics[i].getY();
				auto _alpha = std::asin
				(
					std::abs(_centralY - y) / std::sqrt(std::pow(_centralX - x, 2) + std::pow(_centralY - y, 2))
				);

				switch (i)
				{
					case MicID::UPPER_LEFT_QUATER:
					case MicID::UPPER_RIGHT_QUATER:
					case MicID::UPPER_CENTRAL:
						_alpha = float_Pi / 2 - _alpha;
						params[i].first = x > _centralX ? -_alpha : _alpha;
						break;
					case MicID::LOWER_LEFT_QUATER:
					case MicID::LOWER_RIGHT_QUATER:
					case MicID::LOWER_CENTRAL:
						_alpha = float_Pi / 2 - _alpha;
						params[i].first = x > _centralX ? _alpha : -_alpha;
						break;
					case MicID::LEFT_GATE:
						params[i].first = y > _centralY ? _alpha : -_alpha;
						break;
					case MicID::RIGHT_GATE:
						params[i].first = y > _centralY ? -_alpha : _alpha;
						break;
					case MicID::UPPER_LEFT_CORNER:
					case MicID::LOWER_RIGHT_CORNER:
						params[i].first = _alpha - float_Pi / 4;
						break;
					case MicID::UPPER_RIGHT_CORNER:
					case MicID::LOWER_LEFT_CORNER:
						params[i].first = float_Pi / 4 - _alpha;
						break;
				}

				if (std::abs(_alpha) <= observeAngle)
				{
					auto distance = std::sqrt(std::pow(_centralX - x, 2) + std::pow(_centralY - y, 2));
					params[i].second = distanceToVol(distance, _delta);
				}
				else
				{
					params[i].second = 0;
				}
			}
		});

		return params;
	}
};

#endif //_BALANCE_H_
