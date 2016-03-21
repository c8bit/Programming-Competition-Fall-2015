# Programming-Competition-Fall-2015
1st Place winning solution that I submitted for my first programming contest. 

## The Problem
To summarize the problem, there is a track of `X` stacks of boxes of unknown height, and a robot that can move between the stacks and transport the boxes.
```
#  #  
## # # <----Stacks of 'boxes' (#)
#### #
######
======
X  <----- Robot
```
In the above diagram, the box configuration can be described by a vector of numbers, each representing the number of boxes in that respective column:
```
4 3 2 4 1 3
```
We were also given a 'target vector', a box configuration that needed to be created by moving the existing boxes around. An example could be as follows:
```
1 7 5 0 3 6
```
We needed to give the robot directions as to what moves to take to re-arrange the boxes into the desired configuration. You'll notice the sums do not match up - this indicates that we were REQUIRED to take point penalties, so we had to optimize the solution so the penalty was minimal.

### Constraints
* The robot can do 4 actions:
   * Move left
   * Move right
   * Pick up a box from current stack
   * Drop a held box to the current stack
* The robot can hold a maximum of one box at a time
* The program that generates the robot's directions has full knowledge of the quantity of all stacks at all times, as well as whether or not the robot is holding a box
* Each individual action adds to an 'action counter' used in scoring
* Our program needed to generate the set of directions and feed them into the scoring mechanism (the robot).
* 3 hour time limit after learning the problem to be solved

### Scoring
* Golf Scoring (lowest score wins)
* For each action taken, add 1 point
* For each stack that does NOT exactly meet the specified target quantity, take the difference 'X' between the two quantities, and add 2^X points to your score

Additionally, there were three configuration sets to be scored. The first was available for all contestants to see, and the other 2 were unkown to the contestants (the program had to figure out everything on its own).

By the time the 3 hours was up, I had scored 82 points, while the next runner up had over 12,000 points.

## The Solution
The solution was pretty straightforward - abide by the following algorithm:
  * Step 1: Setup
     * Determine the number of boxes in the starting configuration
     * Determine the number of boxes in the target configuration, then determine the difference `X`
     * Distribute the difference `X` among the number of columns `Y` to determine the minimum penalty `Z ~= X/Y`
  * Step 2: Execution
     * Find the NEAREST column to the robot which has more than `Z` TOO MANY boxes in it, and move there
     * Take one box
     * Find the NEAREST column to the robot which has more than `Z` TOO FEW boxes in it, and move there
     * Drop the box
     * Repeat until all stacks are within `Z` difference from the target

### Why this is good
Since the penalties  grow exponentially, it is extremely important to minimize them, so that becomes top priority. With that being said, a relatively simple and effective course of action is to move the boxes closest to the robot around and not have to move further than is necessary if there is still work to do. There's not too much else to say. Given more time, there are many calculations that could yield more optimal results, such as checking the penalty points remaining vs the amount of points it will take to move around and lower the penalty, since one might end up outweighing the other.

## Coordinator/Judge
All files in the 'scoring' folder credited to:

William 'Amos' Confer
Associate Professor, SUNYIT/SUNY Polytechnic Institute

