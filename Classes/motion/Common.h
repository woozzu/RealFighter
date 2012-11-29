#ifndef _JU6SIGAN_COMMON_H_
#define _JU6SIGAN_COMMON_H_

#include "cocos2d.h"
#include "kazmath/vec4.h"

using namespace std;
using namespace cocos2d;

namespace ju6sigan
{
	/*
	 * Motion Definition
	 * User can use this enumerations returned by MotionRecognizer
	 */
	enum Motion
	{
		HorizontalMotion,
		DiagonalMotion,
		CircleMotion,
		MOTION_COUNT,
		UnknownMotion
	};
	
	/*
	 * For inner implementation,
	 * bind an acceleration vector and a rotation quaterion as one structure.
	 */
	typedef struct _kmVecPair
	{
		kmVec3 accel;
		kmVec4 rot;
	} kmVecPair;
}

#endif
