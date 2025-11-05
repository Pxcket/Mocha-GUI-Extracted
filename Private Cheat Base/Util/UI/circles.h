#pragma once

#include <vector>
#include <cmath>
#include <random>
#include "../natives.h"
#include "../../imgui/imgui.h"

struct Particle {
    float x, y;           // Position
    float vx, vy;         // Velocity
    ImVec4 color;         // Particle color
};

class ParticleSystem {
private:
    std::vector<Particle> particles;
    std::random_device rd;
    std::mt19937 gen;
    int currentParticleCount;

public:
    ParticleSystem() : gen(rd()), currentParticleCount(0) {
        InitializeParticles();
    }

    ~ParticleSystem() {
        particles.clear();
        particles.shrink_to_fit();
    }

    void InitializeParticles() {
        // Clear existing particles
        particles.clear();
        particles.shrink_to_fit();

        // Reserve space for maximum particles to prevent reallocation
        particles.reserve(UI::particles::maxParticles);

        // Initialize particles
        for (int i = 0; i < UI::particles::maxParticles; i++) {
            std::uniform_real_distribution<> disX(0, ImGui::GetIO().DisplaySize.x);
            std::uniform_real_distribution<> disY(0, ImGui::GetIO().DisplaySize.y);
            std::uniform_real_distribution<> disV(-UI::particles::particleSpeed, UI::particles::particleSpeed);

            Particle p;
            p.x = disX(gen);
            p.y = disY(gen);
            p.vx = disV(gen);
            p.vy = disV(gen);
            p.color = UI::particles::particleColor;
            particles.push_back(p);
        }
        currentParticleCount = UI::particles::maxParticles;
    }

    void Update(float deltaTime) {
        // Check if particle count changed
        if (currentParticleCount != UI::particles::maxParticles) {
            InitializeParticles();
        }

        // Update particle colors if they changed
        static ImVec4 lastParticleColor = UI::particles::particleColor;
        if (memcmp(&lastParticleColor, &UI::particles::particleColor, sizeof(ImVec4)) != 0) {
            for (auto& p : particles) {
                p.color = UI::particles::particleColor;
            }
            lastParticleColor = UI::particles::particleColor;
        }

        ImVec2 mousePos = ImGui::GetMousePos();
        ImVec2 screenSize = ImGui::GetIO().DisplaySize;

        for (auto& p : particles) {
            // Update position with current velocity
            p.x += p.vx * deltaTime;
            p.y += p.vy * deltaTime;

            // Mouse repulsion
            float dx = p.x - mousePos.x;
            float dy = p.y - mousePos.y;
            float distSq = dx * dx + dy * dy;

            if (distSq < UI::particles::mouseRepelRadius * UI::particles::mouseRepelRadius) {
                float dist = std::sqrt(distSq);
                if (dist < 1.0f) dist = 1.0f; // Prevent division by zero

                // Calculate repulsion force with exponential falloff
                float repelFactor = std::exp(-dist / (UI::particles::mouseRepelRadius * 0.3f));
                float force = UI::particles::mouseRepelStrength * repelFactor;

                // Add to existing velocity
                float angle = std::atan2(dy, dx);
                p.vx += std::cos(angle) * force;
                p.vy += std::sin(angle) * force;
            }

            // Limit velocity to maximum speed
            float speedSq = p.vx * p.vx + p.vy * p.vy;
            float maxSpeed = UI::particles::particleSpeed * 3.0f; // Allow higher speeds during repulsion
            if (speedSq > maxSpeed * maxSpeed) {
                float speed = std::sqrt(speedSq);
                p.vx = (p.vx / speed) * maxSpeed;
                p.vy = (p.vy / speed) * maxSpeed;
            }

            // Screen wrapping
            if (p.x < 0) {
                p.x = screenSize.x;
            }
            else if (p.x > screenSize.x) {
                p.x = 0;
            }

            if (p.y < 0) {
                p.y = screenSize.y;
            }
            else if (p.y > screenSize.y) {
                p.y = 0;
            }
        }
    }

    void Render(ImDrawList* drawList) {
        ImVec2 screenSize = ImGui::GetIO().DisplaySize;
        float time = ImGui::GetTime(); // Get current time for animation
        const float rainbowSpeed = 0.2f; // Adjust this to control animation speed

        // Draw connections
        for (size_t i = 0; i < particles.size(); i++) {
            for (size_t j = i + 1; j < particles.size(); j++) {
                float dx = particles[i].x - particles[j].x;
                float dy = particles[i].y - particles[j].y;
                float distSq = dx * dx + dy * dy;

                if (distSq < UI::particles::connectionRadius * UI::particles::connectionRadius) {
                    float alpha = 1.0f - std::sqrt(distSq) / UI::particles::connectionRadius;

                    ImVec4 lineColor;
                    if (UI::particles::rainbow) {

                    }
                    else {
                        lineColor = ImVec4(UI::particles::lineColor.x,
                            UI::particles::lineColor.y,
                            UI::particles::lineColor.z,
                            alpha * UI::particles::lineColor.w);
                    }

                    drawList->AddLine(
                        ImVec2(particles[i].x, particles[i].y),
                        ImVec2(particles[j].x, particles[j].y),
                        ImGui::GetColorU32(lineColor)
                    );
                }
            }
        }

        // Draw particles
        for (const auto& p : particles) {
            ImVec4 particleColor;
            if (UI::particles::rainbow) {

            }
            else {
                particleColor = p.color;
            }

            drawList->AddCircleFilled(
                ImVec2(p.x, p.y),
                UI::particles::circleSize,
                ImGui::GetColorU32(particleColor)
            );
        }
    }
};

// Global particle system instance
static ParticleSystem* g_particleSystem = nullptr;

void RenderParticles() {

    if (UI::show && UI::particles::toggle) {

        // Initialize the particle system if it hasn't been created yet
        if (!g_particleSystem) {
            g_particleSystem = new ParticleSystem();
        }

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowSize(io.DisplaySize);
        ImGui::Begin("Circles Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing);

        // Get the current window's draw list
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // Update and render the particle system
        static float lastTime = ImGui::GetTime();
        float currentTime = ImGui::GetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        g_particleSystem->Update(deltaTime);
        g_particleSystem->Render(drawList);

        ImGui::End();
    }
}

// Add this function to clean up the particle system when shutting down
void CleanupParticles() {
    if (g_particleSystem) {
        delete g_particleSystem;
        g_particleSystem = nullptr;
    }
}