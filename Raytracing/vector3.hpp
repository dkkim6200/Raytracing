#ifndef VECTOR_HPP
#define VECTOR_HPP

using namespace std;

class Vector3 {
public:
    float x;
    float y;
    float z;
    
    /**
     @brief Initializes new Vector3 object as a zero vector;
     
     @return Returns new Vector3 object.
     */
    Vector3();
    
    /**
     @brief Initializes new Vector3 object as a zero vector;
     
     @param x X-value of vector
     @param y Y-value of vector
     @param z Z-value of vector
     @return Returns new Vector3 object.
     */
    Vector3(float x, float y, float z);
    
    ~Vector3();
    
    void operator=(const Vector3 &vec);
    Vector3 operator+(const Vector3 &vec); // Vector addition
    Vector3 operator+=(const Vector3 &vec);
    Vector3 operator-(const Vector3 &vec); // Vector subtraction
    Vector3 operator-=(const Vector3 &vec);
    Vector3 operator*(const float scalar); // Scalar multiple
    Vector3 operator*(const Vector3 &vec); // Vector element-wise multiple
    Vector3 operator*=(const float scalar); // Scalar multiple
    Vector3 operator/(const float scalar); // Scalar division
    
    friend ostream& operator<<(ostream& os, const Vector3 &vec);
    
    /**
     @brief Returns the magnitude of this vector.
     
     @return Magnitude of this Vector3 in float
     */
    float getMagnitude();
    
    /**
     @brief Returns the square of the magnitude of this vector.
     
     @return Square of the magnitude of this Vector3 in float
     */
    float getSquaredMag();
    
    /**
     @brief Normalizes this vector.
     
     WARNING! This function alters the current state of this vector!
     */
    Vector3 normalize();
    
    /**
     @brief Returns the dot product of this and 'vec'.
     
     
     I could have used Matrix, but that is not necessary
     since this is quite simple algorithm.
     
     @param  vec The vector to be dotted with this vector.
     @return Dot product of this and 'vec'.
     */
    float dot(Vector3 vec);
    
    /**
     @brief Returns the cross product of this and 'vec';
     
     @param  vec The vector to be crossed with this vector.
     @return Cross product of this and 'vec'.
     */
    Vector3 cross(Vector3 vec);
    
    /**
     @brief Perform orthogonal scalar projection of this to 'vec'
     
     @param vec Vector for this to be projected to
     @return Projected scalar value
     */
    float projectScalar(Vector3 vec);
    
    /**
     @brief Perform orthogonal vector projection of this to 'vec'
     
     @param vec Vector for this to be projected to
     @return Projected vector
     */
    Vector3 projectVector(Vector3 vec);
    
    /**
     @brief Returns angle between this and 'vec'
     
     @param vec Vector to be used to calculate the angle
     @return Angle between this and 'vec'
     */
    float angle(Vector3 vec); // Return the angle in radians
    
    friend Vector3 operator*(const float scalar, Vector3 v);
};

#endif
