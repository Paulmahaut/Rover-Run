# ROVER RUN !

#Background to the assignment
2028: A very intense solar storm has just hit... The MARC - MArs Rover Cartograph rover, which was carrying out its mission very well, has suffered a malfunction. Its programming, guidance and movement systems have been seriously affected...
The ESTF, Efrei Space Task Force, has called on programming experts to design new travel software for MARC.
Your mission is to use this travel software to bring MARC back to a base station where it can be refurbished.


## Functionalities 

1. **Map Initialization**:
   - The project initializes a map from a file, which includes the dimensions and the soil types for each cell.
   - The map is represented as a 2D array of soil types and a corresponding 2D array of movement costs.

2. **Robot Localization**:
   - The robot's position and orientation are managed using the `t_localisation` structure.
   - Functions are provided to initialize the robot's location, check if a position is valid, and move the robot based on its current orientation and the type of move.

3. **Movement and Rotation**:
   - The robot can perform various moves such as moving forward, backward, turning left, right, or making a U-turn.
   - The `locmove` function updates the robot's position based on the move and the terrain effects.

4. **Random Move Selection**:
   - The project includes a function to randomly select a sequence of moves for the robot, ensuring that each move is selected based on its availability.

5. **Cost Calculation**:
   - The project calculates the movement costs from the base station to all other cells on the map.
   - It uses a queue-based approach to propagate the costs from the base station to the rest of the map.

6. **Tree Construction and Pathfinding**:
   - The project constructs a tree representing possible paths the robot can take.
   - It includes functions to build the tree, find the leaf with the minimum cost, and calculate the optimal path from the root to this leaf.

7. **Complexity Measurement**:
   - The project measures the execution time for different phases, including tree construction, leaf search, and path calculation.
   - It uses functions to display and manage the complexity measurements.

8. **Menu Interface**:
   - The project provides a menu interface for the user to select different maps, calculate complexity, or quit the program.

These features collectively enable the simulation of a rover navigating a map, finding the optimal path to a base station, and measuring the computational complexity of the operations involved.

The structure of read.me was designed using AI
