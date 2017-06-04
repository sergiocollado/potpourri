#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

 
/**
 * View at: https://www.codingame.com/replay/solo/231402941
 **/
 
/**
 * Don't let the machines win. You are humanity's last hope...
 **/
 
// http://en.cppreference.com/w/cpp

 /**
  * Example: you are given a 2 by 2 grid: '0' -> is a node; '.' -> empty node
  *
  * > 00
  * > 0.
  * 
  * 
  * One line for each node.
  * 
  *  x1 y1 x2 y2 x3 y3
  * 
  *  x1, y1 - coordinates of the node
  *  x2, y2 - coordinates of node at the rigth
  *  x3, y3 - coordinates of the node at the bottom
  * 
  * your answer should be:
  *
  * $ 0 0 1 0 0 1
  * $ 1 0 -1 -1 -1 -1
  * $ 0 1 -1 -1 -1 -1
  * 
  * -- If there is no neighbour node, then use the coordinates "-1 -1"
  * 
  * So the coordinate system, is the one for computer graphics:
  * 
  *          1       2
  *    +-----+-------+--------------->  X
  *    |
  *    |  
  * 1  +     0       0
  *    | 
  *    |
  * 2  +     0       .
  *    |
  *    |
  *  Y V
  * 
  * 
  * 
  **/
  
      
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

  
int main()
{

    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    
    char Matrix[width][height];
    
    cerr << "Width:" << width << endl << "Height:" << height << endl << endl;
    
    //loop to get the grid
    // INPUT MATRIX IS:
    cerr<< "Input Matrix is:" << endl;
    
    for (int j = 0; j < height; j++) // height coordenate. Y coordenate
    {
        string line; // width characters, each either 0 or .
        getline(cin, line);
        cerr << line << '\n';  // output the matrix line.
        
        for(int i = 0; i< width; i++) // width coordenate, X coordenate
        {
        //store values.
            if(line[i] == '0' || line[i] == '.')
            {
             Matrix[i][j]=line[i];
            }else
            { cerr << "Error parsing input" <<endl;}
            
        }
    }
    

    //the answer will be:
    string node_answer;
    node_answer.clear();
    
    
    for(int j = 0; j < height; j++)
    {
    
     for(int i = 0; i < width; i++)
     {
         
      int node_x=i;
      int node_y=j;     

      cerr << endl << endl;
      cerr << "Coordenates (" << i << ", " << j << ") = " << \
      Matrix[i][j] << endl<< "----------------------" << endl << endl;
      
      switch( Matrix[i][j] )
      {
          case '0': 
            
            //output current node
            node_answer.append(to_string(i));
            node_answer.append(" ");
            node_answer.append(to_string(j));
            node_answer.append(" ");
             
            //output rigth node
             
            node_x = i; //value of the current node- 
            cerr << ">CHECK NODE TO THE RIGHT OF " << i << ", " <<j << \
            " = M(i,j)= " << Matrix[i][j] << endl;

            node_x++; //check to its right.
            
            do
            {
                if (node_x <= width-1)
                {
                 cerr <<"check node (" << node_x << ", " << j << ") = " << \
                 Matrix[node_x][j] << endl;
                 
                }
                 
                 if(  (node_x <= width -1) &&  (Matrix[node_x][j] == '0'))
                 {
                     node_answer.append(to_string(node_x));
                     node_answer.append(" ");
                     node_answer.append(to_string(j));
                     node_answer.append(" ");
                     
                     cerr << ">THE NODE TO ITS RIGHT IS: " << node_x << " " << j << endl;
                     
                     break;
                     
                 } else if( node_x >= width -1)
                 {
                    node_answer.append( "-1 -1 ");
                    cerr << "-1 -1 - no node to the right";
                    break;
                    
                 }
                 
                node_x++;
                              
             }while( (node_x<= width ));
             
             
             //bottom node  
             node_y = j; //value of the current node.
             
             cerr << endl << ">CHECK NODE TO THE BOTTOM OF "<< i << ", " << j\
             << " = M(i,j)= " << Matrix[i][j] << endl;
             
             node_y++; //check below.
             
             do
             {
                if ( node_y <= height -1)
                {
                 cerr <<"check node (" << i << ", " << node_y << ") = " << \
                 Matrix[i][node_y] << endl;
                }
                
                if( (node_y <= height -1) && (Matrix[i][node_y] == '0'))
                {
                     node_answer.append(to_string(i));
                     node_answer.append(" ");
                     node_answer.append(to_string(node_y));
                     node_answer.append(" ");
                     
                     cerr << ">THE NODE BELOW IS: " << i << " " << node_y << " ";
                     
                     break;
    
    
                 } else if(node_y >= height -1)
                 {
                    node_answer.append( "-1 -1 ");
                    cerr << "-1 -1 - no node at the bottom" << endl;
                    break;
                 }
                 
                node_y++;
                
             
              }while( node_y <= height );
            

            //output:
             cerr <<endl << endl<< ">>Answer: " << node_answer << '\n' << endl;
             node_answer.append( "\n" );

     
            break;

         case '.':
             cerr << "=" << "Empty node" <<endl;
             break;
          
         default:
            cerr << "something went wrong: "<< "i:" <<i<< " j:" << j<< " M:" << Matrix[i][j] << endl;
          
         } //end switch - 
         

         
       } //end for(j)
      
    } //end for(i)


    //output:
    cout << node_answer << endl;
    node_answer.clear();

}
