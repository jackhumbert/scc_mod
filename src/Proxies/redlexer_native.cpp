#include "redlexer_native.hpp"

namespace lexer::native {

class Context;
class Lexer;
class IListener;
class State;

lexer::native::Context& _Context_cstr(void);
lexer::native::IListener& _IListener_cstr(IListener const & a1);
lexer::native::IListener& _IListener_cstr2(void);
lexer::native::State& _State_cstr(State const & a1);
lexer::native::State& _State_cstr2(char const * a1);
void* _IListener_dstr(void);
Context& _Context_equals(Context const & a1);
IListener& _IListener_equals(IListener const & a1);
Lexer& _Lexer_equals(Lexer const & a1);
State& _State_equals(State const & a1);
void _Tokenize(char const * a1, IListener * a2);

}

using Context_cstr_t = decltype(&lexer::native::_Context_cstr);
using IListener_cstr_t = decltype(&lexer::native::_IListener_cstr);
using IListener_cstr2_t = decltype(&lexer::native::_IListener_cstr2);
using State_cstr_t = decltype(&lexer::native::_State_cstr);
using State_cstr2_t = decltype(&lexer::native::_State_cstr2);
using IListener_dstr_t = decltype(&lexer::native::_IListener_dstr);
using Context_equals_t = decltype(&lexer::native::_Context_equals);
using IListener_equals_t = decltype(&lexer::native::_IListener_equals);
using Lexer_equals_t = decltype(&lexer::native::_Lexer_equals);
using State_equals_t = decltype(&lexer::native::_State_equals);
using Tokenize_t = decltype(&lexer::native::_Tokenize);

namespace Functions {

Context_cstr_t Context_cstr;
IListener_cstr_t IListener_cstr;
IListener_cstr2_t IListener_cstr2;
State_cstr_t State_cstr;
State_cstr2_t State_cstr2;
IListener_dstr_t IListener_dstr;
Context_equals_t Context_equals;
IListener_equals_t IListener_equals;
Lexer_equals_t Lexer_equals;
State_equals_t State_equals;
Tokenize_t Tokenize;

}

namespace lexer::native {

class __declspec(dllexport) Context {
public:
    Context() {
        *this = Functions::Context_cstr();
    }
    Context& operator=(const Context& other) {
        return Functions::Context_equals(other);
    }
};

class __declspec(dllexport) IListener {
public:
    IListener(const IListener& a1) {
        *this = Functions::IListener_cstr(a1);
    }

    IListener() {
        *this = Functions::IListener_cstr2();
    }

    IListener& operator=(const IListener& other) {
        return Functions::IListener_equals(other);
    }

    virtual ~IListener() {
        Functions::IListener_dstr();
    }
};

class __declspec(dllexport) State {
public:
    State(const State& a1) {
        *this = Functions::State_cstr(a1);
    }

    State(const char * a1) {
        *this = Functions::State_cstr2(a1);
    }

    State& operator=(const State& other) {
        return Functions::State_equals(other);
    }
};

class __declspec(dllexport) Lexer {
public:
    Lexer& operator=(const Lexer& other) {
        return Functions::Lexer_equals(other);
    }

    void Tokenize(const char * a1, IListener * a2) {
        Functions::Tokenize(a1, a2);
    }
};

// lexer::native::Context& WINAPI _Context_cstr(void) {
//     return Functions::Context_cstr();
// }

// void* WINAPI _IListener_cstr(IListener const & a1) {
//     return Functions::IListener_cstr(a1);
// }

// void* WINAPI _IListener_cstr2(void) {
//     return Functions::IListener_cstr2();
// }

// void* WINAPI _State_cstr(State const & a1) {
//     return Functions::State_cstr(a1);
// }

// void* WINAPI _State_cstr2(char const * a1) {
//     return Functions::State_cstr2(a1);
// }

// void* WINAPI _IListener_dstr(void) {
//     return Functions::IListener_dstr();
// }

// Context& WINAPI _Context_equals(Context const & a1) {
//     return Functions::Context_equals(a1);
// }

// IListener& WINAPI _IListener_equals(IListener const & a1) {
//     return Functions::IListener_equals(a1);
// }

// Lexer& WINAPI _Lexer_equals(Lexer const & a1) {
//     return Functions::Lexer_equals(a1);
// }

// State& WINAPI _State_equals(State const & a1) {
//     return Functions::State_equals(a1);
// }

// void WINAPI _Tokenize(char const * a1, IListener * a2) {
//     return Functions::Tokenize(a1, a2);
// }
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

    Functions::Context_cstr = reinterpret_cast<Context_cstr_t>(GetProcAddress(handle, "??0Context@native@lexer@@QEAA@XZ"));
    Functions::IListener_cstr = reinterpret_cast<IListener_cstr_t>(GetProcAddress(handle, "??0Context@native@lexer@@QEAA@XZ"));
    Functions::IListener_cstr2 = reinterpret_cast<IListener_cstr2_t>(GetProcAddress(handle, "??0IListener@native@lexer@@QEAA@XZ"));
    Functions::State_cstr = reinterpret_cast<State_cstr_t>(GetProcAddress(handle, "??0State@native@lexer@@QEAA@AEBV012@@Z"));
    Functions::State_cstr2 = reinterpret_cast<State_cstr2_t>(GetProcAddress(handle, "??0State@native@lexer@@QEAA@PEBD@Z"));
    Functions::IListener_dstr = reinterpret_cast<IListener_dstr_t>(GetProcAddress(handle, "??1IListener@native@lexer@@UEAA@XZ"));
    Functions::Context_equals = reinterpret_cast<Context_equals_t>(GetProcAddress(handle, "??4Context@native@lexer@@QEAAAEAV012@AEBV012@@Z"));
    Functions::IListener_equals = reinterpret_cast<IListener_equals_t>(GetProcAddress(handle, "??4IListener@native@lexer@@QEAAAEAV012@AEBV012@@Z"));
    Functions::Lexer_equals = reinterpret_cast<Lexer_equals_t>(GetProcAddress(handle, "??4Lexer@native@lexer@@QEAAAEAV012@AEBV012@@Z"));
    Functions::State_equals = reinterpret_cast<State_equals_t>(GetProcAddress(handle, "??4State@native@lexer@@QEAAAEAV012@AEBV012@@Z"));
    Functions::Tokenize = reinterpret_cast<Tokenize_t>(GetProcAddress(handle, "?Tokenize@Lexer@native@lexer@@QEBAXPEBDPEAVIListener@23@@Z"));

    return true;
}