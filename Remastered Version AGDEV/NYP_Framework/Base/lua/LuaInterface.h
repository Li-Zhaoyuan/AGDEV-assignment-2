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

	void saveIntValue(const char *varName, const int &zeValue, bool toFresh = false);
	void saveFloatValue(const char *varName, const float &zeValue, bool toFresh = false);

	void saveCoordToFile(lua_State *l, const char *varName, float x, float y, float z, bool toFresh = false);

	void saveMusicSettings(const char *varName, int value, bool toFresh = false);
	int getMusicVolume(const char* key);

    float getField(char *zeKey);
	float getField(lua_State *l, char *zeKey);
    void putError(char *zeErrorCode);
	

    lua_State *theLuaState;
	lua_State *theLuaForMeshs;
    lua_State *theErrorState;
	lua_State *theWayPointState;
	lua_State *theMusicOptionsState;
protected:
    LuaInterface() { theLuaState = nullptr;  }
    virtual ~LuaInterface() {
        if (theLuaState)
        {
            lua_close(theLuaState);
            theLuaState = nullptr;
        }
		/*if (theLuaForMeshs)
		{
			lua_close(theLuaForMeshs);
			theLuaForMeshs = nullptr;
		}*/
		if (theErrorState)
		{
			lua_close(theErrorState);
			theErrorState = nullptr;
		}
		if (theMusicOptionsState)
		{
			lua_close(theMusicOptionsState);
			theMusicOptionsState = nullptr;
		}
		/*if (theWayPointState)
		{
			lua_close(theWayPointState);
			theWayPointState = nullptr;
		}*/
    }
};