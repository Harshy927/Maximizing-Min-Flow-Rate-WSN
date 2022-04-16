//WSN
//range default 30 units
//board 100 X 100


#include<bits/stdc++.h>
using namespace std;

class node
{
	public:
	pair<float,float> pos;
	vector<node*> neighbour;
	node(float x, float y)
	{
		this->pos.first = x;
		this->pos.second = y;
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

int main()
{
	cout<<"Enter the Number of nodes";
	int n;
	cin>>n;
	vector<node*> nod;
	for(int i = 0 ; i < n ; i++)
	{
		float x,y;
		cout<<"enter the x and y coordinates"<<endl;
		cin>>x>>y;
		node *temp = new node(x,y);
		nod.push_back(temp);
	}

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

    for(int i = 0 ; i < nod.size() ; i++)
    {
        node *p = nod[i];
        cout<<" neighbours of "<<p->pos.first<<endl;
        for(auto it : p->neighbour)
        {
            cout<<it->pos.first<<" ";
        }
        cout<<endl;
    }


}