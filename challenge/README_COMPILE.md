## BUILDING
- This is a CMake Project
- In the current directory run build.sh
- The Binary named "super_charger" will be generated in the build folder 

## RUNNING
- The algorithm can be adjusted either to return optimal (slow) solution or slightly suboptimal(fast) solution.
- To control this the variable called "compare_weight" can be changed in main.cpp
- If the value of the "compare_weight" is set to 1 then it will generate an optimal result with guarantee.
- Other values will return a solution with upper bound on the cost,i.e sol_cost = (variable*optimal_cost).
- Min time resolution for charging is set to 0.25 hours, it can aslo be change in main file by changing "search_res" variable.
- Finer time resolution might cause the search to run a little slower.

