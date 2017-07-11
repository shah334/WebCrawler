
#include "webcrawler.h"
// Add your implementation here
#include <vector>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "SimpleHTMLParser.h"
#include <stdlib.h>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <string.h>
using namespace std;
char * data;
char * word;

void
WebCrawler::usage(){

	printf("Example of Input: webcrawl -u 100 http://www.purdue.edu http://www.slashdot.org http://www.cnn.com\n");

}


WebCrawler::WebCrawler(int maxUrls, int nInitialURls,  const char ** initialURLs)
{
  // Allocate space for _urlArray
	//printf("%s",initialURLs[0]);
  _urlArray = new URLRecord[maxUrls];
  _urlToUrlRecord = new HashTableTemplate <int>();
  _wordToURLRecordList = new HashTableTemplate <URLRecordList *>();
  bool insert;
 // insert the initialURls
  for(int i=0;i<nInitialURls;i++){
	  _urlArray[i]._url = strdup(initialURLs[i]);
	  insert = _urlToUrlRecord->insertItem(_urlArray[i]._url,i);//insert the index and urls in _urlToUrlRecord
   }
  // Update _maxUrls, _headURL and _tailURL
  _headURL = 0;
  _tailURL = nInitialURls;
  _maxUrls = maxUrls;
}


void
WebCrawler::crawl()
{
  while (_headURL <_tailURL) {
	 int n;
	 const char * URL = (_urlArray[_headURL]._url);
	 int len;
	 char * doc = fetchHTML(URL,&len);//get the html document from the URL
	 if(doc == NULL){
		 _headURL++;
		 continue;
	 }
	 SimpleHTMLParser parser;
	 bool temp = parser.parse(doc,len);//parse the document
	 int t;
	 _urlArray[_headURL]._description = strdup(parser.description.c_str());
	  vector<string> strs;
	  boost::split(strs,parser.doc,boost::is_any_of(" "));

	  for(int i=0;i<strs.size();i++){
	  	URLRecordList * list = new URLRecordList();
	  	bool isThere = _wordToURLRecordList.find(strs[i].c_str(), &list);
	  	if(!isThere){//word doesnt exist
	  		URLRecordList * l = new URLRecordList();
	  		l->_urlRecordIndex = _headURL;
	  		l->_next = NULL;
	  		temp = _wordToURLRecordList->insertItem(strs[i].c_str(),l);
	  	}else{
	  		URLRecordList * l = list;
	  		while(l->_next!=NULL){
	  			l=l->_next;
	  		}
	  		URLRecordList * node = new URLRecordList();
	  		node->_urlRecordIndex = _headURL;
	  		node->_next = NULL;
	  		l->_next = node;
	  	}
	  }

	  //int tempLen;
	  for(int i=0;i<parser.urlvector.size();i++){
			 int tempLen = 0;
			 string s = parser.urlvector[i];// get the url
			 if(s[0]!='#'){
			 	if(s[0] == '/' && s[1]=='/'){
				 	s = "https:" + s;
				 }
				if(s[0]=='/' && s[1]!='/'){
					s = _urlArray[_headURL]._url + s;
				}
				if(s[0]=='h'){
					if(_tailURL < _maxUrls){
						if(!_urlToUrlRecord->find(s.c_str(),&t)){
							_urlArray[_tailURL]._url = strdup(s.c_str());
							temp = _urlToUrlRecord->insertItem(_urlArray[_tailURL]._url,_tailURL);
							_tailURL ++;
					}
				}
			 }
	    }
	  }
	 _headURL++;
     /*Fetch the next URL in _headURL
        Increment _headURL
        If the document is not text/html
              continue;
        Get the first 500 characters (at most) of the document without tags. Add this description to theURL record for this URL.
        Find all the hyperlinks of this document and add them to the _urlArray and _urlToUrlRecord if they are not already in the _urlToUrlRecord. Only insert up to _maxURL entries.
		For each word in the document without tags, add the index of this URL to a URLRecordList in the _wordToURLRecordList table if the URL is not already there.*/
 	}//while

}

void
WebCrawler::writeURLFile(const char * urlFileName){
	ofstream f;
	f.open(urlFileName);
	for(int i=0;i<_maxUrls;i++){
		f<<i+1<<" "<<_urlArray[i]._url<<"\n"<<_urlArray[i]._description<<"\n\n";
	}
	f.close();
}

void
WebCrawler::createHash(){
		//TODO
	/**bool t;
	bool insert;
	int k = 0;
	for(int i=0;i<_maxUrls;i++){
		vector<string> strs;
		boost::split(strs,_urlArray[i]._description,boost::is_any_of(" "));
		URLRecordList * list = new URLRecordList();
		for(int j=0;j<strs.size();j++){
			printf("%s\n",strs[j].c_str());
			t = _wordToURLRecordList -> find(strs[j].c_str(),&list);
					if(t==false){//word doesnt exist
						printf("hi\n");
						URLRecordList * node = new URLRecordList();
						node->_urlRecordIndex = i;
						node->_next = NULL;
						insert = _wordToURLRecordList -> insertItem(strs[j].c_str(),node);
					}else{//word exist
						while(list->_next!=NULL){
							if(list->_urlRecordIndex == i){
								k = 1;
								break;
								printf("%d\n",list->_urlRecordIndex);
							}
							list = list->_next;
						}
						if(k!=0){
							list->_next->_urlRecordIndex = i;
							list->_next->_next = NULL;
							k=0;
						}

					}
				}
	}*/
}

int main(int argc, char ** argv){

	//printf("hi");
	//Sample input: webcrawl -u 100 http://www.purdue.edu http://www.slashdot.org http://www.cnn.com
	int maxUrls = 100;
	int noUrls = 0;
	string option="";
	int k=0;
	const char ** urls;
	option = string(argv[1]);
	if(option.compare("-u")){
		maxUrls = atoi(argv[2]);
		//printf("%d%s\n",maxUrls,u);
		noUrls = argc - 3;
		//Store the initial urls.
		urls = new const char* [noUrls];
		for(int i=3;i<argc;i++){
			urls[k] = (const char*)argv[i];
			printf("%s\n", urls[k]);
			k++;
		}
	}else{
		noUrls = argc - 1;
		urls = new const char * [argc-1];
		for(int i=1;i<argc;i++){
			urls[k] = (const char*)argv[i];
			k++;
		}
	}
	WebCrawler crawler = WebCrawler(maxUrls,noUrls,urls);
	crawler.crawl();
	crawler.writeURLFile("url.txt");
	//crawler.createHash();

}
