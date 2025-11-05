#pragma once
#include <Windows.h>
#include "xorstr.hpp"
#include <vector>
#include <mutex>





namespace UI
{
	bool Watermark = true;
	bool show = true;
	bool dvd = false;
	int tab = 0;




	namespace particles {

		static bool toggle = false;
		static int maxParticles = 100;
		static float circleSize = 5.0f;
		static float connectionRadius = 250.0f;
		static float mouseRepelRadius = 150.0f;
		static float mouseRepelStrength = 1000.0f;
		static float particleSpeed = 100.0f;
		static bool rainbow = false;
		static ImVec4 particleColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		static ImVec4 lineColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	}
}

