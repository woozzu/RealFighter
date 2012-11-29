#include "MotionRecognizer.h"
#include <fstream>
//#include <stdio.h>

// Max learning iterations used by HMM
#define MAX_ITERATION			20
// If acceleration is under threshold, discard it.
#define ACCELERATION_THRESHOLD	0.5
// If probability of recognition is under threshold, discard it.
#define PROBABILITY_THRESHOLD	0.1

#define SQRT2					1.414					
#define SQRT3					1.732
#define SQRT6					2.449

namespace ju6sigan
{
	// Codebook consists of a number of representitive vectors in 3D
	const float MotionRecognizer::m_codes[CODEBOOK_SIZE][3]
	                                                     = {{SQRT6, 0, 0},
	                                                    		 {-SQRT6, 0, 0},
	                                                    		 {0, SQRT6, 0},
	                                                    		 {0, -SQRT6, 0},
	                                                    		 {0, 0, SQRT6},
	                                                    		 {0, 0, -SQRT6},
	                                                    		 {SQRT2, SQRT2, SQRT2},
	                                                    		 {SQRT2, SQRT2, -SQRT2},
	                                                    		 {SQRT2, -SQRT2, SQRT2},
	                                                    		 {SQRT2, -SQRT2, -SQRT2},
	                                                    		 {-SQRT2, SQRT2, SQRT2},
	                                                    		 {-SQRT2, SQRT2, -SQRT2},
	                                                    		 {-SQRT2, -SQRT2, SQRT2},
	                                                    		 {-SQRT2, -SQRT2, -SQRT2},
	                                                    		 {SQRT3, 0, SQRT3},
	                                                    		 {-SQRT3, 0, SQRT3},
	                                                    		 {0, SQRT3, SQRT3},
	                                                    		 {0, -SQRT3, SQRT3},
	                                                    		 {SQRT3, 0, -SQRT3},
	                                                    		 {-SQRT3, 0, -SQRT3},
	                                                    		 {0, SQRT3, -SQRT3},
	                                                    		 {0, -SQRT3, -SQRT3},
	                                                    		 {SQRT3, SQRT3, 0},
	                                                    		 {-SQRT3, SQRT3, 0},
	                                                    		 {SQRT3, -SQRT3, 0},
	                                                    		 {-SQRT3, -SQRT3, 0}};
	
	MotionRecognizer::MotionRecognizer()
	{
		// A buffer which holds learning data is needed by all types of motion.
		m_sequences = new vector<vector<unsigned long>*>[MOTION_COUNT];
	}
	
	MotionRecognizer::~MotionRecognizer()
	{
		vector<vector<unsigned long>*>::iterator iter;
		for (int i = 0; i < MOTION_COUNT; i++) {
			for (iter = m_sequences[i].begin(); iter != m_sequences[i].end(); iter++)
				delete *iter;
			if (!m_hmm.empty())
				delete m_hmm[i];
		}
		delete[] m_sequences;
	}
	
	void MotionRecognizer::addLearningData(vector<kmVecPair> &data, Motion motion)
	{
		vector<unsigned long> *seq = new vector<unsigned long>();
		vector<kmVec3> norm;
		
		normalize(data, norm);
		quantize(norm, *seq);
		
		// Save it to buffer
		m_sequences[motion].push_back(seq);
	}
	
	void MotionRecognizer::learn()
	{
		// If HMM instances not exist, create them.
		// The HMM instance classify only one type of motion,
		// so every types of motion need one HMM instance.
		if (m_hmm.empty()) {
			for (int i = 0; i < MOTION_COUNT; i++)
				m_hmm.push_back(new Hmm(8, 2, CODEBOOK_SIZE));
		}
		
		// Make HMM learn by sensor data.
		for (int i = 0; i < MOTION_COUNT; i++) {
			if (m_sequences[i].size() > 0)
				m_hmm[i]->baumWelch(m_sequences[i], MAX_ITERATION);
		}
	}
	
	Motion MotionRecognizer::recognize(vector<kmVecPair> &data)
	{
		vector<unsigned long> seq;
		vector<kmVec3> norm;
		double prob;
		double maxProb = 0;
		int maxMotion = 0;
		
		normalize(data, norm);
		
		// If all datas were discarded or there were no datas.
		if (norm.size() == 0)
			return UnknownMotion;
		
		quantize(norm, seq);
		
		// For every HMMs, calculate probabilities.
		for (int i = 0; i < MOTION_COUNT; i++) {
			for (int j = 0; j < seq.size(); j++)
				m_hmm[i]->addObservation(seq[j]);
			prob = exp(m_hmm[i]->viterbi() - m_hmm[i]->obsProb());
			if (isnan(prob))
				prob = 0;
			
			/*char str[100];
			sprintf(str, "%f", prob);
			CCLog(str);*/
			
			// If there is a motion that has max probability,
			// that motion would be the motion recognized.
			if (prob > maxProb) {
				maxProb = prob;
				maxMotion = i;
			}
			
			m_hmm[i]->reset();
		}
		
		// If max probability is less than threshold,
		// we cannot be sure that this is actual motion recognized.
		if (maxProb < PROBABILITY_THRESHOLD)
			return UnknownMotion;
		
		return (Motion)maxMotion;
	}
	
	void MotionRecognizer::normalize(vector<kmVecPair>& data, vector<kmVec3>& norm)
	{
		kmQuaternion q1, q2, q3;
		kmVec3 n;
		vector<kmVecPair>::iterator iter;
		
		for (iter = data.begin(); iter != data.end(); iter++) {
			q1.x = ((kmVecPair)*iter).accel.x;
			q1.y = ((kmVecPair)*iter).accel.y;
			q1.z = ((kmVecPair)*iter).accel.z;
			q1.w = 0;
			
			if (q1.x * q1.x + q1.y * q1.y + q1.z * q1.z < ACCELERATION_THRESHOLD)
				continue;
			
			q2.x = ((kmVecPair)*iter).rot.x;
			q2.y = ((kmVecPair)*iter).rot.y;
			q2.z = ((kmVecPair)*iter).rot.z;
			q2.w = ((kmVecPair)*iter).rot.w;

			// For every acclerations, rotate them by rotation quaternion.
			// Then, axes of acclerations are adjusted to global earth axes.
			kmQuaternionMultiply(&q3, &q2, &q1);
			kmQuaternionConjugate(&q1, &q2);
			kmQuaternionMultiply(&q2, &q3, &q1);
			
			// Normalize vector's size equal to size of codebook vector (=SQRT6)
			kmQuaternionNormalize(&q1, &q2);
			n.x = q1.x * SQRT6;
			n.y = q1.y * SQRT6;
			n.z = q1.z * SQRT6;
			
			norm.push_back(n);
		}
	}
	
	void MotionRecognizer::quantize(vector<kmVec3>& norm, vector<unsigned long>& seq)
	{
		vector<kmVec3>::iterator iter;
		kmVec3 v;
		int i, minIdx;
		float value, minValue;
		
		for (iter = norm.begin(); iter != norm.end(); iter++) {
			minIdx = 0;
			minValue = 99999;
			
			// Classify vectors into the vectors in codebook by Euclidean distance.
			// And codebook vectors are codded to integer numbers.
			for (i = 0; i < CODEBOOK_SIZE; i++) {
				v.x = ((kmVec3)*iter).x - m_codes[i][0];
				v.y = ((kmVec3)*iter).y - m_codes[i][1];
				v.z = ((kmVec3)*iter).z - m_codes[i][2];
				
				value = kmVec3Length(&v);
				if (value < minValue) {
					minIdx = i;
					minValue = value;
				}
			}
			
			seq.push_back((unsigned long)minIdx);
		}
	}
	
	void MotionRecognizer::load()
	{
		if (!m_hmm.empty()) {
			for (int i = 0; i < MOTION_COUNT; i++)
				delete m_hmm[i];
			m_hmm.clear();
		}
		
		unsigned long transFileSize;
		unsigned long emitFileSize;
		char *transFileData;
		char *emitFileData;
		
		// Load transmission and transition data from files that HMM needs.
		for (int i = 0; i < MOTION_COUNT; i++) {
			ostringstream transPath;
			ostringstream emitPath;
			transPath << "motion/motion_t_" << i << ".dat";
			emitPath << "motion/motion_e_" << i << ".dat";
			
			transFileData = (char*)CCFileUtils::sharedFileUtils()->getFileData(
					transPath.str().c_str(), "r", &transFileSize);
			emitFileData = (char*)CCFileUtils::sharedFileUtils()->getFileData(
					emitPath.str().c_str(), "r", &emitFileSize);
			
			m_hmm.push_back(new Hmm());
			m_hmm[i]->loadProbs(transFileData, emitFileData
					, transFileSize, emitFileSize);
			
			if (transFileData != NULL)
				delete[] transFileData;
			if (emitFileData != NULL)
				delete[] emitFileData;
		}
	}
	
	void MotionRecognizer::save()
	{
		if (m_hmm.empty())
			return;
		
		for (int i = 0; i < MOTION_COUNT; i++) {
			ostringstream transPath;
			ostringstream emitPath;
			transPath << "/mnt/sdcard/motion/motion_t_" << i << ".dat";
			emitPath << "/mnt/sdcard/motion/motion_e_" << i << ".dat";
			m_hmm[i]->saveProbs(transPath.str(), emitPath.str());
		}
	}
}