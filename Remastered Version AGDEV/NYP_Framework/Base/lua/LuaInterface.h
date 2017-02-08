#pragma once

#include <SingletonTemplate.h>
#include "lua.hpp"
#include <string>
#include "Vector3.h"

class LuaInterface : public Singleton<LuaInterface>
{
    friend class Singleton<LuaInterface>;
public:
    bool Init();
    void Update(double dt);

    int getIntValue(char *zeKey);
    float getFloatValue(char *zeKey);
    const char *getStringValue(char *zeKey);
	char getCharValue(const char* key);
	Vector3 getVector3Value(const char* key);
	std::string getStringValue(const char* key);

    void saveIntValue(const char *varName, const int &zeValue);
    void saveFloatValue(const char *varName, const float &zeValue);

    float getField(char *zeKey);
    void putError(char *zeErrorCode);
	

    lua_State *theLuaState;
	lua_State *theLuaForMeshs;
    lua_State *theErrorState;

protected:
    LuaInterface() { theLuaState = nullptr;  }
    virtual ~LuaInterface() {
        if (theLuaState)
        {
            lua_close(theLuaState);
            theLuaState = nullptr;
        }
    }
};