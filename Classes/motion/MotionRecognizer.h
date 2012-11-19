#ifndef _MOTION_RECOGNIZER_H_
#define _MOTION_RECOGNIZER_H_

#include "hmm/hmm.h"
#include "Common.h"

#define CODEBOOK_SIZE	26

namespace ju6sigan
{
	class MotionRecognizer
	{
	public:
		MotionRecognizer();
		~MotionRecognizer();
		
		void addLearningData(vector<kmVecPair> &data, Motion motion);
		void learn();
		Motion recognize(vector<kmVecPair> &data);

		void load();
		void save();
		
	private:
		void normalize(vector<kmVecPair> &data, vector<kmVec3> &norm);
		void quantize(vector<kmVec3>& norm, vector<unsigned long>& seq);
		
		vector<Hmm*> m_hmm;
		vector<vector<unsigned long>*> *m_sequences;
		static const float m_codes[CODEBOOK_SIZE][3];
	};
}

#endif