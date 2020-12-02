#pragma once
namespace constants
{
	constexpr int k_screenWidth = 800;
	constexpr int k_screenHeight = 600;
	constexpr int k_tileWidth = 10;
	constexpr int k_tileHeight = 10;
	constexpr int k_mazeWidth = k_screenWidth / k_tileWidth;
	constexpr int k_mazeHeight = k_screenHeight / k_tileHeight;
}