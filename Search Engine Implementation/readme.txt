
**************VECTOR SPACE MODEL INFORMATION RETRIEVAL ********                    ******************************

RETRIEVAL MODEL

This repository contains an implementation of Vector Space Model of Information Retrieval. 
Data is read from a .csv(Comma Separated Values) file. Words are then represented in an inverted index using the data structure-nested maps. The documents are returned
using Boolean Retrieval Model. These documents are then ranked using the Vector Space Model based on tf-idf score.


LIBRARIES USED:

Boost library

ADDITIONAL FEATURE:

When the query is entered, the system returns a set of closely matching results in the form of doc id in the ranked order according to vector space model with the help of tf-idf score. Select from one of them to proceed to document retrieval.Also if the query is mistyped ,the search engine suggest you some queries which are implemented with the help of edit distance.

INSTRUCTIONS ON QUERY FORMAT:

1) Enter words separated by & to return set of documents which have entered words in conjunction. 
2) Enter words separated by ' '(space) to return set of documents which have entered words in disjunction. 
3) The characters: '-','!',' are treated as separators and hence the words obtained will be conjunctively searched.
4) The only precedence order followed among boolean operators is from left to right .
