// --> YOUR NAME here
// Few comments describing the class Points2D

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <stdlib.h>

namespace teaching_project
{

    // Place comments that provide a brief explanation of the class,
    // and its sample usage.
    template <typename Object>
    class Points2D
    {
    public:
        // Default "big five" -- you have to alter them for your assignment.
        // That means that you will remove the "= default" statement.
        //  and you will provide an implementation.

        // Zero-parameter constructor.
        // Set size to 0.
        Points2D<Object>()
        {
            this->size_ = 0;
            this->sequence_ = nullptr;
        };

        // Size only constructor
        Points2D<Object>(int length_)
        {
            this->size_ = length_;
            this->sequence_ = new std::array<Object, 2>[length_];
        };

        // Copy-constructor.
        Points2D(const Points2D &rhs)
        {
            this->sequence_ = new std::array<Object, 2>[rhs.size_];
            this->size_ = rhs.size_;
            for (size_t i = 0; i < rhs.size_; i++)
            {
                this->sequence_[i][0] = rhs[i][0]; //copying one object element to another
                this->sequence_[i][1] = rhs[i][1];
            }
        };
        
        // Move-constructor.
        Points2D(Points2D &rhs) : sequence_{rhs.sequence_}, size_{rhs.size_}
        {
            rhs.size_ = 0;
            rhs.sequence_ = nullptr;
        };

        // Copy-assignment. If you have already written
        // the copy-constructor and the move-constructor
        // you can just use:
        // {
        // Points2D copy = rhs;
        // std::swap(*this, copy);
        // return *this;
        // }
        Points2D &operator=(const Points2D &rhs)
        {
            if(this != &rhs){
                delete sequence_;
                this->sequence_ = new std::array<Object, 2>[rhs.size_];
                this->size_ = rhs.size_;
                for (size_t i = 0; i < rhs.size_; i++)
                {
                    this->sequence_[i][0] = rhs[i][0]; //copying one object element to another
                    this->sequence_[i][1] = rhs[i][1];
                }
            }
        	return *this;
        };

        

        // Move-assignment.
        // Just use std::swap() for all variables.
        Points2D &operator=(Points2D &rhs)
        {
            if (this != &rhs)
            {
                std::swap(this->sequence_, rhs.sequence_);
                std::swap(this->size_, rhs.size_);
            }
            return *this;
        };

        // Destructor to ensure all data is freed
        ~Points2D()
        {
            if (this->size_ > 0)
            {
                delete this->sequence_; //delete the used memory
            }
        };

        // End of big-five.
        // One parameter constructor.
        Points2D(const std::array<Object, 2> &item)
        {
            this->size_ = 1; //initialise size with 1 
            this->sequence_ = new std::array<Object, 2>[1]; // initialise array
            this->sequence_[0][0] = item[0];
            this->sequence_[0][1] = item[1];
        };


        size_t size() const
        {
            return this->size_;
        }

        // @location: an index to a location in the sequence.
        // @returns the point at @location.
        // const version.
        // abort() if out-of-range.
        const std::array<Object, 2> &operator[](size_t location) const
        {
            if (location > this->size_ || location < 0)
            {
                abort();
            }
            return this->sequence_[location];
        }

        //  @c1: A sequence.
        //  @c2: A second sequence.
        //  @return their sum. If the sequences are not of the same size, append the
        //  result with the remaining part of the larger sequence.
        friend Points2D operator+(const Points2D &c1, const Points2D &c2)
        {
            size_t bigger = 0;
            size_t smaller = 0;
            if (c1.size_ > c2.size_)
            {
                bigger = c1.size_;
                smaller = c2.size_;
            }
            else
            {
                bigger = c2.size_;
                smaller = c1.size_;
            }
            Points2D sum_points(bigger); //initialising the new object to store the sum of both objects
            for (size_t i = 0; i < smaller; i++)
            {
                sum_points.sequence_[i][0] = c1[i][0] + c2[i][0];
                sum_points.sequence_[i][1] = c1[i][1] + c2[i][1];
            }
            if (c1.size_ > c2.size_)
            {
                for (size_t i = smaller; i < bigger; i++)
                {
                    sum_points.sequence_[i][0] = c1[i][0];
                    sum_points.sequence_[i][1] = c1[i][1];
                }
            }
            else
            {
                for (size_t i = smaller; i < bigger; i++)
                {
                    sum_points.sequence_[i][0] = c2[i][0];
                    sum_points.sequence_[i][1] = c2[i][1];
                }
            }
            return sum_points;
        }

        // Overloading the << operator.
        friend std::ostream &operator<<(std::ostream &out, const Points2D &temp_points)
        {
            if (temp_points.size_ == 0)
            {
                out << "()" << std::endl;
                return out;
            }
            for (size_t i = 0; i < temp_points.size_; i++)
            {
                out << "(";
                out << temp_points[i][0];
                out << ",";
                out << temp_points[i][1];
                out << ")";
            }
            out << std::endl;
            return out;
        }

        // Overloading the >> operator.
        // Read a chain from an input stream (e.g., standard input).
        friend std::istream &operator>>(std::istream &in, Points2D &temp_points)
        {
            int sz;
            in >> sz; //getting size
            Points2D helper_points(sz); // initialize new temporary object
            
            int temp = 0;
            while(temp < sz){
                in >> helper_points.sequence_[temp][0];
                in >> helper_points.sequence_[temp][1];
                
                temp++;
            }
            temp_points = helper_points;
            return in;
        }

    private:
        // Sequence of points.
        std::array<Object, 2> *sequence_;
        // Size of sequence.
        size_t size_;
    };

} // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_
