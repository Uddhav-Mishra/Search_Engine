#include <bits/stdc++.h>
#include<boost/tokenizer.hpp>   //Contains Boost Library
#include "stemming.cpp" //Contains Stemming Code
using namespace std;
map<string,map<int,int> > dict; //For creating dictionary of words, dict[i][j] represents count of ith word in jth document
map<string,map<int,int> > orgdict;  // for accessing the content value from the dict
vector<int> ans ;

int docid;
map<string,map<int,int> >::iterator itr,itrr ;
map<int,int>::iterator itr1,itr2 ;
map<string,int> query_terms ;
double doc_score[9000][20] ;
double query_score[200] ;
int doc_ans[20000] ;
pair<double,int>p[20000] ;
 string query_tokens[3000] ;
    string distinct_terms[100000] ;
    pair<int,string>dist[10][200000] ;
void getwords(string line,string words[])   //Comma seperated values represent diff. fields of document
{
    string s;
    int id = 0;
    int idx = 0;
    while(line[id] != '\0')
    {
        while(line[id] != ',')
        s+=line[id++];

            words[idx++] = s;
            s  ="";
            id++;


    }
}

struct node     //A structure for different fields
{
    string title;
    string author;  // relevant attribute of document stored in the structure
    string date;
    string content;
    string link;


};
struct node doc[1000000];
struct node orgdoc[100000];
int err(string k)
{
                      // func. to take only those rows in the dataset where the data  matches the datatype
   string s;
    s+=k[0];
    s+=k[1];
    s+=k[2];
    if(s == "jan"||s=="feb"||s=="mar"||s=="apr"||s=="jun"||s=="jul"||s=="aug"||s=="sep"||s=="oct"||s=="nov"||s=="dec")
        return 1;
    return 0;
}


int orgerr(string k)
{
    string s;
    s+=k[0];
    s+=k[1];
    s+=k[2];
    if(s == "Jan"||s=="Feb"||s=="Mar"||s=="Apr"||s=="Jun"||s=="Jul"||s=="Aug"||s=="Sep"||s=="Oct"||s=="Nov"||s=="Dec")
        return 1;
    return 0;
}

int edit_distance(string a, string b){
int x = a.size();  int y = b.size() ;  //function for calculating edit distance for suggestions
int dp[x+1][y+1] ;
for(int i=0;i<=x;i++){
    for(int j=0;j<=y;j++){
        if(i==0){dp[i][j]=j ;}
        else if(j==0){dp[i][j]=i ;}
        else if(a[i-1]==b[j-1]){dp[i][j]=dp[i-1][j-1];}
        else{
            dp[i][j]=1+min(dp[i-1][j],min(dp[i][j-1],dp[i-1][j-1])) ;
        }
    }
}
return dp[x][y];       //returns edit distance
}

void stem_the_input_file() // function for stemming the dataset
{
     int i;

   struct stemmer * z = create_stemmer();  // stemming the data set by linking the header file from stemming code


   s = (char *) malloc(i_max + 1);
   FILE * f = fopen("data.txt","r");
      if (f == 0) { cout<<"stemming file not found"<<endl;}
      stemfile(z, f);

   free(s);

   free_stemmer(z);
fclose(f);
}


string stem_the_query(string query)
{
    struct stemmer * z = create_stemmer();

   s = (char *) malloc(i_max + 1);

    query=stemstring(z,query); //Stemming the query string

   free(s);

   free_stemmer(z);
   return query;
}
int create_structure_of_original_words()
{
    string line;
   docid = 0;
    ifstream myfile2("data.txt");
    if (!myfile2.is_open())
  {
      cout<<"error";
      return 5;
  }
  while ( getline (myfile2,line) )
    {

        string word[20];
        getwords(line,word);                 //  relevant attributes of the dataset in the structure use for tokenising
            if(orgerr(word[1]))
            {
                orgdoc[docid].title = word[0];
                orgdoc[docid].date = word[1];
                orgdoc[docid].author = word[2];
                orgdoc[docid].link = word[10];
                orgdoc[docid].content = word[4];


                docid++;
            }


    }
   // cout<<docid<<endl;
        myfile2.close();
}











int create_structure_of_stemmed_words()    // function for creating structure of the dataset
{
  ifstream myfile ("nmn.txt");
  string line;
     docid = 0;
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {

        string word[20];
        getwords(line,word);
            if(err(word[1]))
            {
                doc[docid].title = word[0];
                doc[docid].date = word[1];
                doc[docid].author = word[2];
                doc[docid].link = word[10];
                doc[docid].content = word[4];


                docid++;
            }


    }
    myfile.close();
  }
  else
    return 5;
}














void  make_dictionary_stemmed_words()  // fuction for dictionary construction of stemmed dataset
{
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer ;
  boost::char_separator<char> sep{" +-\?;:.[!\"]"};
  for(int i = 0;i<docid;i++)
  {
    //std::string s = "Boost C++ Libraries";
    tokenizer tok{doc[i].title, sep};
    for (const auto &t : tok)
    {
        dict[t][i]++;
    }
     tokenizer tok1{doc[i].author, sep};
    for (const auto &t : tok1)
    {
        dict[t][i]++;
    }
    tokenizer tok2{doc[i].content, sep};
    for (const auto &t : tok2)
    {
        //if(i == 0)
          //  cout<<t<<endl;
        dict[t][i]++;
    }
    tokenizer tok3{doc[i].date, sep};
    for (const auto &t : tok3)
    {
      //  cout<<t<<endl;
        dict[t][i]++;
    }

  }
}




void make_dictionary_original_words() //function for dictionary construction for original unstemmed dataset
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer ;
  boost::char_separator<char> sep{" +-?;\:.[!\"]"};       //separators used for dataset
  for(int i = 0;i<docid;i++)
  {
    //std::string s = "Boost C++ Libraries";
    tokenizer tok{orgdoc[i].title, sep};      //tokenising original doc title
    for (const auto &t : tok)
    {
        orgdict[t][i]++;
    }
     tokenizer tok1{orgdoc[i].author, sep};   //tokenising original doc author
    for (const auto &t : tok1)
    {
        orgdict[t][i]++;
    }
    tokenizer tok2{orgdoc[i].content, sep};   // tokenising original doc content
    for (const auto &t : tok2)
    {
        //if(i == 0)
          //  cout<<t<<endl;
        orgdict[t][i]++;
    }
    tokenizer tok3{orgdoc[i].date, sep};   //tokenising original doc date
    for (const auto &t : tok3)
    {
      //  cout<<t<<endl;
        orgdict[t][i]++;
    }

  }
}




void get_suggestions(string query)    // function for suggestions
{




    typedef boost::tokenizer<boost::char_separator<char> > tokenizer ;
    boost::char_separator<char> sep2{" +-?;:.[\"]/","!&|"};
    tokenizer tok{query, sep2};
  // edit distance part SUGGESTIONS
   int i = 0 ;
   for (const auto &t : tok)
{    if(t!="!"&&t!="&"&&t!="|"){ query_tokens[i]=t ;i++; }}
int query_size = i ;
itr = orgdict.begin() ; itrr = orgdict.end() ; i = 0 ;
while(itr!=itrr){
        string h = itr->first ;
    if(h!="!"&&h!="&"&&h!="|"){distinct_terms[i]= h ; i++;}
    itr++;
}
int dict_size = i ;
for(i=0;i<query_size;i++){
    for(int j=0;j<dict_size;j++){
        dist[i][j].first = edit_distance(distinct_terms[j],query_tokens[i]) ;
        dist[i][j].second = distinct_terms[j] ;
    }
    sort(dist[i],dist[i]+dict_size) ;
}

cout << "do you mean this?????\n" ;
i=dict_size-1 ;
for(int j=0;j<5;j++){ cout << "(" <<j+1 << ") " ;
    for(i=0;i<query_size;i++){
        cout  << dist[i][j].second << " " ;
    }
    cout << endl ;
}

}


void get_boolean_retrieval(string query) // function for boolean retrieval
{

    typedef boost::tokenizer<boost::char_separator<char> > tokenizer ;
    boost::char_separator<char> sep2{" +*-?\;:.[\"]/","!&|"};

    tokenizer tok4{query, sep2};


    int x = 0 ; // x = terms in query except for ! | &
 int doc_ans[20000] ; int docs =docid;

  for(int i=1;i<=docs;i++){doc_ans[i]=0;}

  int flag = 0 ;  // 0 = OR --- 1 = AND ----2 = NOT
  //cout<<"seg"<<endl;

for (const auto &t : tok4)
{
    if(t=="&"||t=="|"||t=="!"){
        if(t=="|"){flag=0; }
        else if(t=="&"){flag=1;}
        else if(t=="!"){flag=2;}
    }
    else{
            query_terms[t]++ ;
 itr=dict.find(t) ;
 if(itr != dict.end())
 {itr1=(itr->second).begin() ;
  itr2=(itr->second).end() ;
while(itr1!=itr2){
        int y = itr1->first ; // cout <<"here " <<  y << endl ;
   if(flag==0){ doc_ans[y]=1;}
   else if(flag==1){
    if(doc_ans[y]==1){doc_ans[y]=2 ;}
   }
   else if(flag==2){  if(doc_ans[y]==1){doc_ans[y]=0 ;}   }
    itr1++ ;
}
if(flag==1){
    for(int i=1;i<=docs;i++){
        if(doc_ans[i]==2){doc_ans[i]=1 ;}
        else{doc_ans[i]=0 ;}
    }
}}
flag=0;
}
}
  /*--------------------------------------Boolean Query Completes here--------------------------------------------------*/

  for(int i=1;i<=docs;i++){
    if(doc_ans[i]==1){ans.push_back(i);
    //cout<<i<<endl;
    }
  }
        cout <<"no. of docs satisfying boolean query " << ans.size()<<endl<<endl ;

}







void tf_idf_ranking()   // function for tdf idf for ranking
{
    int x;
if(ans.size()>0){
                cout<<"Now ranking them using vector space model."<<endl;

int distinct_queries = query_terms.size() ;
int ans_docs = ans.size() ;
map<string,int>::iterator itr3,itr4 ;
itr3=query_terms.begin() ; itr4=query_terms.end() ;  int i = 0,j ;

// TF*IDF OF QUERY
while(itr3!=itr4){
    x = max(1,(int)((dict.find(itr3->first)->second).size())) ;
    //cout <<"value of x is"<< x << endl ;
    query_score[i] = (double)(1.0+log10(itr3->second))*(log10((double)docid/(double)x));
    itr3++ ;i++;
}
//cout << "query_score[0] is " << query_score[0] << endl ;


// calculating document score for each doc
for(i=0;i<ans_docs;i++){
    itr3=query_terms.begin() ;
    for(j=0;j<distinct_queries;j++){
            itr1 = ((dict.find(itr3->first)->second).find(ans[i])) ; itr2 =(dict.find(itr3->first)->second).end() ;
           if(itr1!=itr2){ x = (int)(itr1->second) ;}
           else{x = 0 ;}
       if(x!=0) {doc_score[i][j] = 1.0+ (double)log10((double)x) ;}
       else{ doc_score[i][j]=0.0;} //CHECK WHETHER 1.0 OR 0
        itr3++ ;
    }
}

//NORMALIZATION OF QUERY VECTOR
double dd =  0.0 ;

for(i=0;i<distinct_queries;i++){
   dd+= (double) 1.0*(query_score[i]*query_score[i]) ;
}
dd = 1.0*sqrt(dd) ;
for(i=0;i<distinct_queries;i++){
   if(dd!=0) {query_score[i] = 1.0*((double)(query_score[i])/(double)dd) ;}
   else{query_score[i] = 0.0 ;}
}
//cout << "query_score[0] is " << query_score[0] << endl ;

//NORMALIZATION OF ALL DOCUMENT VECTORS
for(i=0;i<ans_docs;i++){
    dd = 0.0 ;
    for(j=0;j<distinct_queries;j++){
          dd += (double)1.0*(doc_score[i][j]*doc_score[i][j]) ;
    }
    dd = (double)1.0*sqrt(dd) ;
     for(j=0;j<distinct_queries;j++){
          if(dd!=0){doc_score[i][j]= 1.0*((double)(doc_score[i][j])/(double)dd) ;}
          else{doc_score[i][j] = 0 ;}
    }
}
// sorting of (scores and doc no.s) in pair structure

for(i=0;i<ans_docs;i++){
    dd = 0.0 ;
    for(j=0;j<distinct_queries;j++){
          dd += (double)1.0*(query_score[j]*doc_score[i][j]) ;
    }
    p[i].second=ans[i] ;
    p[i].first=dd ;
        if(p[i].second==0){cout << "score of 0th doc is " << p[i].first << endl;}
}

sort(p,p+ans_docs);
i = ans_docs-1;
cout << "top 20 docs satisfying query\n" ;

for(j=0;j<min(20,ans_docs);j++){
    cout << "doc no. " << p[i].second << " score is " << p[i].first << endl ; i-- ;
}

}
}






