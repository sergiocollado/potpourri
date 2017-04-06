# Notes on Prim algorithm for generating random Mazes

## Initial definitions:

```C
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define SCREEN_X	240;
#define SCREEN_Y  320;

long int numin=1; //number of cells in the maze
const int xsize=13;   
const int ysize = 17;
const int cell_size=20;
uint8_t maze_data[240][320];
struct cell
{
	bool in; //is the cell in the maze?
	bool up; //does the wall above this cell exist?
	bool left; //does the wall to the left of this cell exist?
	int prevx, prevy; //the coordinates of the previous cell used for backtracking.
};


struct cell maze[xsize][ysize];
```

## Initialization function for the maze:

```C

void initialize()
{
	//initialize the maze
	int x,y;
	int bk_color;
	for(x=0; x<xsize; x++)
	{
		for(y=0; y<ysize; y++)
		{
			//the cells on the edges of the maze are 'in' to provide padding.Otherwise, all maze cells are not in.
			maze[x][y].in = (x==0 || x==xsize-1 || y==0 || y==ysize-1)?1:0;
			//all maze cells have all walls existing by default, except the perimeter cells.
			maze[x][y].up = ( x==0 || x==xsize-1 || y==0)?0:1;
			maze[x][y].left = ( x==0 || y==0 || y==ysize-1)?0:1;
		}
	}
	
	srand(osKernelSysTick());
	bk_color = rand()%10;
	
	switch(bk_color)
	{
		case 0:GUI_SetBkColor(GUI_BROWN); break;
		case 1:GUI_SetBkColor(GUI_BLUE); break;
		case 2:GUI_SetBkColor(GUI_GREEN);break;
		case 3:GUI_SetBkColor(GUI_LIGHTBLUE);break;
		case 4:GUI_SetBkColor(GUI_DARKMAGENTA);break;
		case 5:GUI_SetBkColor(GUI_YELLOW);break;
		case 6:GUI_SetBkColor(GUI_GRAY);break;
		case 7:GUI_SetBkColor(GUI_LIGHTGRAY); break;
		case 8:GUI_SetBkColor(GUI_DARKGRAY);break;
		case 9:GUI_SetBkColor(GUI_ORANGE); break;
	}

	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	
		//set the data matrix.
	memset(maze_data,1,240*320);
	
  osDelay(2000);
	
	return;
}
```


## Function for generating the random Maze:

```C
void generate(){
	int xcur=1, ycur=1;//start growing from the corner. It could theoretically start growing from anywhere, doesn't matter.
	int whichway;
	bool success;
	maze[xcur][ycur].in = 1;
	GUI_FillRect(xcur*cell_size , (ycur)*cell_size, xcur*cell_size+0.5*cell_size, (ycur)*cell_size+0.5*cell_size);
	clear_data(xcur*cell_size , (ycur)*cell_size, xcur*cell_size+0.5*cell_size, (ycur)*cell_size+0.5*cell_size);
		osDelay(50);
		
	do{

		if( maze[xcur][ycur-1].in&&maze[xcur][ycur+1].in&&
			   maze[xcur-1][ycur].in&&maze[xcur+1][ycur].in )
		{
				   //If at a dead end, randomly destroy a wall to make it not a dead end!
			do{
				success=0;
				whichway=rand()%4;
				switch(whichway){
				case UP:
					if(maze[xcur][ycur].up&&ycur!=1){
						success=1;
						maze[xcur][ycur].up=0;
						 GUI_FillRect(xcur*cell_size, (ycur)*cell_size-0.5*cell_size, xcur*cell_size+0.5*cell_size, ycur*cell_size);
						 clear_data(xcur*cell_size, (ycur)*cell_size-0.5*cell_size, xcur*cell_size+0.5*cell_size, ycur*cell_size);
						}
					break;
				case DOWN:
					if(maze[xcur][ycur+1].up&&ycur!=ysize-2){
						success=1;
						maze[xcur][ycur+1].up=0;
						 GUI_FillRect(xcur*cell_size, (ycur*cell_size)+0.5*cell_size, xcur*cell_size+0.5*cell_size, (ycur)*cell_size + 2*0.5*cell_size);
						 clear_data(xcur*cell_size, (ycur*cell_size)+0.5*cell_size, xcur*cell_size+0.5*cell_size, (ycur)*cell_size + 2*0.5*cell_size);
						}
					break;
				case LEFT:
					if(maze[xcur][ycur].left&&xcur!=1){
						success=1;
						maze[xcur][ycur].left=0;
						 GUI_FillRect(xcur*cell_size - 0.5*cell_size, (ycur)*cell_size, xcur*cell_size, (ycur)*cell_size+0.5*cell_size);
						 clear_data(xcur*cell_size - 0.5*cell_size, (ycur)*cell_size, xcur*cell_size, (ycur)*cell_size+0.5*cell_size);
					}
					break;
				case RIGHT:
					if(maze[xcur+1][ycur].left&&xcur!=xsize-2){
						success=1;
						maze[xcur+1][ycur].left=0;
						 GUI_FillRect(xcur*cell_size + 0.5*cell_size, (ycur)*cell_size, xcur*cell_size+2*0.5*cell_size, (ycur)*cell_size+0.5*cell_size);
						clear_data(xcur*cell_size + 0.5*cell_size, (ycur)*cell_size, xcur*cell_size+2*0.5*cell_size, (ycur)*cell_size+0.5*cell_size);
					}
					break;
				}
				osDelay(50);
			}while(!success);
		}

		while( maze[xcur][ycur-1].in&&maze[xcur][ycur+1].in&&
			   maze[xcur-1][ycur].in&&maze[xcur+1][ycur].in )
		{
				   //If all the neighbourhood cells are in, backtrack.
				int xcur2=maze[xcur][ycur].prevx;
				ycur=maze[xcur][ycur].prevy;
				xcur=xcur2;
		}

		do{
			//Randomly grow the maze if possible.
			success=0;
			whichway=rand()%4;
			switch(whichway){
			case UP:
				if(!maze[xcur][ycur-1].in){
					success=1;
					maze[xcur][ycur].up=0;
					GUI_FillRect(xcur*cell_size, (ycur)*cell_size-0.5*cell_size, xcur*cell_size+0.5*cell_size, (ycur)*cell_size);
					clear_data(xcur*cell_size, (ycur)*cell_size-0.5*cell_size, xcur*cell_size+0.5*cell_size, (ycur)*cell_size);
					osDelay(50);
					maze[xcur][ycur-1].prevx=xcur;
					maze[xcur][ycur-1].prevy=ycur;
					ycur--;
				}
				break;
			case DOWN:
				if(!maze[xcur][ycur+1].in){
					success=1;
					maze[xcur][ycur+1].up=0;
					GUI_FillRect(xcur*cell_size , (ycur)*cell_size+0.5*cell_size, xcur*cell_size+0.5*cell_size, (ycur)*cell_size+2*0.5*cell_size);
					clear_data(xcur*cell_size , (ycur)*cell_size+0.5*cell_size, xcur*cell_size+0.5*cell_size, (ycur)*cell_size+2*0.5*cell_size);
					osDelay(50);
					maze[xcur][ycur+1].prevx=xcur;
					maze[xcur][ycur+1].prevy=ycur;
					ycur++;
				}
				break;
			case LEFT:
				if(!maze[xcur-1][ycur].in){
					success=1;
					GUI_FillRect(xcur*cell_size - 0.5*cell_size, (ycur)*cell_size, xcur*cell_size, (ycur)*cell_size+0.5*cell_size);
					clear_data(xcur*cell_size - 0.5*cell_size, (ycur)*cell_size, xcur*cell_size, (ycur)*cell_size+0.5*cell_size);
					osDelay(50);
					maze[xcur][ycur].left=0;
					maze[xcur-1][ycur].prevx=xcur;
					maze[xcur-1][ycur].prevy=ycur;
					xcur--;
				}
				break;
			case RIGHT:
				if(!maze[xcur+1][ycur].in){
					success=1;
					maze[xcur+1][ycur].left=0;
					GUI_FillRect(xcur*cell_size + 0.5*cell_size, (ycur)*cell_size, xcur*cell_size+2*0.5*cell_size, (ycur)*cell_size+0.5*cell_size);
					clear_data(xcur*cell_size + 0.5*cell_size, (ycur)*cell_size, xcur*cell_size+2*0.5*cell_size, (ycur)*cell_size+0.5*cell_size);
					osDelay(50);
					maze[xcur+1][ycur].prevx=xcur;
					maze[xcur+1][ycur].prevy=ycur;
					xcur++;
				}
				break;
			}
			
			//here the painting function
			 GUI_FillRect(xcur*cell_size , (ycur)*cell_size, xcur*cell_size+0.5*cell_size, (ycur)*cell_size+0.5*cell_size);
			 clear_data(xcur*cell_size , (ycur)*cell_size, xcur*cell_size+0.5*cell_size, (ycur)*cell_size+0.5*cell_size);
			osDelay(50);
			
		}while(!success);
		maze[xcur][ycur].in=1;
		numin++; //Every iteration of this loop, one maze cell is added to the maze.
		
	}while(numin<(xsize-2)*(ysize-2));

	return;
}
```


