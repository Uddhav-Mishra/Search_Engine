#include<iostream>
#include<cstdio>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using Eigen::MatrixXd;
using namespace std ;

float u[2000][2000],v[2000][2000],d[2000][2000],vt[2000][2000],a[2000][2000],c[2000][2000],r[2000][2000] ;
float d1temp[2000][2000],d2temp[2000][2000],vtemp[2000][2000],utemp[2000][2000],t1[2000],t2[2000],t3[2000];
bool visu[2000],visv[2000] ;


int main(){
int i,j ;
freopen("output.txt","r",stdin) ;
 freopen("output2.txt","w",stdout) ;
int n,m ;
 cin >> n >> m ;
 MatrixXd C(943,n);
  MatrixXd R(m,1243);
  // getting input of various matrices from previous  program cur 1 output
for(i=0;i<n;i++){for(j=0;j<n;j++){cin >> utemp[i][j] ;}} // stores temp value of u (svd not the original )
for(i=0;i<n;i++){for(j=0;j<n;j++){cin >> d1temp[i][j] ;}  t1[i]=t2[i]=d1temp[i][i] ;   }// stores temp value of u (svd not the original )
for(i=0;i<m;i++){for(j=0;j<m;j++){cin >> d2temp[i][j] ;}      t3[i]=d2temp[i][i] ;    }// stores temp t3 used for sorting t2 for eigen vector
for(i=0;i<m;i++){for(j=0;j<m;j++){cin >> vtemp[i][j] ;}}// stores temp value of v (used in svd)
for(i=0;i<943;i++){for(j=0;j<n;j++){cin >> c[i][j] ;C(i,j) = c[i][j] ;}} // C (decomposed)
for(i=0;i<m;i++){for(j=0;j<1243;j++){cin >> r[i][j] ;R(i,j)=r[i][j];}}
// R (decomposed)

sort(t2,t2+n,greater<float>()) ; // sorting eigen

 for(i=0;i<n;i++){d[i][i]=t2[i] ;} // setting middle matrix

 for(i=0;i<n;i++){
    for(int j=0;j<n;j++){
        if(!visu[j]&&t1[j]==t2[i]){
            visu[j]=1;
            for(int k=0;k<n;k++){u[k][i]=utemp[k][j];} // sorting and arranging u vector of svd
            break;
        }
    }
     for(int j=0;j<m;j++){
        if(!visv[j]&& t3[j]==t2[i]){
            visv[j]=1;
            for(int k=0;k<m;k++){v[k][i]=vtemp[k][j];} // sorting and arranging v vector of svd
            break;
        }
    }
 }


for(int k=0;k<m;k++){
    if(!visv[k]){
    for(int j=0;j<m;j++){
        v[j][i] = vtemp[j][k] ; i++; // resolving leftover values
    }
    }
}
for(i=0;i<m;i++){ // taking transpose of v
for(j=0;j<m;j++){vt[i][j]=v[j][i] ;}}

// check print
/*
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        cout << u[i][j] << " " ;
    }cout << endl;
}
for(i=0;i<m;i++){
    for(j=0;j<m;j++){
        cout << vtemp[i][j] << " " ;
    }cout << endl;
}
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        cout << d[i][j] << " " ;
    }cout << endl;
}*/
// final answers in u[i][j] d[i][j] vt[i][j] ;
fclose(stdin) ;
//fclose(stdout) ;
freopen("data.txt","r",stdin) ; // reading original  data
for(i=0;i<100000;i++){
    int x1,x2,x3,x4 ;
    cin >> x1 >> x2 >> x3 >> x4 ;
    a[x1-1][x2-1] = x3 ; // making user movie database into a
}
int k  = 0 ;
 MatrixXd U(n,n-k);
  MatrixXd D(n-k,n-k);
   MatrixXd V(n-k,m);
MatrixXd F(n,m);

for(i=0;i<n;i++){ for(j=0;j<n-k;j++){  U(i,j) = u[i][j] ; }}
for(i=0;i<n-k;i++){ for(j=0;j<n-k;j++){D(i,j) = d[i][j] ; if(D(i,j)!=0.0){D(i,j) = 1/D(i,j) ;}}}
for(i=0;i<n-k;i++){ for(j=0;j<m;j++){   V(i,j) = vt[i][j] ;}}

F = U*D*V ;
 F = (V.transpose())*(D)*(U.transpose()) ;

 U.resize(n,m) ;
 U = F ;
  F.resize(943,1243) ;
  F = C*U*R ;
for(i=0;i<943;i++){ for(j=0;j<1243;j++){ F(i,j) = F(i,j)/1000 ;}}
float ans = 0.0 ;

for(i=0;i<943;i++){
    for(j=0;j<1243;j++){
        ans += (F(i,j)-a[i][j])*(F(i,j)-a[i][j]) ;
       // cout << F(i,j)<< " " << a[i][j] << "     " ;
    }
}
ans = sqrt(ans) ;
cout << ans << endl ; // final error of svd
fclose(stdout) ;



}
