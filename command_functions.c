#include "all_include.h"

int InitCommand(){
	CurrentCommand._numberOfAvailableSimpleCommands=MAX_NUMBER_OF_SIMPLE_COMMANDS;
    CurrentCommand._numberOfSimpleCommands=0;

    return 1;
}



int InsertSimpleCommand(struct SimpleCommand simpleCommand){

	//CurrentCommand._simpleCommands is the array of simpleCommands
	//CurrentCommand._numberOfSimpleCommands will give the index in that array

	if(CurrentCommand._numberOfSimpleCommands >= CurrentCommand._numberOfAvailableSimpleCommands ){
		printf("Max number of commands reached, insertSimpleCommand FAILED\n");
		return 0;
	}

	CurrentCommand._simpleCommands[CurrentCommand._numberOfSimpleCommands]=simpleCommand;

 	CurrentCommand._numberOfSimpleCommands++;
   
 	return 1;
}


void execute(){
    int ret; 
    for (int i = 0; i <CurrentCommand._numberOfSimpleCommands; i++ ){
        ret = fork();
        if (ret == 0) { 
            printf("forking child process executing %s\n",CurrentCommand._simpleCommands[i]._arguments[0]);
            //child 
            //printf("1st : %s\n",)
            execvp(CurrentCommand._simpleCommands[i]._arguments[0],CurrentCommand._simpleCommands[i]._arguments);
            perror("execvp");
            _exit(1);
        }
        else if(ret < 0){
            perror("fork");
            return;
        }
        // Parent shell continue
        
    }// for
    if (!CurrentCommand._background){
        // wait for last process
        waitpid(ret, NULL);
    } 
}

void DisplayCommand(){

	printf("COMMAND STRUCTURE\n");
	printf("    numberOfAvailableSimpleCommands : %d\n",CurrentCommand._numberOfAvailableSimpleCommands);
    printf("             numberOfSimpleCommands : %d\n",CurrentCommand._numberOfSimpleCommands);

    printf("                            \nSIMPLE COMMANDS\n");
    for(int i=0;i<CurrentCommand._numberOfSimpleCommands;i++){
    	printf("                     Simple command : %d\n",i);
    	struct SimpleCommand SC=CurrentCommand._simpleCommands[i];
    	printf("         numberOfAvailableArguments : %d\n",SC._numberOfAvailableArguments); 
        printf("                  numberOfArguments : %d\n",SC._numberOfArguments); 
        
        for(int j=0;j<SC._numberOfArguments;j++){
    	 	printf("                             Arg %d : %s\n",j,SC._arguments[j]);
    	}
        printf("                          ---------------\n");
    }
    
    printf("                            OutFile : %s\n",CurrentCommand._outFile);
    printf("                          inputFile : %s\n",CurrentCommand._inputFile);
    printf("                           errFile  : %s\n",CurrentCommand._errFile);
    printf("                         background : %d\n",CurrentCommand._background); 
}

