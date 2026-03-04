#define _USE_MATH_DEFINES
#include <cmath>
#include "ThrashTheCacheComponent.h"
#include <imgui.h>
#include <imgui_plot.h>
#include <chrono>
#include <vector>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <algorithm>
#include <numeric>


dae::ThrashTheCacheComponent::ThrashTheCacheComponent(GameObject* owner)
	: Component(owner),
	m_SamplesExerciseOne{ 10 },
	m_SamplesExerciseTwo{ 100 }
{
	GetXValues();
}

void dae::ThrashTheCacheComponent::FixedUpdate(const float)
{
}

void dae::ThrashTheCacheComponent::Update(float)
{


}

void dae::ThrashTheCacheComponent::Render() const
{
	//ImGui::ShowDemoWindow();
	PlotExerciseOne();
	PlotExerciseTwo();


}

void dae::ThrashTheCacheComponent::GetXValues()
{
	int stepsize;
	for (stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		m_XValues.push_back(static_cast<float>(stepsize));
	}
}


void dae::ThrashTheCacheComponent::GenerateExerciseOneValues() const
{
	int stepsize;
	int* arr = new int[m_size] {};

	for (stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<float> samples;

		for (int sample = 0; sample < m_SamplesExerciseOne; sample++)
		{

			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < m_size; i += stepsize)
			{
				arr[i] *= 2;

			}
			auto end = std::chrono::high_resolution_clock::now();
			float totalElapsedSec = duration_cast<std::chrono::microseconds>(end - start).count() / 1000.f;
			samples.push_back(totalElapsedSec);
		}
		float averageTime = RemoveOutliersAndAveraging(samples);
		m_ExerciseOne.push_back(static_cast<float>(averageTime));
	}

	delete[] arr;
}

void dae::ThrashTheCacheComponent::PlotExerciseOne() const
{
	ImGui::Begin("Exercise 1");
	ImGui::InputInt("# samples", &m_SamplesExerciseOne, 1, 200);

	if (ImGui::Button("Thrash the Cache"))
	{
		m_ExerciseOne.clear();
		GenerateExerciseOneValues();
	}

	if (!m_ExerciseOne.empty())
	{
		ImGui::PlotConfig conf;
		conf.values.xs = m_XValues.data();
		conf.values.ys = m_ExerciseOne.data();
		conf.values.count = static_cast<int>(m_ExerciseOne.size());
		conf.values.color = ImColor(255, 255, 0);
		conf.scale.min = 0;
		conf.scale.max = *std::max_element(m_ExerciseOne.begin(), m_ExerciseOne.end());
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%g, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(220, 120);
		conf.line_thickness = 2.f;

		conf.tooltip.show = true;
		conf.grid_x.size = 128;
		conf.grid_x.subticks = 4;
		conf.grid_y.size = 0.5f;
		conf.grid_y.subticks = 5;

		ImGui::Plot("Exercise One", conf);

	}

	ImGui::End();
}

void dae::ThrashTheCacheComponent::GenerateExerciseTwo() const
{
	int stepsize;

	GameObject3D* arrGO = new GameObject3D[m_size]{};

	for (stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<float> samples;

		for (int sample = 0; sample < m_SamplesExerciseTwo; sample++)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < m_size; i += stepsize)
			{
				arrGO[i].id *= 2;

			}
			auto end = std::chrono::high_resolution_clock::now();
			float totalElapsedSec = duration_cast<std::chrono::microseconds>(end - start).count() / 1000.f;
			samples.push_back(totalElapsedSec);
		}
		float averageTime = RemoveOutliersAndAveraging(samples);
		m_ExerciseTwo.push_back(static_cast<float>(averageTime));
	}

	delete[] arrGO;

}

void dae::ThrashTheCacheComponent::GenerateExerciseTwoAlt() const
{
	int stepsize;

	GameObject3DAlt* arrGO = new GameObject3DAlt[m_size]{};

	for (stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<float> samples;

		for (int sample = 0; sample < m_SamplesExerciseTwo; sample++)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < m_size; i += stepsize)
			{
				arrGO[i].id *= 2;

			}
			auto end = std::chrono::high_resolution_clock::now();
			float totalElapsedSec = duration_cast<std::chrono::microseconds>(end - start).count() / 1000.f;
			samples.push_back(totalElapsedSec);
		}
		float averageTime = RemoveOutliersAndAveraging(samples);
		m_ExerciseTwoAlt.push_back(static_cast<float>(averageTime));
	}

	delete[] arrGO;
}


void dae::ThrashTheCacheComponent::PlotExerciseTwo() const
{
	ImGui::Begin("Exercise 2");
	ImGui::InputInt("# samples", &m_SamplesExerciseTwo, 1, 100);

	if (ImGui::Button("Thrash the Cache with GameObject3D"))
	{
		m_ExerciseTwo.clear();
		GenerateExerciseTwo();
	}

	if (!m_ExerciseTwo.empty())
	{
		ImGui::PlotConfig conf;
		conf.values.xs = m_XValues.data();
		conf.values.ys = m_ExerciseTwo.data();
		conf.values.count = static_cast<int>(m_ExerciseTwo.size());
		conf.values.color = ImColor(0, 255, 0);
		conf.scale.min = 0;
		conf.scale.max = *std::max_element(m_ExerciseTwo.begin(), m_ExerciseTwo.end());
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%g, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(220, 120);
		conf.line_thickness = 2.f;

		conf.tooltip.show = true;
		conf.grid_x.size = 128;
		conf.grid_x.subticks = 4;
		conf.grid_y.size = 0.5f;
		conf.grid_y.subticks = 5;

		ImGui::Plot("ExerciseTwo", conf);
	}


	if (ImGui::Button("Thrash the Cache with GameObject3DAlt"))
	{
		m_ExerciseTwoAlt.clear();
		GenerateExerciseTwoAlt();
	}

	if (!m_ExerciseTwoAlt.empty())
	{
		ImGui::PlotConfig conf;
		conf.values.xs = m_XValues.data();
		conf.values.ys = m_ExerciseTwoAlt.data();
		conf.values.count = static_cast<int>(m_ExerciseTwoAlt.size());
		conf.values.color = ImColor(47, 143, 255);
		conf.scale.min = 0;
		conf.scale.max = *std::max_element(m_ExerciseTwoAlt.begin(), m_ExerciseTwoAlt.end());
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%g, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(220, 120);
		conf.line_thickness = 2.f;

		conf.tooltip.show = true;
		conf.grid_x.size = 128;
		conf.grid_x.subticks = 4;
		conf.grid_y.size = 0.5f;
		conf.grid_y.subticks = 5;

		ImGui::Plot("ExerciseTwoAlt", conf);
	}


	ImGui::Text("Combined: ");

	if (!m_ExerciseTwo.empty() && !m_ExerciseTwoAlt.empty())
	{
		static const float* y_data[] = { m_ExerciseTwo.data(), m_ExerciseTwoAlt.data() };
		static ImU32 colors[2] = { ImColor(0, 255, 0), ImColor(47,143,255) };

		ImGui::PlotConfig conf;
		conf.values.xs = m_XValues.data();
		conf.values.ys_list = y_data;
		conf.values.count = static_cast<int>(m_ExerciseTwoAlt.size());
		conf.values.ys_count = 2;
		conf.values.colors = colors;
		conf.scale.min = 0;
		conf.scale.max = std::max(*std::max_element(m_ExerciseTwo.begin(), m_ExerciseTwo.end()), *std::max_element(m_ExerciseTwoAlt.begin(), m_ExerciseTwoAlt.end()));
		conf.line_thickness = 2.f;

		conf.tooltip.show = true;
		conf.grid_x.show = true;
		conf.grid_x.size = 128;
		conf.grid_x.subticks = 4;
		conf.grid_y.show = true;
		conf.grid_y.size = 0.5f;
		conf.grid_y.subticks = 5;

		conf.frame_size = ImVec2(220, 120);
		ImGui::Plot("ExerciseTwo Combined", conf);
	}


	ImGui::End();
}

float dae::ThrashTheCacheComponent::RemoveOutliersAndAveraging(std::vector<float> timeValues) const
{
	std::sort(timeValues.begin(), timeValues.end());
	timeValues.erase(timeValues.begin());
	timeValues.pop_back();

	float total{};
	for (auto value : timeValues)
	{
		total += value;
	}
	float averageTime = total / timeValues.size();
	return averageTime;
}