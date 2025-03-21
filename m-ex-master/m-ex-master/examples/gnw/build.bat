SET "TKPATH=../../MexTK/"

:: compile main code, found in the src folder. 
"%TKPATH%MexTK.exe" -ff -i "src/gnw.c" -s ftFunction -dat "../../../../files/PlGw.dat" -ow 

pause