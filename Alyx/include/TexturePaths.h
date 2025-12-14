#pragma once
#include <string>

namespace TexturePaths {
	
	// objects 

	const std::string metalbox = "metalbox_full.png";
	const std::string metalbox_diffuse = "metalbox_full_diffuse.png";
	const std::string metalbox_specular = "metalbox_full_specular.png"; 

	// skybox 

	const std::vector<std::string> cubeMapFaces_Dusk{
		"vz_dusk_right.png",
		"vz_dusk_left.png",
		"vz_dusk_up.png",
		"vz_dusk_down.png",
		"vz_dusk_front.png",
		"vz_dusk_back.png"
	};

	const std::vector<std::string> cubeMapFaces_ClearOcean{
		"vz_clear_ocean_right.png",
		"vz_clear_ocean_left.png",
		"vz_clear_ocean_up.png",
		"vz_clear_ocean_down.png",
		"vz_clear_ocean_front.png",
		"vz_clear_ocean_back.png",
	}; 

}