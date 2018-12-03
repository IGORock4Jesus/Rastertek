#include "ObjParser.h"
#include <fstream>
#include <string>
#include <vector>
#include <regex>



ObjParser::ObjParser()
{
}


ObjParser::~ObjParser()
{
}

std::vector<Vertex> ObjParser::Load(std::wstring filename)
{
	std::ifstream file{ filename };
	if (file.bad() || !file.good())
		return {};

	struct Face
	{
		struct Vertex
		{
			int v, t, n;
		};
		Vertex vs[3];
	};

	std::string str;
	std::vector<D3DXVECTOR3> vs;
	std::vector<D3DXVECTOR2> ts;
	std::vector<D3DXVECTOR3> ns;
	std::vector<Face> fs;

	std::regex vreg{ "v\\s+([-]?\\d+[.]\\d+)\\s+([-]?\\d+[.]\\d+)\\s+([-]?\\d+[.]\\d+)" };
	std::regex nreg{ "vn\\s+([-]?\\d+[.]\\d+)\\s+([-]?\\d+[.]\\d+)\\s+([-]?\\d+[.]\\d+)" };
	//std::regex treg{ "vt\\s+([-]?\\d+[.]\\d+)\\s+([-]?\\d+[.]\\d+)\\s+([-]?\\d+[.]\\d+)" };
	std::regex treg{ "vt\\s+([-]?\\d+[.]\\d+)\\s+([-]?\\d+[.]\\d+)" };
	std::regex freg{ "f\\s+(\\d+)/(\\d+)/(\\d+)\\s+(\\d+)/(\\d+)/(\\d+)\\s+(\\d+)/(\\d+)/(\\d+)" };

	std::smatch m;

	while (getline(file, str))
	{
		if (str.length() == 0) continue;
		else if (std::regex_search(str, m, vreg)) {
			vs.push_back({ std::stof(m[1]), std::stof(m[2]), std::stof(m[3]) });
		}
		else if (std::regex_search(str, m, nreg)) {
			ns.push_back({ std::stof(m[1]), std::stof(m[2]), std::stof(m[3]) });
		}
		else if (std::regex_search(str, m, treg)) {
			ts.push_back({ std::stof(m[1]), std::stof(m[2]) });
		}
		else if (std::regex_search(str, m, freg)) {
			fs.push_back({ {{std::stoi(m[1])-1, std::stoi(m[2])-1, std::stoi(m[3])-1},
							{std::stoi(m[4])-1, std::stoi(m[5])-1, std::stoi(m[6])-1},
							{std::stoi(m[7])-1, std::stoi(m[8])-1, std::stoi(m[9])-1}
						 } });
		}
	}

	size_t size = fs.size();
	std::vector<Vertex> o{ size*3 };

	for (size_t f = 0; f < size; f++)
	{
		o[f * 3].position = vs[fs[f].vs[0].v];
		o[f * 3 + 1].position = vs[fs[f].vs[1].v];
		o[f * 3 + 2].position = vs[fs[f].vs[2].v];

		o[f * 3].texel = ts[fs[f].vs[0].t];
		o[f * 3 + 1].texel = ts[fs[f].vs[1].t];
		o[f * 3 + 2].texel = ts[fs[f].vs[2].t];

		o[f * 3].normal = ns[fs[f].vs[0].n];
		o[f * 3 + 1].normal = ns[fs[f].vs[1].n];
		o[f * 3 + 2].normal = ns[fs[f].vs[2].n];
	}

	return std::move(o);
}
