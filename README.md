# Homework order
Bob has many projects to do as a part of his studies so he has to prepare a schedule. Since there is a possibility that he may be unable to complete all the projects by their respective deadlines, he has to make sure that the most important ones are completed. The priority of projects may be subject to change over time. Projects may be divided in the groups. Bob may be interested in finding the project with a highest priority from a given group. The groups may be merged. Help Bob schedule his homework - implement the following operations:
##### e group - Extract element with maximum value from the group and print it's value.
##### p group - Print values of all elements in the group according to their decreasing order. 
##### m group1 group2 - Merge groups 1 and 2. Group 1 should contain all elements. Group two should become empty .
##### i group oldValue newValue - increase value of element in group from oldValue to new Value.
If operation is illegal (extraction from empty group, increasing priority of element that does not belong to the specified group), the output should be "na"
Input
Input will have the following form:n operation operation....
where n is the number of operations. There are at most 1000 groups. There are at most 200000 elements in a group.

#### So my soultion is just an implementation of Binomial Heap
