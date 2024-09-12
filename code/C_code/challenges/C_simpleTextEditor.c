
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define DB false

extern char* strndup(const char*, unsigned long); // strndup is not a standard c function, but a posix exteinsion
// to avoid the error "implicit declarartion of function X", this declaration has to be made.

/*
Implement a simple text editor. The editor initially contains an empty string, . Perform  operations of the following  types:

append - Append string  to the end of .
delete - Delete the last  characters of .
print - Print the  character of .
undo - Undo the last (not previously undone) operation of type 1 or 2, reverting  to the state it was in prior to that operation.

Example input:
STDIN   Function
-----   --------
8       Q = 8
1 abc   ops[0] = '1 abc'
3 3     ops[1] = '3 3'
2 3     ...
1 xy
3 2
4 
4 
3 1


Expected output:
c
y
a
*/

typedef struct document document; // fordward declaration

enum commandCode {APPEND=1, DELETE, PRINT, UNDO};
// check: https://stackoverflow.com/questions/9907160/how-to-convert-enum-names-to-string-in-c

typedef struct command {
    enum commandCode code;
    int val;
    char* string;
    void (*fc_ptr)(document* doc, int val, char* string);
} command;

void ClearCmd(command* cmd)
{
    cmd->code = 0;
    cmd->val  = 0;
    cmd->string = NULL;
    cmd->fc_ptr = NULL;
}

void deleteCmd(command* cmd)
{
    cmd->code = 0;
    cmd->val = 0;
    if (cmd->string != NULL)
    {
        //free(cmd->string);
        cmd->string = NULL;
    }
    cmd->fc_ptr = NULL; 
}

void printCmd(command* cmd)
{
    printf("code: %d, val: %d, string: %s\n", cmd->code, cmd->val, cmd->string);
}

void printListCmd(command* cmd, int num_cmd)
{
    if (DB) printf("List commands: \n");  
    for (int i = 0; i < num_cmd; i++) { printf("cmd[%2d]: ", i); printCmd(cmd+i); }
    if (DB) printf("\n");
}

typedef struct document{
    char* text;
    command* commands;
    int num_commands;
    int max_num_commands;
} document;

void addCmd(document* doc, command* cmd)
{
    if (doc && doc->num_commands < doc->max_num_commands && cmd)
    {
        doc->num_commands++; // go next command in the list
        doc->commands[doc->num_commands-1].code   = cmd->code;
        doc->commands[doc->num_commands-1].val    = cmd->val;
        doc->commands[doc->num_commands-1].string = cmd->string;
        doc->commands[doc->num_commands-1].fc_ptr = cmd->fc_ptr;   
    }
    if (DB) { printf("Added commmand: "); printCmd(&doc->commands[doc->num_commands-1]); }
}

void executeCmd(document* doc, command* cmd)
{
    if (doc && cmd && cmd->fc_ptr)
    {
       if (DB) { printf("execute command:\n"); printCmd(cmd); } 
       cmd->fc_ptr(doc, cmd->val, cmd->string);     
    }
    else {
        fprintf(stderr, "ERROR incorrect parameters for executeCmd\n");
    }
}

void append(document* doc, int val, char* string)
{
   if (DB) printf("called append: %s\n", string);
   if (doc && doc->text && string) 
   {
        // save the position in which it is append, to undo it later if needed.
        doc->commands[doc->num_commands-1].val = strlen(string);
        
        // append
        if (doc->text != strcat(doc->text, string)) // concatenate the string
        {
            fprintf(stderr, "\nERROR in appending %s\n", string);
        }
   }

   if (DB) printf("after append: %s\n", doc->text);
}

void delete(document* doc, int val, char* string)
{
    if (DB) printf("called delete: %d\n", val);
    if (doc && doc->text && val > 0 ) 
    {
            //save into this command, the string to be deleted - so it can be undone later.
            doc->commands[doc->num_commands-1].string = strndup(&doc->text[strlen(doc->text)-val], (unsigned long)(val+1));
            
            //delete the memory
            memset(&doc->text[strlen(doc->text)-val], 0x00, val*sizeof(char));
    }
    else {
        if (DB) fprintf(stderr, "ERROR in delete val: %d\n,", val);
    }
}

/*
void undodelete(document* doc, int val, char* string)
{
    if (DB) printf("called undo delete: %d\n", val);
    if (doc && doc->text && val > 0 && string) 
    {
            //save into this command, the string to be deleted - so it can be undone later.
            doc->commands[doc->num_commands-1].string = strndup(&doc->text[strlen(doc->text)-val], (unsigned long)(val+1));
            // append the previous saved 
            //delete the memory
            memset(&doc->text[strlen(doc->text)-val], 0x00, val*sizeof(char));
    }
    else {
        if (DB) fprintf(stderr, "ERROR in delete val: %d\n,", val);
    }
} */

void print(document* doc, int val, char* string)
{
    if (DB) printf("called print: %d - strlen(doc->text): %lu\n", val, strlen(doc->text));
    if (doc && doc->text && val > 0 && (val < (strlen(doc->text)+1)))  
    {
        printf("%c\n", doc->text[val-1]);
    }
    else {
        if (DB) fprintf(stderr, "ERROR in print %d\n", val);
    } 
}

void undo(document* doc, int val, char* string)
{
    if (DB) printf("called undo\n");
    if (doc && doc->commands)
    {
        //undo the last command of type append or delete
        
        command* lastOperation = NULL;
        int initial_num_commands = doc->num_commands; 
        
        // loop backwards to find the last append o delete operation
        int index = initial_num_commands -1;
        for (; index >= 0; index--) {
            if  (doc->commands[index].code == APPEND
                || doc->commands[index].code == DELETE) {
                    break;
            }
        }
        
        lastOperation = &doc->commands[index];
              
        // undo the operation   
        switch (lastOperation->code)
        {
            case (APPEND): //append, --to undo, then delete
            {
                if (DB) printf("undo last append operation : append of: %s\n", lastOperation->string);
                delete(doc, lastOperation->val, NULL); 
            }
            break;
            case (DELETE): //delete, --to undo, then append
            {
                if (DB) printf("undo last delete operation\n");
                append(doc, 0, lastOperation->string);
            }
            break;
            default:
            {
                if (DB) fprintf(stderr, "ERROR wrong undo call: code: %d\n", lastOperation->code);
            }
            break;
        }
        
        // clean the hsitory of commands
        for (int i = initial_num_commands -1; i >= index; i--) {
             deleteCmd(&doc->commands[i]);
             doc->num_commands--;
        }
        
        if (DB) printf("Undo: update commmand list: \n");
        if (DB) printListCmd(doc->commands, doc->num_commands);
        
    }
    
}

void parseCommand(command* cmd) 
{
    int q = -1;
    int q2 = -1;
    scanf("%d", &q);
    //int val = 0;
    char appendstr[500];
    
    ClearCmd(cmd); // just in case.
    
    switch (q)
    {
        case APPEND:
        {
            cmd->code = APPEND;
            scanf("%s", appendstr);
            cmd->string = strndup(appendstr, strlen(appendstr)+1);  // free later, please. In the commands destructor.
            cmd->val = 0;
            cmd->fc_ptr = &append;
            if (DB) printf("append : %s\n", appendstr);
        }
        break;
        case DELETE:
        {
            cmd->code = DELETE;  
            scanf("%d", &q2);
            cmd->val = q2;   
            cmd->string  = NULL;
            cmd->fc_ptr = &delete;  
            if (DB) printf("delete : %d\n", q2);     
        }
        break;
        case PRINT:
        {
            cmd->code = PRINT;   
            scanf("%d", &q2);
            cmd->val = q2; 
            cmd->string  = NULL;
            cmd->fc_ptr = &print; 
            if (DB) printf("print :%d\n", q2);         
        }
        break;
        case UNDO:
        {
            cmd->code = UNDO;     
            cmd->val = 0;
            cmd->string  = NULL;  
            cmd->fc_ptr = &undo; 
            if (DB) printf("undo\n");   
        }
        break;
        defaul:
            if (DB) printf("ERROR: parseCommand unknown option: %d\n", q);
        break;
    }    
};


int main() {

    //#ifdef __STDC_VERSION__
    //printf("C version: %li\n", __STDC_VERSION__);
    //#endif
    
    /* TODO: */    
    
    // get number of operations
    int q = 0;  //num_operations 
    scanf("%d", &q);
    if (DB) printf("Number of commands: %d\n", q);
    
    char docString[1000000]; // is this enough memory? dynamic??
    
    command commands[q];
    document doc = {docString, commands, 0, q};

    if (DB) printf("\n ----------------------------\n");
    for (int i = 0; i < q; i++) // loop through all the commands.   
    {
        command cmd;
        parseCommand(&cmd);
        addCmd(&doc, &cmd);
        if (DB) printListCmd(doc.commands, doc.num_commands);
        executeCmd(&doc, &cmd);
        if (DB) printf("\n doc text: %s\n", doc.text);
        if (DB) printf("\n ----------------------------\n");

    }
     
    return EXIT_SUCCESS;
}


/*
// simples solution. ref: https://programs.programmingoneonone.com/2021/05/hackerrank-simple-text-editor-solution.html


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int main() {

    FILE * in = stdin;
    FILE * out = stdout;
   
    int command;
    int k;
    char buf[1000000];
    char ** undos;
    int n, i, ptr = 0;
    size_t len;
    fscanf(in, "%d", &n);
    undos = calloc(sizeof(char *), n);
    undos[ptr] = malloc(sizeof(char));
    strcpy(undos[ptr], "");
    for (i = 0; i < n; ++i) {
        fscanf(in, "%d", &command);
        switch(command) {
            case 1:
                fscanf(in, "%1000000s\n", buf);
                ++ptr;
                undos[ptr] = malloc(sizeof(char) * (strlen(undos[ptr-1]) + strlen(buf) + 1));
                strcpy(undos[ptr], undos[ptr-1]);
                strcat(undos[ptr], buf);
                break;
            case 2:
                fscanf(in, "%d", &k);
                ++ptr;
                undos[ptr] = malloc(sizeof(char) * (strlen(undos[ptr - 1]) - k + 1));
                len = strlen(undos[ptr - 1]);
                memcpy(undos[ptr], undos[ptr-1], strlen(undos[ptr - 1]) - k);
                undos[ptr][len - k] = 0;
                break;
            case 3:
                fscanf(in, "%d", &k);
                fprintf(out, "%c\n", undos[ptr][k-1]);
                break;
            case 4:
                --ptr;
                break;
        }
    }
    return 0;
}
*/