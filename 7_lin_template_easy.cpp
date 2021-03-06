#include <stdio.h>
// we're big guys now, let's use already implemeted list
// you might want check this out: http://www.cplusplus.com/reference/list/list/#functions
#include <list>
#include<iostream>

using namespace std;

// Global variables are bad, but in this case
// passing them in function would soon exceed memory limit.
// Trust me, I tried.
int n;
list<int> *graph;
list<int> *line;

void euler(int u) {
    while (!graph[u].empty())
    {
        int v = *graph[u].begin();

        // iterate over neighbours of v
        // you can use list<int>::iterator it = graph[v].begin()
        // which makes "it" iterator (sth like pointer) pointing on first element of graph[v] list
        // iterator can be moved to next position like this: it++
        // and if you move it after last element of list it will be equal to graph[v].end()
        for (list<int>::iterator it = graph[v].begin();it!=graph[v].end();it++)
        {
        	// if you find u remove it from list
            // you can access element pointed by iterator just like with pointer
            if (*it==u)
            {
                graph[v].erase(it);
                break;
				// use erase method
            }
        }

        // recursively enter v
        graph[u].pop_front();
        euler(v);
    }

    // add city to line
	line->push_front(u);
}

int main() {
    int Z;

    scanf("%d", &Z);

    while (Z--) {

        int n, m, u, v;
        scanf("%d %d", &n, &m);

        graph = new list<int>[n+2];
        line = new list<int>;

        for(int i=0; i<m; i++) {
            scanf("%d %d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int start = 1;
        for (int i = 1; i <= n; i++)
        {
            // find starting city for euler
            // it must be a vertex with odd number of neighbours if it exists
            // or any one if every one has even degree
            if (graph[i].size()%2==1)
            {
                start=i;
                break;
            }
        }

        // start euler from correct city  
		euler(start); 	//jesli testy nie dzialaj�: dodatkowy if jak start==1, �eby nie wchodzi� do startu z powrotem        
		
		
        printf("1\n");
        printf("%lu ", line->size());
        for (list<int>::iterator it = line->begin(); it != line->end(); it++) {
            printf("%d ", *it);
        }
        printf("\n");

        delete [] graph;
        delete line;
    }
}
