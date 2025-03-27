:: Compile and inject gnw.c into the vanilla PlGw.dat file.
:: This will add a node called ftFunction to the dat file.
:: ftFunction contains the code we wrote and where mex should look for the move_table.
"MexTK/MexTK.exe" -ff -i gnw.c -s MexTK/ftFunction -dat PlGw.dat -ow 
pause
