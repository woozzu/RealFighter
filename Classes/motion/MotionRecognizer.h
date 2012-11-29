#ifndef _JU6SIGAN_MOTION_RECOGNIZER_H_
#define _JU6SIGAN_MOTION_RECOGNIZER_H_

#include "hmm/hmm.h"
#include "Common.h"

#define CODEBOOK_SIZE	26

namespace ju6sigan
{
	/**
	 * Using a HMM library, classify sensor data into several types of motion.
	 * Types of motion is defined in common header.
	 * HMM learning and saving data are inner purpose, so user does not use them.
	 */
	class MotionRecognizer
	{
	public:
		MotionRecognizer();
		~MotionRecognizer();
		
		/**
		 * For inner purpose
		 * 
		 * Add learning sensor data with expected motion type.
		 * Before call learn(), you should add enough sensor datas to be learned well.
		 * 
		 * @param data (in) Sensor data
		 * @param motion (in) Expected type of motion
		 */
		void addLearningData(vector<kmVecPair> &data, Motion motion);
		
		/**
		 * For inner purpose
		 * 
		 * HMM learns using added sensor datas.
		 * It may take several times.
		 */
		void learn();
		
		/**
		 * Recognize sensor data.
		 * This recognizer must be loaded or learned before calling it.
		 * 
		 * @param data (in) Sensor data
		 * @return A type of motion
		 */
		Motion recognize(vector<kmVecPair> &data);

		/**
		 * Load initializing data from files.
		 * The files should be named 'motion_e_N.dat', 'motion_t_N.dat' (N is integer >= 0),
		 * and be placed in application's resource directory.
		 */
		void load();
		
		/**
		 * For inner purpose
		 * 
		 * Save HMM's inner datas into files.
		 * The files are named 'motion_e_N.dat', 'motion_t_N.dat' (N is integer >= 0)
		 * 
		 * This method can run only android app.
		 */
		void save();
		
	private:
		/**
		 * Adjust axes of acceleration by quaternion and normalize acceleration vector size.
		 * 
		 * @param data (in) Sensor data
		 * @param norm (out) Normalized sensor data
		 */
		void normalize(vector<kmVecPair> &data, vector<kmVec3> &norm);
		
		/**
		 * Quantize normalized sensor data.
		 * That is, classify the data into several vectors in the codebook.
		 * 
		 * @param norm (in) Normalized sensor data
		 * @param seq (out) Quantized and coded data
		 */
		void quantize(vector<kmVec3>& norm, vector<unsigned long>& seq);
		
		vector<Hmm*> m_hmm;
		vector<vector<unsigned long>*> *m_sequences;
		static const float m_codes[CODEBOOK_SIZE][3];
	};
}

#endif