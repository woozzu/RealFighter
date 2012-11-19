#ifndef _JU6SIGAN_COMMON_H_
#define _JU6SIGAN_COMMON_H_

#include "cocos2d.h"
#include "kazmath/vec4.h"

using namespace std;
using namespace cocos2d;

namespace ju6sigan
{
	enum Motion
	{
		HorizontalMotion,
		VerticalMotion,
		DiagonalMotion,
		CircleMotion,
		MOTION_COUNT,
		UnknownMotion
	};
	
	typedef struct _kmVecPair
	{
		kmVec3 accel;
		kmVec4 rot;
	} kmVecPair;
}

#endif
