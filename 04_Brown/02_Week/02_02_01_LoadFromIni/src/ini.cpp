#include "ini.h"

namespace Ini {

    Section& Document::AddSection(string name) {
        static Section result;
        return result;
    }

    const Section& Document::GetSection(const string& name) const {
        static const Section result;
        return result;
    }

    size_t Document::SectionCount() const {
        return size_t();
    }

    Document Load(istream& input) {
        return Document();
    }
}