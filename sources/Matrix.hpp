#ifndef MATRIX_
#define MATRIX_

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace zich
{
    class Matrix
    {
        private:
            std::vector<double> matrix;
            int lines;
            int columns;
            
        public:
            Matrix(std::vector<double> mat,int lines,int columns){
                if((size_t)mat.size() != (size_t)(lines*columns)|| lines < 0 || columns < 0){
                    throw std::out_of_range{"The lines or columns or vector not in the right size!"};
                }
                this->matrix = mat;
                this->lines = lines;
                this->columns=columns;

            
            }
            static void matrix_size_exeption(const Matrix &mat,const Matrix &self);
            static void matrix_size_exeption_multipication(const Matrix &mat,const Matrix &self);

            Matrix operator+ (const Matrix &self) const;
            Matrix operator+= (Matrix &self); 
            Matrix operator+ ()const;
            Matrix operator- (const Matrix &self) const;
            Matrix operator -= (Matrix &self);
            Matrix operator- ()const;

            bool operator<(const Matrix & self)const;
            bool operator<=(const Matrix & self)const;
            bool operator>(const Matrix & self)const;
            bool operator>=(const Matrix & self)const;
            bool operator==(const Matrix & self)const;
            bool operator!=(const Matrix & self)const;

            Matrix & operator++();
            Matrix operator++(int needed);
            Matrix & operator--();
            Matrix  operator--(int needed);

            Matrix operator*= (double num);
            Matrix operator* (double num);
            friend Matrix operator* (double num,const Matrix &mat);
            Matrix operator*= (const Matrix &mat);
            Matrix operator* (const Matrix &mat);

            friend std::ostream & operator << (std::ostream & os, const Matrix & self);
            static void matrix_input_stream_exeption(int lines,int columns,std::string mat);
            friend std::istream & operator >> (std::istream & is, Matrix & self);
             // istream call to that operator it not object from our class so he need to be friend for private variable

    };
    
}


#endif