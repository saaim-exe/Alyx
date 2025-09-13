#include "Util.h"
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>

	namespace Util {

		std::string ReadTextFromFile(const std::string& path)
		{
			std::ifstream file(path);
			std::string str;
			std::string line;
			while (std::getline(file, line)) {
				str += line + "\n";
			}
			return str;
		}


	}

