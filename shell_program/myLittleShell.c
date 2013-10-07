/**
* Little shell program 
* @author Luis Palacios
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <readline/readline.h>

extern char **environ;

/**
* Parses the command and executes using binaries found with either absolute or relative paths 
*/
void parseAndExecute(char *part) {

	char *args[100]; 
	char **argp = args;
	//Parse the passed char* by tabs until you reach the null terminator/strsep finds
	//no matching tokens and sets part to null.	
	do {			
		*argp = strsep(&part, " \t");	//Fill an entry in argp with a token.	 
		if(**argp != '\0')
			argp++;
	} while(part != NULL);
	
	*argp = 0;
	
	if(strchr(args[0],'/'))
		execve(args[0], args, environ);
	else {
		//Search through the path variable for the corresponding program to execute 
		//requested command.
		char *paths = getenv("PATH");
		while(paths) {
			char *path = strsep(&paths, ":");		
			char buf[255];
			//path/args[0]
			sprintf(buf,"%s/%s", path, args[0]);
			
			struct stat s;
			if(stat(buf,&s) == 0) {
				execve(buf,args,environ);	
				return;
			}
		}
	}
}
/**
* Parses the the passed char* and sets stdin and stdout argppropriately
*/
void redirection(char *part) {
	char buf[255];
	memset(buf, 0, 255);
	memcpy(buf, part, strcspn(part, "<>"));

	char *out = strchr(part, '>');
	if(out > 0) {

		out += 1;
		while(*out ==' ') out++;
		char outfile[255];
		int outlen = strcspn(out," <>|&;");
		strncpy(outfile, out, outlen);
		outfile[outlen] = 0;
		int outfd = open(outfile,O_RDWR|O_CREAT);
		chmod(outfile, 00777);
		if(outfd < 0) perror("Unable open file");
		dup2(outfd,1);
	}

	char *in = strchr(part,'<');
	if(in>0) {
		in+=1;
		while(*in == ' ') in++;
		char infile[255];
		int inlen = strcspn(in," <>|&;");
		strncpy(infile, in, inlen);
		infile[inlen] = 0;
		int infd=open(infile, O_RDONLY);
		dup2(infd, 0);
	}
	
	parseAndExecute(buf);	
}

/**
* This method takes a command to be executed and if needed will create a pipe
* and fork processes which will deal with every segment of the command.  The parent process
* executes the commands and the child process recursively deals with piped commands from parent process.
*/
void pipeline(char *command) {
	char *commandptr = command;
	//Check for |, if none commandptr will be point to NULL	
	char *part = strsep(&commandptr,"|");				

	// start the command with the char part taken from commandptr
	if(!commandptr) {
		redirection(part);
		return;
	}

	//Create a new pipe
	int newpipe[2];
	pipe(newpipe);
	
		
	int pid=fork();
	//Child takes the read side of pipe as input and closes the write side
	if(!pid) {
		dup2(newpipe[0], 0); 
		close(newpipe[1]); 
		
		pipeline(commandptr);
	}	
	//parent writes to stdout and closes the read side of the pipe
	else { 
		dup2(newpipe[1], 1);
		close(newpipe[0]); 

		redirection(part);
	}
}

/**
* Returns a char* of a string representation of the current working directory and outputs it onto console.
*/ 
char *cmdprompt() {
	static char cmdprompt[102];
	char pwd[100];
	getcwd(pwd,100);
	sprintf(cmdprompt,"%s/>>> ",pwd);
	return cmdprompt;
}

/**
* Deal with basic commands 'exit' and 'cd'
*/
int basicCommands(char *line) {
	if(strcmp("exit",line) == 0) {
		exit(0);
		return 1;
	}
	else if(strncmp("cd ",line,3) == 0) {
		chdir(line + 3);
		return 1;
	}
	return 0;
}

/**
* 
* This shell program was written to support a script using the readline developer files
*/
int main(int argc, char ** argv) {
	
	if(argc > 1) {
		int script = open(argv[1],O_RDONLY);
		dup2(script,0); 
	}
	
	while(1) {
		char *line = readline(cmdprompt());
		char buf[1000];
		if(line && *line) 
			add_history(line); //store in history for future use

		if(!line) {
			return 0;
		}
		if(line[0] == '#') continue;

		char *src = line;
		char *out = buf;
		while(*src && strchr(src,'$') > 0) {
			int offset = strchr(src,'$') - src;
			strncpy(out,src,offset);
			src += offset;
			out += offset;			
			//Replace any $1,$2,$X with argv[2],argv[3] ....			
			char *arg = argv[*(src + 1) - 48 + 1];
			strcpy(out,arg);
			src += 2;
			out += strlen(arg);
		}
		strcpy(out,src);

		if(!basicCommands(buf) && strlen(buf) > 0) {
			int status_loc;						
			int pid = fork();
			if(!pid) {
				pipeline(buf);
			}
			else {
				waitpid(pid, &status_loc, 0);
			}
		}
		//free the allocated memory from using readline.
		free(line);
	}	
}
