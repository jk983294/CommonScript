# The executable's code is redirected to the selected Valgrind tool, and the tool adds its own code to handle its debugging. 
# Then the code is handed back to the Valgrind core and the execution continues
valgrind --tool=memcheck find ~ -name .bashrc
valgrind -v --tool=memcheck --trace-children=yes --log-file=valgrind_pid_%p.log rcapache2 restart