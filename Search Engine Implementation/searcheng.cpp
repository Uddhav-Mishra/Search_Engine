#include <bits/stdc++.h>
#include "dictionary.cpp"  //containing the dictionary construction

using namespace std;

int main () {

    cout<<"Processing(+Stemming) the text file...Please wait."<<endl;  // function of stemming of the dataset
    stem_the_input_file();

/*--------------------------------------Stemming the INPUT file ends here--------------------------------------------------*/

  int erro = create_structure_of_original_words(); // function of structure of different fields of dataset
  if(erro == 5)
  {
      cout<<"file didn't open!"<<endl;
      return 0 ;
  }
  erro = create_structure_of_stemmed_words();
    if(erro == 5)
    {
        cout<<"Unable to open file!"<<endl;
        return 0;
    }

/*--------------------------------------Putting Data in structure ends here--------------------------------------------------*/


cout<<"File processed!"<<endl;
cout<<"Total Docs are "<<docid<<endl;
cout<<"Now making a dictionary.."<<endl;

    make_dictionary_stemmed_words(); //tokenising function
    make_dictionary_original_words();  //function for dictionary formation without stemming


  /*--------------------------------------Tokenising the Structure and Dictionary formation ends here--------------------------------------------------*/

  cout<<"Dictionary made! Total distinct words are "<<dict.size()<<endl;
  cout<<endl;


  while(1)
  {
       cout<<"Please Enter your query NOW. Press '0' to exit."<<endl;
        cout<<"(refer README file for query related details)"<<endl;
        scanf("\n");

      string query;
  getline(cin, query);
  if(query == "0") // query credits
  {
            cout<<"Thankyou!"<<endl;
            cout<<"Credits"<<endl;
            cout<<"Uddhav Mishra"<<endl;
            cout<<"Naman Goyal"<<endl;
            cout<<"Animesh Singh"<<endl;
            cout<<"Medha Smriti"<<endl;
            cout<<" Shubham Jain"<<endl;
            return 0;
  }
    get_suggestions(query);     //  suggestions function in case  query mistyped

    cout<<"Change the query?(y/n)"<<endl;
    string c;
    cin>>c;
    if(c =="y")
    {
        cout<<"Re-enter your query"<<endl;
        continue;

    }
// Suggestion part ends

    query=stem_the_query(query);
    get_boolean_retrieval(query);

 // TF-IDF Ranked retrieval STARTS

    tf_idf_ranking();   //tdf idf calculation fuction for ranking docs

  }
  return 0;
}
