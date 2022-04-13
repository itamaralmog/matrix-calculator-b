#include "Matrix.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <regex>
using namespace zich;
using namespace std;

namespace zich{
    void Matrix::matrix_size_exeption(const Matrix &mat,const Matrix &self){
    //check the size of matrix in add matrix and etc' else that can exist.
       if(mat.matrix.size() != self.matrix.size() || self.lines != mat.lines || self.columns != mat.columns){
            throw "matrix size exeption";
        } 
    }
    void Matrix::matrix_size_exeption_multipication(const Matrix &mat,const Matrix &self){
    //check the size of matrix in multipacation else it can exist.
       if(mat.columns!=self.lines){
            throw "matrix size multipication exeption";
        } 
    }
    //function + binary matrix and matrix
    Matrix Matrix::operator+ (const Matrix &self) const
    {
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        vector<double> res;
        for(unsigned long i = 0; i < self.matrix.size(); i++){
            res.push_back(self.matrix.at(i)+mat.matrix.at(i));
        }
        Matrix result{res,self.lines,self.columns};
        return result;
    } 
    //function += binary matrix and matrix
    Matrix Matrix::operator+= (Matrix &self)
    {
        matrix_size_exeption(*this,self);
        for(unsigned long i = 0 ;i < this->matrix.size() ; i++)
        {
            this->matrix.at(i)+=self.matrix.at(i);
        }
        return *this;
    }
    //function + unary
    Matrix Matrix::operator+()const
    {
        Matrix mat{this->matrix,this->lines,this->columns};
        return mat;
    }
    //function - binary matrix and matrix
    Matrix Matrix::operator- (const Matrix &self) const
    {
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        vector<double> res;
        for(unsigned long i = 0; i < self.matrix.size(); i++){
            res.push_back(mat.matrix.at(i)-self.matrix.at(i));
        }
        Matrix result{res,self.lines,self.columns};
        return result;
    } 
    //function -= binary
    Matrix Matrix::operator-= (Matrix &self)
    {
        matrix_size_exeption(*this,self);
        for(unsigned long i = 0 ;i < this->matrix.size() ; i++)
        {
            this->matrix.at(i)-=self.matrix.at(i);
        }
        return *this;
    }
    //function - unary
    Matrix Matrix::operator-()const
    {
        Matrix mat = *this;
        for(int i = 0 ;i < mat.lines*mat.columns; i++)
        {
            mat.matrix.at((unsigned long)i) = -mat.matrix.at((unsigned long)i);
        }
        return mat;
    }
    //function < binary
    bool Matrix::operator<(const Matrix & self)const{
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        double sum_mat=0;
        double sum_self=0;
        for(unsigned long  i = 0 ; i < mat.matrix.size(); ++i){
           sum_mat +=mat.matrix.at(i);
           sum_self +=self.matrix.at(i);
        }
        return sum_mat<sum_self;
    }
    //function <= binary
    bool Matrix::operator<=(const Matrix & self)const{
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        return (mat < self) || (mat == self);
    }
    //function > binary
    bool Matrix::operator>(const Matrix & self)const{
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        return !((mat < self) || (mat == self));
    }
    //function >= binary
    bool Matrix::operator>=(const Matrix & self)const{
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        return(mat > self) || (mat == self);
    }
    //function == binary
    bool Matrix::operator==(const Matrix & self)const{
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        for(unsigned long  i = 0 ; i < mat.matrix.size(); ++i){
            if(mat.matrix.at(i) != self.matrix.at(i)){
                return false;
            }
        }
        return true;
    }
    //function != binary
    bool Matrix::operator!=(const Matrix & self)const{
        Matrix mat = *this;
        matrix_size_exeption(mat,self);
        return !(mat == self);
    }
    //function ++ before
    Matrix & Matrix::operator++(){ //++a
        for(unsigned long i = 0 ; i < this->matrix.size();++i){
            this->matrix.at(i)+=1;
        }
        return *this;
    }
    //function ++ after
    Matrix Matrix::operator++(int needed){//a++
       Matrix mat = *this;
       Matrix new_mat{mat.matrix,mat.lines,mat.columns};
       for(unsigned long i = 0 ; i < mat.matrix.size();++i){
            this->matrix.at(i)++;
        }
        return new_mat; 
    }
    //function -- before
    Matrix & Matrix::operator--(){
        for(unsigned long i = 0 ; i < this->matrix.size();++i){
            this->matrix.at(i)-=1;
        }
        return *this;
    }
    //function -- after
    Matrix Matrix::operator--(int needed){
       Matrix mat = *this;
       Matrix new_mat{mat.matrix,mat.lines,mat.columns};
       for(unsigned long i = 0 ; i < mat.matrix.size();++i){
            this->matrix.at(i)--;
        }
        return new_mat;  
    }
    //function *= matrix and than double
    Matrix Matrix::operator *= (double num)
    {
        double n = (double)num;
        for(unsigned long i = 0 ;i < this->matrix.size() ; i++)
        {
            this->matrix.at(i)= (double)this->matrix.at(i)*n;
        }
        return *this;
    }
    //function * matrix and than double
    Matrix Matrix::operator * (double num)
    {
        double n = (double)num;
        vector<double> new_mat;
        for(unsigned long i = 0 ;i < this->matrix.size() ; i++)
        {
            new_mat.push_back((double)this->matrix.at(i)*n);
        }
        Matrix result{new_mat,this->lines,this->columns};
        return result;
    }
    //function *= matrix and matrix
    Matrix Matrix::operator *=(const Matrix &mat1)
    {
        Matrix mat = *this;
        matrix_size_exeption_multipication(mat,mat1);
        vector<double> new_mat;
        unsigned long place = 0;  
        for(unsigned long i = 0 ; i < mat.lines; i++){
            for(unsigned long j = 0; j < mat1.columns ; j++){
                new_mat.push_back(0);       
                for(unsigned long k = 0; k < mat1.lines; k++){
                    new_mat.at(place)+= (mat.matrix.at(i*(unsigned long)mat.columns+k))*(mat1.matrix.at(k*(unsigned long)mat1.columns+j));
                }
                place++;
            }
        }
        this->matrix = new_mat;
        this->columns = mat1.columns;;
        return mat;
    }
    //function * matrix and matrix
    Matrix Matrix::operator * (const Matrix &mat1)
    {
        Matrix mat = *this;
        matrix_size_exeption_multipication(mat,mat1);
        vector<double> new_mat;
        unsigned long place = 0;  
        for(unsigned long i = 0 ; i < mat.lines; i++){
            for(unsigned long j = 0; j < mat1.columns ; j++){
                new_mat.push_back(0);       
                for(unsigned long k = 0; k < mat1.lines; k++){
                        new_mat.at(place)+= (mat.matrix.at(i*(unsigned long)mat.columns+k))*(mat1.matrix.at(k*(unsigned long)mat1.columns+j));
                }
                place++;
            }
        }
        Matrix result{new_mat,mat.lines,mat1.columns};
        return result;
    }
    //function * int and than matrix
    Matrix operator * ( double num ,const Matrix &mat)
    {
        double n = (double)num;
        vector<double> res;
        for(unsigned long i = 0 ;i < mat.matrix.size() ; i++)
        {
            res.push_back((double)mat.matrix.at((unsigned long)i)*n);
        }
        Matrix result{res,mat.lines,mat.columns};
        return result;
    }
    //
    ostream & operator << (ostream & os, const Matrix &self)
    {
        string result;
        for(int i = 0 ; i < self.lines ; i++){
            result += "[";
            for(int j = 0 ; j < self.columns ; j++){
                int place = i*self.columns+j;
                result += to_string((int)self.matrix.at((unsigned long)place)); //(int) erase in the end.
                if(j != self.columns -1){
                    result += " ";
                }
            }
            if(i != self.lines -1){
                    result += "]\n";
            }
            else{
                result += "]";
            }
        }
        os << result;
        return os;
    }
    void matrix_input_stream_exeption(int lines,int columns,std::string matend){
        int sum_spaces = lines*(columns-1)+2;
        int sum_psiks = lines-1;
        int sum_spaces_between = 0;
        for(unsigned long i=0; i < matend.size(); i++){
            if(matend[i] == ' '){
                sum_spaces--;
                sum_spaces_between++;
            }
            if(matend[i] == ','){
                sum_psiks--;
            }
            if(i <= matend.size()-2 && matend[i] == ']' && matend[i+1] != ','){
                throw "not in format 1";
            }
            if(matend[i] == ']'){
                if(sum_spaces_between != (columns-1)){
                    throw "not in format 2";
                }
                sum_spaces_between = -1;
            }  
        }
        if(sum_spaces != 0 || sum_psiks !=0){
            throw "not in format 3";
        }
    }
    istream & operator >> (std::istream & is, Matrix & self){
        string element;
        string matend;
        int columns = 0;
        int lines = 0;
        vector<double> matrix;
        while(!is.eof()){
            is >> element;
            matend+=element+" ";
        } // get the input.
        matend = matend.substr(0, matend.size()-4);
        lines = (int)count(matend.begin(), matend.end(), '[');
        for(unsigned long i=0; i < matend.size(); i++){
            if(matend[i] == ' '){
                columns++; 
            }
            if(matend[i] == ']'){
                break;
            }
        } // count the columns by space.
        columns++;
        matrix_input_stream_exeption(lines,columns,matend);
        string a;
        for(unsigned long i = 0; i < matend.size(); ++i){
            if( matend[i] != '[' && matend[i] != ']' && matend[i] != ',' ){
                a+=matend[i];
            }
        } // erase all the chars that are not number.
        matend = a;
        string num_in_matrix;
        stringstream stream_matrix(matend);
        while (getline(stream_matrix, num_in_matrix,' ')) {
                try{
                    double num_double =stod(num_in_matrix);
                    matrix.push_back(num_double);
                }
                catch (exception& ex) {
                    throw "not number";
                }
        }
        self.columns = columns;
        self.lines = lines;
        self.matrix = matrix;
        return is;
    }   
}


