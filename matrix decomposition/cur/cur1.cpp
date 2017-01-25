#include<iostream>
#include<cstdio>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include<time.h>
using Eigen::MatrixXd;
using namespace std ;

 long long int sum=0;
float rms,rms_col,rms_row;
float a[1000][2000],atr[1000][2000],u[2000][2000],v[2000][2000],d[2000][2000] ;
 float row_p[2000],col_p[2000];
 float mat[2000][2000] ;
  float c[2000][2000];    float w[2000][2000],r[2000][2000];
int row_size,col_size,col_no,row_no,c_track[2000],r_track[2000] ;
int main(){

int nn,mm ;
cin >> nn >> mm ;
// CODE 1 PART STARTS
row_size = 943 ; col_size = 1243 ;
freopen("data.txt","r",stdin) ;
freopen("output.txt","w",stdout) ;

int dataset_size = 100000;
for(int i=0;i<dataset_size;i++){ // reading dataset

    int x1,x2,x3,x4 ;

    cin >> x1 >> x2 >> x3 >> x4 ;

    a[x1-1][x2-1] = x3 ; atr[x2-1][x1-1]=x3  ;
 mat[x1-1][x2-1] = x3 ;
}


    for(int i=0;i<row_size;i++)
    {
        for(int j=0;j<col_size;j++)
            sum+=mat[i][j]*mat[i][j];
    }
   float rms=sqrt(sum);

    sum=0;
    for(int i=0;i<col_size;i++)
    {
        for(int j=0;j<row_size;j++)
            sum+=mat[j][i]*mat[j][i];
        col_p[i]=sqrt(sum)/rms;
    }

    sum=0;
    for(int i=0;i<row_size;i++)
    {
        for(int j=0;j<col_size;j++)
            sum+=mat[i][j]*mat[i][j];
        row_p[i]=sqrt(sum)/rms;
    }


    srand (time(NULL));
    for(int i=1;i<=mm;i++)// for C, m=no of columns taken in C
    {
        col_no=rand() % col_size;
        c_track[i-1]=col_no;
        for(int j=0;j<row_size;j++)
            c[j][i-1]=mat[j][col_no];

    }

    srand (time(NULL));
    for(int i=1;i<=nn;i++)// for R, n=no of columns taken in R
    {
        row_no=rand() % row_size;
        r_track[i-1]=row_no;
        for(int j=0;j<col_size;j++)
            r[i-1][j]=mat[row_no][j];
    }
    for(int i=0;i<mm;i++)
    {
        for(int j=0;j<row_size;j++)
            c[j][i]/=sqrt(mm*col_p[c_track[i]]);
    }

    for(int i=0;i<nn;i++)
    {
        for(int j=0;j<col_size;j++)
            r[i][j]/=sqrt(nn*row_p[r_track[i]]);
    }


for(int i=0;i<mm;i++){
for(int j=0;j<nn;j++){
        w[i][j]=mat[r_track[j]][c_track[i]];
    }
}
swap(nn,mm) ;
// w is of dimensions mm x nn SVD OF this matrix
    // CODE 1 PART ENDS W RECEIVED
     MatrixXd m(nn,mm);
  MatrixXd mtr(mm,nn);
   MatrixXd asd(nn,nn);
      MatrixXd asd1(mm,mm);
 for(int i=0;i<nn;i++){
    for(int j=0;j<mm;j++){
        m(i,j)=w[i][j] ; mtr(j,i)=w[i][j] ;
    }
 }


asd = m*mtr ; // tiill here 168seconds
asd1 = mtr*m ;
Eigen::EigenSolver<MatrixXd> es(asd);
Eigen::MatrixXcd U = es.eigenvectors(); // eigen vector for a*at
 Eigen::EigenSolver<MatrixXd> es1(asd1);
Eigen::MatrixXcd V = es1.eigenvectors();// eigen vector for  at*a
Eigen::MatrixXcd D = es.eigenvalues().asDiagonal();// eigen values for a*at
Eigen::MatrixXcd D1 = es1.eigenvalues().asDiagonal();// eigen values for  at*a
int i,j ;


// PRINTING FOR OTHER CODE (INPUT)
cout<< nn << " " << mm << endl ;

for(i=0;i<nn;i++){
    for(j=0;j<nn;j++){
        cout << U(i,j).real() << " " ;
    }cout << endl ;
}
for(i=0;i<nn;i++){
    for(j=0;j<nn;j++){
        cout << D(i,j).real() << " " ;
    }cout << endl ;
}
for(i=0;i<mm;i++){
    for(j=0;j<mm;j++){
        cout << D1(i,j).real() << " " ;
    }cout << endl ;
}
for(i=0;i<mm;i++){
    for(j=0;j<mm;j++){
        cout << V(i,j).real() << " " ;
    }cout << endl ;
}

for(i=0;i<943;i++){
    for(j=0;j<nn;j++){
        cout << c[i][j] << " ";
    }
    cout << endl ;
}
for(i=0;i<mm;i++){
    for(j=0;j<1243;j++){
        cout << r[i][j] << " ";
    }
    cout << endl ;
}

}
