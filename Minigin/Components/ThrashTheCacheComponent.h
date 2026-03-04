#pragma once
#include "Component.h"
#include <vector>

namespace dae
{

	struct Transform
	{
		float matrix[16] = {
		  1,0,0,0,
		  0,1,0,0,
		  0,0,1,0,
		  0,0,0,1
		};
	};

	class GameObject3D
	{
	public:
		Transform local;
		int id{ 1 };
	};

	class GameObject3DAlt
	{
	public:
		Transform* local;
		int id{ 1 };
	};

	class ThrashTheCacheComponent : public Component
	{
	public:
		ThrashTheCacheComponent(GameObject* owner);
		virtual ~ThrashTheCacheComponent() = default;

		// Inherited via Component
		void FixedUpdate(const float fixedTimeStep) override;
		void Update(float elapsedSec) override;
		void Render() const override;

		void GetXValues();


		void GenerateExerciseOneValues() const;
		void PlotExerciseOne() const;

		void GenerateExerciseTwo() const ;
		void GenerateExerciseTwoAlt() const;
		void PlotExerciseTwo() const;

		float RemoveOutliers();

	private:
		static constexpr int m_size = 10000000;
		mutable int m_SamplesExerciseOne;
		mutable int m_SamplesExerciseTwo;

		mutable std::vector<float> m_ExerciseOne;
		mutable std::vector<float> m_ExerciseTwo;
		mutable std::vector<float> m_ExerciseTwoAlt;
		mutable std::vector<float> m_XValues;

	};


}