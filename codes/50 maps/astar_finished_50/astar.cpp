////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// c++ `Magick++-config --cxxflags --cppflags` -O2 -o findpath findpath.cpp   `Magick++-config --ldflags --libs`


// STL A* Search implementation
// (C)2001 Justin Heyes-Jones
//
// Finding a path on a simple grid maze
// This shows how to do shortest path finding using A*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stlastar.h" // See header for copyright and usage information
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <Magick++.h>
#include <iostream>
#include <fstream>

using namespace Magick;
using namespace std;

int total_dist=0;
int edges=0;
int readarray[1000000];
string line;
int arraysize=0;
int mm;

string input_type="image"; //either (binary or array)
const int m =50;
const int n =50;
int x_start=5  ;        //  start x poistion 
int y_start=5  ;        //  start y postion 
int x_goal =26 ;         //  goal  x postion
int y_goal =26 ;         //  goal  y postion
const char* map_image_direcotry =  "/home/ganam/Desktop/final 1/50 maps/image_50_0.jpg";
const char* map_binary_directory= "/home/ganam/Desktop/final 1/50 maps/binary_50_0.bin";
const char* nodes_directory     = "/home/ganam/Desktop/final 1/astar_finished/nodes.TXT"; //set this to the same directory of "findpath.cpp"
float myarray[m][n];
int myarrayint[m][n];

#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0

#include <fstream>
using namespace std;

// Global data

// The world map

const int MAP_WIDTH  = n;
const int MAP_HEIGHT = m;

int world_map[ MAP_WIDTH * MAP_HEIGHT ]; 
int GetMap( int x, int y )
{
	if( x < 0 ||
	    x >= MAP_WIDTH ||
		 y < 0 ||
		 y >= MAP_HEIGHT
	  )
	{
		return 9;
	}

	return world_map[(y*MAP_WIDTH)+x];
}



// Definitions

class MapSearchNode
{
public:
	int x;	 // the (x,y) positions of the node
	int y;

	MapSearchNode() { x = y = 0; }
	MapSearchNode( int px, int py ) { x=px; y=py; }

	float GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
	bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
	float GetCost( MapSearchNode &successor );
	bool IsSameState( MapSearchNode &rhs );

	void PrintNodeInfo();


};

bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{

	// same state in a maze search is simply when (x,y) are the same
	if( (x == rhs.x) &&
		(y == rhs.y) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

void MapSearchNode::PrintNodeInfo()
{
	char str[1000];
	sprintf( str, "Node position : (%d,%d)\n", x,y );
	ofstream fout;
	fout.open("nodes.TXT",ios::app);
    fout<<x<<endl;
    fout<<y<<endl;
	cout << str;
	fout.close();
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	return fabsf(x - nodeGoal.x) + fabsf(y - nodeGoal.y);
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	if( (x == nodeGoal.x) &&
		(y == nodeGoal.y) )
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{

	int parent_x = -1;
	int parent_y = -1;

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}


	MapSearchNode NewNode;

	// push each possible move except allowing the search to go backwards

	if( (GetMap( x-1, y ) < 9)
		&& !((parent_x == x-1) && (parent_y == y))
	  )
	{
		NewNode = MapSearchNode( x-1, y );
		astarsearch->AddSuccessor( NewNode );
	}

	if( (GetMap( x, y-1 ) < 9)
		&& !((parent_x == x) && (parent_y == y-1))
	  )
	{
		NewNode = MapSearchNode( x, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}

	if( (GetMap( x+1, y ) < 9)
		&& !((parent_x == x+1) && (parent_y == y))
	  )
	{
		NewNode = MapSearchNode( x+1, y );
		astarsearch->AddSuccessor( NewNode );
	}


	if( (GetMap( x, y+1 ) < 9)
		&& !((parent_x == x) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}

///////////////////////////////////////////////
if( (GetMap( x+1, y+1 ) < 9)
		&& !((parent_x == x+1) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x+1, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}
if( (GetMap( x-1, y-1 ) < 9)
		&& !((parent_x == x-1) && (parent_y == y-1))
		)
	{
		NewNode = MapSearchNode( x-1, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}

if( (GetMap( x-1, y+1 ) < 9)
		&& !((parent_x == x-1) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x-1, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}

if( (GetMap( x+1, y-1 ) < 9)
		&& !((parent_x == x+1) && (parent_y == y-1))
		)
	{
		NewNode = MapSearchNode( x+1, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}
	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor )
{
	return (float) GetMap( x, y );

}


// Main

int main( int argc, char *argv[] )
{     ofstream fout;
    fout.open("nodes.TXT",ios::trunc); //this to open and empty the file
    fout.close();
    if(input_type=="image")
    {
        for(int i=0;i<m ;i++)
        {
            for(int j=0;j<n ;j++)
            {
                InitializeMagick(*argv);
//              Image img("/home/ganam/Desktop/ph auto/astar_finished/image7.jpg");
                Image img(map_image_direcotry);
                cout<<i<<","<<j<<endl;
                ColorRGB rgb(img.pixelColor(i, j));
                myarray[i][j]=rgb.red();
            }            
        }
        cout<<myarray<<endl;
        fstream myfile0("maparray.bin",ios::out  | ios::trunc | ios::binary |ios::in);
        myfile0.close();// those two lines to open the file and empty it then close it again

        fstream myfile("maparray.bin",ios::out  | ios::app | ios::binary |ios::in);

        for(int i=0;i<m;i=i+1)
        {
            for(int j=0 ; j<n ; j=j+1)
            {
                if(myarray[i][j]<.5)
                {myarrayint[i][j]=9;}
                else
                {myarrayint[i][j]=1;}
            }
        }
        
        myfile.seekp(0);
        for(int i=0; i<m; i=i+1)
        {
            for(int j=0 ; j<n ; j=j+1)
            {
                if(j==n-1){cout<<endl;}
                myfile.write((char*) &myarrayint[i][j], sizeof(int)); 
                cout<<myarrayint[i][j];
            }
        }
        
        /////read test
        myfile.seekg(0);
        int out[m*n];
        for(int i=0;i<m*n;i=i+1)
        {
            myfile.read((char*) &out[i], sizeof(int));  
        }
        
        int counter=0;
        cout<<endl;
        for(int i=0;i<m*n;i=i+1)
        {
            if(counter%n==0) {cout<<endl;}
            cout<<out[i];
            counter=counter+1;
        }
        

        
        fstream myfile11("maparray.bin",ios::out  | ios::app | ios::binary |ios::in);
        //int world_map[ MAP_WIDTH * MAP_HEIGHT ];
        myfile11.seekg(0);
        for(int i=0;i<MAP_WIDTH*MAP_HEIGHT;i=i+1)
        {
            myfile11.read((char*) &world_map[i], sizeof(int));
        }
        
        
        
    }
    else if(input_type=="binary")
    {
        InitializeMagick(*argv);
        ofstream fout;
	fout.open("nodes.TXT",ios::trunc); //this to open and empty the file
	fout.close();

//      fstream myfile("maparray7.bin",ios::out  | ios::app | ios::binary |ios::in);
        fstream myfile(map_binary_directory,ios::out  | ios::app | ios::binary |ios::in);
     if(!myfile.is_open()){cout<<"error";}
     else
     {//int world_map[ MAP_WIDTH * MAP_HEIGHT ];
         myfile.seekg(0);

      for(int i=0;i<MAP_WIDTH*MAP_HEIGHT;i=i+1)
         {

           myfile.read((char*) &world_map[i], sizeof(int));
         }

     }
    }
     clock_t begin = clock();

	cout << "STL A* Search implementation\n(C)2001 Justin Heyes-Jones\n";

	// Our sample problem defines the world as a 2d array representing a terrain
	// Each element contains an integer from 0 to 5 which indicates the cost
	// of travel across the terrain. Zero means the least possible difficulty
	// in travelling (think ice rink if you can skate) whilst 5 represents the
	// most difficult. 9 indicates that we cannot pass.

	// Create an instance of the search class...

	AStarSearch<MapSearchNode> astarsearch;

	unsigned int SearchCount = 0;

	const unsigned int NumSearches = 1;

	while(SearchCount < NumSearches)
	{

		// Create a start state
		MapSearchNode nodeStart;
		nodeStart.x = x_start;//rand()%MAP_WIDTH;
		nodeStart.y = y_start;//rand()%MAP_HEIGHT;

		// Define the goal state
		MapSearchNode nodeEnd;
		nodeEnd.x = x_goal; //rand()%MAP_WIDTH;
		nodeEnd.y = y_goal
		; //rand()%MAP_HEIGHT;

		// Set Start and goal states

		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;
		unsigned int SearchSteps = 0;

		do
		{
			SearchState = astarsearch.SearchStep();

			SearchSteps++;

	#if DEBUG_LISTS

			cout << "Steps:" << SearchSteps << "\n";

			int len = 0;

			cout << "Open:\n";
			MapSearchNode *p = astarsearch.GetOpenListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY
				((MapSearchNode *)p)->PrintNodeInfo();
	#endif
				p = astarsearch.GetOpenListNext();

			}

			cout << "Open list has " << len << " nodes\n";

			len = 0;

			cout << "Closed:\n";
			p = astarsearch.GetClosedListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY
				p->PrintNodeInfo();
	#endif
				p = astarsearch.GetClosedListNext();
			}

			cout << "Closed list has " << len << " nodes\n";
	#endif

		}
		while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

		if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
		{
			cout << "Search found goal state\n";

				MapSearchNode *node = astarsearch.GetSolutionStart();

	#if DISPLAY_SOLUTION
				cout << "Displaying solution\n";
	#endif
				int steps = 0;

				node->PrintNodeInfo();
				for( ;; )
				{
					node = astarsearch.GetSolutionNext();

					if( !node )
					{
						break;
					}

					node->PrintNodeInfo();
					steps ++;

				};

				cout << "Solution steps " << steps << endl;

				// Once you're done with the solution you can free the nodes up
				astarsearch.FreeSolutionNodes();


		}
		else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED )
		{
			cout << "Search terminated. Did not find goal state\n";

		}

		// Display the number of loops the search went through
		cout << "SearchSteps : " << SearchSteps << "\n";

		SearchCount ++;

		astarsearch.EnsureMemoryFreed();
	}

	
	
	// read the nodes from the nodes.txt file
ifstream fin;	
fin.open(nodes_directory);
        for( std::string line; getline( fin, line ); )
        {
            mm= atoi(line.c_str());
            readarray[arraysize]=mm;
            arraysize=arraysize+1;
        }

	fin.close();
        
// sorting the postions of the nodes in x and y array 
          int xarray[arraysize/2];
          int yarray[arraysize/2];
          
        int counter2=0;
        for(int i=0 ; i<arraysize ; i=i+2)
        {
            xarray[counter2]=readarray[i];
            yarray[counter2]=readarray[i+1];
            counter2=counter2+1;
        }


       
// filtering the array to keep only the edge points 
        int xmark;
        int ymark;
        int marksarray[arraysize/2];
        marksarray[0]=0;
        for(int i=1 ; i<arraysize/2 ; i=i+1)
        {
           xmark=xarray[i]-xarray[i-1];
           ymark=yarray[i]-yarray[i-1]; 
           if     (xmark==-1 && ymark==-1){ marksarray[i]=1;}
           else if(xmark==-1 && ymark==0) { marksarray[i]=2;}
           else if(xmark==-1 && ymark==1) { marksarray[i]=3;}
           else if(xmark==0 && ymark==-1) { marksarray[i]=4;}
           else if(xmark==0 && ymark==1)  { marksarray[i]=6;}
           else if(xmark==1 && ymark==-1) { marksarray[i]=7;}
           else if(xmark==1 && ymark==0)  { marksarray[i]=8;}
           else if(xmark==1 && ymark==1)  { marksarray[i]=9;}

        }
        
        int xDestContainer[1000000];
        int yDestContainer[1000000];
        xDestContainer[0]=xarray[0];
        yDestContainer[0]=yarray[0];
        
        int DestSize=0;
        for(int i=1 ; i<arraysize/2 ; i=i+1)
        {
         if (marksarray[i]-marksarray[i-1]!=0  || i==arraysize/2-1 )
            {
                
                xDestContainer[DestSize]=xarray[i-1];
                yDestContainer[DestSize]=yarray[i-1];
                DestSize=DestSize+1;
                
            }
        }
for(int i=0 ; i<DestSize ; i=i+1)
        {
//          cout<<"x="<<xDestContainer[i]<<" y="<<yDestContainer[i]<<endl;
        }
        
for(int i =0; i<DestSize-1; i=i+1)
{

    total_dist=total_dist+sqrt( pow (xDestContainer[i]-xDestContainer[i+1] , 2 ) + pow( yDestContainer[i]-yDestContainer[i+1], 2 ))  ;
                          
                           
}
clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
cout<<"time_spent="<<time_spent<< endl;
cout<<"total_dist="<<total_dist<<endl;
cout<<"edges="<<DestSize<<endl;
// display results
//diplay goal and start star in green , goal in yellow ;
             Image disimage(map_image_direcotry);    
             disimage.pixelColor(y_start, x_start, "green" ); 
             disimage.pixelColor(y_goal,x_goal , "yellow" ); 
             disimage.scale(Geometry(500,500, 500, 500) );
             disimage.display();
             disimage.scale(Geometry(m,n, m, n) );
             
//display the bath in blue
    for(int i =0; i< counter2; i=i+1)
    {
                disimage.pixelColor(yarray[i],xarray[i],  "red" );
             
    }

       disimage.scale(Geometry(500,500, 500, 500) );
       disimage.display();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
