function SaveToLuaFile(outputString, overwrite)
   print("SaveToLuaFile...")
   local f;						-- The file
   if overwrite == 1 then		-- Wipe the contents with new data
      f = assert(io.open("lua/DM2240_HighScore.lua", "w"))
   elseif overwrite == 0 then	-- Append with new data
      f = assert(io.open("lua/DM2240_HighScore.lua", "a"))
   end
   -- Write to the file
   f:write(outputString)
   -- Close the file
   f:close()
   print("OK")
end

function SaveToLuaFileForMusic(outputString, overwrite)
   print("SaveToLuaFile...")
   local f;						-- The file
   if overwrite == 1 then		-- Wipe the contents with new data
      f = assert(io.open("lua/options.lua", "w"))
   elseif overwrite == 0 then	-- Append with new data
      f = assert(io.open("lua/options.lua", "a"))
   end
   -- Write to the file
   f:write(outputString)
   -- Close the file
   f:close()
   print("OK")
end

function SaveSpecificValue(zeKey, zeValue)
	print("Save To Lua File")
	local fileHandle
	fileHandle = assert(io.open("lua/DM2240_HighScore","r"))
	local DataTable = {}
	for line in fileHandle:lines()	-- Iterating through the lines in the file
	do
	local IndexOfKey = string.find(line, " = ")	-- The key in this case will be "Key = Value"
	local KeyValue = string.sub(line,1,IndexOfKey[1])	-- Getting KeyValue
	local Value = string.sub(line,IndexOfKey[2])	-- Getting Value
	if (KeyValue == zeKey)then
		Value = zeValue
	end
	DataTable[KeyValue] = Value
	end
	-- After loading from file, then close the handle!
	fileHandle:close()
end

function SaveToLuaFileForCoord(outputString, overwrite)
   print("SaveToLuaFileForCoord...")
   local f;						-- The file
   if overwrite == 1 then		-- Wipe the contents with new data
      f = assert(io.open("lua/waypointpos.lua", "w"))
   elseif overwrite == 0 then	-- Append with new data
      f = assert(io.open("lua/waypointpos.lua", "a"))
   end
   -- Write to the file
   f:write(outputString)
   -- Close the file
   f:close()
   print("OK")
end
--if wan dont wan to scale the screen to moniter change the 0 value
title = "DM2240 - Week 14 Scripting"
width = 0
height = 0
--keyboard
moveForward = 87
moveBackward = 83
moveLeft = 65
moveRight = 68

moveUp = 38
moveDown = 40
moveLeft2 = 37
moveRight2 = 39

enterKey = 13

reload = 69
reset = 80

--player
fireRate = 0.2
ammo = 15
maxclip = 1

Waypoint_A_1 = { x = 10.0, y = 0.0, z = 50.0 }
test{1,0,3}

