#include "LuaInterface.h"
#include <string>
#include <iostream>

bool LuaInterface::Init()
{
    // Create lua state
    theLuaState = lua_open();
	//theLuaForMeshs = lua_open();
    if (theLuaState)
    {
        // 2. Load lua auxiliary libraries
        luaL_openlibs(theLuaState);
        // 3. Load lua script
        luaL_dofile(theLuaState, "lua/DM2240.lua");

        theErrorState = lua_open();
        if (theErrorState)
        {
            luaL_openlibs(theLuaState);
            luaL_dofile(theErrorState, "lua/errorLookup.lua");
        }

        return true;
    }

    return false;
}

void LuaInterface::Update(double dt)
{
    if (theLuaState)
    {
        // 4. Read the variables
        lua_getglobal(theLuaState, "title");
        //std::string title(lua_tostring(theLuaState, -1));
        char *title = (char*)(lua_typename(theLuaState, -1));

        lua_getglobal(theLuaState, "width");
        int width = lua_tointeger(theLuaState, -1);

        lua_getglobal(theLuaState, "height");
        int height = lua_tointeger(theLuaState, -1);

        std::cout << title << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout << "Width of screen:" << width << std::endl;
        std::cout << "Height of screen:" << height << std::endl;
    }
}

int LuaInterface::getIntValue(char *zeKey)
{
    lua_getglobal(theLuaState, zeKey);
    return lua_tointeger(theLuaState, -1);
}

float LuaInterface::getFloatValue(char *zeKey)
{
    lua_getglobal(theLuaState, zeKey);
    return (float)lua_tonumber(theLuaState, -1);
}

const char *LuaInterface::getStringValue(char *zeKey)
{
    lua_getglobal(theLuaState, zeKey);
    return lua_tolstring(theLuaState, -1, NULL);
}

char LuaInterface::getCharValue(const char* key)
{
	lua_getglobal(theLuaState, key);

	size_t len;
	std::string str = lua_tostring(theLuaState, -1);


	return str.c_str()[0];
	
}

Vector3 LuaInterface::getVector3Value(const char* key)
{
	lua_getglobal(theLuaState, key);
	lua_rawgeti(theLuaState, -1, 1);
	int x = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	lua_rawgeti(theLuaState, -1, 2);
	int y = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	lua_rawgeti(theLuaState, -1, 3);
	int z = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);

	return Vector3(x, y, z);
}

std::string LuaInterface::getStringValue(const char* key)
{
	lua_getglobal(theLuaState, key);

	size_t len;
	std::string str = lua_tolstring(theLuaState, -1, &len);

	return str;
}

void LuaInterface::saveIntValue(const char *varName, const int &zeValue)
{
    lua_getglobal(theLuaState, "SaveToLuaFile");
    char outputString[80];
    sprintf_s(outputString, "%s %d\n", varName, zeValue);
    lua_pushstring(theLuaState, outputString);
    lua_pushinteger(theLuaState, 1);
    lua_call(theLuaState, 2, 0);
}

void LuaInterface::saveFloatValue(const char *varName, const float &zeValue)
{
    lua_getglobal(theLuaState, "SaveToLuaFile");
    char outputString[80];
    sprintf_s(outputString, "%s %6.4f\n", varName, zeValue);
    lua_pushstring(theLuaState, outputString);
    lua_pushinteger(theLuaState, 1);
    lua_call(theLuaState, 2, 0);
}

float LuaInterface::getField(char *zeKey)
{
    float result;

    // Check if the variable in the Lua stack belongs to a table
    if (!lua_istable(theLuaState, -1))
    {
        putError("error100");
        return 0;
    }

    lua_pushstring(theLuaState, zeKey);
    lua_gettable(theLuaState, -2);
    if (!lua_isnumber(theLuaState, -1))
    {
        putError("error101");
        return 0;
    }

    result = (float)lua_tonumber(theLuaState, -1);
    lua_pop(theLuaState, 1);
    return result;
}

void LuaInterface::putError(char *zeErrorCode)
{
    if (!zeErrorCode)
        return;

    lua_getglobal(theErrorState, zeErrorCode);
    const char *errorMsg = lua_tostring(theErrorState, -1);
    if (errorMsg)
        std::cout << errorMsg << std::endl;
    else
        std::cout << zeErrorCode << " is not valid!" << std::endl;
}