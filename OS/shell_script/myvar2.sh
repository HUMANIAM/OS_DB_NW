#!/bin/sh
echo "MYVAR is: $MYVAR"
MYVAR="hi there"
echo "MYVAR is: $MYVAR"

#Notes 
# when you call this program from the interactive shell a new shell is spawned to run the called program and that is because the 
# first line "#!/bin/sh". so some times you need to export created variables in your interactive shell to the spawned shell to be able to
# deal with them.
# EX : NEWVAR="hell my dog"; export NEWVAR
# you can understand it as if you declare the variable in the current interactive shell then pass it to the new created shell that run your #program. any change in the spawned shell script will not effect the original variables created in the interactive shell script.

# if you want to run the shell script in the interactive shell you can source it by (. ./shellName.sh)
