/* Command pattern
*
* [stream of commands] -> [parser]  -> [Invoker: launches commands] --> [Command: get parametes] --> [Receiver: executes action]
*
*/

//Each command will be represented by a structure. And its function will be defined by a pointer to a function

typedef  void(*functionPointerType)(void);

struct commandStruct {
	char const *name; 				//name of the command
	functionPointerType execute;	//function pointer to the command function
	char const *help; 				//help string
};

//command function prototypes
void CmdVersion(void);
void CmdOnBootTest(void);
void CmdBlinkLEDs(void);

/* the full list of commands will be defined with an array */
const struct commandList commands[] = {
	{"version", &CmdVersion, "display system version"},
	{"onBootTest", &CmdOnBootTest, "run on boot tests"},
	{"blinkLEDs", &CmdBlinkLEDs, "blink tests"},
	{"", null, ""} //end of the commands table. Must be the Last!
}; 

bool ExcuteCmd( char* Cmd)
{	
	bool result = 1; //return false
	for( unsigned int i =0, i < (sizeof(commandList[])/sizeof(comandStruct)), i++)
	{
		 if( strcmp( Cmd, ComandList[i].name) == 0) //if the command name is in the list.
		 {
			 ComandList[i].execute();
			 return result=0; //return true
		 }
	}
	return result;
}
