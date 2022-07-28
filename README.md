# A-Star Algorithm
 Created a simulation of the A* pathfinding algorithm using c++ and SDL2 graphics rendering library.
 
 
 This set up for the algorithm uses a priority queue for the OpenSet and ClosedSet. It calculates
 the Heuristic using the raw distance based on it's X and Y coordinates on the grid and the distance
 formula. 
 
 The simulation aspect of the project allows the user to create a number of obstacles to change the path 
 that the computer generates. The start and endpoints are always at the same location, the top left corner
 and bottom right corner. Once the obstacles are placed onto the screen the user presses space to tell the 
 computer to find the correct path. Once said path is found then the computer retraces it's steps to
 highlight the correct and most optimal path in a blue color. If a path could not be found, the computer
 typically searches every single available node until it has no where left to go, and prints out a failure
 statement. 
 
 Possible room for improvement is allowing the user to change where they want the target or end node
 is placed. An addition to the number of obstacles, for example instead of just having walls, bomb,
 or spikes can be placed where they have some effect on the path the computer must take. changing the 
 collision of mouse clicks and the way to add neighbours to improve the effeciency of the algorithm.
