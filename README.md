# 3-D Vector Class

1. This 3-D vector class implements all the basic operation that can be done on a 3-D vector.

  - The first class named tdvector have member variable as vector of size 3 which is private and saves the 3 components along i, j, k direction and another integer which saves the magnitude related to this vector.
  - The other functions inside the class includes the some operator overloaded functions which are important to calculate any vector related quantities such as unit vector, dot product, scaler multiplication etc.
  
2. The vp class implements some of the vector related quantities such as angle between two vectors, their box products etc, using the functions inside tdvector class. 

3. The important design decision was to separate tdvector from vp class so that the user has access to all the crude functions in the form of operator, to make functions according to his/her needs, like the functions implemented in vp class. 
