#pragma once

namespace red {

struct ScriptDataLoader {
    virtual void sub_00();
    virtual void sub_08();
    virtual void sub_10();
    virtual void sub_18();
    virtual void * MapObject(uint32_t id);
    virtual void Read(void * data, uint64_t size);
};

}