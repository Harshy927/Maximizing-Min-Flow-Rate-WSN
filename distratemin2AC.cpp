//WSN
//range default 30 units
//board 100 X 100
//1st iteration -> 1 AC



#include<bits/stdc++.h>
using namespace std;

class node
{
	public:
    int rate;//pkts/sec
	pair<float,float> pos; // x,y coordinate on 100X100 board
	vector<node*> neighbour; // neighbours within range
	node(float x, float y,int rate)
	{
		this->pos.first = x;
		this->pos.second = y;
        this->rate = rate;
	}

	void addNeighbour(node *a)
	{
		this->neighbour.push_back(a);
	}

};

float euclidean(node *x , node *y)
{
	float x1 = x->pos.first;
	float y1 = x->pos.second;
	float x2 = y->pos.first;
	float y2 = y->pos.second;

	float p1 = (x1-x2)*(x1-x2);
	
	float p2 = (y1-y2)*(y1-y2);

	p1 = p1+p2;
	return sqrt(p1);

	
}

struct compareRate
{
    bool operator()(node* const&p1, node* const&p2)
    {
        return p1->rate < p2->rate;
    }
};

int main()
{
	cout<<"Enter the Number of nodes";
	int n;
	cin>>n;
	vector<node*> nod;
	int maxr = INT_MIN; // max rate -> termination condition
    int minr = INT_MAX; // min rate -> starting condition
    int minIndex = -1;
	for(int i = 0 ; i < n ; i++)
	{
		float x,y;
		cout<<"enter the x and y coordinates"<<endl;
		cin>>x>>y;
        int r;
        cout<<"Enter the rate of transfer(packets/s)"<<endl;
        cin>>r;
		maxr = max(r,maxr);
        if(r < minr)
        {
            minr = r;
            minIndex = i;
        }
		node *temp = new node(x,y,r);
		nod.push_back(temp);
		// pq.push({r,temp});// sorted on rate ascending
	}

    sort(nod.begin(),nod.end());

	//assigning neighbours
	for(int i = 0 ; i < n-1 ; i++)
	{
		for(int j = i+1 ; j < n ; j++)
		{
			float dis = euclidean(nod[i],nod[j]);
			if(dis <= 30)
			{
				nod[i]->addNeighbour(nod[j]);
				nod[j]->addNeighbour(nod[i]);
			}
		}
	}

	// while(!pq.empty() and pq.top().first != maxr)
	// {
	// 	cout<<"Iteration "<<count++<<endl;
	// 	node *temp = pq.top().second;
	// 	pq.pop();
	// 	cout<<"Rate of wsn at position x="<<temp->pos.first<<",y="<<temp->pos.second;
	// 	cout<<" increased from "<<temp->rate<<" to "<<temp->rate+1<<endl;
	// 	temp->rate = temp->rate+1;
	// 	pq.push({temp->rate,temp});
	// }



    //Now we start from node having minr located at minIndex in our nod array
    node* node1 = nod[0];
    node* node2 = nod[1];
    float maxratio = INT_MIN;
    node *next_node = NULL;
    int count = 1;
    float cost = 0;
    while(count < 10)
    {
        cout<<"Iteration "<<count++<<endl;
        // curr_node->rate = curr_node->rate+1;
        node1->rate = node1->rate+1;
        node2->rate = node2->rate+1;
        //for all neighbours of curr_node calculate rate/dist ratio
        float distance;
        for(int i = 0 ; i < node1->neighbour.size() ; i++)
        {
            node *it = node1->neighbour[i];
            distance = euclidean(node1,it);
            float ratio = 1/(it->rate*distance);
            if(ratio > maxratio)
            {
                maxratio = ratio;
                next_node = it;
            }
        }
        // cost += ; cost updation here
        //energy spent = 1kj(recharging) + 1kj per meter()
        cost += 1 + euclidean(node1,next_node);
        node1 = next_node;
        maxratio = INT_MIN;
        for(int i = 0 ; i < node2->neighbour.size() ; i++)
        {
            node *it = node2->neighbour[i];
            distance = euclidean(node2,it);
            float ratio = 1/(it->rate*distance);
            if(ratio > maxratio)
            {
                maxratio = ratio;
                next_node = it;
            }
        }
        cost += 1 + euclidean(node2,next_node);
        node2 = next_node;
        maxratio = INT_MIN;

    }


    cout<<"Total Cost = "<<cost<<endl;
}



// 1. node class ->done
// 2.neighbours based on euclidean distance
// 3.define a source and a sink
//sink ->rate = -1 
// AC -> infinite capacity
//hops to node with smallest rate and updates it by 1(generality)
//termination : when all nodes have same value
//Question : nodes also lose energy while functioning -> how to incorporate that


// Sample Input
// 5 
// 0 0 5
// 10 10 4
// 30 30 7
// 50 50 8
// 80 80 7
