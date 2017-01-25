#include<iostream>
#include<cstdio>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using Eigen::MatrixXd;
using namespace std ;

float u[2000][2000],v[2000][2000],d[2000][2000],vt[2000][2000],a[2000][2000] ;
float d1temp[2000][2000],d2temp[2000][2000],vtemp[2000][2000],utemp[2000][2000],t1[2000],t2[2000],t3[2000];
bool visu[2000],visv[2000] ;
float an  = 0.0 ;

int main(){
int i,j ;
freopen("output.txt","r",stdin) ;
 freopen("output2.txt","w",stdout) ;

  // getting input of various matrices from previous  program svd 1 output
for(i=0;i<943;i++){for(j=0;j<943;j++){cin >> utemp[i][j] ;}}// stores temp value of u (svd not the original )
for(i=0;i<943;i++){for(j=0;j<943;j++){cin >> d1temp[i][j] ;}  t1[i]=t2[i]=d1temp[i][i] ;   }// stores temp value of u (svd not the original )
for(i=0;i<1243;i++){for(j=0;j<1243;j++){cin >> d2temp[i][j] ;}      t3[i]=d2temp[i][i] ;    }// stores temp t3 used for sorting t2 for eigen vector
for(i=0;i<1243;i++){for(j=0;j<1243;j++){cin >> vtemp[i][j] ;}}// stores temp value of v (used in svd)

sort(t2,t2+943,greater<float>()) ;

 for(i=0;i<943;i++){d[i][i]=t2[i] ;}

 for(i=0;i<943;i++){
    for(int j=0;j<943;j++){
        if(!visu[j]&&t1[j]==t2[i]){
            visu[j]=1;
            for(int k=0;k<943;k++){u[k][i]=utemp[k][j];}
            break;
        }
    }
     for(int j=0;j<1243;j++){
        if(!visv[j]&& t3[j]==t2[i]){
            visv[j]=1;
            for(int k=0;k<1243;k++){v[k][i]=vtemp[k][j];}
            break;
        }
    }
 }
 //cout << i << endl;
 // int ans1 = 0,ans2=0 ;
 //for(i=0;i<943;i++){if(!visu[i]){ans1++;}}
  //for(i=0;i<1243;i++){if(!visv[i]){ans2++;}}
  //cout << ans1 << ans2 << endl ;
for(int k=0;k<1243;k++){
    if(!visv[k]){
    for(int j=0;j<1243;j++){
        v[j][i] = vtemp[j][k] ; i++;
    }
    }
}
for(i=0;i<1243;i++){
for(j=0;j<1243;j++){vt[i][j]=v[j][i] ;}}

// PRINT NOW


for(i=0;i<943;i++){
    for(j=0;j<943;j++){
        cout << u[i][j] << " " ;
    }cout << endl;
}
for(i=0;i<1243;i++){
    for(j=0;j<1243;j++){
        cout << vtemp[i][j] << " " ;
    }cout << endl;
}
for(i=0;i<943;i++){
    for(j=0;j<943;j++){
        cout << d[i][j] << " " ;
    }cout << endl;
}
// final answers in u[i][j] d[i][j] vt[i][j] ; TILL HERE RUN IN 170 seconds
fclose(stdin) ;
//fclose(stdout) ;
freopen("data.txt","r",stdin) ;
for(i=0;i<100000;i++){
    int x1,x2,x3,x4 ;
    cin >> x1 >> x2 >> x3 >> x4 ;
    a[x1-1][x2-1] = x3 ;
}
int k  = 100 ;
 MatrixXd U(943,943-k); // k= no. of eigen removed
  MatrixXd D(943-k,943-k);
   MatrixXd V(943-k,1243);
MatrixXd F(943,1243);

for(i=0;i<943;i++){
    for(j=0;j<943-k;j++){
        U(i,j) = u[i][j] ;// U = U MATIX OF SVD DECOMPOSOTION
    }
}
for(i=0;i<943-k;i++){
    for(j=0;j<943-k;j++){
        D(i,j) = d[i][j] ;// D = sigma matrix
    }
}
for(i=0;i<943-k;i++){
    for(j=0;j<1243;j++){
        V(i,j) = vt[i][j] ; // V= vtranspose==vt matrix
    }
}
F = U*D*V ; // final matrix obtained
for(i=0;i<943;i++){ for(j=0;j<1243;j++){ F(i,j) = F(i,j)/1000 ;}}
float ans = 0.0 ;

for(i=0;i<943;i++){
    for(j=0;j<1243;j++){
        ans += (F(i,j)-a[i][j])*(F(i,j)-a[i][j]) ; // frobinius error
       // cout << F(i,j)<< " " << a[i][j] << "     " ;
    }
  //  cout << endl ;
}
an = ans ;
ans = sqrt(ans ) ;
cout << ans << endl ;

}
