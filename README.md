# ECS122B-Program2
Comparison of subset enumeration vs n-tuple enumeration for Algorithms class at UC Davis. Assignment was done in a group.

Purpose: Compares the run time of two brute force approaches to enumeration: subset enumeration and n-tuple enumeration. Utilizes bash scripts to automate testing.

Results: n-tuple enumeration was much faster as the data set grew. This was due to its ability to remove "redundant" comparisions by avoiding repeated comparisions based off differences in item ordering.
