#include "ini.h"

namespace Ini {

    Section& Document::AddSection(string name) {
        auto res = sections.insert(pair<string, Section>(name, Section()));
        return (*(res.first)).second;
    }

    const Section& Document::GetSection(const string& name) const {
        auto it = sections.find(name);
        const Section& result = it!= sections.end()? (*it).second: throw out_of_range("Wrong section name");
         return result;
    }

    size_t Document::SectionCount() const {
        return sections.size();
    }

    Document Load(istream& input) {
        Document result;
        Section* section = nullptr;
        for (string line; getline(input, line);) {
            if (!line.empty()) {
                if (line[0] == '[') {
                    string section_name = line.substr(1, line.size() - 2);
                    section = &result.AddSection(section_name);
                } else {
                    auto pos = line.find_first_of('=');
                    string l = line.substr(0, pos);
                    string r = line.substr(pos + 1, line.size() - (pos));
                    section->insert(pair<string, string>(move(l), move(r)));
                }
            }

        }
        return result;
    }
}