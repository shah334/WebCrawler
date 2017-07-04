
all: git-commit gethttp

gethttp: gethttp.cpp openhttp.cpp SimpleHTMLParser.cpp webcrawler.cpp
	g++ -o gethttp -g gethttp.cpp openhttp.cpp SimpleHTMLParser.cpp webcrawler.cpp -lcurl

git-commit:
	git add Makefile *.h *.cpp  .local.git.out >> .local.git.out
	git commit -a -m "Commit web-crawler" >> .local.git.out

clean:
	rm -f *.o gethttp core
