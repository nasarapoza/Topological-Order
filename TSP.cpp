// Name: Nasa Iwai
// March 4th

#include "TSP.hpp"
#include <queue>
#include <vector>
#include <tuple>
#include <iostream>
#include <stack>
#include <set>
#include <list>
#include <map>
using namespace std;

// TODO: Write a comparator struct for your MST priority queue
//comparator
class CompV {
    public:
        bool operator()(tuple<int, int, double> & src, tuple<int,int,double> & dest) {
            if(std::get<2>(src) > std::get<2>(dest)) {
                return true;
            }  
            return false;
        }
};

// MST should be rooted at point id 0
std::vector<int> MST(const std::vector<std::pair<int, int>>& points) {
    int size = points.size();
    // initialize all prev fields in the mst to -1 to indicate unvisited
    std::vector<int> mst (size, -1);
    
    // TODO: Perform MST calculations
    std::priority_queue< std::tuple<int ,int, double>  , std::vector<tuple<int, int, double> > ,CompV > pq;

    //initialize priority queue starting at 0
    for(int i = 1; i < size; ++i) {
        pq.push(std::make_tuple(0, i, dist(points[0],points[i])) );
    }

    mst[0] = 1; 
    
    //while loop
    while(!pq.empty() ) {
        std::tuple<int,int,double> t = pq.top();
             
        int id1 = get<0>(t);
        int id2 = get<1>(t);
        double distT = get<2>(t);
             
        pq.pop();
             
        if(mst[id2] == -1 ) {
             mst[id2] = id1;
             for(int i = 0; i < size; i++) {
                if(mst[i] == -1) {
                    pq.push(std::make_tuple(id2, i, dist(points[id2], points[i])) );
                }
             }
        }
             
    }//end of while
             
    mst[0] = -1; 
             
    return mst;
} //end of mst method
             
std::vector<int> TwoOPT(const std::vector<std::pair<int, int>>& points) {
    std::vector<int> visit_order;

    // TODO: Perform 2-OPT calculations

    //adjacency list
    std::vector<std::vector<int> >  adjList(points.size());
  
    std::vector<int> reachable; //already there
    std::stack<int> stack; 

    visit_order = MST(points);

    int size = visit_order.size();

    //creating adjacenecy list
    for(int i = 1; i < visit_order.size(); i++) {
        adjList[visit_order[i]].push_back(i);
    }

        stack.push(0);

    std::map<int, bool> mymap;
    for(int itM = 0; itM < size; itM++) {
        mymap[itM] = false;
    }

    while(!stack.empty()) {

        int curr = stack.top();
        mymap[curr] = true;

        reachable.push_back(curr);
        stack.pop();

        for(auto i = adjList[curr].begin(); i != adjList[curr].end(); i++) {

            if(mymap.at(*i) == false ) { //&& mymap[curr] == true) {
                mymap.at(*i) = true;
                stack.push(*i);
            }
        }//end of for loop
    } 
    return reachable;
    //return visit_order;
}





