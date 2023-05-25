#include "redlexer_native.hpp"

namespace lexer::native {

class __declspec(dllexport) Context {
public:
    Context() {
        unk00 = 0;
        unk08 = 0;
    }
    Context& operator=(const Context& other) {
        unk00 = other.unk00;
        unk08 = other.unk08;
        return *this;
    }

    uint64_t unk00;
    uint32_t unk08;    
};

class __declspec(dllexport) IListener {
public:
    IListener(const IListener& a1) = default;
    IListener() = default;

    IListener& operator=(const IListener& other) {
        return *this;
    }

    virtual ~IListener() = default;
};

class __declspec(dllexport) State {
public:
    State(const State& a1) {

    }
    
    State(const char * a1) : unk00(a1) {

    }

    State& operator=(const State& other) {
        unk00 = other.unk00;
        unk08 = other.unk08;
        unk10 = other.unk10;
        unk18 = other.unk18;
        unk20 = other.unk20;
        unk28 = other.unk28;
        unk30 = other.unk30;
        unk38 = other.unk38;
        unk40 = other.unk40;
        return *this;
    }

    const char * unk00;
    uint64_t unk08;
    uint64_t unk10;
    uint64_t unk18;
    uint64_t unk20;
    uint64_t unk28;
    uint64_t unk30;
    uint64_t unk38;
    uint64_t unk40;

};

class __declspec(dllexport) Lexer {
public:
    Lexer& operator=(const Lexer& other) {
        return *this;
    }

    void Tokenize(const char * a1, IListener * a2) const;
};

} // namespace

using Tokenize_t = void (*)(const lexer::native::Lexer * self, const char * a1, lexer::native::IListener * a2);

namespace Functions {

Tokenize_t Tokenize;

}


void lexer::native::Lexer::Tokenize(const char * a1, lexer::native::IListener * a2) const {
    Functions::Tokenize(this, a1, a2);
}

bool redlexer::LoadOriginal() {
    constexpr auto dllName = "redlexer_native.dll";

    std::filesystem::path dll = "old";
    dll /= dllName;

    auto handle = LoadLibrary(dll.c_str());
    if (!handle)
    {
        return false;
    }

    Functions::Tokenize = reinterpret_cast<Tokenize_t>(GetProcAddress(handle, "?Tokenize@Lexer@native@lexer@@QEBAXPEBDPEAVIListener@23@@Z"));

    return true;
}