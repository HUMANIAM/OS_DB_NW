1- command &  							#run the process in the background
2- ps 		  							#tracking the running processes (ps aux #all processes in the system) 
3- kill -9 PID							#kill a process
4- bg 	PID    							#running suspended process while keeping them in the background
5- fg   PID    							# running a stop process 
6- renice -n  -12  -p 1055     			# change priority of a running process (-20(highest) to 19(lowest))
7- nice -n nicevalue [command arg]      # run a process with a specific priority
