#include<iostream>
#include<cstdio>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using Eigen::MatrixXd;
using namespace std ;

float a[1000][2000],atr[1000][2000],u[2000][2000],v[2000][2000],d[2000][2000] ;
float dtemp[2000],d2temp[2000],vtemp[2000][2000],utemp[2000][2000],d1[2000];
int visu[2000],visv[2000] ;
 MatrixXd m(943,1682);
  MatrixXd mtr(1682,943);
   MatrixXd asd(943,943);
      MatrixXd asd1(1682,1682);
int dataset_size = 100000;
int main(){
ios::sync_with_stdio(false);
freopen("data.txt","r",stdin) ;
freopen("output.txt","w",stdout) ;

int dataset_size = 100000;
for(int i=0;i<dataset_size;i++){ // reading dataset

    int x1,x2,x3,x4 ;

    cin >> x1 >> x2 >> x3 >> x4 ;

    a[x1-1][x2-1] = x3 ; atr[x2-1][x1-1]=x3  ;

}
 for(int i=0;i<943;i++){
    for(int j=0;j<1682;j++){
        m(i,j)=a[i][j] ; mtr(j,i)=a[i][j] ; // m = user movie rating
    }
 }

asd = m*mtr ; // tiill here 168seconds
asd1 = mtr*m ;
Eigen::EigenSolver<MatrixXd> es(asd);
Eigen::MatrixXcd U = es.eigenvectors();
 Eigen::EigenSolver<MatrixXd> es1(asd1);
Eigen::MatrixXcd V = es1.eigenvectors();
Eigen::MatrixXcd D = es.eigenvalues().asDiagonal();//making d a daigonal matrix
Eigen::MatrixXcd D1 = es1.eigenvalues().asDiagonal();//making d a daigonal matrix
int i,j ;

for(i=0;i<943;i++){
    for(j=0;j<943;j++){
        cout << U(i,j).real() << " " ; // u matrix for data
    }cout << endl ;
}
for(i=0;i<943;i++){
    for(j=0;j<943;j++){
        cout << D(i,j).real() << " " ; // eigen valiues for u
    }cout << endl ;
}
for(i=0;i<1243;i++){
    for(j=0;j<1243;j++){
        cout << D1(i,j).real() << " " ; //eigen vector for v
    }cout << endl ;
}
for(i=0;i<1243;i++){
    for(j=0;j<1243;j++){
        cout << V(i,j).real() << " " ; //eigen values for v
    }cout << endl ;
}


}
